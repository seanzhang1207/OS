bits 32

global test_process_1
global test_process_2
global test_process_3

global SYSEXIT_FUNC
global SYSENTER_FUNC

SYSEXIT_FUNC:
    mov ax, 0x23
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    pop ecx ; remove esp
    pop ecx ; stack
    pop edx ; addr
    sysexit

SYSENTER_FUNC:
    pop edx ; ret addr
    mov ecx, esp
    sysenter


test_process_1:
    mov eax, 1
    call SYSENTER_FUNC
    jmp test_process_1

test_process_2:
    mov eax, 2
    call SYSENTER_FUNC
    jmp test_process_2

test_process_3:
    mov eax, 3
    call SYSENTER_FUNC
    jmp test_process_3
