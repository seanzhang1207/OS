#include "include/multiboot.h"
#include "include/memory.h"
#include "include/kscreen.h"

#include "include/portio.h"

void c_sysexit(unsigned int retaddr, unsigned int retstack){
    sysexit(retaddr, retstack);
}



void parse_mtb_info(struct multiboot_info *mtb_info) {
    kprint(0xf, "Parsing Multiboot Boot Information...\n");
    kprint(0x7, "-> flags: ");
    for (int i=11; i>=0; i--){
        if ((mtb_info->flags >> i) & 1){
            kprint(0x7, "1");
        } else {
            kprint(0x7, "0");
        }
    }
    kprint(0x7, "\n");

    if(mtb_info->flags & 1){
        kprint(0x7, "-> mem_lower: %x\n", mtb_info->mem_lower);
        kprint(0x7, "-> mem_upper: %x\n", mtb_info->mem_upper);
    } else {
        kprint(0x4, "-> mem_* fields not present.\n");
    }

    if((mtb_info->flags >> 1) & 1){
        kprint(0x7, "-> boot_device: %x\n", mtb_info->boot_device >> 24);
        kprint(0x7, "-> boot_partition: %x\n", (mtb_info->boot_device & 0xff0000) >> 16);
        if (((mtb_info->boot_device & 0xff00) >> 8) != 0xff){
            kprint(0x7, "-> second_boot_partition: %x\n", (mtb_info->boot_device & 0xff00) >> 8);
        }
        if (((mtb_info->boot_device & 0xff)) != 0xff){
            kprint(0x7, "-> third_boot_partition: %x\n", (mtb_info->boot_device & 0xff));
        }
    } else {
        kprint(0x4, "-> boot_device field not present.\n");
    }

    if((mtb_info->flags >> 2) & 1){
        kprint(0x7, "-> cmdline: %s\n", mtb_info->cmdline + 0xc0000000);
    } else {
        kprint(0x4, "-> cmdline field not present.\n");
    }

    if((mtb_info->flags >> 3) & 1){
        kprint(0x7, "-> mods_count: %x\n", mtb_info->mods_count);
        kprint(0x7, "-> mods_addr: %x\n", mtb_info->mods_addr);
    } else {
        kprint(0x4, "-> mods_* fields not present.\n");
    }

    if((mtb_info->flags >> 6) & 1){
        kprint(0x7, "-> mmap_length: %x\n", mtb_info->mmap_length);
        mtb_info->mmap_addr += 0xc0000000;
        kprint(0x7, "-> mmap_addr: %x\n", mtb_info->mmap_addr);
        for (unsigned int i=0; i < mtb_info->mmap_length / sizeof(multiboot_memory_map_t); i++){
            kprint(0x7, "     * base: %lx, length: %lx type: %b\n", ((multiboot_memory_map_t *)(mtb_info->mmap_addr))[i].addr, ((multiboot_memory_map_t *)(mtb_info->mmap_addr))[i].len, ((multiboot_memory_map_t *)(mtb_info->mmap_addr))[i].type);
        }
    } else {
        kprint(0xc, "-> mmap_* fields not present.\nThis is a fatal error. HALT.");
        return;
    }

    if((mtb_info->flags >> 7) & 1){
        kprint(0x7, "-> drives_length: %x\n", mtb_info->drives_length);
        kprint(0x7, "-> drives_addr: %x\n", mtb_info->drives_addr);
    } else {
        kprint(0x4, "-> drives_* fields not present.\n");
    }

    if((mtb_info->flags >> 8) & 1){
        kprint(0x7, "-> config_table: %x\n", mtb_info->config_table);
    } else {
        kprint(0x4, "-> config_table fields not present.\n");
    }

    if((mtb_info->flags >> 9) & 1){
        kprint(0x7, "-> boot_loader_name: %s\n", (mtb_info->boot_loader_name + 0xc0000000));
    } else {
        kprint(0x4, "-> boot_loader_name fields not present.\n");
    }

    if((mtb_info->flags >> 10) & 1){
        kprint(0x7, "-> apm_table: %x\n", mtb_info->apm_table);
    } else {
        kprint(0x4, "-> apm_table fields not present.\n");
    }

    if((mtb_info->flags >> 11) & 1){
        kprint(0x7, "-> vbe_control_info: %x\n", mtb_info->vbe_control_info);
        kprint(0x7, "-> vbe_mode_info: %x\n", mtb_info->vbe_mode_info);
        kprint(0x7, "-> vbe_mode: %x\n", mtb_info->vbe_mode);
        kprint(0x7, "-> vbe_interface_seg: %x\n", mtb_info->vbe_interface_seg);
        kprint(0x7, "-> vbe_interface_off: %x\n", mtb_info->vbe_interface_off);
        kprint(0x7, "-> vbe_interface_len: %x\n", mtb_info->vbe_interface_len);
    } else {
        kprint(0x4, "-> vbe_* fields not present.\n");
    }
}

