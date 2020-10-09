/*voltmetre.h
***** Fichier .h reliant les fonction de lecture et d'envoi de trame du voltmetre *****

ATTENTION : Il faut rajouter dans interruptions_init.c, fonction init_interruptions() les lignes suivantes, avant sei() :

    PCICR = (1<<PCIE0); //Enable interrupt PCINT(0-7), any logical change
    PCMSK0 = (1<<PCINT0); //Enable interrupt on PCINT0

*/

#ifndef VOLTMETRE_H
#define VOLTMETRE_H

#include <avr/io.h>
#include "main.h"
#include "vars.h"

//fonction :
void read_volt();
void analyse_trame(char *tab);

#endif
