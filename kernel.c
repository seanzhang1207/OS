#include "include/multiboot.h"
#include "include/memory.h"
#include "include/kscreen.h"

char *scancode[256];

void scancode_init(){
    scancode[0x01] = "";
    scancode[0x02] = "1";
    scancode[0x03] = "2";
    scancode[0x04] = "3";
    scancode[0x05] = "4";
    scancode[0x06] = "5";
    scancode[0x07] = "6";
    scancode[0x08] = "7";
    scancode[0x09] = "8";
    scancode[0x0A] = "9";
    scancode[0x0B] = "0";
    scancode[0x0C] = "-";
    scancode[0x0D] = "=";
    scancode[0x0E] = "";
    scancode[0x0F] = "";
    scancode[0x10] = "Q";
    scancode[0x11] = "W";
    scancode[0x12] = "E";
    scancode[0x13] = "R";
    scancode[0x14] = "T";
    scancode[0x15] = "Y";
    scancode[0x16] = "U";
    scancode[0x17] = "I";
    scancode[0x18] = "O";
    scancode[0x19] = "P";
    scancode[0x1A] = "[";
    scancode[0x1B] = "]";
    scancode[0x1C] = "\n";
    scancode[0x1D] = "";
    scancode[0x1E] = "A";
    scancode[0x1F] = "S";
    scancode[0x20] = "D";
    scancode[0x21] = "F";
    scancode[0x22] = "G";
    scancode[0x23] = "H";
    scancode[0x24] = "J";
    scancode[0x25] = "K";
    scancode[0x26] = "L";
    scancode[0x27] = ";";
    scancode[0x28] = "'";
    scancode[0x29] = "`";
    scancode[0x2A] = "";
    scancode[0x2B] = "\\";
    scancode[0x2C] = "Z";
    scancode[0x2D] = "X";
    scancode[0x2E] = "C";
    scancode[0x2F] = "V";
    scancode[0x30] = "B";
    scancode[0x31] = "N";
    scancode[0x32] = "M";
    scancode[0x33] = ",";
    scancode[0x34] = ".";
    scancode[0x35] = "/";
    scancode[0x36] = "";
    scancode[0x37] = "*";
    scancode[0x38] = "";
    scancode[0x39] = " ";
    scancode[0x3A] = "";
    scancode[0x3B] = "";
    scancode[0x3C] = "";
    scancode[0x3D] = "";
    scancode[0x3E] = "";
    scancode[0x3F] = "";
    scancode[0x40] = "";
    scancode[0x41] = "";
    scancode[0x42] = "";
    scancode[0x43] = "";
    scancode[0x44] = "";
    scancode[0x45] = "";
    scancode[0x46] = "";
    scancode[0x47] = "7";
    scancode[0x48] = "8";
    scancode[0x49] = "9";
    scancode[0x4A] = "-";
    scancode[0x4B] = "4";
    scancode[0x4C] = "5";
    scancode[0x4D] = "6";
    scancode[0x4E] = "+";
    scancode[0x4F] = "1";
    scancode[0x50] = "2";
    scancode[0x51] = "3";
    scancode[0x52] = "0";
    scancode[0x53] = ".";
    scancode[0x57] = "";
    scancode[0x58] = "";

    scancode[0x81] = "escape released\n";
    scancode[0x82] = "1 released\n";
    scancode[0x83] = "2 released\n";
    scancode[0x84] = "3 released\n";
    scancode[0x85] = "4 released\n";
    scancode[0x86] = "5 released\n";
    scancode[0x87] = "6 released\n";
    scancode[0x88] = "7 released\n";
    scancode[0x89] = "8 released\n";
    scancode[0x8A] = "9 released\n";
    scancode[0x8B] = "0 (zero) released\n";
    scancode[0x8C] = "- released\n";
    scancode[0x8D] = "= released\n";
    scancode[0x8E] = "backspace released\n";
    scancode[0x8F] = "tab released\n";
    scancode[0x90] = "Q released\n";
    scancode[0x91] = "W released\n";
    scancode[0x92] = "E released\n";
    scancode[0x93] = "R released\n";
    scancode[0x94] = "T released\n";
    scancode[0x95] = "Y released\n";
    scancode[0x96] = "U released\n";
    scancode[0x97] = "I released\n";
    scancode[0x98] = "O released\n";
    scancode[0x99] = "P released\n";
    scancode[0x9A] = "[ released\n";
    scancode[0x9B] = "] released\n";
    scancode[0x9C] = "enter released\n";
    scancode[0x9D] = "left control released\n";
    scancode[0x9E] = "A released\n";
    scancode[0x9F] = "S released\n";
    scancode[0xA0] = "D released\n";
    scancode[0xA1] = "F released\n";
    scancode[0xA2] = "G released\n";
    scancode[0xA3] = "H released\n";
    scancode[0xA4] = "J released\n";
    scancode[0xA5] = "K released\n";
    scancode[0xA6] = "L released\n";
    scancode[0xA7] = " ; released\n";
    scancode[0xA8] = "' (single quote) released\n";
    scancode[0xA9] = "` (back tick) released\n";
    scancode[0xAA] = "left shift released\n";
    scancode[0xAB] = "\\ released\n";
    scancode[0xAC] = "Z released\n";
    scancode[0xAD] = "X released\n";
    scancode[0xAE] = "C released\n";
    scancode[0xAF] = "V released\n";
    scancode[0xB0] = "B released\n";
    scancode[0xB1] = "N released\n";
    scancode[0xB2] = "M released\n";
    scancode[0xB3] = ", released\n";
    scancode[0xB4] = ". released\n";
    scancode[0xB5] = "/ released\n";
    scancode[0xB6] = "right shift released\n";
    scancode[0xB7] = "* released\n";
    scancode[0xB8] = "left alt released\n";
    scancode[0xB9] = "space released\n";
    scancode[0xBA] = "CapsLock released\n";
    scancode[0xBB] = "F1 released\n";
    scancode[0xBC] = "F2 released\n";
    scancode[0xBD] = "F3 released\n";
    scancode[0xBE] = "F4 released\n";
    scancode[0xBF] = "F5 released\n";
    scancode[0xC0] = "F6 released\n";
    scancode[0xC1] = "F7 released\n";
    scancode[0xC2] = "F8 released\n";
    scancode[0xC3] = "F9 released\n";
    scancode[0xC4] = "F10 released\n";
    scancode[0xC5] = "NumberLock released\n";
    scancode[0xC6] = "ScrollLock released\n";
    scancode[0xC7] = "7 released\n";
    scancode[0xC8] = "8 released\n";
    scancode[0xC9] = "9 released\n";
    scancode[0xCA] = "- released\n";
    scancode[0xCB] = "4 released\n";
    scancode[0xCC] = "5 released\n";
    scancode[0xCD] = "6 released\n";
    scancode[0xCE] = "+ released\n";
    scancode[0xCF] = "1 released\n";
    scancode[0xD0] = "2 released\n";
    scancode[0xD1] = "3 released\n";
    scancode[0xD2] = "0 released\n";
    scancode[0xD3] = ". released\n";
    scancode[0xD7] = "F11 released\n";
    scancode[0xD8] = "F12 released\n";
}

