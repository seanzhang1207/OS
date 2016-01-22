#include "../include/multiboot.h"
#include "../include/kscreen.h"

#include "liballoc.h"

#define MAX_MEM	0x100000000
#define PAGE_SIZE 4096

#define BUDDY0_SIZE	MAX_MEM / sizeof(unsigned int) / 8 / PAGE_SIZE	// 4K
#define BUDDY1_SIZE	BUDDY0_SIZE / 2									// 8K
#define BUDDY2_SIZE	BUDDY1_SIZE / 2									// 16K
#define BUDDY3_SIZE	BUDDY2_SIZE / 2									// 32K
#define BUDDY4_SIZE	BUDDY3_SIZE / 2									// 64K
#define BUDDY5_SIZE	BUDDY4_SIZE / 2									// 128K
#define BUDDY6_SIZE	BUDDY5_SIZE / 2									// 256K
#define BUDDY7_SIZE	BUDDY6_SIZE / 2									// 512K
#define BUDDY8_SIZE	BUDDY7_SIZE / 2									// 1M
#define BUDDY9_SIZE	BUDDY8_SIZE / 2									// 2M
#define BUDDY10_SIZE BUDDY9_SIZE / 2								// 4M

unsigned int buddy0[BUDDY0_SIZE];
unsigned int buddy1[BUDDY1_SIZE];
unsigned int buddy2[BUDDY2_SIZE];
unsigned int buddy3[BUDDY3_SIZE];
unsigned int buddy4[BUDDY4_SIZE];
unsigned int buddy5[BUDDY5_SIZE];
unsigned int buddy6[BUDDY6_SIZE];
unsigned int buddy7[BUDDY7_SIZE];
unsigned int buddy8[BUDDY8_SIZE];
unsigned int buddy9[BUDDY9_SIZE];
unsigned int buddy10[BUDDY10_SIZE];

unsigned int *buddy[11] = {buddy0, buddy1, buddy2, buddy3, buddy4, buddy5, buddy6, buddy7, buddy8, buddy9, buddy10};
unsigned int last[11] = {	0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, \
							0xffffffff, 0xffffffff, 0};
unsigned int buddysize[11] = {	BUDDY0_SIZE, BUDDY1_SIZE, BUDDY2_SIZE, BUDDY3_SIZE, BUDDY4_SIZE, BUDDY5_SIZE, \
								BUDDY6_SIZE, BUDDY7_SIZE, BUDDY8_SIZE, BUDDY9_SIZE, BUDDY10_SIZE };

#define calc_addr(order, index, bit)	((1 << (order + 12)) * ((index << 5) + bit))
#define set_addr(addr, order)			buddy[order][addr >> (order + 12 + 5)] |= (1 << (((addr >> (order + 12)))&0x1f))
#define clear_addr(addr, order)			buddy[order][addr >> (order + 12 + 5)] &= ~(1 << (((addr >> (order + 12)))&0x1f))
#define bsr(val) ({ unsigned char _v; __asm__ volatile ("bsr %%edx,%%edx":"=d" (_v):"d" (val)); _v; })
#define bsf(val) ({ unsigned char _v; __asm__ volatile ("bsf %%edx,%%edx":"=d" (_v):"d" (val)); _v; })

void pmfree(unsigned int paddr, unsigned int order) {
	unsigned int index = paddr >> (order + 17);
	unsigned int bit = (paddr >> (order + 12)) & 0x1f;
	if (order == 10) {
		buddy[order][index] |= 1 << bit;
		last[order] = index;
	} else if (bit & 1 && buddy[order][index] & (1 << (bit - 1))) {
		buddy[order][index] &= ~(1 << (bit - 1));
		pmfree(paddr, order + 1);
	} else if (!(bit & 1) && buddy[order][index] & (1 << (bit + 1))) {
		buddy[order][index] &= ~(1 << (bit + 1));
		pmfree(paddr, order + 1);
	} else {
		buddy[order][index] |= 1 << bit;
		last[order] = index;
	}
}

