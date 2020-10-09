/*
 * asservissement.c
 * Created: 27/11/2013
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <avr/sleep.h>

#include <util/delay.h>
#include <util/twi.h>

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
#include "vars.h"
#include "pid.h"

//Voie 0, premier signal : Monter/descendre
//Voie 1,inclinaison latéralgauche/droite (roll)
//Voie 2, inclinaison avancer reculer
//Voie 3, yawn

void output_motors(struct vars_t *v){
	//Saturation en O % :
	if (v->MotorOut1<0) {v->MotorOut1=0;}
	if (v->MotorOut2<0) {v->MotorOut2=0;}
	if (v->MotorOut3<0) {v->MotorOut3=0;}
	if (v->MotorOut4<0) {v->MotorOut4=0;}
		
	//Saturation en 100 % :
	if (v->MotorOut1>1000) {v->MotorOut1=1000;}
	if (v->MotorOut2>1000) {v->MotorOut2=1000;}
	if (v->MotorOut3>1000) {v->MotorOut3=1000;}
	if (v->MotorOut4>1000) {v->MotorOut4=1000;}
	
	//Si les manches indiquent les moteurs à zeros, alors :
	if (v->FlagCollectiveZero==1){
		v->MotorOut1=0;
		v->MotorOut2=0;
		v->MotorOut3=0;
		v->MotorOut4=0;
	}
	
	//Scale :
	v->MotorOut1+=1000;
	v->MotorOut2+=1000;
	v->MotorOut3+=1000;
	v->MotorOut4+=1000;
	
	//printf("MotorOut1 = %d, MotorOut2 = %d, MotorOut3 = %d, MotorOut4 = %d\r",v->MotorOut1,v->MotorOut2,v->MotorOut3,v->MotorOut4);
	//Sortie finale :
	OCR4A = v->MotorOut1; //M1
	OCR4B = v->MotorOut2; //M2
	OCR4C = v->MotorOut3; //M3
	OCR5A = v->MotorOut4; //M4
}

void init_motors_pids() {
	pid_Init(K_ROLL_P * SCALING_FACTOR, K_ROLL_I * SCALING_FACTOR , K_ROLL_D * SCALING_FACTOR , &pidData_roll);
	pid_Init(K_PITCH_P * SCALING_FACTOR, K_PITCH_I * SCALING_FACTOR , K_PITCH_D * SCALING_FACTOR , &pidData_pitch);
	pid_Init(K_YAW_P * SCALING_FACTOR, K_YAW_I * SCALING_FACTOR , K_YAW_D * SCALING_FACTOR , &pidData_yaw);
		
	pid_Init(K_ROLL_P2 * SCALING_FACTOR, K_ROLL_I2 * SCALING_FACTOR , K_ROLL_D2 * SCALING_FACTOR , &pidData_roll2);
	pid_Init(K_PITCH_P2 * SCALING_FACTOR, K_PITCH_I2 * SCALING_FACTOR , K_PITCH_D2 * SCALING_FACTOR , &pidData_pitch2);
	pid_Init(K_YAW_P2 * SCALING_FACTOR, K_YAW_I2 * SCALING_FACTOR , K_YAW_D2 * SCALING_FACTOR , &pidData_yaw2);
}

void reset_motors_pids() {
	pid_Reset_Integrator(&pidData_roll);
	pid_Reset_Integrator(&pidData_pitch);
	pid_Reset_Integrator(&pidData_yaw);
	
	pid_Reset_Integrator(&pidData_roll2);
	pid_Reset_Integrator(&pidData_pitch2);
	pid_Reset_Integrator(&pidData_yaw2);
}


void computedata_motors(struct vars_t *v){
// Fonction pour calculer les valeurs à mettre sur les moteurs en fonction de la consigne
		int y, y1;
		int z;
		int col;
		
		//saturation si le collectif est trop elevé
		col = v->computedCollective;
		
		if (col > MAX_MOTORS) {
			col = MAX_MOTORS;
		}
		// start mixing
		v->MotorOut1 = col;
		v->MotorOut2 = col;
		v->MotorOut3 = col;
		v->MotorOut4 = col;

		// Calculate roll command output

		y1 = (v->RxInRoll_Angle - v->AngleX)*8;
//		y1 = pid_Controller(v->RxInRoll_Angle, v->AngleX, &pidData_roll);
		y = pid_Controller(y1, v->GyroX, &pidData_roll2);
		//y = pid_Controller(v->RxInRoll_Angle, v->GyroX, &pidData_roll);
		
		//z = pid_Controller(v->y*(RxInRoll_Angle-, v->GyroX, &pidData_roll);

		// Add roll command output to motor 2 and 3
		v->MotorOut1 += y;
		v->MotorOut2 -= y;
		v->MotorOut3 -= y;
		v->MotorOut4 += y;

		// Calculate pitch command output
		
		y1 = (v->RxInPitch_Angle - v->AngleY)*8;
//		y1 = pid_Controller(v->RxInPitch_Angle, v->AngleY, &pidData_pitch);
		y = pid_Controller(y1, v->GyroY, &pidData_pitch2);
		//y = pid_Controller(v->RxInPitch_Angle, v->GyroY, &pidData_pitch);

		// Add Pitch command output to motor 1 and 4
		v->MotorOut1 += y;
		v->MotorOut2 += y;
		v->MotorOut3 -= y;
		v->MotorOut4 -= y;

		// Calculate Yaw command output
		
//		y1 = (-v->RxInYaw_Angle - v->AngleZ)*8;
//		y1 = pid_Controller(-v->RxInYaw_Angle, v->AngleZ, &pidData_yaw);
		y = pid_Controller(-v->RxInYaw_Angle, v->GyroZ, &pidData_yaw2);
								
		// limit Yaw command to -YawLimit and YawLimit
		//if (y < -(v->YawLimit)){y = -(v->YawLimit);}
		//if (y > v->YawLimit){y = v->YawLimit;}
		
		// Add Yaw command output to motor 1, 2, 3 and 4
		v->MotorOut1 += y;
		v->MotorOut2 -= y;
		v->MotorOut3 += y;
		v->MotorOut4 -= y;

		if (v->MotorOut1 < LOWVALUE)
			v->MotorOut1 = LOWVALUE;
		if (v->MotorOut2 < LOWVALUE)
			v->MotorOut2 = LOWVALUE;
		if (v->MotorOut3 < LOWVALUE)
			v->MotorOut3 = LOWVALUE;
		if (v->MotorOut4 < LOWVALUE)
			v->MotorOut4 = LOWVALUE;	
}


