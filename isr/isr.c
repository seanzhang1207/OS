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
    scancode[0x33] = ", ";
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
    //kprint(0x9, "System Call Fired!\n");
}

void pit_c(){
    kprint(0x9, "PIT ");
}
