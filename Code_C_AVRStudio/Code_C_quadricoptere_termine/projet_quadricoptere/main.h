
#ifndef MAIN_H_ // debut MAIN_H_
#define MAIN_H_

#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include <string.h>
#include <ctype.h>
#include <avr/pgmspace.h>
#include <avr/sleep.h>

#include "vars.h"
#include "asserv_haut.h"

//Leds
#define LED1 3
#define LED2 4

//Moteurs
#define M1 3 //DDRH
#define M2 4 //DDRH
#define M3 5 //DDRH
#define M4 3 //DDRL
#define M5 4 //DDRL
#define M6 5 //DDRL

//UART 0: port PE
#define RXD0 0 // Broche 2
#define TXD0 1 // Broche 3

//UART 1 : sur le port PD
#define RXD1 2
#define TXD1 3

//UART 2 : sur le port PH
#define RXD2 0
#define TXD2 1

//UART 3 : sur le port PJ
#define RXD3 0
#define TXD3 1

//Used to set the AVR Baud Rate TO 115200 w/16MHz crystal
#define MYUBRR 8

//Choix de l'asservissement en altitude
#define ASSER_ALT 0
#define ASSER_VIT 1

//Variable globale :
int diff_volt;
unsigned long int last_value_volt;
int flag_int_volt;
int ind_trame_volt;
char code;
char tab[9];

//struct vars_t v;

#endif /* fin MAIN_H_ */
