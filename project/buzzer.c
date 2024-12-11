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
    // Efecto dinámico de LEDs, simulando luces de un pino de Navidad
    if ((i % 4) == 0) {
      red_led_on();  // Enciende LED rojo
    } else if ((i % 4) == 1) {
      green_led_on();  // Enciende LED verde
    } else if ((i % 4) == 2) {
      red_led_on();
      green_led_on();  // Ambos LEDs para dar un efecto brillante
    } else {
      leds_off();  // Pausa visual
    }

    // Configurar el buzzer con la frecuencia de la nota
    buzzer_set_period(1000000 / notes[i]);

    // Reducir la duración de cada nota para hacerlo más movido
    int dur = tempo[i] / 2;
    while (dur--) {
      __delay_cycles(5000);  // Hacer las notas más rápidas
    }

    // Apagar LEDs entre notas
    leds_off();
  }

  // Resetear el estado del buzzer y los LEDs
  buzzer_set_period(0);
  leds_off();
}

void oot() { // Christmas Tree Theme
  // Notas para una melodía navideña rápida (en Hz)
  const int notes[] = {E4, G4, A4, G4, E4, E4, F4, G4, F4, E4, D4, E4, F4, G4, A4, B4, A4, G4, E4};
  
  // Tempo para cada nota (duración en milisegundos)
  const int tempo[] = {300, 300, 300, 300, 300, 200, 200, 300, 300, 200, 200, 300, 300, 300, 200, 300, 300, 300, 400};
  
  // Calcular la cantidad de notas
  int noteAmt = sizeof(notes) / sizeof(notes[0]);

  // Reproducir la melodía
  playTune(notes, tempo, noteAmt);
}

