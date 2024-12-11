#include <msp430.h>
#include "statemachines.h"


void __interrupt_vec(WDT_VECTOR) WDT() { // WatchDog Timer
  // counter to keep track of how many times interrupts have been triggered
  static char blink_count = 0;
  // increment the counter by 1, if the counter reaches 125, reset it
  if (++blink_count == 125) {
    blink_count = 0;
    }
}
