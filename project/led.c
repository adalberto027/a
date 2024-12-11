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

// Synchronize LEDs with tone changes
void playTuneWithLED(const int *notes, const int *tempo, int noteAmt) {
  for (int i = 0; i < noteAmt; i++) {
    if (i % 2 == 0) {
      P1OUT |= LED_RED;                  // Turn on red LED
      P1OUT &= ~LED_GREEN;               // Turn off green LED
    } else {
      P1OUT |= LED_GREEN;                // Turn on green LED
      P1OUT &= ~LED_RED;                 // Turn off red LED
    }

    // Set buzzer frequency
    buzzer_set_period(1000000 / notes[i]);

    // Wait for the duration of the note
    int dur = tempo[i];
    while (dur--) {
      __delay_cycles(8000);              // Delay adjusted for tone duration
    }
  }

  // Turn off both LEDs and stop the buzzer at the end
  P1OUT &= ~LED_RED;
  P1OUT &= ~LED_GREEN;
  buzzer_set_period(0);
}
