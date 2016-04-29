#include "../include/portio.h"
#include "../include/stdarg.h"

void put_cursor(int x, int y) {
    unsigned short position = (y*80) + x; // cursor LOW port to vga INDEX register
	outb(0x0f, 0x3d4);
    outb((unsigned char)(position & 0xff), 0x3d5); // cursor HIGH port to vga INDEX register
    outb(0x0e, 0x3d4);
    outb((unsigned char )((position >> 8) & 0xff), 0x3d5);
    return;
}

unsigned int cur_x = 0, cur_y = 0;

char getkey() {
    char c = 0;
    do {
        if (inb(0x60) != c) {
            c = inb(0x60);
            if (c>0) return c;
        }
    } while (1);
}

#define MAX_X     79
#define MAX_Y     24

#define cursor(x, y) (0xc00b8000 + 2 * (x + 80 * y))

void scroll(void) {
    put_cursor(MAX_X, MAX_Y);
    *((char *)(cursor(MAX_X-5, MAX_Y))) = 'E';
    *((char *)(cursor(MAX_X-4, MAX_Y))) = 'N';
    *((char *)(cursor(MAX_X-3, MAX_Y))) = 'T';
    *((char *)(cursor(MAX_X-2, MAX_Y))) = 'E';
    *((char *)(cursor(MAX_X-1, MAX_Y))) = 'R';
    *((char *)(cursor(MAX_X, MAX_Y))) = 31;
    getkey();
    for (int x = 0; x <= MAX_X; x++) {
        for (int y = 0; y <= MAX_Y; y++) {
            *((char *)(cursor(x, y))) = ' ';
        }
    }
    cur_x = 0;
    cur_y = 0;
}

void nextline() {
    extern unsigned int cur_x, cur_y;
    put_cursor(cur_x, cur_y);
    if (cur_y == MAX_Y) {
        scroll();
    } else {
        cur_x = 0;
        cur_y = cur_y + 1;
    }
    put_cursor(cur_x, cur_y);
    return;
}

void pchar(char ch, char color) {
    extern unsigned int cur_x, cur_y;
    if (ch == '\n') {
        nextline();
        return;
    }
    if (cur_x == MAX_X + 1) {
        cur_y = cur_y + 1;
        cur_x = 0;
    }
    *((char *)(cursor(cur_x, cur_y))) = ch;
    *((char *)(cursor(cur_x, cur_y) + 1)) = color;
    if (cur_x == MAX_X && cur_y == MAX_Y) {
        scroll();
    } else {
        cur_x = cur_x + 1;
    }
    return;
}

void printhex(char hex, char color) { //2012-2-1
    char high = (hex & 0xf0) >> 4;
    char low = hex & 0xf;
    if (high>9) {
        high = high + 0x37;
    } else {
        high = high + 0x30;
    }
    if (low>9) {
        low = low + 0x37;
    } else {
        low = low + 0x30;
    }
    pchar(high, color);
    pchar(low, color);
    return;
}

void printmem(char *start, int count, char color) {    //2012-2-1
    int i;
    for(i = 0;i<count;i++) {
        if ((i%8 == 0) & (i != 0)) pchar(' ', color);
        if ((i%32 == 0) & (i != 0)) pchar('\n', color);
        printhex(*(start + i), color);
    }
    pchar(' ', color);
    return;
}

void print(char color, char *ptr) {         //this is called when there's syscall of printing screen or by kprint(). Since there can't be '%'s in a write() system call, this print() function is way easier and faster than kprint()
    extern unsigned int cur_x, cur_y;
    while (*ptr != '\0') {
        pchar(*ptr, color);
        ptr = ptr + 1;
    }
    put_cursor(cur_x, cur_y);
    return;
}

void kprint(char color, const char *format, ...) {     //This is a printf()-like function used by kernel for debugging and when it needs to print something that needs to be seen by user whatever virtual screen the user is looking at. This function supports %c, %s, %x and %%. I think %d is not needed.
    extern unsigned int cur_x, cur_y;
    va_list arg;
    int buf;
    va_start(arg, format);
    while (*format != '\0') {
        if (*format != '%') {
            pchar(*format, color);
            format = format + 1;
        } else {
            if (*((char *)(format + 1)) == 'c') {
                pchar(va_arg(arg, char), color);
            } else if (*((char *)(format + 1)) == 's') {
                print(color, va_arg(arg, char *));
            } else if (*((char *)(format + 1)) == '%') {
                pchar('%', color);
            } else if (*((char *)(format + 1)) == '"') {
                pchar('"', color);
            } else if (*((char *)(format + 1)) == 'x') {
                buf = va_arg(arg, unsigned int);
                printhex((char)((buf & 0xff000000) >> 24), color);
                printhex((char)((buf & 0xff0000) >> 16), color);
                printhex((char)((buf & 0xff00) >> 8), color);
                printhex((char)(buf & 0xff), color);
            } else if (*((char *)(format + 1)) == 'l' && *((char *)(format + 2)) == 'x') {
                buf = va_arg(arg, unsigned long long int);
                printhex((char)((buf & 0xff00000000000000) >> 56), color);
                printhex((char)((buf & 0xff000000000000) >> 48), color);
                printhex((char)((buf & 0xff0000000000) >> 40), color);
                printhex((char)((buf & 0xff00000000) >> 32), color);
                printhex((char)((buf & 0xff000000) >> 24), color);
                printhex((char)((buf & 0xff0000) >> 16), color);
                printhex((char)((buf & 0xff00) >> 8), color);
                printhex((char)(buf & 0xff), color);
                format += 1;
            } else if (*((char *)(format + 1)) == 'b') {
                printhex(va_arg(arg, char), color);
            } else if (*((char *)(format + 1)) == 't') {
                buf = (int)va_arg(arg, char);
                if (buf == 1) print(color, "Sun");
                if (buf == 2) print(color, "Mon");
                if (buf == 3) print(color, "Tue");
                if (buf == 4) print(color, "Wed");
                if (buf == 5) print(color, "Thu");
                if (buf == 6) print(color, "Fri");
                if (buf == 7) print(color, "Sat");
            }
            format = format + 2;
        }
    }
    put_cursor(cur_x, cur_y);
    return;
}
