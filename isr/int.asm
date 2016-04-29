global set_idt_entry
extern IDT

set_idt_entry:
    push ebp
    mov ebp, esp
    push eax
    push ebx
    push ecx
    push edx
    mov eax, [ebp+8]
    shl eax, 3
    add eax, IDT
    mov ebx, [ebp+12]
    mov ecx, [ebp+16]
    mov edx, [ebp+20]
    mov [eax], bx
    mov [eax+2], cx
    mov [eax+4], dx
    shr ebx, 16
    mov [eax+6], bx
    pop edx
    pop ecx
    pop ebx
    pop eax
    pop ebp
    ret