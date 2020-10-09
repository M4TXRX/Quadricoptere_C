// R�cup�ration des donn�es utiles (acc/gyr/angl)

#include <avr/io.h>
#include <avr/interrupt.h>
#include "vars.h"
 
 /*
 "volatile" signifie que l'on force le microcontr�leur � accepter "etat" 
 comme une variable, m�me si elle n'est pas appel�e dans le programme.
 */
 
 volatile char val_attendues[7] = {0xFA, 0xFF, 0x36, 0x1E, 0, 0, 0x0C};		//structure message
 //Ces valeurs pr�c�de les donn�es et sont les octets qui pr��isent les types de donn�es.
 
 int init_usart_centrale(void)
	 {
	 UBRR0H = 0;
	 UBRR0L = 8; // 115200 bauds
	 /*UBRR (USART MSPIM Baud Rate Registers)
	 
     RXIE permet de g�rer les interruptions. 
     Tant que le microcontr�leur ne re�oit pas de donn�es, le programme n'est pas bloqu� et peut donc executer d'autre consigne.
     Lorsqu'il re�oit une donn�e, le registre RXCIE permet de la d�tecter et d'ex�cuter une variable. 
	 */
	 UCSR0C = (1<<UCSZ01)|(1<<UCSZ00);
	 UCSR0B = (1<<RXEN0)|(1<<RXCIE0);
	 /* Mode Asynchrone (RS232), Donn�es de 8 bits, Bit de parit� d�sactiv� pour ne pas rajout� de bit � la trame qui est d�j� cod�e sur 8 bits
	 */
	 
	 return(0);
	 }


ISR(USART0_RX_vect){ //interruption
 
    	static int etat=0; //on initialise �tat � 0
    	static int index_tab_result = 0; //place dans le tableau
    	static int type_result; //permet de stocker les valeurs de donn�es (acc�l�ration 0x4031, l'Angle 0x2031...)
    	static int*tab_result; //permet de faire pointer "tab_result" vers le tableau "vitesse_angulaire[3]" ou "angls[3]" dans vars.h
    	static int receiving; //sert � stocker les donn�es qu'on re�oit par UDR0
    	char c;
    	c = UDR0; //notre variable c va recevoir en entr�e les donn�e de UDR0
 
/*Les cas 0 � 6 sont les octets qui ne varient pas soit Preambule, Bid, Mid, Len, Checksum (cf cr 2015)*/
    	switch(etat){
           	case 0:
           	case 1:
           	case 2:
           	case 3:
           	case 6:
                   	if(c == val_attendues[etat]){ //on compare ce qu'on re�oit dans notre variable c � nos valeurs fixe, pr�cis� dans "val_attendues[]"
                           	etat++; // on incr�mente l'�tat pour
                   	}
                   	else{
                           	etat = 0;
                   	}
                   	break;
 
                   	/*
                   	*/
                   	
           	case 4: //data ID (data re�ues)
           	case 19: //data ID (data re�ues)
                   	etat++;
                   	receiving=((int)c)<<8; // on d�cale ce qu'on re�oit de 8 bits vers la gauche (ex : on re�oit 0x20 on le place 8 bits � gauche)
                   	break;
           	case 5: //data ID (data re�ues)
           	case 20: //data ID (data re�ues)
                   	etat++;
                   	type_result = receiving | ((int)c & 0xff);// on masque la donn�e re�ue (ex : on re�oit 0x31 on fait un masque (&) avec 0xFF pour  r�cup�rer sa valeur et un masque (|=ou) avec le 0x20 re�u pr�c�demment pour faire 0x2031 et le stocker dans type_result)
                   	switch (type_result) { //on test pour savoir dans lequel des deux cas on est avec la valeur dans type_result
                           	case 0x2031: //cas ou on re�oit l'angle
                                  	tab_result = angls; // on fait pointer tab_result vers le tableau "angls"
                                  	break;
                           	case 0x8021: //cas ou on re�oit la vitesse angulaire
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
                   	receiving=((int)c)<<8; //partie enti�re qu'on d�cale de 8 bits vers la droite pour laisser les 8 bits d'avant � la partie d�cimale
                   	break;
           	case 8:
           	case 12:
           	case 16:
           	case 23:
           	case 27:
           	case 31:
                   	etat++;
                   	tab_result[index_tab_result] = receiving|((int)c & 0xff); //partie d�cimale et partie enti�re sock�e dans "tab_result[]".
                   	index_tab_result++; //on incr�mente "index_tab_result" pour stocker l'angle en x, y, z, l'acc�l�ration x, y z...
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
                   	etat++;//on incr�mente �tat lors de ces case car nous n'utilisons pas les 2 derniers octets pour l'angles X, Y et Z (cf sch�matisation d'une trame)
                   	break ;
                           	
           	case 21:
                   	if (c == val_attendues[6] ) { // si on est � 0x0C alors on incr�mente �tat
                           	etat++;
                           	index_tab_result = 0; //et on remet index_tab_result � 0 car on va stocker les valeurs de l'acc�l�ration au lieu de l'angle donc on nettoir le tableau avec les valeurs de l'angle
                   	}
                   	else {
                           	etat = 0; //sinon etat est remis � 0 et on reprend au d�but
                   	}
                   	break;
           	case 33:
                   	etat = 0;  // etat vaut 0 car on est � la fin de notre trame
                   	index_tab_result = 0; //et on remet index_tab_result � 0
                   	break;
                           	
    	} //
    		
    	
    	
} //
	
	
void centrale_read_gyro(struct vars_t *v) {		
	// X axis
	v->GyroX = -(vitesse_angulaire[1])*128;
	
	// Y axis
	v->GyroY = -(vitesse_angulaire[0])*128;//on multiplie par 64 en 1er  car c'est proche de 57. 
    //Cela permet d'obtenir notre vitesse_angulaire en angle (degr�) pour la comparer apr�s � notre angle.
	//On multiplie par 2 pour d�caler de 1 bit vers la gauche (30 degr�s au max en inclinaison).
	
	// Z axis
	v->GyroZ = (vitesse_angulaire[2])*8;
}

void centrale_read_angls(struct vars_t *v) {
	// X axis
	v->AngleY = -(angls[0])*2;		//2 pour 30�	//tangage
	//2 pour 30� //tangage//on multiplie par 2 pour d�caler de 1 bit vers la gauche.
	// Cela permet de rapprocher notre angle max de 1000 (valeur angle max telecommande)
    // pour comparer la consigne de la t�lecommande avec l'angle calculer par la centrale inertielle.
	
	// Y axis
	v->AngleX = -(angls[1])*2;		//roulis
	
	// Z axis
	v->AngleZ = (angls[2])*2;		//lacet
}
