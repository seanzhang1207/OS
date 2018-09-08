#ifndef MEMORY_H
#define MEMORY_H

#include "multiboot.h"

extern void buddy_init(multiboot_memory_map_t *mmap, int mmap_length);

extern void map_page(void * physaddr, void * virtualaddr, unsigned int flags);

extern void *get_physaddr(void * virtualaddr);

extern unsigned int pmalloc(unsigned int order);

extern void pmfree(unsigned int paddr, unsigned int order);

extern void *kmalloc(unsigned int);

extern void *krealloc(void *, unsigned int);

extern void *kcalloc(unsigned int, unsigned int);

extern void kfree(void *);

#endif /* MEMORY_H */