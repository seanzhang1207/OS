global _loader                          ; Make entry point visible to linker.
extern init                             ; main is defined elsewhere

bits 32

; setting up the Multiboot header - see GRUB docs for details
MODULEALIGN equ  1<<0                   ; align loaded modules on page boundaries
MEMINFO     equ  1<<1                   ; provide memory map
FLAGS       equ  MODULEALIGN | MEMINFO  ; this is the Multiboot 'flag' field
MAGIC       equ    0x1BADB002           ; 'magic number' lets bootloader find the header
CHECKSUM    equ -(MAGIC + FLAGS)        ; checksum required

; This is the virtual base address of kernel space. It must be used to convert virtual
; addresses into physical addresses until paging is enabled. Note that this is not
; the virtual address where the kernel image itself is loaded -- just the amount that must
; be subtracted from a virtual address to get a physical address.
KERNEL_VIRTUAL_BASE equ 0xC0000000                  ; 3GB

KERNEL_PAGE_NUMBER equ (KERNEL_VIRTUAL_BASE >> 22)  ; Page directory index of kernel's PTE.

section .data
align 4096
BootPageDirectory:
    ; This page directory entry identity-maps the first 4MB of the 32-bit physical address space.
    ; All bits are clear except the following:
    ; bit 7: PS The kernel page is 4MB.
    ; bit 1: RW The kernel page is read/write.
    ; bit 0: P  The kernel page is present.
    ; This entry must be here -- otherwise the kernel will crash immediately after paging is
    ; enabled because it can't fetch the next instruction! It's ok to unmap this page later.
    dd BootPageTable - KERNEL_VIRTUAL_BASE + 7
    times (KERNEL_PAGE_NUMBER - 1) dd 0                 ; page tables before kernel space.
    ; This page table entry defines a 4MB mem range containing the kernel.
    dd BootPageTable - KERNEL_VIRTUAL_BASE + 7
    times (1024 - KERNEL_PAGE_NUMBER - 2) dd 0  ; page tables after the kernel image.
    dd BootPageDirectory - KERNEL_VIRTUAL_BASE + 7  ; map last entry of page dir to itself.

BootPageTable:
    %assign i 0
    %rep    1024
        dd (i * 4096) | 7
    %assign i i+1
    %endrep

section .Multiboot
MultiBootHeader:
    dd MAGIC
    dd FLAGS
    dd CHECKSUM


section .boot
align 4

; reserve initial kernel stack space -- that's 16k.
STACKSIZE equ 0x4000

; setting up entry point for linker

_loader:
    ; NOTE: Until paging is set up, the code must be position-independent and use physical
    ; addresses, not virtual ones!
    cli

    mov ecx, (BootPageDirectory - KERNEL_VIRTUAL_BASE)
    mov cr3, ecx                                        ; Load Page Directory Base Register.

    mov ecx, cr0
    or ecx, 0x80000000                          ; Set PG bit in CR0 to enable paging.
    mov cr0, ecx

    ; Start fetching instructions in kernel space.
    ; Since eip at this point holds the physical address of this command (approximately 0x00100000)
    ; we need to do a long jump to the correct virtual address of StartInHigherHalf which is
    ; approximately 0xC0100000.
    lea ecx, [StartInHigherHalf]
    jmp ecx                                                     ; NOTE: Must be absolute jump!


section .text

StartInHigherHalf:
    ; Unmap the identity-mapped first 4MB of physical address space. It should not be needed
    ; anymore.

    cli

    mov dword [BootPageDirectory], 0
    invlpg [0]

    LGDT  [GDTR]

    jmp   gdt_os_code:_reload_CS ; 0x08 points at the new code selector
_reload_CS:
    ; Reload data segment registers:
    mov ax, gdt_os_data ; 0x10 points at the new data selector
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    mov esp, stack+STACKSIZE            ; set up the stack

    ;Check if CPUID is supported
    pushfd                               ;Save EFLAGS
    pushfd                               ;Store EFLAGS
    xor dword [esp],0x00200000           ;Invert the ID bit in stored EFLAGS
    popfd                                ;Load stored EFLAGS (with ID bit inverted)
    pushfd                               ;Store EFLAGS again (ID bit may or may not be inverted)
    pop eax                              ;eax = modified EFLAGS (ID bit may or may not be inverted)
    xor eax,[esp]                        ;eax = whichever bits were changed
    popfd                                ;Restore original EFLAGS
    and eax,0x00200000                   ;eax = zero if ID bit can't be changed, else non-zero
    push eax

    add ebx, KERNEL_VIRTUAL_BASE        ; add kernel base to multiboot info structure
    push ebx

    ; now that we have multiboot info pushed onto stack,
    ; we need to do some stuff before calling the kernel.

    ; Reprogram the 8259 PIC chip

