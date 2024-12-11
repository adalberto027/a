#include <msp430.h>
#include "led.h"
#include "switches.h"

// flags to check states
unsigned char led_altered = 0;                    // initially unaltered (0)
unsigned char r_led_on = 0, g_led_on = 0;         // initially off (0)
static char redVal[] = {0, LED_RED}, greenVal[] = {0, LED_GREEN};

// arrays to represent possible states of leds (e.g. 0 = off, on = LED_RED)
void led_init() {
  P1DIR |= LEDS;          // sets a bit in P1DIR (port 1) to 1 configuring it as an output
  led_altered = 1;        // state of leds have been altered so update char to 1
  led_update();           // call on led_update function
}

// updates the led states based on r_on/g_on
void led_update() {
  // check if the leds need to be updated (they have been altered)
  if (led_altered) {
    char ledFlags = redVal[r_led_on] | greenVal[g_led_on];     // find the desired state for the leds (0 or 1)
    // apply the ledFlags values without changing the other pins to output (leds)
    P1OUT &= (0xff^LEDS) | ledFlags;                           // Clear the state of LEDs
    P1OUT |= ledFlags;                                         // Update the LEDs to their new state (on or off)
    led_altered = 0;                                           // Reset the state
  }
}

// turns on the green led
void green_led_on() {
  P1OUT |= LED_GREEN;                  // Turn on the green LED
  __delay_cycles(300000);              // Adjusted delay for shorter visibility (sync with melody)
}

// turns on the red led
void red_led_on() {
  P1OUT |= LED_RED;                    // Turn on the red LED
  __delay_cycles(300000);              // Adjusted delay for shorter visibility (sync with melody)
}

// turns off both leds
void leds_off() {
  P1OUT &= ~LED_GREEN;                 // Turn off the green LED
  P1OUT &= ~LED_RED;                   // Turn off the red LED
  __delay_cycles(100000);              // Shorter delay for smoother transitions
}

// flashes the leds
void led_flash(int n) {
  for (int i = 0; i < n; i++) {
    P1OUT |= LED_RED;                  // Turn on red LED
    __delay_cycles(500000);            // Delay for visibility
    P1OUT &= ~LED_RED;                 // Turn off red LED
    __delay_cycles(250000);            // Pause
    P1OUT |= LED_GREEN;                // Turn on green LED
    __delay_cycles(500000);            // Delay for visibility
    P1OUT &= ~LED_GREEN;               // Turn off green LED
    __delay_cycles(250000);            // Pause
  }
  leds_off();                          // Ensure LEDs are off after flashing
}
