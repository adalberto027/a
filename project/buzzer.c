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
    // Alternar LEDs para un efecto navideño
    if (i % 2 == 0) {
      red_led_on();  // Enciende LED rojo para notas pares
    } else {
      green_led_on();  // Enciende LED verde para notas impares
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

void oot() { // Jingle Bells Theme
  // Notas para la melodía navideña (en Hz)
  const int notes[] = {E4, E4, E4, E4, E4, E4, E4, G4, C4, D4, E4,
                       F4, F4, F4, F4, F4, E4, E4, E4, E4, D4, D4, E4, D4, G4};
  
  // Tempo para cada nota (duración en milisegundos)
  const int tempo[] = {400, 400, 800, 400, 400, 800, 400, 400, 400, 400, 800,
                       400, 400, 800, 400, 400, 400, 400, 400, 800, 400, 400, 400, 400, 800};
  
  // Calcular la cantidad de notas
  int noteAmt = sizeof(notes) / sizeof(notes[0]);

  // Reproducir la melodía con efectos LED navideños
  for (int i = 0; i < noteAmt; i++) {
    // Efectos LED según el índice de la nota
    if (i % 3 == 0) {           // Notas clave
      red_led_on();
    } else if (i % 3 == 1) {    // Notas de transición
      green_led_on();
    } else {                    // Notas finales del ciclo
      red_led_on();
      green_led_on();           // Ambos LEDs encienden
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

