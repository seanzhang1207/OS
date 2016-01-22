#ifndef DEBUG_H
#define DEBUG_H

void put_cursor(int x, int y);

char getkey();

#define cursor(x,y) (0xc00b8000 + 2 * (x + 80 * y))

void scroll(void);

void nextline();

void pchar(char ch, char color);

void printhex(char hex,char color);

void printmem(char *start,int count,char color);

void print(char color,char *ptr);

void kprint(char color,const char *format,...);

#endif /* DEBUG_H */

