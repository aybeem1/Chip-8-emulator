#include <stdio.h>
#include <stdint.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "chip-8struct.h"
#define START_ADDRESS 0x200
#define FONT_START_ADDRESS 0x50
#define FONT_SIZE 80




 typedef struct Platform {

    SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* texture;

 } Platform; 

	Platform* Platform_create(char const* title, int windowWidth, int windowHeight, int textureWidth, int textureHeight)
	{
        Platform* platform = (Platform*)malloc(sizeof(Platform));
        if (!platform) return NULL;

        SDL_Init(SDL_INIT_VIDEO);
        
       
        platform->window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
        
        platform->renderer = SDL_CreateRenderer(platform->window, -1, SDL_RENDERER_ACCELERATED);
        
      
        platform->texture = SDL_CreateTexture(platform->renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, textureWidth, textureHeight);
        
        return platform;;
        }
 
	void Platform_destroy(Platform* platform)
	{
		if (!platform) return;
    
        SDL_DestroyTexture(platform->texture);
        SDL_DestroyRenderer(platform->renderer);
        SDL_DestroyWindow(platform->window);
        SDL_Quit();
    
        free(platform);
	}
    void Platform_Update(Platform* platform, void const* buffer, int pitch) {
        SDL_UpdateTexture(platform->texture, NULL, buffer, pitch);
        SDL_RenderClear(platform->renderer);
        SDL_RenderCopy(platform->renderer, platform->texture, NULL, NULL);
        SDL_RenderPresent(platform->renderer);
    }

	bool Platform_ProcessInput(Platform* platform, uint8_t* keys) {
    bool quit = false;
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT: {
                quit = true;
            } break;
            case SDL_KEYDOWN: {
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE: { quit = true; } break;
                    case SDLK_x: { keys[0] = 1; } break;
                    case SDLK_1: { keys[1] = 1; } break;
                    case SDLK_2: { keys[2] = 1; } break;
                    case SDLK_3: { keys[3] = 1; } break;
                    case SDLK_q: { keys[4] = 1; } break;
                    case SDLK_w: { keys[5] = 1; } break;
                    case SDLK_e: { keys[6] = 1; } break;
                    case SDLK_a: { keys[7] = 1; } break;
                    case SDLK_s: { keys[8] = 1; } break;
                    case SDLK_d: { keys[9] = 1; } break;
                    case SDLK_z: { keys[0xA] = 1; } break;
                    case SDLK_c: { keys[0xB] = 1; } break;
                    case SDLK_4: { keys[0xC] = 1; } break;
                    case SDLK_r: { keys[0xD] = 1; } break;
                    case SDLK_f: { keys[0xE] = 1; } break;
                    case SDLK_v: { keys[0xF] = 1; } break;
                }
            } break;
            case SDL_KEYUP: {
                switch (event.key.keysym.sym) {
                    case SDLK_x: { keys[0] = 0; } break;
                    case SDLK_1: { keys[1] = 0; } break;
                    case SDLK_2: { keys[2] = 0; } break;
                    case SDLK_3: { keys[3] = 0; } break;
                    case SDLK_q: { keys[4] = 0; } break;
                    case SDLK_w: { keys[5] = 0; } break;
                    case SDLK_e: { keys[6] = 0; } break;
                    case SDLK_a: { keys[7] = 0; } break;
                    case SDLK_s: { keys[8] = 0; } break;
                    case SDLK_d: { keys[9] = 0; } break;
                    case SDLK_z: { keys[0xA] = 0; } break;
                    case SDLK_c: { keys[0xB] = 0; } break;
                    case SDLK_4: { keys[0xC] = 0; } break;
                    case SDLK_r: { keys[0xD] = 0; } break;
                    case SDLK_f: { keys[0xE] = 0; } break;
                    case SDLK_v: { keys[0xF] = 0; } break;
                }
            } break;
        }
    }
    return quit;
}