; ================[TEST CODE BELOW]================
    mov eax, TEST_TSS
    mov ebx, _1
    mov [ebx], ax
    mov eax, TEST_TSS
    mov ebx, _2
    and eax, 0xff0000
    shr eax, 16
    mov [ebx], al
    mov eax, TEST_TSS
    mov ebx, _3
    and eax, 0xff000000
    shr eax, 24
    mov [ebx], al
; ================[TEST CODE ABOVE]================

    call init
; ================[TEST CODE BELOW]================
    ;call dummy_isr
    lidt [IDTR]
    mov eax, 0x2b
    ltr ax

    sti

    mov ecx, user_stack
    mov edx, test_user
    mov ax, 0x23
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    extern test_schedule_init
    call test_schedule_init
    ;sysexit

; ================[TEST CODE ABOVE]================

    jmp $                          ; halt

global sysenter_call
test_user:
    mov ecx, esp
    mov edx, _user_ret
    mov ax, 0x23
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    ;jmp $
    sysenter
_user_ret:
    jmp test_user

sysenter_call:
    push ebx
    mov bx, 0x10
    mov ds, bx
    mov es, bx
    mov fs, bx
    mov gs, bx
    ;sti
    mov bx, 0x23
    mov ds, bx
    mov es, bx
    mov fs, bx
    mov gs, bx
    pop ebx
    sysexit

sysexit_halt:
    jmp $


; Intel syntax

locked:                      ; The lock variable. 1 = locked, 0 = unlocked.
     dd      0

spin_lock:
     mov     eax, 1          ; Set the EAX register to 1.

     xchg    eax, [locked]   ; Atomically swap the EAX register with
                             ;  the lock variable.
                             ; This will always store 1 to the lock, leaving
                             ;  the previous value in the EAX register.

     test    eax, eax        ; Test EAX with itself. Among other things, this will
                             ;  set the processor's Zero Flag if EAX is 0.
                             ; If EAX is 0, then the lock was unlocked and
                             ;  we just locked it.
                             ; Otherwise, EAX is 1 and we didn't acquire the lock.

     jnz     spin_lock       ; Jump back to the MOV instruction if the Zero Flag is
                             ;  not set; the lock was previously locked, and so
                             ; we need to spin until it becomes unlocked.

     ret                     ; The lock has been acquired, return to the calling
                             ;  function.

spin_unlock:
     mov     eax, 0          ; Set the EAX register to 0.

     xchg    eax, [locked]   ; Atomically swap the EAX register with
                             ;  the lock variable.

     ret                     ; The lock has been released.





align 4

GDTR:
    dw GDT_END - GDT - 1
    dd GDT

IDTR:
    dw IDT_END - IDT - 1
    dd IDT

align 8
GDT:

    dd 0
    dd 0
gdt_os_code equ   $-GDT
oscode:
    dw 0xffff
    dw 0
    db 0
    db 10011010b
    db 11011111b
    db 0
gdt_os_data equ   $-GDT
osdata:
    dw 0xffff
    dw 0
    db 0
    db 10010010b
    db 11011111b
    db 0
gdt_user_code equ   $-GDT
usercode:
    dw 0xffff
    dw 0
    db 0
    db 11111010b
    db 11011111b
    db 0
gdt_user_data equ   $-GDT
userdata:
    dw 0xffff
    dw 0
    db 0
    db 11110010b
    db 11011111b
    db 0

; ================[TEST CODE BELOW]================
gdt_tss equ $-GDT
tss:
    dw TEST_TSS_END - TEST_TSS
_1:
    dw 0
_2:
    db 0
    db 10001001b
    db 01010000b
_3:
    db 0
; ================[TEST CODE ABOVE]================


GDT_END:
global IDT
align 8
IDT:
    times 512 dd 0  ; 256 entries, each 8 bytes long.
IDT_END:

; ================[TEST CODE BELOW]================
TEST_TSS:
    dd 0  ; The previous TSS - if we used hardware task switching this would form a linked list.
esp0:
    dd tssstack + 4096      ; The stack pointer to load when we change to kernel mode.
    dd 0x10        ; The stack segment to load when we change to kernel mode.
    dd 0       ; everything below here is unusued now..
    dd 0
    dd 0
    dd 0
    dd 0
    dd 0
    dd 0
    dd 0
    dd 0
    dd 0
    dd 0
    dd 0
    dd 0
    dd 0
    dd 0
    dd 0
    dd 0
    dd 0
    dd 0
    dd 0
    dd 0
    dd 0
    dd 0
TEST_TSS_END:
; ================[TEST CODE ABOVE]================

section .bss
align 32
stack:
    resb STACKSIZE      ; reserve 16k stack on a uint64_t boundary

; ================[TEST CODE BELOW]================
tssstack:
    resb STACKSIZE      ; reserve 16k stack on a uint64_t boundary for tss

global syscall_stack

syscall_stack:
    resb STACKSIZE      ; reserve 16k stack on a uint64_t boundary for tss

user_stack:
    resb STACKSIZE
; ================[TEST CODE ABOVE]================
