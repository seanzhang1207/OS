#include "../include/portio.h"

#define PIC1        0x20        /* IO base address for master PIC */
#define PIC2        0xA0        /* IO base address for slave PIC */
#define PIC1_COMMAND    PIC1
#define PIC1_DATA   (PIC1+1)
#define PIC2_COMMAND    PIC2
#define PIC2_DATA   (PIC2+1)

#define PIC_EOI     0x20        /* End-of-interrupt command code */

#define ICW1_ICW4   0x01        /* ICW4 (not) needed */
#define ICW1_SINGLE 0x02        /* Single (cascade) mode */
#define ICW1_INTERVAL4  0x04        /* Call address interval 4 (8) */
#define ICW1_LEVEL  0x08        /* Level triggered (edge) mode */
#define ICW1_INIT   0x10        /* Initialization - required! */
 
#define ICW4_8086   0x01        /* 8086/88 (MCS-80/85) mode */
#define ICW4_AUTO   0x02        /* Auto (normal) EOI */
#define ICW4_BUF_SLAVE  0x08    /* Buffered mode/slave */
#define ICW4_BUF_MASTER 0x0C    /* Buffered mode/master */
#define ICW4_SFNM   0x10        /* Special fully nested (not) */

void PIC_sendEOI(unsigned char irq)
{
    if(irq >= 8)
        outb(PIC2_COMMAND,PIC_EOI);
    outb(PIC1_COMMAND,PIC_EOI);
}

void PIC_remap(int offset1, int offset2)
{
    kprint(0xf, "Remapping PIC...\n");
    unsigned char a1, a2;
 
    a1 = inb(PIC1_DATA);                        // save masks
    a2 = inb(PIC2_DATA);
 
    outb(ICW1_INIT+ICW1_ICW4, PIC1_COMMAND);  // starts the initialization sequence (in cascade mode)
    io_wait();
    outb(ICW1_INIT+ICW1_ICW4, PIC2_COMMAND);
    io_wait();
    outb(offset1, PIC1_DATA);                 // ICW2: Master PIC vector offset
    io_wait();
    outb(offset2, PIC2_DATA);                 // ICW2: Slave PIC vector offset
    io_wait();
    outb(4, PIC1_DATA);                       // ICW3: tell Master PIC that there is a slave PIC at IRQ2 (0000 0100)
    io_wait();
    outb(2, PIC2_DATA);                       // ICW3: tell Slave PIC its cascade identity (0000 0010)
    io_wait();
 
    outb(ICW4_8086, PIC1_DATA);
    io_wait();
    outb(ICW4_8086, PIC2_DATA);
    io_wait();
 
    outb(a1, PIC1_DATA);   // restore saved masks.
    outb(a2, PIC2_DATA);
}

void IRQ_set_mask(unsigned char IRQline) {
    unsigned short int port;
    unsigned char value;
 
    if(IRQline < 8) {
        port = PIC1_DATA;
    } else {
        port = PIC2_DATA;
        IRQline -= 8;
    }
    value = inb(port) | (1 << IRQline);
    outb(port, value);        
}
 
void IRQ_clear_mask(unsigned char IRQline) {
    unsigned short int port;
    unsigned char value;
 
    if(IRQline < 8) {
        port = PIC1_DATA;
    } else {
        port = PIC2_DATA;
        IRQline -= 8;
    }
    value = inb(port) & ~(1 << IRQline);
    outb(port, value);        
}

extern void set_idt_entry(unsigned int entry, unsigned int addr, unsigned int sel, unsigned int attr);
extern void divide_by_zero();
extern void debug();
extern void nmi();
extern void breakpoint();
extern void into_detected_overflow();
extern void out_of_bounds();
extern void invalid_opcode();
extern void no_coprocessor();
extern void double_fault();
extern void coprocessor_segment_overrun();
extern void bad_tss();
extern void segment_not_present();
extern void stack_fault();
extern void general_protection();
extern void page_fault();
extern void unknown_interrupt();
extern void coprocessor_fault();
extern void alignment_check();
extern void machine_check();
extern void default_isr();
extern void sys_call();
extern void keyboard_isr();
extern void pit();

void int_init(){
	scancode_init();
    for (int i=0; i<255; i++) set_idt_entry(i, 0, 0, 0);
    set_idt_entry(0x0, divide_by_zero, 0x8, 0x8e00);
    set_idt_entry(0x1, debug, 0x8, 0x8e00);
    set_idt_entry(0x2, nmi, 0x8, 0x8e00);
    set_idt_entry(0x3, breakpoint, 0x8, 0x8e00);
    set_idt_entry(0x4, into_detected_overflow, 0x8, 0x8e00);
    set_idt_entry(0x5, out_of_bounds, 0x8, 0x8e00);
    set_idt_entry(0x6, invalid_opcode, 0x8, 0x8e00);
    set_idt_entry(0x7, no_coprocessor, 0x8, 0x8e00);
    set_idt_entry(0x8, double_fault, 0x8, 0x8e00);
    set_idt_entry(0x9, coprocessor_segment_overrun, 0x8, 0x8e00);
    set_idt_entry(0xa, bad_tss, 0x8, 0x8e00);
    set_idt_entry(0xb, segment_not_present, 0x8, 0x8e00);
    set_idt_entry(0xc, stack_fault, 0x8, 0x8e00);
    set_idt_entry(0xd, general_protection, 0x8, 0x8e00);
    set_idt_entry(0xe, page_fault, 0x8, 0x8e00);
    set_idt_entry(0xf, unknown_interrupt, 0x8, 0x8e00);
    set_idt_entry(0x10, coprocessor_fault, 0x8, 0x8e00);
    set_idt_entry(0x11, &alignment_check, 0x8, 0x8e00);
    set_idt_entry(0x12, machine_check, 0x8, 0x8e00);
    set_idt_entry(0x20, pit, 0x8, 0x8e00);
    set_idt_entry(0x21, keyboard_isr, 0x8, 0x8e00);
    set_idt_entry(0x99, sys_call, 0x8, 0xee00);
}