global divide_by_zero
global debug
global nmi
global breakpoint
global into_detected_overflow
global out_of_bounds
global invalid_opcode
global no_coprocessor
global double_fault
global coprocessor_segment_overrun
global bad_tss
global segment_not_present
global stack_fault
global general_protection
global page_fault
global unknown_interrupt
global coprocessor_fault
global alignment_check
global machine_check
global default_isr

extern general_handler

NO_ERR_CODE equ 0xffffffff

divide_by_zero:
	push NO_ERR_CODE
	push 0
	call general_handler
	add esp, 8
	iret
debug:
	push NO_ERR_CODE
	push 1
	call general_handler
	add esp, 8
	iret
nmi:
	push NO_ERR_CODE
	push 2
	call general_handler
	add esp, 8
	iret
breakpoint:
	push NO_ERR_CODE
	push 3
	call general_handler
	add esp, 8
	iret
into_detected_overflow:
	push NO_ERR_CODE
	push 4
	call general_handler
	add esp, 8
	iret
out_of_bounds:
	push NO_ERR_CODE
	push 5
	call general_handler
	add esp, 8
	iret
invalid_opcode:
	push NO_ERR_CODE
	push 6
	call general_handler
	add esp, 8
	iret
no_coprocessor:
	push NO_ERR_CODE
	push 7
	call general_handler
	add esp, 8
	iret
double_fault:
	push 8
	call general_handler
	hlt
coprocessor_segment_overrun:
	push NO_ERR_CODE
	push 9
	call general_handler
	add esp, 8
	iret
bad_tss:
	push 10
	call general_handler
	add esp, 8
	iret
segment_not_present:
	push 11
	call general_handler
	add esp, 8
	iret
stack_fault:
	push 12
	call general_handler
	add esp, 8
	iret
general_protection:
	push 13
	call general_handler
	add esp, 8
	iret
page_fault:
	mov eax, cr2
	push eax
	push 14
	call general_handler
	pop eax
	add esp, 8
	iret
unknown_interrupt:
	push NO_ERR_CODE
	push 15
	call general_handler
	add esp, 8
	iret
coprocessor_fault:
	push NO_ERR_CODE
	push 16
	call general_handler
	add esp, 8
	iret
alignment_check:
	push 17
	call general_handler
	add esp, 8
	iret
machine_check:
	push NO_ERR_CODE
	push 18
	call general_handler
	add esp, 8
	hlt
default_isr:
	push NO_ERR_CODE
	push 255
	call general_handler
	add esp, 8
	hlt