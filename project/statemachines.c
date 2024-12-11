#include <msp430.h>
#include "led.h"
#include "switches.h"
#include "statemachines.h"
#include "buzzer.h"

#include "lcdutils.h"
#include "lcddraw.h"
#include "song_images.h"

void next_state(int state) {
  leds_off();
  
  switch(state) {
  case 1:
    led_flash(3);
    leds_off();
    red_led_on();
    //drawZeldasLullaby();
    drawDefault(COLOR_GRAY);
    //zeldas_lullaby();
    oot(); // added
    leds_off();
    break;
  case 2:
    led_flash(3);
    leds_off();
    red_led_on();
    //drawOOT();
    drawDefault(COLOR_BLUE);
    oot();
    leds_off();
    break;
  case 3:
    led_flash(3);
    leds_off();
    red_led_on();
    //drawSOH();
    drawDefault(COLOR_PINK);
    //soh();
    oot(); // added
    leds_off();
    break;
  case 4:
    led_flash(3);
    leds_off();
    red_led_on();
    //drawTP();
    drawDefault(COLOR_ORANGE);
    //tp();
    oot(); // added
    leds_off();
    break;
  default:
    green_led_on();
    break;
  }
  // turn on the green led to indicate that the MSP ready for the next step.
  green_led_on();
  drawDefault(COLOR_WHITE);
}
