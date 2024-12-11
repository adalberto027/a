#include <msp430.h>
#include <libTimer.h>
#include "buzzer.h"
#include "notes.h"
#include "statemachines.h"
#include "led.h"

// Initialize the buzzer
void buzzer_init() {
    timerAUpmode();		/* used to drive speaker */
    P2SEL2 &= ~(BIT6 | BIT7);
    P2SEL &= ~BIT7; 
    P2SEL |= BIT6;
    P2DIR = BIT6;		/* enable output to speaker (P2.6) */
}

// Set the period for the buzzer to produce tones
void buzzer_set_period(short cycles) {
  CCR0 = cycles; 
  CCR1 = cycles >> 1;	
}

// Play the melody with synchronized LED behavior
void playTune(const int *notes, const int *tempo, int noteAmt) {
  for (int i = 0; i < noteAmt; i++) {
    // Alternate LEDs based on the note index
    if (i % 2 == 0) {
      red_led_on();  // Turn on red LED
    } else {
      green_led_on();  // Turn on green LED
    }

    // Set the buzzer frequency for the current note
    buzzer_set_period(1000000 / notes[i]);

    // Wait for the duration of the note
    int dur = tempo[i];
    while (dur--) {
      __delay_cycles(8000);  // Delay based on the tempo
    }
  }

  // Turn off LEDs and stop the buzzer at the end
  buzzer_set_period(0);
  leds_off();
}

// Main function to play Jingle Bells - Chorus
void oot() {
  // Notes for the chorus of "Jingle Bells" (in Hz)
  const int notes[] = {
    E4, E4, E4,  // Jingle bells
    E4, E4, E4,  // Jingle bells
    E4, G4, C4, D4, E4,  // Jingle all the way!
    F4, F4, F4, F4, F4, E4, E4, E4,  // Oh what fun it is to ride
    E4, D4, D4, E4, D4, G4  // In a one-horse open sleigh!
  };

  // Tempo for each note (in milliseconds)
  const int tempo[] = {
    400, 400, 800,  // Jingle bells
    400, 400, 800,  // Jingle bells
    400, 400, 400, 400, 800,  // Jingle all the way!
    400, 400, 800, 400, 400, 400, 400, 800,  // Oh what fun it is to ride
    400, 400, 400, 400, 400, 800  // In a one-horse open sleigh!
  };

  // Calculate the number of notes
  int noteAmt = sizeof(notes) / sizeof(notes[0]);

  // Play the melody
  playTune(notes, tempo, noteAmt);
}
