//annexe.c

#include "annexe.h"
#include "interruptions_init.h"

static FILE uart_str = FDEV_SETUP_STREAM(uart_putchar, uart_getchar, _FDEV_SETUP_RW);

void init_uart(void) {
    /*TERMINAL:
    115200 baud - Even Parity - 8bit of Data - 1 Stop Bit
    Baud is set with MYUBRR var.*/
    UBRR1 = MYUBRR;
	UCSR1B = (1<<RXEN1)|(1<<TXEN1);			//Enable Rx and Tx in UART
    UCSR1C = (1<<UCSZ10)|(1<<UCSZ11);		//8-Bit Characters
	//UCSR2C |= (1<<UPM21); //Parité paire
	
	stdout=&uart_str;

}

int uart_putchar(char c, FILE *stream){

  if (c == '\n')
    uart_putchar('\r', stream);

  do{
  //rien
  }while ( !(UCSR2A & (1<<UDRE2))) ;
  UDR2 = c;
  return 0;
}

int uart_getchar(FILE *stream){

    while( !(UCSR2A & (1<<RXC2)) );
	return(UDR2);
}

//static FILE uart_str = FDEV_SETUP_STREAM(uart_putchar, uart_getchar, _FDEV_SETUP_RW);


//Fonction qui permet de faire clignoter la led1 (Green DEL)
void cli_led1 (int nb) {
	int i, j;
	
	reset_led1();
	
	for (i=0; i<nb; i++) {

		PORTJ |= (1<<LED1);//LED1 ON

		for (j=0; j<10; j++){
			_delay_ms(10);
		}

		PORTJ &= (~(1<<LED1));//LED1 OFF

		for (j=0; j<10; j++){
			_delay_ms(10);
		}
	}
}

void set_led1 (){
		PORTJ |= (1<<LED1);//LED1 ON
}

void reset_led1(){
	PORTJ &= (~(1<<LED1));//LED1 OFF
}

//Fonction qui permet de faire clignoter la LED2 (RED DEL)
void cli_led2 (int nb) {
	int i, j;

	reset_led2();
	
	for (i=0; i<nb; i++) {

		PORTJ |= (1<<LED2);//LED2 ON

		for (j=0; j<10; j++){
			_delay_ms(10);
		}

		PORTJ &= (~(1<<LED2));//LED2 OFF

		for (j=0; j<10; j++){
			_delay_ms(10);
		}
	}
}

void set_led2 (){
	PORTJ |= (1<<LED2);//LED2 ON
}

void reset_led2(){
	PORTJ &= (~(1<<LED2));//LED2 OFF
}

void init_port(void){
	//Pour les LEDs :
	DDRJ = DDRJ | (1<<DDJ3) | (1<<DDJ4);

	//Pour les moteurs :
	DDRH |= (1<<DDH3)|(1<<DDH4)|(1<<DDH5);
	DDRL |= (1<<DDL3)|(1<<DDL4)|(1<<DDL5);

	//Pour l'UART vers l'écran :
	DDRD = DDRD & (~(1<<RXD1)); //En entrée
	DDRD = DDRD | (1<<TXD1); //En sortie
	PORTD |= (1 << PD0);
	PORTD |= (1 << PD1);


	//Pour l'UART en 0
	DDRE = DDRE & (~(1<<RXD0)); //En entrée
	DDRE = DDRE | (1<<TXD0); //En sortie

	//Pour la télécommande
	DDRE &= ~(1<<RECEPT_TEL); //En entrée (PINE7)
}

