#include "../include/memory.h"
#include "../include/kscreen.h"

#define HEAP_BASE 0xd0000000

#define bsr(val) ({ unsigned char _v; __asm__ volatile ("bsr %%edx,%%edx":"=d" (_v):"d" (val)); _v; })

unsigned int heap_free_start = HEAP_BASE;
unsigned int heap_free_end = HEAP_BASE;
unsigned int heap_free_pgnum = 0;

unsigned int _heap_add_page(){
	unsigned int paddr = pmalloc(0);
	if (paddr) {
		map_page(paddr, heap_free_end, 3); 
		heap_free_end += 4096;
		heap_free_pgnum += 1;
		//kprint(0x7, "heap_free_start = %x\nheap_free_end = %x\nheap_free_pgnum = %b\n", heap_free_start, heap_free_end, heap_free_pgnum);
		return 1;
	} else {
		kprint(0xc, "ERROR: pmalloc() failed.\n");
		return 0;
	}
}

void *_heap_alloc(unsigned int pgnum){
	unsigned int retaddr = heap_free_start;
	if (heap_free_pgnum < pgnum) {
		while (heap_free_pgnum < pgnum) {
			if (! _heap_add_page()) {
				return 0;
			}
		}
	}
	heap_free_pgnum -= pgnum;
	heap_free_start += pgnum * 4096;
	return retaddr;
}


/** This function is supposed to lock the memory data structures. It
 * could be as simple as disabling interrupts or acquiring a spinlock.
 * It's up to you to decide. 
 *
 * \return 0 if the lock was acquired successfully. Anything else is
 * failure.
 */
int liballoc_lock(){
	//__asm__ volatile ("cli"::);
	//currently interrupts are always disabled.
	return 0;
}

/** This function unlocks what was previously locked by the liballoc_lock
 * function.  If it disabled interrupts, it enables interrupts. If it
 * had acquiried a spinlock, it releases the spinlock. etc.
 *
 * \return 0 if the lock was successfully released.
 */
int liballoc_unlock(){
	//__asm__ volatile ("sti"::);
	//currently we simply do not allow any interrupts. the idt hasn't been set up yet.
	return 0;
}

/** This is the hook into the local system which allocates pages. It
 * accepts an integer parameter which is the number of pages
 * required.  The page size was set up in the liballoc_init function.
 *
 * \return NULL if the pages were not allocated.
 * \return A pointer to the allocated memory.
 */
void *liballoc_alloc(unsigned int pgnum){
	return _heap_alloc(pgnum);
}

/** This frees previously allocated memory. The void* parameter passed
 * to the function is the exact same value returned from a previous
 * liballoc_alloc call.
 *
 * The integer value is the number of pages to free.
 *
 * \return 0 if the memory was successfully freed.
 */
int liballoc_free(void* vaddr, unsigned int pgnum){
	return 0;
}
