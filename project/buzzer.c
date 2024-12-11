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

//void zeldas_lullaby() { // Zelda's Lullaby
  // notes for song (store in flash)
  //const int notes[] = {C3, G3, E4, C3, A3, Fsharp4, C3, G3, E4, C3, A3, Fsharp4, C3, B4, G3};
  // tempo for each note (store in flash)
  //const int tempo[] = {500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 750, 250, 500};
  // play the song
  //int noteAmt = sizeof(notes)/sizeof(notes[0]);
  //playTune(notes,tempo,noteAmt);
  // reset the buzzer state
  //buzzer_set_period(0); // CHANGED FROM bk TO 0
//}

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

//void soh() { // Song of Healing
  // notes for song (store in flash)
  //const int notes[] = {F3, B4, C4, A4, C4, F4, C4, F3, B4, C4, A4, C4, F4, C4, F3, B4, C4, A4, E4, D4, C4, E4, E3, B3, F3, B4, C4, A4, C4, F4, C4, F3, B4, C4, A4, C4, F4, C4, F3, B4, C4};
  // tempo for each note (store in flash)
  //const int tempo[] = {800, 800, 600, 600, 600, 800, 600, 800, 800, 600, 600, 600, 800, 800, 800, 800, 600, 600, 600, 800, 800, 800, 900, 900, 900, 800, 800, 600, 600, 600, 800, 600, 800, 800, 600, 600, 600, 800, 600, 800, 800, 600}; 
  //const int notes[] = {F3, B4, C4, A4, C4, F4, C4, F3, B4, C4, A4, C4, F4, C4, F3, B4, C4, A4, E4, D4, C4, E4, E3};
//const int tempo[] = {800, 800, 600, 600, 600, 800, 600, 800, 800, 600, 600, 600, 800, 800, 800, 800, 600, 600, 600, 800, 800, 800, 900};
  // play the song
  //int noteAmt = sizeof(notes)/sizeof(notes[0]);
  //playTune(notes,tempo,noteAmt);
  // reset the buzzer state
  //buzzer_set_period(0); // CHANGED FROM bk TO 0
//}

//void tp() { // Twilight Princess Theme
  // notes for the song (store in flash)
  //const int notes[] = {D3, E3, F3, A3, C4, E4, D3, E3, F3, A3, C4, E4, D3, E3, F3, A3, C4, E4, G4, E4, C4, A3, F3, E3, A4, F5, E5, C5, B4, A4, G4, B4, D6, A6, E6, D6};
  // tempo for each note (store in flash)
  //const int tempo[] = {400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 300, 300, 300, 300, 300, 300, 300, 300, 300, 300, 300, 300, 500, 400, 400, 400, 400, 400, 400, 400, 300, 300, 300, 300};
  //const int notes[] = {D3, E3, F3, A3, C4, E4, D3, E3, F3, A3, C4, E4, D3, E3, F3, A3, C4, E4, G4, E4, C4, A3, F3, E3, A4, F5, E5, C5, B4, A4};
  //const int tempo[] = {400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 300, 300, 300, 300, 300, 300, 300, 300, 300, 300, 300, 300, 500, 400, 400, 400, 400, 400};
  // play the song
  //int noteAmt = sizeof(notes)/sizeof(notes[0]);
  //playTune(notes,tempo,noteAmt);
  // reset the buzzer state
  //buzzer_set_period(0); // CHANGED FROM bk TO 0
//}
