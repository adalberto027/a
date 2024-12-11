#ifndef switches_included
#define switches_included

// define references to switches
#define SW1 BIT0 // switch1 is connected to P2.0 BIT0
#define SW2 BIT1 // switch2 is connected to P2.1 BIT1
#define SW3 BIT2 // switch3 is connected to P2.2 BIT2
#define SW4 BIT3 // switch4 is connected to P2.3 BIT3

#define SWITCHES (SW1 | SW2 | SW3 | SW4) // defines switches to bits

// function prototypes
void switch_init();                       // initializes the switches
void switch_interrupt_handler();          // handles interruptions
char switch_update_interrupt_sense();     // updates the interruptions sense

// flag to check switch states
extern char switch_state_down;            // effectively booleans

#endif
