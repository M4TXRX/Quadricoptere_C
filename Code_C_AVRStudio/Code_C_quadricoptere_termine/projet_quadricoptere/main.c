/*
Quad-X
====================================\
			[AVANT]					|
									|
       M1(CW)        M2(CCW)		|
	 	   \   __   /				|
            \ /  \ /				|
[GAUCHE]     |    |		  [DROITE]	|
            / ---- \				|
 		   /        \				|
 	   M4(CCW)    	 M3(CW)			|
									|
			[ARRIERE]				|
====================================/
    TERMINAL:
    9600 baud - Even Parity - 8bit of Data - 1 Stop Bit
    Baud is set with MYUBRR var.
*/
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <avr/sleep.h>

#include <util/delay.h>

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#include "interruptions_init.h"
#include "timers_init.h"
#include "main.h"
#include "annexe.h"
#include "vars.h"
#include "asservissement.h"
#include "asserv_haut.h"
#include "voltmetre.h"
#include "centrale.h"

	//Global Vars
struct vars_t v;
/*######################################################*/
int main(){
    //To use printf and getchar ...
//	stdout=&uart_str;
	//stdin=&uart_str;

    //INIT all function :
	init_port();
	init_interruptions ();
	init_uart();
	init_usart_centrale();
	
	init_vars(&v);
//	gyros_init();
	//accels_init();
	init_timer1();
	init_timer3();
	init_pwm_m();
	
	init_motors_pids();
	
	init_asserv_haut_pids();//Fonction d'initialisation sur l'asservissement en hauteur
	
	reset_asserv_haut_pids();//Fonction de reset
	
	//printf("printf success ! \n");

	//v.FlagArmed = 0;
	v.cpt_asser = 0;

	
//	printf("Avant");
//	cli_led1 (10);
	//printf(" Boucle\n");
	do{
/*		if(flag_int_volt == 1){
			read_volt();
		}
*/		

		/*v.RxChannels[0] = 0;
		v.RxChannels[1] = 0;
		v.RxChannels[2] = 0;
		v.RxChannels[3] = 0;*/
	

		ConvertRxChannels(&v);

		//v.FlagArmed = 0;
		//v.AsserHaut = 0;

		//gyros_read_values_raw_cal(&v);
		centrale_read_angls(&v);
		centrale_read_gyro(&v);	
		
		/*if (v.GyroX > 10) {
			set_led1();
		}
		else {
			reset_led1();
		}*/


		/*printf("Temps a l'etat haut =%lu \n", temps_etat_haut_US);
		printf("Angle de roulis = %d \n", v.AngleX);
		printf("Angle de tangage = %d \n", v.AngleY);
		printf("Angle de lacet = %d \n", v.AngleZ);
		_delay_ms(500);*/


//		altitude=temps_etat_haut_US*(float)(5/58000);

				
		/*En commentaire pour test*/
		
		/*if (v.AngleX > 10) {
			set_led1();
		}
		else {
			reset_led1();
		}*/
		
		//printf("Boucle\n");		
		if (v.FlagArmed == 1){//Si le module est armé
			if (v.FlagCollectiveZero == 1){
				v.computedCollective = 0;
				init_motors_pids();
				init_asserv_haut_pids();

				reset_motors_pids();
				reset_asserv_haut_pids();
			}
			
			if (flag_asser==1) {
				v.cpt_asser++;
				if (v.AsserHaut == 1){
					if (v.cpt_asser >= 5){
						//set_led2();
						v.computedCollective = asserv_alt(&v);
						//printf("cpt_asser \n");
						v.cpt_asser = 0;
				//printf("printf de partout \n");
						}
				}
				else {
					v.computedCollective = v.RxInCollective;
					reset_led2();
					//printf("ICI 2 \n");
				}
				
				computedata_motors(&v);
				output_motors(&v);
		
				//rajouter camera
				//printf("MotorOut1 : %d \n", v.MotorOut1);
				
				flag_asser = 0;//Pour le prochain passage
			}
		}
	}while(1);

	return 0;
}

//Interruption telecommande
ISR( INT7_vect )
{
	static int i_PPM=0;
	int val_temp;

	val_temp = TCNT1;

	// Ici TCNT1 contient la valeur courante de TCNT1 sur Front Descendant de la PPM1 :
	v.RxChannels[i_PPM] = (val_temp - val_TCNT1_fd_PPM) >> 1;
	if (i_PPM == 0) {
		v.RxChannels[i_PPM] -= 1100;
		if (v.RxChannels[i_PPM] < 0)
			v.RxChannels[i_PPM] = 0;
	}
	else if (i_PPM < 8) {
		v.RxChannels[i_PPM] -= 1500;
	}
	val_TCNT1_fd_PPM = val_temp;

	if (v.RxChannels[i_PPM]> 4000){ // pour 4ms<->4000
		i_PPM=0;
	}
	else{
		i_PPM++;
	}
}