void main(struct multiboot_info *mtb_info) {
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

    //If we ever reach this point, we've all information we need to proceed. No need to check. 
    extern unsigned int *buddy[];
    kprint(0xf, "Done.\nInitalizing Physical Memory Manager...\n");
    kprint(0x7, "-> buddy = %x\n-> call buddy_init()...\n", (unsigned int)buddy);
    extern void buddy_init(multiboot_memory_map_t *mmap, int mmap_length);
    buddy_init((multiboot_memory_map_t *)(mtb_info->mmap_addr), mtb_info->mmap_length / sizeof(multiboot_memory_map_t));
    kprint(0xf, "Done. We're now able to do pmalloc and pmfree! Yay!\nTesting kmalloc....\n");
    unsigned int *a = kmalloc(sizeof(unsigned int)* 4096);
    kprint(0x7, "a = %x\n", a);
    for (int i=0; i < 4096; i++){
        a[i] = i;
    }
    for (int i=0; i < 4096; i++){
        if (a[i] != i) {
            kprint(0xc, "Oops. There's gotta be something wrong. GO DEBUG. I'M HALTING.\n");
            return;
        }
    }
    kfree(a);
    extern unsigned int goto_usermode;
    kprint(0xf, "Done. There seems to be no problem. \nWe're now able to do kmalloc and kfree! Hoooooh-ray!!!\n");
    kprint(0xf, "%x\n", &goto_usermode);

    kprint(0xf, "Done.\nSetting up IDT...");

    kprint(0xf, "Done.\nSetting up ACPI...");

    kprint(0xf, "All Done. ");
    kprint(0xc, "HALT.");
    scancode_init();
}

