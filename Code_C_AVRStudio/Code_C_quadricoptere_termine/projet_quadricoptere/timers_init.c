/** TIMERS **/

#include "timers_init.h"
#include <util/delay.h>

void init_pwm_m(){
    short unsigned int valeur_init;	 // init des PWM à 0%

	PORTH |= (1<<M1)|(1<<M2)|(1<<M3);
	PORTL |= (1<<M4)|(1<<M5)|(1<<M6);

	//TIMER 4 :
	// Clear OC4A/B on Compare Match when up-counting. Set OC4A/B on Compare Match when down-counting.
	//Mode PWM phase correct (WGM)
	TCCR4A = (1<<COM4A1)|(1<<COM4B1)|(1<<COM4C1)|(2<<WGM40);
	TCCR4B = (2<<WGM42)|(1<<CS41); // prediv : 8
	ICR4 = 10000;

	// TIMER 5 :
	// PWM, Phase Correct avec TOP = 0xFF = 255
	TCCR5A = (1<<COM5A1)|(1<<COM5B1)|(1<<COM5C1)|(2<<WGM50);
	TCCR5B = (2<<WGM52)|(1<<CS51); // prediv : 8
	ICR5 = 10000;

	valeur_init = 1000;//Valeur max : 2000

	OCR4A = valeur_init; //M1
	OCR4B = valeur_init; //M2
	OCR4C = valeur_init; //M3
	OCR5A = valeur_init; //M4
}

void init_timer1(){
//Pour transformer en valeur numérique les valeurs de la PPM
	TCCR1A = 0; //mode normal
	TCCR1B = (2<<CS10); // prediv : 8
	TIFR1  = (1<<TOV1); // remise a 0 du flag
	TIMSK1 = (1<<TOIE1); // génère une interruption sur overflow
}


void init_timer3(){
//Ce timer sert à avoir un échantillonage précis et périodique de 20 ms
	TCCR3A = 0;
	TCCR3B = (1<<WGM32) | (2<<CS00); // mode CTC prediv : 8
	TIMSK3 = (1<<OCIE3A); //génère une interruption sur overflow
	OCR3A  =  40000; //fréquence de 50Hz ( T = 20 ms )
}
