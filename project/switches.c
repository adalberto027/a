#include <msp430.h>
#include "switches.h"
#include "led.h"
#include "statemachines.h"

// flag that indicates if a switch is pressed
char switch_state_down;

// initializes switches
void switch_init() {
  P2REN |= SWITCHES;                  // enables pull-up/pull-down resistors for switches
  P2IE |= SWITCHES;                   // enables interrupts for switches
  P2OUT |= SWITCHES;                  // configures pull-up resistors
  P2DIR &= ~SWITCHES;                 // sets switches as input
  switch_update_interrupt_sense();    // initializes interrupt sense for switches
  switch_interrupt_handler();         // handles any initial switch state
  led_update();                       // updates the led status
}

// initializes interrupt sense for switches
char switch_update_interrupt_sense() {
  char p2val = P2IN;              // store the input state
  P2IES |= (p2val & SWITCHES);    // if switch up, sense down
  P2IES &= (p2val | ~SWITCHES);   // if switch down, sense up
  return p2val;
}

// handles any initial switch state
void switch_interrupt_handler() {
    char p2val = switch_update_interrupt_sense();       // find the current state of the switches
    // check the state of SW1, SW2, SW3, SW4
    char button_1 = (p2val & SW1) ? 0 : SW1;            // if SW1 is not pressed (1), set char to 0
    char button_2 = (p2val & SW2) ? 0 : SW2;            // if SW2 is pressed (0), set char to SW2
    char button_3 = (p2val & SW3) ? 0 : SW3;
    char button_4 = (p2val & SW4) ? 0 : SW4;
    
    // go to appropriate state based on button pressed
    if (button_1) {
    next_state(1);
    switch_state_down = 1;
    } 
    else if (button_2) {
      next_state(2);
      switch_state_down = 1;
    } 
    else if (button_3) {
      next_state(3);
      switch_state_down = 1;
    } 
    else if (button_4) {
      next_state(4);
      switch_state_down = 1;
    }
}