//ugly so made a function, gets time but like really specfically for cycle measuring
unsigned long long get_time_ns() {
    struct timespec ts;
   
    clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
    return (unsigned long long)ts.tv_sec * 1000000000ULL + ts.tv_nsec;
}






uint8_t fontset[FONT_SIZE] =
{
	0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
	0x20, 0x60, 0x20, 0x20, 0x70, // 1
	0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
	0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
	0x90, 0x90, 0xF0, 0x10, 0x10, // 4
	0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
	0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
	0xF0, 0x10, 0x20, 0x40, 0x40, // 7
	0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
	0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
	0xF0, 0x90, 0xF0, 0x90, 0x90, // A
	0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
	0xF0, 0x80, 0x80, 0x80, 0xF0, // C
	0xE0, 0x90, 0x90, 0x90, 0xE0, // D
	0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
	0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};


int main(int argc, char *argv[])
{

    //if their aren't this many command line things then it is being used wrong
    if(argc != 4)
    {
        //yell at them for being bad
        printf("Usage: %s <scale> <delay> <ROM>", argv[0]);
        return 1;
        //return saying hey something went wrong
    }

        //saves command line info into variables
        int videoScale = atoi(argv[1]);
        int cycleDelay = atoi(argv[2]);
        char const* romFilename = argv[3];

        //create the graphics for the chip8 
        Platform* platform = Platform_create("CHIP-8 Emulator", VIDEO_WIDTH * videoScale, VIDEO_HEIGHT * videoScale, VIDEO_WIDTH, VIDEO_HEIGHT);
        if (!platform) return 1;

        //create chip8 object and init
        chip8 Chip8; 
        chip8init(&Chip8);
        chip8LoadProgram(&Chip8, romFilename);

        int videoPitch = sizeof(Chip8.display[0]) * VIDEO_WIDTH;

        unsigned long long lastCycleTime = get_time_ns();
        bool quit = false;
        
    while (!quit)
    {
        quit = Platform_ProcessInput(platform, Chip8.keypad);

        unsigned long long current_time = get_time_ns();
        unsigned long long dt = current_time - lastCycleTime;

        if (dt > cycleDelay * 1000000ULL)   // see note below
        {
            lastCycleTime = current_time;
            chip8Cycle(&Chip8);
            Platform_Update(platform, Chip8.display, videoPitch);
        }
    }   

    Platform_destroy(platform);
    return 0;

}

void chip8init(chip8* chip8){
    memset(chip8, 0, sizeof(*chip8));
    chip8->pc = START_ADDRESS; //resets pointers
    chip8->I = 0;
    chip8->sp = 0;


    //generates random seed ONCE
    srand((unsigned int)time(NULL));

    for(unsigned int i = 0; i < FONT_SIZE; i++)
    {


        chip8->mem[FONT_START_ADDRESS + i] = fontset[i];

    }

}




void chip8LoadProgram(chip8* chip8, const char* program)
{   
    //handling proper command line usage will be done in main


    FILE* game = fopen(program, "r");//opens file under read restictions
    if(!game) //if not found is sad
    {
        printf("file not found");
        return;

    }

    fseek(game, 0, SEEK_END);//puts pointer to eof
    long int buffer_size = ftell(game);//gives last postion
    if(buffer_size > 4096)
    {
        printf("Too large of file, sorry!");
        return;

    }
    rewind(game);//sets back to start

    uint8_t* buffer = (uint8_t*) malloc(buffer_size * sizeof(uint8_t));//frees up mem for size of game in buffer

    fread(buffer, sizeof(buffer[0]), buffer_size, game);//reads the game and puts into buffer
    fclose(game);//closes game file


    //loads buffer into mem
    for(int i = 0; i < buffer_size; i++)
    {

        chip8->mem[START_ADDRESS + i] = buffer[i];
        //games are supposed to be loaded in starting at 0x200

    }

    //frees buffer cause we don't need it any more    
    free(buffer);


}


