#ifndef VARS_H
#define VARS_H

struct vars_t
{
    int AccelX;
    int AccelY;
    int AccelZ;

    int GyroX;
    int GyroY;
    int GyroZ;
	
	int AngleX;
	int AngleY;
	int AngleZ;

    int GyroXZero;
    int GyroYZero;
    int GyroZZero;
	
	// valeur des gyro convertis en °/s
	int GyroXConv;
	int GyroYConv;
	int GyroZConv;
	
	float hauteur;
	float hauteur_prec;	//hauteur précédente
	int choix_asser_alt;	//Choix de l'asservissement (altitude (=0) ou vitesse verticale(=1))
	int pos_manette_ver;	//Position de la manette pour la verticale
	float coeff_asser;
	
	float erreurh;
	float erreurh_prec;//Erreur précédente
	
	float erreur_vitesse_prec;
	float erreur_vitesse;
	float vitesse;
	float vitesse_prec;
	
	int MotorOut1;
	int MotorOut2;
	int MotorOut3;
	int MotorOut4;
	
	unsigned char FlagCollectiveZero;
	int coll_calc;//Collective calculé
	int RxChannels [9] ; // valeur du temps à l'etat haut du signal PPM
	int RxInRoll; // -1000 +1000
	int RxInPitch; // -1000 +1000
	int RxInYaw; // -1000 +1000
	int RxInCollective; // -1000 à 1000
	int RxInRoll_Angle; //-1000 à 1000
	int RxInYaw_Angle; // -1000 à 1000
	int RxInPitch_Angle; // -1000  à 1000
	//unsigned int height, cons_height; // 0 +1000
	int computedCollective; // 0 +1000
	int RxInModeNav, oldRxInMode; // -1000 +1000
	int FlagArmed;  //indique si on est désarmé ou armé
	int RxArmed;
	int Mode_Nav;
	int RxAsserHaut;
	int YawLimit;
	unsigned int alt;
	int cons_alt;
	int AsserHaut;
	int cpt_asser;
};

	volatile int val_TCNT1_fd_PPM;
	volatile int val_TCNT1_fd_SONAR;
	volatile unsigned int temps_etat_haut_PPM [9] ; // valeur du temps à l'etat haut du signal PPM
	volatile int front_montant_US;
	volatile unsigned int temps_etat_haut_US; //Pour le capteur ultrason
	volatile unsigned int diz_timer1;
	unsigned int flag_asser;
	volatile unsigned int val_timer1;
	//Déclaration de la variable accélaration regroupant dans un tableau 3 entiers
	int vitesse_angulaire[3];
	//Déclaration de la variable angle regroupannt les valeurs dans un tableau
	int angls[3];
 
#endif
