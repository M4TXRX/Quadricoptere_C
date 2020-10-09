//interruptions_routines.c
/* Created: 15/03/2012 16:31:28 */

/** ROUTINES D'INTERRUPTION **/

#include "interruptions_init.h"
#include "vars.h"
#include "main.h"



// Interruption capteur ultrason
ISR(INT6_vect)
{
	val_timer1 = diz_timer1*65536 + TCNT1;
	
	if (PINE&(1<<PINE6)) { //rising
		front_montant_US = val_timer1;
	}
	else { //falling
		temps_etat_haut_US = (val_timer1 - front_montant_US); // / 2;
	}

}

// interruption pour scruter le gyro et récuperer les données à traiter

ISR( TIMER1_OVF_vect ){ //Timer 1
	diz_timer1++;
}
ISR( TIMER3_COMPA_vect ){//Timer 0 - Sert aussi à définir Te (Fréquence d'échantillonage)
	flag_asser = 1;
}

ISR(PCINT0_vect){
	unsigned long int temp;
	if ( (PINB&(1<<PINB0)) == 0) {
		temp = TCNT1 + ((unsigned long int)diz_timer1 << 16);
		//printf("t%lu ", temp);
		diff_volt = (temp - last_value_volt)/2;
		last_value_volt = temp;
		flag_int_volt = 1;
	}
}