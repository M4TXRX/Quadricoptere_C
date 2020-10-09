/*This file has been prepared for Doxygen automatic documentation generation.*/
/*! \file *********************************************************************
 *
 * \brief Asservissement en Hauteur.
 *	
 * Fonctions permettant d'utiliser le sonar pour asservir en hauteur
 * Il ne faut pas oublier d'utiliser un timer pour lire les données
 * On lit les valeurs de la hauteur dans la variable v.alt ...
 * 
 * - File:               asserv_haut.h
 *
 * \author               Atmel Corporation: http://www.atmel.com \n
 *                       Support email: avr@atmel.com
 *
 * $Name$
 * $Revision: 2 $
 * $RCSfile$
 * $Date:  12.03.2014 à 14:05 $
 *****************************************************************************/



#ifndef ASSERV_HAUT_H_
#define ASSERV_HAUT_H_

#include "pid.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include "vars.h"

#define K_ALT_P		 0.4
#define K_ALT_I		 0.001
#define K_ALT_D		 0.00

#define LOWVALUE     20
#define GAINVITESSE  4

// height = 1000 -> 5m. vitesse max 0.5m/s -> 100/s
#define VIT_MAX		100 // s-1
#define VIT_MIN		-75 // s-1
#define CMD_MOTEUR_MAX		360
#define CMD_MOTEUR_MIN		-240
#define CMD_MOTEUR_NOMINAL	300

struct PID_DATA pidData_alt;

void init_asserv_haut_pids();//Fonction d'initialisation
void reset_asserv_haut_pids();//Fonction de reset
int asserv_alt(struct vars_t *v);//Algorithme d'asservissement en hauteur

#endif /* ASSERV_HAUT_H_ */
