#ifndef buzzer_included
#define buzzer_included

// Function prototypes
void buzzer_init();                      // Initializes the buzzer hardware
void buzzer_set_period(short cycles);    // Sets the period of the buzzer to produce different tones
void oot();                              // Plays the chorus of Jingle Bells
void tp();                               // Placeholder for an additional theme (currently not used)

#endif // buzzer_included
