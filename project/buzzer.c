#include <msp430.h>
#include <libTimer.h>
#include "buzzer.h"
#include "notes.h"
#include "statemachines.h"
#include "led.h"

void buzzer_init() {
    timerAUpmode();		/* used to drive speaker */
    P2SEL2 &= ~(BIT6 | BIT7);
    P2SEL &= ~BIT7; 
    P2SEL |= BIT6;
    P2DIR = BIT6;		/* enable output to speaker (P2.6) */
}

void buzzer_set_period(short cycles) {
  CCR0 = cycles; 
  CCR1 = cycles >> 1;	
}

void playTune(const int *notes, const int*tempo, int noteAmt) {
  for(int i = 0; i < noteAmt; i++) {
    if((i % 2) == 0 ) {
      red_led_on();
    }
    else {
      green_led_on();
    }
    buzzer_set_period(1000000 / notes[i]);
    int dur = tempo[i];
    while(dur--) {
	__delay_cycles(10000);
    }
    leds_off();
  }
  // reset the buzzer state
  buzzer_set_period(0);                 // turn off buzzer CHANGED FROM bk TO 0
  leds_off();                           // endsure leds are off
}

void oot() { // Ocarina of Time Theme
  // notes for song (store in flash)
  const int notes[] = {F2, F3, A3, D4, E4, C2, G3, B3, D4, E4, F2, C3, F3, A3, D4, E4, C2, G2, E3, B3, D4, E4, D5, D6, F2, C3, F3, A3, D4};
  // tempo for each note (store in flash)
  const int tempo[] ={1276, 300, 300, 300, 1276, 1276, 300, 300, 300, 1276, 1276, 600, 500, 500, 500, 1276, 600, 500, 500, 500, 400, 500, 500, 1276, 600, 300, 300, 300, 300, 600, 1276, 300, 300};
  // play the song
  int noteAmt = sizeof(notes)/sizeof(notes[0]);
  playTune(notes,tempo,noteAmt);
  // reset the buzzer state
  buzzer_set_period(0); // CHANGED FROM bk TO 0
}
