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
    // Efecto LED suave y constante
    if (i % 2 == 0) {
      red_led_on();  // Enciende LED rojo para notas pares
    } else {
      green_led_on();  // Enciende LED verde para notas impares
    }

    // Configurar el buzzer con la frecuencia de la nota
    buzzer_set_period(1000000 / notes[i]);

    // Duración relajada para mantener el ritmo navideño
    int dur = tempo[i];
    while (dur--) {
      __delay_cycles(8000);  // Mantener un tempo tranquilo
    }

    // Apagar LEDs entre notas para un efecto de parpadeo sutil
    leds_off();
    __delay_cycles(100000);  // Pausa breve entre notas para suavidad
  }

  // Resetear el estado del buzzer y los LEDs
  buzzer_set_period(0); // Apagar el buzzer
  leds_off();           // Asegurar que los LEDs estén apagados
}

void oot() { // Silent Night Theme
  // Notas para una melodía navideña clásica (en Hz)
  const int notes[] = {G4, A4, G4, E4, G4, A4, B4, C5, B4, A4, G4, E4, G4, A4, G4};
  
  // Tempo para cada nota (duración en milisegundos)
  const int tempo[] = {600, 600, 800, 600, 600, 600, 800, 800, 800, 600, 600, 800, 600, 600, 1000};
  
  // Calcular la cantidad de notas
  int noteAmt = sizeof(notes) / sizeof(notes[0]);

  // Reproducir la melodía
  playTune(notes, tempo, noteAmt);
}

