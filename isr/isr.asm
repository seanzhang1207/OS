extern key
global keyboard_isr
global sys_call
global pit
extern pit_c

keyboard_isr:
    pushad
    mov eax, 0
    in al, 0x60
    push eax
    call key
    pop eax
    mov dx, 0x20
    mov al, 0x20
    out dx, al
    popad
    iret

extern syscall_print
sys_call:
    pushad
    call syscall_print
    popad
    iret

pit:
    pushad
    call pit_c
    mov al, 0x20
    mov dx, 0xa0
    out dx, al
    mov al, 0x20
    mov dx, 0x20
    out dx, al
    popad
    iret
