#include <femtorv32.h>

int      FGA_mode;
uint16_t FGA_width;
uint16_t FGA_height;

void FGA_setmode(int mode) {
   if(!FEMTOSOC_HAS_DEVICE(IO_FGA_CNTL_bit)) {
      return;
   }
   FGA_mode = mode;
   IO_OUT(IO_FGA_CNTL, FGA_SET_MODE | (mode << 8));
   memset(FGA_BASEMEM,0,128000);
   switch(mode) {
   case FGA_MODE_320x200x16bpp:
     FGA_width = 320;
     FGA_height = 200;
     break;
   case FGA_MODE_320x200x8bpp:
     FGA_width = 320;
     FGA_height = 200;
     break;
   case FGA_MODE_640x400x4bpp:
     FGA_width =  640;
     FGA_height = 400;
     break;
   }
}

void FGA_write_window(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2) {
  IO_OUT(IO_FGA_CNTL, FGA_SET_WWINDOW_X | x1 << 8 | x2 << 20);
  IO_OUT(IO_FGA_CNTL, FGA_SET_WWINDOW_Y | y1 << 8 | y2 << 20);  
}

/***************************************************************************/