void ConvertRxChannels (struct vars_t *v){
	
	//On le met dans les variables prévue pour ...
	//Voie 0, premier signal : Monter/descendre
	//Voie 1,inclinaison latéralgauche/droite (roll)
	//Voie 2, inclinaison avancer reculer
	//Voie 3, yawn
	
	
	//Consigne de vitesse de montée pour l'asservissement normal ...
	v->RxInCollective = v->RxChannels[0];
	
	//Consigne d'altitude pour l'asservissement en hauteur.
	//v->cons_alt = v->RxChannels[0];
	//On a pris un choix de variable différent pour plus de lisibilité
	//dans le code d'asservissement en hauteur.

	//v->RxInRoll = v->RxChannels[1];
	//v->RxInPitch = v->RxChannels[2];
	//v->RxInYaw = v->RxChannels[3];

    v->RxInRoll_Angle = v->RxChannels[1];
    v->RxInPitch_Angle = v->RxChannels[2];
    v->RxInYaw_Angle = v->RxChannels[3];
	v->RxArmed = v->RxChannels[4];
	//v->RxInModeNav = v->RxChannels[5]; //SW2
	v->RxAsserHaut = v->RxChannels[6]; //SW3 (Channel 7) Permet de choisir entre un asservissement en hauteur/vitesse
	//v->RxInModeNav = v->RxChannels[7]; //SW1
	v->alt = temps_etat_haut_US;
	
	//printf("temps_etat_haut_US = %d\n", temps_etat_haut_US);
	//printf("diz_timer = %d", diz_timer1);
	//printf("RxArmed = %d\n",v->RxArmed);
	//printf("RxInCollective = %d\n",v->RxInCollective);
	
	//Si on est vraiment à zero, alors on active le flag du zero ...
	v->FlagCollectiveZero = 0;
	if (v->RxInCollective < 50){
		v->FlagCollectiveZero = 1;
	}
		
	//Si le switch SW3 est en haut, on veut controller l'altitude
	//Si le switch SW3 est en bas, on veut controller la vitesse
	if (v->RxAsserHaut < 0)
	{
		v->AsserHaut = 0; //Control de la vitesse
		//cli_led2(2);
		//set_led2();
	}
	else
	{
		v->AsserHaut = 1; //Control hauteur	
		//reset_led2();
	}
	
	//On regarde si c'est bien armé (=on pourra commencer à le piloter)
	if ((v->FlagArmed == 0) && (v->RxArmed>200) && (v->FlagCollectiveZero==1)) {
//		gyros_calibrate(v);
		v->FlagArmed = 1;
		//set_led1();
	}
	// ! désarmer en vol fait conserver les valeurs de Rxchannels
	if (v->RxArmed<-200 && (v->FlagCollectiveZero==1)) {
		v->FlagArmed = 0;
		//reset_led1();
	}
	//Choix de mode de navigation
	v->Mode_Nav = 0;
	if (v->RxInModeNav<-300) {v->Mode_Nav = 0;}
	if (v->RxInModeNav>-300 && v->RxInModeNav<300) {v->Mode_Nav = 1;}
	if (v->RxInModeNav>300) {v->Mode_Nav = 2;}	
	
}

void init_vars(struct vars_t *v){
	v->AccelX=0;
	v->AccelY=0;
	v->AccelZ=0;

	v->GyroX=0;
	v->GyroY=0;
	v->GyroZ=0;

	v->GyroXZero=0;
	v->GyroYZero=0;
	v->GyroZZero=0;
	    
	// valeur des gyro convertis en °/s
	v->GyroXConv=0;
	v->GyroYConv=0;
	v->GyroZConv=0;
	    
	v->hauteur=0;
	v->hauteur_prec=0;	//hauteur précédente
	v->choix_asser_alt=0;	//Choix de l'asservissement (altitude (=0) ou vitesse verticale(=1))
	v->pos_manette_ver=0;	//Position de la manette pour la verticale
	v->coeff_asser=0;
	    
	v->erreurh=0;
	v->erreurh_prec=0;//Erreur précédente
	    
	v->erreur_vitesse_prec=0;
	v->erreur_vitesse=0;
	v->vitesse=0;
	v->vitesse_prec=0;
	    
	v->MotorOut1=0;
	v->MotorOut2=0;
	v->MotorOut3=0;
	v->MotorOut4=0;
	    
	v->FlagCollectiveZero=0;
	v->coll_calc=0;//Collective calculé
	v->RxInRoll=0; // -1000 +1000
	v->RxInPitch=0; // -1000 +1000
	v->RxInYaw=0; // -1000 +1000
	v->RxInRoll_Angle=0; // -1000 +1000
	v->RxInPitch_Angle=0; // -1000 +1000
	v->RxInYaw_Angle=0; // -1000 +1000
	v->RxInCollective=0; // 0 +1000
	//unsigned int height, cons_height; // 0 +1000
	v->computedCollective=0; // 0 +1000
	v->RxInModeNav=0;
	v->oldRxInMode=0; // -1000 +1000
	v->FlagArmed=0;  //indique si on est désarmé ou armé
	v->RxArmed=0;
	v->Mode_Nav=0;
	    
	v->YawLimit=400;
}
