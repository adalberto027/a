#include <msp430.h>
#include "led.h"
#include "switches.h"

// Flags to check states
unsigned char led_altered = 0;                    // Initially unaltered (0)
unsigned char r_led_on = 0, g_led_on = 0;         // Initially off (0)
static char redVal[] = {0, LED_RED}, greenVal[] = {0, LED_GREEN};

// Initialize LEDs
void led_init() {
  P1DIR |= LEDS;          // Configure LED pins as outputs
  P1OUT &= ~LEDS;         // Turn off all LEDs initially
  led_altered = 1;        // Indicate LEDs have been altered
  led_update();           // Update LEDs to initial state
}

// Update LEDs based on the current state
void led_update() {
  if (led_altered) {
    char ledFlags = redVal[r_led_on] | greenVal[g_led_on];
    P1OUT &= (0xff ^ LEDS) | ledFlags;  // Clear the state of LEDs
    P1OUT |= ledFlags;                 // Apply the new LED states
    led_altered = 0;                   // Reset the alteration flag
  }
}

// Turn on the green LED
void green_led_on() {
  P1OUT |= LED_GREEN;   // Turn on the green LED
  P1OUT &= ~LED_RED;    // Turn off the red LED
}

// Turn on the red LED
void red_led_on() {
  P1OUT |= LED_RED;     // Turn on the red LED
  P1OUT &= ~LED_GREEN;  // Turn off the green LED
}

// Turn off both LEDs
void leds_off() {
  P1OUT &= ~LEDS;       // Turn off all LEDs
}

// Flash the LEDs
void led_flash(int n) {
  for (int i = 0; i < n; i++) {
    red_led_on();                // Turn on the red LED
    __delay_cycles(500000);      // Delay for visibility
    leds_off();                  // Turn off LEDs
    __delay_cycles(250000);      // Pause
    green_led_on();              // Turn on the green LED
    __delay_cycles(500000);      // Delay for visibility
    leds_off();                  // Turn off LEDs
    __delay_cycles(250000);      // Pause
  }
}