void chip8ExecuteOpcode(chip8* chip8, short opcode)
{
    
    //extracting data from opcode to tell what  it is 
    //and operator with F will extract only selected part of opcode
    //eg 0x1234 & 0xF000 = 0x1000

    uint16_t nnn = opcode & 0x0FFFu;
    uint16_t type = opcode & 0xF000u;
    uint16_t nn =  opcode & 0X00FFu;
    uint16_t vy = (opcode & 0x00F0u) >> 4u;
    uint16_t vx = (opcode & 0x0F00u) >> 8u;
    uint16_t val =  opcode & 0x000Fu; 
    
    

   
    //move stack pointer upppp (one op code = sp places)

    //this checks the msb which genrally defines the kind of
    //instruction it is thats why it's called "type"
    switch(type) {
        //0 is kinda like misc
        case 0x0000:
            switch(nnn)
            {
                //clears screen
                case 0x00E0:
                        memset(&chip8->display, 0, sizeof(chip8->display));
                    break;
                //returns from a subroutine
                case 0x00EE:
                    //function is over so go unwind 1 in stack
                    chip8->sp--;
                    //sets the program counter to the new instruction 
                    chip8->pc = chip8->stack[chip8->sp];

                    break;
                default: 
                    printf("Invalid address");
                    exit(1);
                
            }

            break;
        case 0x1000:
                
                //jumps to address 
                chip8->pc = nnn;
    
            break;
        case 0x2000:
            
            //calls a subrotuine
            //this saves where we were before the subroutine
            chip8->stack[chip8->sp] = chip8->pc;
            chip8->sp++;
            chip8->pc = nnn; 
            //moves us to the subroutine
    
            break;
        case 0x3000:
            
            //if Vx == nn skip the next instruction
            if(chip8->V[vx] == nn)
            {

                chip8->pc += 2;

            }
        
    
            break;
        case 0x4000:
            
            //if Vx != nn skip the next instruction
            //evil 0x3nnn
            if(chip8->V[vx] != nn)
            {

                chip8->pc += 2;

            }
    
            break;
        case 0x5000:

            //if Vy and Vx are equal skip 
            if(chip8->V[vy] == chip8->V[vx])
            {

                chip8->pc += 2;

            }
         
    
            break;
        case 0x6000:
            
            //set Vx to nn
            chip8->V[vx] = nn;
        
    
            break;
        case 0x7000:
            
            //Add nn to Vx
            chip8->V[vx] += nn; 
    
            break;
        //setting registers
        case 0x8000:
            switch(val){
                case 0x0000u: {

                    //set Vx to Vy
                    chip8->V[vx] = chip8->V[vy];
                }    break;
                
                case 0x0001u: {

                    //Apply Or to Vx with Vy and set Vx to the result
                    chip8->V[vx] |= chip8->V[vy];
                }    break;
                case 0x0002u: {
                    //Apply And to Vx with Vy and set Vx to the result

                    chip8->V[vx] &= chip8->V[vy];
                    }    break;
                
                case 0x0003u:
                {
                    //Apply Xor to Vx with Vy and set Vx to the result
                    chip8->V[vx] ^= chip8->V[vy];
                }break;

                //add Vx and Vy and flag if the result overflows 8 bits,
                //set Vx to the 8 lsb of the sum
                case 0x0004u: {
                    uint16_t sum = chip8->V[vx] + chip8->V[vy];
                    chip8->V[vx] = sum & 0xFFu;
                    chip8->V[0xF] = (sum > 255) ? 1 : 0;
                 } break;

                //flag if Vx>Vy and subtract Vy from Vx 
                //then set Vx to the result
                //omg negative numbers ahh scary    
                case 0x0005u: {
                    
                    uint8_t x = chip8->V[vx], y = chip8->V[vy];
                    chip8->V[vx] = x - y;
                    chip8->V[0xF] = (x >= y) ? 1 : 0; 
                 } break;
            
                case 0x0006:{
                    //checks the lsb of vx and flags if it is one
                    //then divides vx by 2 via a bit shift 1 right
                    uint8_t x = chip8->V[vx];
                    chip8->V[vx] = x >> 1;
                    chip8->V[0xF] = x & 0x1u; 
                    
                 } break;
                case 0x0007: {
                    //subtracts vx from vy and flags if the result is positve
                    //stores result in vx
                    uint16_t x = chip8->V[vx], y = chip8->V[vy];
                    chip8->V[vx] = y - x;
                    chip8->V[0xF] = (y >= x) ? 1 : 0;                                
                 } break;
                case 0x000E: {

                    //checks the msb of vx and then 
                    //mutiples vx by two via a bit shift 1 left
                    uint8_t x = chip8->V[vx]; 
                    chip8->V[vx] = x << 1;
                    chip8->V[0xF] = (x & 0x80u) >> 7u;

                    
                 } break;
            }
        break;        

              
        case 0x9000:
            
            //if vx is not equal to vy skip an instruction

            if(chip8->V[vx] != chip8->V[vy])
            {

                chip8->pc += 2;

            }
    
            break;
        case 0xA000:
            //set index to nnn
            chip8->I = nnn;
    
            break;
        case 0xB000:
            //jump pc to adress nnn = V0
            chip8->pc = chip8->V[0] + nnn;
    
            break;
        case 0xC000:
            
            //set vx to random num 0-256 with & bitmask of nn
             chip8->V[vx] =  (rand() % 256) & nn;


            break;
        case 0xD000:
            //renames val to height for better readabilty
            //gives how many rows tall the sprite is 
            uint16_t height = val;

            //if sprite goes off of screen will just wrap
            //back around to start
            uint8_t xPos = chip8->V[vx] % VIDEO_WIDTH;
            uint8_t yPos = chip8->V[vy] % VIDEO_HEIGHT;
            
            //clear flag register
            chip8->V[0xF] = 0;

            //loops through each given row
            for(unsigned int row = 0; row < height; ++row)
            {

                //fetches 1 byte of the sprite from mem
                //index tells us the start of the graphics
                //being stored in mem
                uint8_t spritebyte = chip8->mem[chip8->I + row];

                //loop through each bit of the byte
                for(unsigned int col = 0; col < 8; ++col)
                {
                    
                    
                    if (xPos + col >= VIDEO_WIDTH || yPos + row >= VIDEO_HEIGHT) continue;
                    //uses bit mask to load each pixel, 
                    //is shifted one to the right everytime
                    //col is incremented
                    uint8_t spritePixel = spritebyte & (0x80 >> col);
                    //calculates where the postion is (2D -> 1D) in memory and saves it's address
                    uint32_t* screenPixel = &(chip8->display[(yPos + row) * VIDEO_WIDTH + (xPos + col)]);


                    //if there is a sprite pixel here (on = true)
                    if(spritePixel) {

                        //if there is a screen pixel also here
                        if(*screenPixel == 0xFFFFFFFF)
                        {
                            //then there is a collison
                            chip8->V[0xF] = 1;

                        } 

                        //XOR /w sprite pixel because it must be on now
                        *screenPixel ^= 0xFFFFFFFF;

                    }
            

                } 

            }

            break;
        case 0xE000:
                switch(nn)
                {   
                    unsigned char key;   
                    //checks if vx has current key and if so skips
                    //next instruction
                    case 0x9E:

                        key = chip8->V[vx];
                        if(chip8->keypad[key])
                        {

                            chip8->pc += 2;

                        }

                        break;
                    
                    //checks if vx doesn't have current key and if so skips
                    //next instruction
                    case 0xA1:
                        key = chip8->V[vx];
                        if(!chip8->keypad[key])
                        {
                            
                            chip8->pc += 2;

                        }
                        break;
                }    
    
            break;
        case 0xF000:

                switch(nn){
                    case 0x07:
                        ///sets vx to delay timer
                        chip8->V[vx] = chip8->delay_timer;
                        break;
                    case 0x0A:
                        //waits for keypad input
                        if (chip8->keypad[0])
                        {
                            chip8->V[vx] = 0;
                        }
                        else if (chip8->keypad[1])
                        {
                            chip8->V[vx] = 1;
                        }
                        else if (chip8->keypad[2])
                        {
                            chip8->V[vx] = 2;
                        }
                        else if (chip8->keypad[3])
                        {
                            chip8->V[vx] = 3;
                        }
                        else if (chip8->keypad[4])
                        {
                            chip8->V[vx] = 4;
                        }
                        else if (chip8->keypad[5])
                        {
                            chip8->V[vx] = 5;
                        }
                        else if (chip8->keypad[6])
                        {
                            chip8->V[vx] = 6;
                        }
                        else if (chip8->keypad[7])
                        {
                            chip8->V[vx] = 7;
                        }
                        else if (chip8->keypad[8])
                        {
                            chip8->V[vx] = 8;
                        }
                        else if (chip8->keypad[9])
                        {
                            chip8->V[vx] = 9;
                        }
                        else if (chip8->keypad[10])
                        {
                            chip8->V[vx] = 10;
                        }
                        else if (chip8->keypad[11])
                        {
                            chip8->V[vx] = 11;
                        }
                        else if (chip8->keypad[12])
                        {
                            chip8->V[vx] = 12;
                        }
                        else if (chip8->keypad[13])
                        {
                            chip8->V[vx] = 13;
                        }
                        else if (chip8->keypad[14])
                        {
                            chip8->V[vx] = 14;
                        }
                        else if (chip8->keypad[15])
                        {
                            chip8->V[vx] = 15;
                        }
                        else
                        {   //else effectivly loops it 
                            //by going back to the same
                            //instruction that called it
                            //until a key is pressed
                            chip8->pc -= 2;
                        }
                        break;

                    case 0x15:
                        //sets delay timer to vx
                        chip8->delay_timer = chip8->V[vx];
                        
                        break;

                    case 0x18:
                        //sets sound timer to vx
                        chip8->sound_timer = chip8->V[vx];

                        break;

                    case 0x1E:
                        
                        //Sets index to index + vx
                        chip8->I += chip8->V[vx];

                        break;

                    case 0x29:
                        
                        //vx is used to get a digit
                        //then that digit is assinged to the index
                        //digits start being stored at 0x50
                        //each digit is 5 bytes
                        uint16_t digit = chip8->V[vx];
                        chip8->I = FONT_START_ADDRESS + (5 * digit);

                        break;

                    case 0x33:
                        //stores BCD value of vx in index + 2 - index
                        uint16_t value = chip8->V[vx];

                        //ones place
                        chip8->mem[chip8->I + 2] = value % 10;
                        value /= 10;
                        
                        //tens place
                        chip8->mem[chip8->I + 1] = value % 10;
                        value /= 10;

                        //hundreds place
                        chip8->mem[chip8->I] = value % 10;                       

                        break;

                    case 0x55:
                        //stores registers 0-F in mem starting at index
                        for(uint8_t i = 0; i <= vx; i++)
                        {

                            chip8->mem[chip8->I + i] = chip8->V[i];

                        }

                        break;

                    case 0x65:
                        //takes registers from memory and assigns
                        //them to registers 0-F
                        for(uint8_t i = 0; i <= vx; i++)
                        {

                            chip8->V[i] = chip8->mem[chip8->I + i];

                        }

                        break;

                }
    
            break;
        
        
    }
    



}

void chip8Cycle(chip8* chip8)
{
    //fetches, moves first half of instruction into upper half and adds on the bottom half
    uint16_t opcode = chip8->mem[chip8->pc] << 8u | chip8->mem[chip8->pc+1];

    chip8->pc += 2;

    chip8ExecuteOpcode(chip8, opcode);

    if(chip8->delay_timer > 0)
    {

        chip8->delay_timer--;

    }

    if(chip8->sound_timer > 0)
    {

        chip8->sound_timer--;

    }

}