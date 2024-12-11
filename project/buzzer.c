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
    // Efecto de luces navideñas alternando LEDs
    if (i % 2 == 0) {
      red_led_on();  // Enciende LED rojo
    } else {
      green_led_on();  // Enciende LED verde
    }

    // Configurar el buzzer para la nota actual
    buzzer_set_period(1000000 / notes[i]);

    // Reproducir la nota con un ritmo clásico navideño
    int dur = tempo[i];
    while (dur--) {
      __delay_cycles(8000);  // Tiempo para cada nota
    }

    // Apagar LEDs brevemente entre notas
    leds_off();
    __delay_cycles(50000);  // Breve pausa para transición suave
  }

  // Resetear el buzzer y apagar los LEDs al finalizar
  buzzer_set_period(0);
  leds_off();
}

void oot() { // Jingle Bells - Estribillo
  // Notas para el estribillo de "Jingle Bells" (en Hz)
  const int notes[] = {
    E4, E4, E4,  // Jingle bells
    E4, E4, E4,  // Jingle bells
    E4, G4, C4, D4, E4,  // Jingle all the way!
    F4, F4, F4, F4, F4, E4, E4, E4,  // Oh what fun it is to ride
    E4, D4, D4, E4, D4, G4  // In a one-horse open sleigh!
  };

  // Tempo para cada nota (en milisegundos)
  const int tempo[] = {
    400, 400, 800,  // Jingle bells
    400, 400, 800,  // Jingle bells
    400, 400, 400, 400, 800,  // Jingle all the way!
    400, 400, 800, 400, 400, 400, 400, 800,  // Oh what fun it is to ride
    400, 400, 400, 400, 400, 800  // In a one-horse open sleigh!
  };

  // Calcular la cantidad de notas
  int noteAmt = sizeof(notes) / sizeof(notes[0]);

  // Reproducir la melodía
  playTune(notes, tempo, noteAmt);
}
