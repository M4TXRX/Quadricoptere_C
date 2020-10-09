

/*This file has been prepared for Doxygen automatic documentation generation.*/
/*! \file *********************************************************************
 *
 * \brief Algo d'asservissement en hauteur.
 *
 * Asservissement en hauteur avec le sonar
 *
 * - File:               asserv_haut.c
 * - Compiler:           IAR EWAAVR 4.11A
 * - Supported devices:  All AVR devices can be used.
 * - AppNote:            AVR221 - Discrete PID controller
 *
 * \author               Atmel Corporation: http://www.atmel.com \n
 *                       Support email: avr@atmel.com
 *
 * $Name$
 * $Revision: 1 $
 * $RCSfile$
 * $Date: 12.03.2014 $
 *****************************************************************************/


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

#include "asserv_haut.h"

/*! \brief Initialisation du PID.
 *
 *  Initialise les variables pour le PID servant pour l'asservissement en hauteur
 *
 */
void init_asserv_haut_pids(){
	pid_Init(K_ALT_P * SCALING_FACTOR, K_ALT_I * SCALING_FACTOR, K_ALT_D * SCALING_FACTOR, &pidData_alt);
}

/*! \brief Réinitialisation du PID.
 *
 *  Réinitialise les paramètres du PID
 *
 */
void reset_asserv_haut_pids(){
	pid_Reset_Integrator(&pidData_alt);	
}

/*! \brief Algorithme d'asservissement.
 *
 *  Algorithme d'asservissement en hauteur.
 *
 *  \param v  Structure de stockage des différentes valeurs.
 */
int asserv_alt(struct vars_t *v){
	//Valeur la plus faible = 1615
	//Valeur max = 60 000
	//Valeur pour environ 1 m = 9000
	v->cons_alt = 9000;//Pour les tests ...
	//Sinon c'est
	//v->cons_alt = v->RxInCollective;
//	printf("Cons alt");
	int erreur_alt;
	
	int consigne_vit;
	//int erreur_vit;
	int vit_actuelle;
	
	static unsigned int altitude_prec = 0;
	static int erreur_vit_prec = 0;
	static long int integrale;

	int col;

	/***** début d'un code pour calculer la moyenne pondérée des 2 altitudes *********/
	// calcul de l'altitude moyenne

	//Na = 10 - (5/300 * altitude_actuelle);
	//Nb = 5/300 * altitude_actuelle;

	//altitude_actuelle = (Na*alt_ultra + Nb*alt_pression) / (Na+Nb);
	/**********************************************************************************/

	/* calcul de la vitesse du quadricoptere */
	//printf("v_alt = %d",v->alt);
	
	vit_actuelle = (v->alt - altitude_prec)/0.02;// * 50 / nb_20ms; // * 50 means / Te
	//printf("v_alt = %d, altitude_prec = %d , vit_actuelle = %d",v->alt, altitude_prec, vit_actuelle);
	altitude_prec = v->alt;
	
	//printf("vit_act = %d, altitude_prec = %d", vit_actuelle,altitude_prec);

	/* calcul de l'erreur d'altitude et de la consigne de vitesse */
	erreur_alt = (v->cons_alt) - (v->alt);

	consigne_vit = erreur_alt / GAINVITESSE; // GainVitesse = 0.25

	/* saturation de la consigne de vitesse */
	if(consigne_vit > VIT_MAX){
		consigne_vit = VIT_MAX; // saturation max
	}

	if(consigne_vit < VIT_MIN ){
		consigne_vit = VIT_MIN;  // saturation min
	}

	/* calcul des coefficients du PID */
	col = pid_Controller(consigne_vit, vit_actuelle, &pidData_alt);

	/* saturation de la commande moteur */
	if(col > CMD_MOTEUR_MAX) {col = CMD_MOTEUR_MAX;} // saturation max
	if(col < CMD_MOTEUR_MIN) {col = CMD_MOTEUR_MIN;} // saturation min

	/* Mutliplication du collectif par un gain d'accélération et ajout une commande nominale */
	col += CMD_MOTEUR_NOMINAL;//?
	
	return col;
}
