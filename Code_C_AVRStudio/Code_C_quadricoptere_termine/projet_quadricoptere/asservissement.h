/*
 * asservissement.h
*/
#ifndef ASSERVISSEMENT_H_
#define ASSERVISSEMENT_H_

#include "pid.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include "vars.h"
/*
void asser_h (struct vars_t *v, volatile unsigned int consigne[]);
void asser_att(struct vars_t *v, volatile unsigned int consigne[]);
*/

void output_motors(struct vars_t *v);
void init_motors_pids();
void reset_motors_pids() ;
void computedata_motors(struct vars_t *v);

#define MAX_MOTORS   1000

//Grâce à de nombreux test sur le comportement du quadricoptère on trouve les coefficient suivant

#define K_ROLL_P     0.5	 //Amélioration du coefficient P de roulis 
#define K_ROLL_I     0.00
#define K_ROLL_D     0.00

#define K_PITCH_P    0.5 //Amélioration du coefficient P de tangage grâce à de nombreux tests
#define K_PITCH_I    0.00
#define K_PITCH_D    0.00

#define K_YAW_P      0.01
#define K_YAW_I      0.00
#define K_YAW_D      0.00


//Pour la vitesse angulaire
#define K_ROLL_P2     0.01	 //Amélioration du coefficient P de roulis
#define K_ROLL_I2     0.00
#define K_ROLL_D2     0.00

#define K_PITCH_P2    0.01	//Amélioration du coefficient P de tangage grâce à de nombreux tests
#define K_PITCH_I2    0.00
#define K_PITCH_D2    0.00

#define K_YAW_P2      0.1
#define K_YAW_I2      0.0
#define K_YAW_D2      0.00

#define LOWVALUE     20

volatile unsigned char fin;
struct PID_DATA pidData_roll;
struct PID_DATA pidData_pitch;
struct PID_DATA pidData_yaw;
struct PID_DATA pidData_roll2;
struct PID_DATA pidData_pitch2;
struct PID_DATA pidData_yaw2;

#endif /* ASSERVISSEMENT_H_ */

//Voie 0, premier signal : Monter/descendre
//Voie 1,inclinaison latéralgauche/droite (roll)
//Voie 2, inclinaison avancer reculer
//Voie 3, yawn

