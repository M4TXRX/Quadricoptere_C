/*** INTERRUPTIONS signaux PPM de la télécommande ***/

#include "interruptions_init.h"

void init_interruptions(){
	//INT7 is used for the telecomande
	//INT6 is used for the sonar
	//INT0 for the voltmeter

	EICRB = (1<<ISC61)|(1<<ISC71);  // Falling Edge for INT7 and for INT6 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	EIMSK = (1<<INT6)|(1<<INT7);    // Autorisation des interruption(s) (INT1 et) INT0 (p72)														*/

    PCICR = (1<<PCIE0); //Enable interrupt PCINT(0-7), any logical change
    PCMSK0 = (1<<PCINT0); //Enable interrupt on PCINT0

	sei(); // validation globale des interruptions
}
