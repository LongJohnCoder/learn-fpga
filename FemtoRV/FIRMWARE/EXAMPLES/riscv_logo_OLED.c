/* 
 * FEMTORV32 - FEMTOSOC demo program:
 * Displaying a rotating RISCV logo
 */ 

#include <femtorv32.h>

/* The RISCV logo, with a tiny resolution
 * (remember, I only got 4Kb of RAM
 * on the IceStick !) 
 */
unsigned char logo[16][16] = {
   {7,7,7,7,7,7,5,3,3,3,3,3,3,3,3,7},
   {7,7,7,7,7,7,7,5,3,3,3,3,3,3,3,7},
   {1,1,1,1,2,7,7,7,3,3,3,3,3,3,3,7},
   {0,0,0,0,0,1,7,7,5,3,3,3,3,3,3,7},
   {0,0,0,0,0,0,7,7,6,3,3,3,3,3,6,7},
   {0,0,0,0,0,0,7,7,5,3,3,3,3,4,7,7},
   {0,0,0,0,0,2,7,7,4,3,3,3,3,7,7,7},
   {0,2,2,2,7,7,7,6,3,3,3,3,6,7,7,7},
   {0,7,7,7,7,7,6,3,3,3,3,5,7,7,2,7},
   {0,1,7,7,7,4,3,3,3,3,3,7,7,7,0,7},
   {0,0,2,7,7,6,3,3,3,3,6,7,7,1,0,7},
   {0,0,0,2,7,7,5,3,3,5,7,7,2,0,0,7},
   {0,0,0,0,7,7,7,5,4,7,7,2,0,0,0,7},
   {0,0,0,0,0,7,7,7,7,7,7,0,0,0,0,7},
   {0,0,0,0,0,1,7,7,7,7,1,0,0,0,0,7},
   {7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7}
};

/* 
 * The colormap.
 */ 
uint16_t cmap[8] = {
   GL_RGB(0x28,0x33,0x74),
   GL_RGB(0x7B,0x80,0x9B),
   GL_RGB(0xAA,0xAC,0xBC),
   GL_RGB(0xF9,0xB1,0x15),
   GL_RGB(0xF9,0xBE,0x65),
   GL_RGB(0xF9,0xC7,0x82),
   GL_RGB(0xFC,0xD8,0xB0),
   GL_RGB(0xFA,0xFB,0xF8)
};

/*
 * Generated by TOOLS/make_sintab.c
 */

int sintab[64] = {
   0,25,49,74,97,120,142,162,181,197,212,225,236,244,251,254,
   256,254,251,244,236,225,212,197,181,162,142,120,97,74,49,25,
   0,-25,-49,-74,-97,-120,-142,-162,-181,-197,-212,-225,-236,-244,
   -251,-254,-256,-254,-251,-244,-236,-225,-212,-197,-181,-162,
   -142,-120,-97,-74,-49,-25
};

void main() {
    GL_init();
    int frame = 0;
    for(;;) {
	oled_write_window(0,0,OLED_WIDTH-1,OLED_HEIGHT-1);
       
        int scaling = sintab[frame&63]+400;
        int Ux = scaling*sintab[frame & 63];         
        int Uy = scaling*sintab[(frame + 16) & 63];  
        int Vx = -Uy;                                
        int Vy =  Ux;                                

        int X0 = -64*(Ux+Vx); 
        int Y0 = -64*(Uy+Vy);

	for(int y=0; y<OLED_HEIGHT; ++y) {
	    int X = X0;
	    int Y = Y0;
	    for(int x=0; x<OLED_WIDTH; ++x) {
	        unsigned char col = logo[(Y >> 18)&15][(X >> 18)&15];
	        OLED_WRITE_DATA_UINT16(cmap[col]);
	        X += Ux;
	        Y += Uy;
	    }
	    X0 += Vx;
	    Y0 += Vy;
	}
	++frame;
        IO_OUT(IO_LEDS,frame >> 4);
    }
}