void mem_init(struct multiboot_info *mtb_info) {
    extern unsigned int *buddy[];
    kprint(0xf, "Done.\nInitalizing Physical Memory Manager...\n");
    kprint(0x7, "-> buddy = %x\n-> call buddy_init()...\n", (unsigned int)buddy);
    extern void buddy_init(multiboot_memory_map_t *mmap, int mmap_length);
    buddy_init((multiboot_memory_map_t *)(mtb_info->mmap_addr), mtb_info->mmap_length / sizeof(multiboot_memory_map_t));
    kprint(0xf, "Done. We're now able to do pmalloc and pmfree! Yay!\nTesting kmalloc....\n");
    unsigned int *a = kmalloc(sizeof(unsigned int)* 4096);
    kprint(0x7, "a = %x\n", a);
    for (int i=0; i < 4096; i++) {
        a[i] = i;
    }
    for (int i=0; i < 4096; i++) {
        if (a[i] != i) {
            kprint(0xc, "Oops. There's gotta be something wrong. GO DEBUG. I'M HALTING.\n");
            return;
        }
    }
    kfree(a);
    kprint(0xf, "Done. There seems to be no problem. \nWe're now able to do kmalloc and kfree! Hoooooh-ray!!!\n");
}

typedef unsigned int uint32_t;
typedef unsigned int bool;

static inline void cpuid(int code, uint32_t *a, uint32_t *d) {
  asm volatile("cpuid":"=a"(*a),"=d"(*d):"a"(code):"ecx","ebx");
}

const uint32_t CPUID_FLAG_MSR = 1 << 5;

bool cpu_has_msr() {
   uint32_t a, d; // eax, edx
   cpuid(1, &a, &d);
   return d & CPUID_FLAG_MSR;
}

void rdmsr(uint32_t msr, uint32_t *lo, uint32_t *hi) {
   asm volatile("rdmsr" : "=a"(*lo), "=d"(*hi) : "c"(msr));
}

void wrmsr(uint32_t msr, uint32_t lo, uint32_t hi) {
   asm volatile("wrmsr" : : "a"(lo), "d"(hi), "c"(msr));
}

int check_apic() {
   uint32_t eax, edx;
   cpuid(1, &eax, &edx);
   return edx & (1 << 9);
}

void init(struct multiboot_info *mtb_info, int cpuid_unavailable) {

    PIC_remap(0x20, 0x28);

    parse_mtb_info(mtb_info);

    mem_init(mtb_info);

    //If we ever reach this point, we've all information we need to proceed. No need to check.

    kprint(0xf, "Done.\nSetting up IDT...");

    /* ========== TEST CODE BELOW ========== */
    extern void int_init();
    int_init();

    extern void sysenter_call();
    extern unsigned int syscall_stack;
    if (cpu_has_msr()) {
        wrmsr(0x174, 0x8, 0);
        wrmsr(0x175, syscall_stack + 4096, 0);
        wrmsr(0x176, sysenter_call, 0);
    } else {
        kprint(0x4, "CPU has no MSR.\n");
    }


    /* ========== TEST CODE ABOVE ========== */

}
