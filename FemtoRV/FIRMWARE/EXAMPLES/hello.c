#include <femtorv32.h>

int main() {
  
   /*
    * redirects display to UART (default), OLED display
    * or led matrix, based on configured devices (in femtosoc.v).
    * Note: pulls the two fonts (eats up a subsequent part of the
    * available 6 Kbs).
    *   To save code size, on the IceStick, you can use 
    * instead MAX7219_tty_init() if you know you are 
    * using the led matrix, or GL_tty_init() if you know you are 
    * using the small OLED display.
    */
   femtosoc_tty_init();
   
   for(;;) {
      printf("RISC-V FemtoRV32>>> Bonne annee 2021 !\n");
      delay(500);
      /*
     printf("Hello world !!\n Let me introduce myself, I am FemtoRV32, one of the smallest RISC-V cores\n");
     delay(1000);
     printf("Running now at %d MHz\n", FEMTORV32_FREQ);
     delay(1000);
       */ 
   }

   return 0;
}

