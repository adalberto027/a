#ifndef buzzer_included
#define buzzer_included

// Function prototypes
void buzzer_init();                      // Initializes the buzzer hardware
void buzzer_set_period(short cycles);    // Sets the period of the buzzer to produce different tones
void oot();                              // Jingle Bells chorus
void tp();                               // Twilight Princess Theme (commented out, not used)

#endif // buzzer_included
