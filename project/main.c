#include <msp430.h>
#include "libTimer.h"
#include "led.h"
#include "switches.h"
#include "buzzer.h"
#include "lcdutils.h" // LCD utilities
#include "lcddraw.h"  // LCD drawing functions

#include "song_images.h" // Custom images for the song (e.g., Christmas tree or bells)

int main(void) {
  configureClocks();   // Configure system clocks
  lcd_init();          // Initialize the LCD screen

  // Clear the screen and set a festive background color
  clearScreen(COLOR_RED);
  
  // Draw a festive image or text on the LCD (e.g., Jingle Bells title)
  drawString5x7(10, 10, "Jingle Bells", COLOR_GREEN, COLOR_RED);

  // Initialize peripherals
  switch_init();       // Initialize switches
  led_init();          // Initialize LEDs
  buzzer_init();       // Initialize buzzer

  // Turn on the green LED to indicate ready state
  green_led_on();

  // Enable Watchdog Timer interrupts
  enableWDTInterrupts();

  // Main loop, CPU off and interrupts enabled
  or_sr(0x18);
}

