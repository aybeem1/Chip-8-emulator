#ifndef CHIP8_H_
#define CHIP8_H_
#define VIDEO_WIDTH 64
#define VIDEO_HEIGHT 32

//hi this my chip-8 "emulator"
//I have no idea what I am doing but I'm very excited about tthis project!!
//90% of this will prob be completed in one night cause school is evil
//alr lemme actually start

//Stuff our little chip needs:
//4kb mem (wow) [x]
//64*32 display [x]
//A PC [x]
//A 16 bit register to point at memory stuff  [x]
//a 16 bit address stack [x] 
//An 8-bit delay timer  (60 Hz) [x]
//An 8-bit sound timer [x]
//16 one byte registers (numbered thru hexa decimal last one can be used as  a flag register) [x]

//things to know:
//CHIP-8 programs are loaded in memory at 0x200, 0x000 to 0x1FF are for the interperter (what u are making)

struct chip8 {


    //opcode are the special instructions used for chip-8,there are 35 each is 2 bytes long
    unsigned char running;
    unsigned short opcode;

    unsigned char mem[4096];
    uint32_t display[VIDEO_HEIGHT*VIDEO_WIDTH];
    //there is some versions of chip-8 like super chip or something that are like double this

    //program counter
    unsigned short pc;
    //this Index register is used specfically for holding stuff like sprites and font, big data.
    unsigned short I;

    //15 8-bit general purpose registers, 16th is used for flags
    unsigned char V[16];

    //timers both count @ 60Hz, sound timer buzzes when it reaches zero
    unsigned char delay_timer;
    unsigned char sound_timer;

    //stack holds locations when you jump (like calling a function)
    //pointer tells you where you were last.
    //chip-8 has 16 layers of stack
    unsigned short stack[16];
    unsigned short sp;

    //chip 8 has a keypad with hexadecimal values (1-16)
    unsigned char keypad[16];

}; 

typedef struct chip8 chip8;

void chip8init(chip8*);
void chip8Cycle(chip8* chip8);

void chip8ExecuteOpcode(chip8* chip8, short opcode);

void chip8LoadProgram(chip8* chip8, const char* program);

#endif