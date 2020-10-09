// Récupération des données utiles (acc/gyr/angl)

#include <avr/io.h>
#include <avr/interrupt.h>
#include "vars.h"
 
 /*
 "volatile" signifie que l'on force le microcontrôleur à accepter "etat" 
 comme une variable, même si elle n'est pas appelée dans le programme.
 */
 
 volatile char val_attendues[7] = {0xFA, 0xFF, 0x36, 0x1E, 0, 0, 0x0C};		//structure message
 //Ces valeurs précède les données et sont les octets qui préçisent les types de données.
 
 int init_usart_centrale(void)
	 {
	 UBRR0H = 0;
	 UBRR0L = 8; // 115200 bauds
	 /*UBRR (USART MSPIM Baud Rate Registers)
	 
     RXIE permet de gérer les interruptions. 
     Tant que le microcontrôleur ne reçoit pas de données, le programme n'est pas bloqué et peut donc executer d'autre consigne.
     Lorsqu'il reçoit une donnée, le registre RXCIE permet de la détecter et d'exécuter une variable. 
	 */
	 UCSR0C = (1<<UCSZ01)|(1<<UCSZ00);
	 UCSR0B = (1<<RXEN0)|(1<<RXCIE0);
	 /* Mode Asynchrone (RS232), Données de 8 bits, Bit de parité désactivé pour ne pas rajouté de bit à la trame qui est déjà codée sur 8 bits
	 */
	 
	 return(0);
	 }


ISR(USART0_RX_vect){ //interruption
 
    	static int etat=0; //on initialise état à 0
    	static int index_tab_result = 0; //place dans le tableau
    	static int type_result; //permet de stocker les valeurs de données (accélération 0x4031, l'Angle 0x2031...)
    	static int*tab_result; //permet de faire pointer "tab_result" vers le tableau "vitesse_angulaire[3]" ou "angls[3]" dans vars.h
    	static int receiving; //sert à stocker les données qu'on reçoit par UDR0
    	char c;
    	c = UDR0; //notre variable c va recevoir en entrée les donnée de UDR0
 
/*Les cas 0 à 6 sont les octets qui ne varient pas soit Preambule, Bid, Mid, Len, Checksum (cf cr 2015)*/
    	switch(etat){
           	case 0:
           	case 1:
           	case 2:
           	case 3:
           	case 6:
                   	if(c == val_attendues[etat]){ //on compare ce qu'on reçoit dans notre variable c à nos valeurs fixe, précisé dans "val_attendues[]"
                           	etat++; // on incrémente l'état pour
                   	}
                   	else{
                           	etat = 0;
                   	}
                   	break;
 
                   	/*
                   	*/
                   	
           	case 4: //data ID (data reçues)
           	case 19: //data ID (data reçues)
                   	etat++;
                   	receiving=((int)c)<<8; // on décale ce qu'on reçoit de 8 bits vers la gauche (ex : on reçoit 0x20 on le place 8 bits à gauche)
                   	break;
           	case 5: //data ID (data reçues)
           	case 20: //data ID (data reçues)
                   	etat++;
                   	type_result = receiving | ((int)c & 0xff);// on masque la donnée reçue (ex : on reçoit 0x31 on fait un masque (&) avec 0xFF pour  récupérer sa valeur et un masque (|=ou) avec le 0x20 reçu précédemment pour faire 0x2031 et le stocker dans type_result)
                   	switch (type_result) { //on test pour savoir dans lequel des deux cas on est avec la valeur dans type_result
                           	case 0x2031: //cas ou on reçoit l'angle
                                  	tab_result = angls; // on fait pointer tab_result vers le tableau "angls"
                                  	break;
                           	case 0x8021: //cas ou on reçoit la vitesse angulaire
                                  	tab_result = vitesse_angulaire; // on fait pointer tab_result vers le tableau "vitesse_angulaire"
                                  	break;
                   	}
                   	break;
                           	
           	case 7:
           	case 11:
           	case 15:
           	case 22:
           	case 26:
           	case 30:
                   	etat++;
                   	receiving=((int)c)<<8; //partie entière qu'on décale de 8 bits vers la droite pour laisser les 8 bits d'avant à la partie décimale
                   	break;
           	case 8:
           	case 12:
           	case 16:
           	case 23:
           	case 27:
           	case 31:
                   	etat++;
                   	tab_result[index_tab_result] = receiving|((int)c & 0xff); //partie décimale et partie entière sockée dans "tab_result[]".
                   	index_tab_result++; //on incrémente "index_tab_result" pour stocker l'angle en x, y, z, l'accélération x, y z...
                   	break;
           	case 9:
           	case 10:
           	case 13:
           	case 14:
           	case 17:
           	case 18:
    	    	case 24:
           	case 25:
           	case 28:
           	case 29:
           	case 32:
                   	etat++;//on incrémente état lors de ces case car nous n'utilisons pas les 2 derniers octets pour l'angles X, Y et Z (cf schématisation d'une trame)
                   	break ;
                           	
           	case 21:
                   	if (c == val_attendues[6] ) { // si on est à 0x0C alors on incrémente état
                           	etat++;
                           	index_tab_result = 0; //et on remet index_tab_result à 0 car on va stocker les valeurs de l'accélération au lieu de l'angle donc on nettoir le tableau avec les valeurs de l'angle
                   	}
                   	else {
                           	etat = 0; //sinon etat est remis à 0 et on reprend au début
                   	}
                   	break;
           	case 33:
                   	etat = 0;  // etat vaut 0 car on est à la fin de notre trame
                   	index_tab_result = 0; //et on remet index_tab_result à 0
                   	break;
                           	
    	} //
    		
    	
    	
} //
	
	
void centrale_read_gyro(struct vars_t *v) {		
	// X axis
	v->GyroX = -(vitesse_angulaire[1])*128;
	
	// Y axis
	v->GyroY = -(vitesse_angulaire[0])*128;//on multiplie par 64 en 1er  car c'est proche de 57. 
    //Cela permet d'obtenir notre vitesse_angulaire en angle (degré) pour la comparer après à notre angle.
	//On multiplie par 2 pour décaler de 1 bit vers la gauche (30 degrés au max en inclinaison).
	
	// Z axis
	v->GyroZ = (vitesse_angulaire[2])*8;
}

void centrale_read_angls(struct vars_t *v) {
	// X axis
	v->AngleY = -(angls[0])*2;		//2 pour 30°	//tangage
	//2 pour 30° //tangage//on multiplie par 2 pour décaler de 1 bit vers la gauche.
	// Cela permet de rapprocher notre angle max de 1000 (valeur angle max telecommande)
    // pour comparer la consigne de la télecommande avec l'angle calculer par la centrale inertielle.
	
	// Y axis
	v->AngleX = -(angls[1])*2;		//roulis
	
	// Z axis
	v->AngleZ = (angls[2])*2;		//lacet
}
