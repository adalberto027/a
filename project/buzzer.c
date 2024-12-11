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

void playTune(const int *notes, const int *tempo, int noteAmt) {
  for (int i = 0; i < noteAmt; i++) {
    // Alternar LEDs según las notas para un efecto navideño clásico
    if (i % 2 == 0) {
      red_led_on();  // Enciende LED rojo
    } else {
      green_led_on();  // Enciende LED verde
    }

    // Configurar el buzzer con la frecuencia de la nota
    buzzer_set_period(1000000 / notes[i]);

    // Duración de cada nota con ritmo navideño
    int dur = tempo[i];
    while (dur--) {
      __delay_cycles(8000);  // Mantener un ritmo reconocible
    }

    // Pausar LEDs brevemente entre notas para un parpadeo suave
    leds_off();
    __delay_cycles(50000);
  }

  // Resetear el estado del buzzer y los LEDs
  buzzer_set_period(0); // Apagar el buzzer
  leds_off();           // Asegurar que los LEDs estén apagados
}

void oot() { // Jingle Bells Theme
  // Notas para "Jingle Bells" (en Hz)
  const int notes[] = {
    E4, E4, E4, E4, E4, E4, E4, G4, C4, D4, E4,  // Dashing through the snow...
    F4, F4, F4, F4, F4, E4, E4, E4, E4, D4, D4, E4, D4, G4  // In a one-horse open sleigh...
  };
  
  // Tempo para cada nota (en milisegundos)
  const int tempo[] = {
    400, 400, 800, 400, 400, 800, 400, 400, 400, 400, 800,  // Dashing through the snow...
    400, 400, 800, 400, 400, 400, 400, 400, 800, 400, 400, 400, 400, 800  // In a one-horse open sleigh...
  };

  // Calcular la cantidad de notas
  int noteAmt = sizeof(notes) / sizeof(notes[0]);

  // Reproducir la melodía
  playTune(notes, tempo, noteAmt);
}

