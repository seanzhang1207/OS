#ifndef PORTIO_H
#define PORTIO_H

#define inb(port) ({ unsigned char _v; __asm__ volatile ("inb %%dx,%%al":"=a" (_v):"d" (port)); _v; })
#define outb(value,port) __asm__ ("outb %%al,%%dx"::"a" (value),"d" (port))
#define inw(port) ({ unsigned short int _w; __asm__ volatile ("inw %%dx,%%ax":"=a" (_w):"d" (port)); _w; })
#define outw(value,port) __asm__ ("outw %%ax,%%dx"::"a" (value),"d" (port))
static inline void io_wait(void)
{
    /* TODO: This is probably fragile. */
    asm volatile ( "jmp 1f\n\t"
                   "1:jmp 2f\n\t"
                   "2:" );
}

#endif /* PORTIO_H */