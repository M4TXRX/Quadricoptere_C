/*voltmetre.c
***** Contient les codes des fonctions de lecture et d'envoi de trame du voltmetre *****

ATTENTION : Il faut rajouter dans interruptions_init.c, fonction init_interruptions() les lignes suivantes, avant sei() :

    PCICR = (1<<PCIE0); //Enable interrupt PCINT(0-7), any logical change
    PCMSK0 = (1<<PCINT0); //Enable interrupt on PCINT0



*/

#include "voltmetre.h"

//permet de détecter et lire la trame
void read_volt(){
	//printf("%d", diff_volt);
	if (diff_volt < 7040){
		code = (diff_volt - 5000) / 8;
//		printf("%c", code);
		if(code==0x7e){
			ind_trame_volt=0;
		}
		else{
			tab[ind_trame_volt++] = code;
			if(ind_trame_volt==7){ //une fois la trame finie
//				printf("a\n");
				analyse_trame(tab);
			}
		}

	}
	flag_int_volt = 0;
}

// permet d'envoyer la trame via l'uart
void analyse_trame(char *tab){

	if(tab[1]==6){
		printf("%c %c",tab[3], tab[2]);
	}

}
