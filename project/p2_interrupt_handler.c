#include <msp430.h>
#include "switches.h"
#include "buzzer.h"
#include "led.h"

// Interrupt handler for switches
void __interrupt_vec(PORT2_VECTOR) Port2() {
  if (P2IFG & SWITCHES) {          // Check if an interrupt has been triggered by any switch
    P2IFG &= ~SWITCHES;            // Reset the interrupt flags for the switches
    switch_interrupt_handler();    // Handle the switch action

    // Custom action for your project: toggle melody playback
    static int playing = 0;        // Track if the melody is currently playing

    if (playing) {
      buzzer_set_period(0);        // Stop the buzzer
      leds_off();                  // Turn off all LEDs
      playing = 0;                 // Update state to not playing
    } else {
      oot();                       // Play the "Jingle Bells" chorus
      playing = 1;                 // Update state to playing
    }
  }
}
