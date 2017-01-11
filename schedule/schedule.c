#include "include/memory.h"

#define sysexit(retaddr, retstack) {__asm__ __volatile__( "sysexit" \
                                            : \
                                            :"c"(retstack), "d"(retaddr) \
                                            :)}


typedef struct Process{
    unsigned int pid;
    unsigned int eip;
    unsigned int esp;
    unsigned int ticks;
    void *stack;
    struct Process *next;
} Process;


Process *test_create_process(unsigned int entry_point, unsigned int ticks) {
    static unsigned int next_pid = 0;
    Process *proc = kmalloc(sizeof(Process));
    proc->pid = next_pid;
    next_pid++;
    proc->eip = entry_point;
    proc.ticks = ticks;
    proc->esp = kmalloc(sizeof(unsigned int)*1024) + sizeof(unsigned int)*1024;
    return proc;
}

extern unsigned int test_process_1, test_process_2, test_process_3;
extern void SYSEXIT_FUNC(unsigned int addr, unsigned int stack);

Process *rrqueue;

void test_schedule_init(){
    rrqueue = test_create_process(test_process_1, 10);
    rrqueue->next = test_create_process(test_process_2, 10);
    rrqueue->next-> = test_create_process(test_process_3, 10);
}