unsigned int _pmsplit(unsigned int order){
	unsigned int addr;
	if (last[order] != 0xffffffff) {
		for (unsigned int i=last[order]; i < buddysize[order]; i++) {
			if (buddy[order][i]) {
				addr = calc_addr(order, i, bsf(buddy[order][i]));
				buddy[order][i] &= ~(1 << bsf(buddy[order][i]));
				last[order] = i;
				pmfree(addr + (4096 << (order - 1)), order - 1);
				return addr;
			}
		}
		last[order] = 0xffffffff;
		if (order == 10) {
			return 0;
		} else {
			addr = _pmsplit(order + 1);
			if (addr) {
				pmfree(addr + (4096 << (order - 1)), order - 1);
			}
			return addr;
		}
	} else {
		addr = _pmsplit(order + 1);
		if (addr) {
			pmfree(addr + (4096 << (order - 1)), order - 1);
		}
		return addr;
	}
	return 0;
}

unsigned int pmalloc(unsigned int order) {
	if (last[order] != 0xffffffff) {
		for (unsigned int i=last[order]; i < buddysize[order]; i++) {
			if (buddy[order][i]) {
				unsigned int addr = calc_addr(order, i, bsf(buddy[order][i]));
				buddy[order][i] &= ~(1 << bsf(buddy[order][i]));
				last[order] = i;
				return addr;
			}
		}
		last[order] = 0xffffffff;
		if (order == 10) {
			return 0;
		} else {
			return _pmsplit(order + 1);
		}
	} else {
		return _pmsplit(order + 1);
	}
	return 0;
}

void * get_physaddr(void * virtualaddr) {
    unsigned long pdindex = (unsigned long)virtualaddr >> 22;
    unsigned long ptindex = (unsigned long)virtualaddr >> 12 & 0x03FF;
 
    unsigned long * pd = (unsigned long *)0xFFFFF000;
    // Here you need to check whether the PD entry is present.
 
    unsigned long * pt = ((unsigned long *)0xFFC00000) + (0x400 * pdindex);
    // Here you need to check whether the PT entry is present.
 
    return (void *)((pt[ptindex] & ~0xFFF) + ((unsigned long)virtualaddr & 0xFFF));
}

void map_page(void * physaddr, void * virtualaddr, unsigned int flags) {
    // Make sure that both addresses are page-aligned.
    kprint(0x7, "mapping paddr %x to vaddr %x with flags %b.\n", physaddr, virtualaddr, flags);
 
    unsigned long pdindex = (unsigned long)virtualaddr >> 22;
    unsigned long ptindex = (unsigned long)virtualaddr >> 12 & 0x03FF;
 
    unsigned long * pd = (unsigned long *)0xFFFFF000;
    // Here you need to check whether the PD entry is present.
    // When it is not present, you need to create a new empty PT and
    // adjust the PDE accordingly.
    if (!(pd[pdindex] & 1)) {
    	kprint(0x4, "page table not present. creating a new one.\n");
    	unsigned int paddr = pmalloc(0);
    	if (paddr) {
    		pd[pdindex] = paddr | 3;
    	} else {
    		kprint(0xc, "ERROR: pmalloc() failed.\n", paddr);
    		return;
    	}
    }
 
    unsigned long * pt = ((unsigned long *)0xFFC00000) + (0x400 * pdindex);
    // Here you need to check whether the PT entry is present.
    // When it is, then there is already a mapping present. What do you do now?
 
    pt[ptindex] = ((unsigned long)physaddr) | (flags & 0xFFF) | 0x01; // Present
 
    // Now you need to flush the entry in the TLB
    // or you might not notice the change.
}

void buddy_init(multiboot_memory_map_t *mmap, int mmap_length) {
	for (unsigned int i=0; i < BUDDY0_SIZE; i++) {
		buddy0[i] = 0;
		buddy1[i>>1] = 0;
		buddy2[i>>2] = 0;
		buddy3[i>>3] = 0;
		buddy4[i>>4] = 0;
		buddy5[i>>5] = 0;
		buddy6[i>>6] = 0;
		buddy7[i>>7] = 0;
		buddy8[i>>8] = 0;
		buddy9[i>>9] = 0;
		buddy10[i>>10] = 0;
	}
	for (int i=0; i < mmap_length; i++) {
		if (mmap[i].type == 1) {
			for (unsigned int j=0; j < mmap[i].len; j += 0x1000) {
				//kprint(0x7, "%x ", j);
				if (mmap[i].addr + j >= 0x400000) pmfree(mmap[i].addr + j, 0);
			}
		}
	}
	for (int i=0; i < 11; i++) {
		for (unsigned int j=0; j < buddysize[i]; j++){
			if (buddy[i][j]){
				last[i] = j;
				break;
			}
		}
	}
}


