void general_handler(unsigned int exception, unsigned int error_code, unsigned int error_code_2){
    char *exceptions[19]={  "Divide by zero", 
                "Debug", 
                "NMI", 
                "Breakpoint", 
                "Into detected overflow", 
                "Out of Bounds", 
                "Invalid opcode", 
                "No coprocessor", 
                "Double fault", 
                "Coprocessor segment overrun", 
                "Bad TSS", 
                "Segment ot present", 
                "Stack fault", 
                "General protection", 
                "Page fault", 
                "Unknown interrupt", 
                "Coprocessor fault", 
                "Alignment check fault", 
                "Machine check"};
    kprint(0x4, "EXCEPTION 0x%b - %s.\nError code:%x   Additional info:%x\n", (char)exception, exceptions[exception], error_code, error_code_2);
    PIC_sendEOI((unsigned char)exception);
    //kprint(4x4, "HALTED.");
    //__asm__("hlt");
}