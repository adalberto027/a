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
    // Alternar LEDs según el rango de las notas
    if (notes[i] < 500) {         // Notas graves
      red_led_on();
    } else if (notes[i] < 1000) { // Notas medias
      green_led_on();
    } else {                      // Notas agudas
      red_led_on();
      green_led_on();             // Ambos LEDs encienden para notas altas
    }
    
    // Configurar el buzzer con la frecuencia de la nota
    buzzer_set_period(1000000 / notes[i]);

    // Controlar la duración de la nota
    int dur = tempo[i];
    while (dur--) {
      __delay_cycles(10000);
    }
    
    // Apagar LEDs entre notas
    leds_off();
  }

  // Resetear el estado del buzzer y los LEDs
  buzzer_set_period(0); // Apagar el buzzer
  leds_off();           // Asegurar que los LEDs estén apagados
}


void oot() { // Futuristic Theme
  // Notas para la nueva melodía (en Hz)
  const int notes[] = {C4, E4, G4, B4, C5, G4, E4, C4, D4, F4, A4, C5};
  
  // Tempo para cada nota (duración en milisegundos)
  const int tempo[] = {400, 400, 600, 800, 500, 300, 300, 400, 400, 400, 600, 800};
  
  // Calcular la cantidad de notas
  int noteAmt = sizeof(notes) / sizeof(notes[0]);

  // Reproducir la melodía con efectos de LEDs
  for (int i = 0; i < noteAmt; i++) {
    // Efectos LED según el índice de la nota
    if (i % 4 == 0) {           // Notas clave
      red_led_on();
    } else if (i % 4 == 1) {    // Notas de transición
      green_led_on();
    } else if (i % 4 == 2) {    // Notas con énfasis
      red_led_on();
      green_led_on();           // Ambos LEDs encienden
    } else {
      leds_off();               // Pausa visual
    }

    // Configurar el buzzer con la frecuencia de la nota actual
    buzzer_set_period(1000000 / notes[i]);

    // Controlar la duración de la nota
    int dur = tempo[i];
    while (dur--) {
      __delay_cycles(5000);     // Ajustar la duración del ciclo
      if (dur < tempo[i] / 2) { // Apagar LEDs a la mitad de la duración
        leds_off();
      }
    }
  }

  // Apagar el buzzer y los LEDs al finalizar
  buzzer_set_period(0);
  leds_off();
}