unsigned int shift = 0;
unsigned int ctrl = 0;
unsigned int alt = 0;

void key(unsigned int sc) {
    if (sc <= 0x58){
        if (sc == 0x2a || sc == 0x36) {
            shift = 1;
        } else if (sc == 0x38) {
            alt = 1; 
        } else if (sc == 0x1d) {
            ctrl = 1;
        } else {
            if (scancode[sc][0] >= 'A' && scancode[sc][0] <= 'Z'){
                if (shift) {
                    kprint(0x7, "%s", scancode[sc]);
                } else if (ctrl){
                    if (scancode[sc][0] == 'C') {
                        kprint(0x7, "Ctrl-C Detected. \n");
                    }
                } else {
                    kprint(0x7, "%c", scancode[sc][0] + 0x20);
                }
            } else if (scancode[sc][0] >= '0' && scancode[sc][0] <= '9'){
                if (shift){
                    if (scancode[sc][0] == '1'){
                        kprint(0x7, "%c", '!');
                    } else if (scancode[sc][0] == '2'){
                        kprint(0x7, "%c", '@');
                    } else if (scancode[sc][0] == '3'){
                        kprint(0x7, "%c", '#');
                    } else if (scancode[sc][0] == '4'){
                        kprint(0x7, "%c", '$');
                    } else if (scancode[sc][0] == '5'){
                        kprint(0x7, "%c", '%');
                    } else if (scancode[sc][0] == '6'){
                        kprint(0x7, "%c", '^');
                    } else if (scancode[sc][0] == '7'){
                        kprint(0x7, "%c", '&');
                    } else if (scancode[sc][0] == '8'){
                        kprint(0x7, "%c", '*');
                    } else if (scancode[sc][0] == '9'){
                        kprint(0x7, "%c", '(');
                    } else if (scancode[sc][0] == '0'){
                        kprint(0x7, "%c", ')');
                    }
                } else {
                    kprint(0x7, "%s", scancode[sc]);
                }
            } else {
                if (shift){
                    if (scancode[sc][0] == '-'){
                        kprint(0x7, "%c", '_');
                    } else if (scancode[sc][0] == '='){
                        kprint(0x7, "%c", '+');
                    } else if (scancode[sc][0] == '`'){
                        kprint(0x7, "%c", '~');
                    } else if (scancode[sc][0] == '['){
                        kprint(0x7, "%c", '{');
                    } else if (scancode[sc][0] == ']'){
                        kprint(0x7, "%c", '}');
                    } else if (scancode[sc][0] == '\\'){
                        kprint(0x7, "%c", '|');
                    } else if (scancode[sc][0] == ';'){
                        kprint(0x7, "%c", ':');
                    } else if (scancode[sc][0] == '\''){
                        kprint(0x7, "%c", '"');
                    } else if (scancode[sc][0] == ','){
                        kprint(0x7, "%c", '<');
                    } else if (scancode[sc][0] == '.'){
                        kprint(0x7, "%c", '>');
                    } else if (scancode[sc][0] == '/'){
                        kprint(0x7, "%c", '?');
                    }
                } else {
                    kprint(0x7, "%s", scancode[sc]);
                }
            }
        }
    } else {
        if (sc == 0xaa || sc == 0xb6) {
            shift = 0;
        } else if (sc == 0xb8) {
            alt = 0; 
        } else if (sc == 0x9d) {
            ctrl = 0;
        }
    }
    
}

void syscall_print(){
    kprint(0x9, "System Call Fired!\n");
}


