#include <msp430.h>
#include "libTimer.h"
#include "led.h"
#include "switches.h"
#include "buzzer.h"
#include "lcdutils.h" // ADDED
#include "lcddraw.h" // ADDED

#include "song_images.h"

int main(void) {
  configureClocks();
  lcd_init(); // ADDED
  //drawDefault();
  //u_char width = screenWidth, height = screenHeight; // ADDED
  //clearScreen(COLOR_BLUE); // ADDED
  //int col = 0, row = 0; // ADDED
  //int centerCol = width/2, centerRow = height/2; // ADDED
  //for (row = 0; row < 20; row++) { // ADDED
    //for (col = -row; col <= row; col+=2) { // ADDED
      //drawPixel(centerCol + col, centerRow + row, COLOR_PINK); // ADDED
      //}
    //}
  
  switch_init();              // initialize switches
  led_init();                 // initialize led
  buzzer_init();            // initialize buzzer
  
  green_led_on();             // turn on the green led
  enableWDTInterrupts();      // enable WatchDog interrupts

  or_sr(0x18); // CPU off, GIE on
}
