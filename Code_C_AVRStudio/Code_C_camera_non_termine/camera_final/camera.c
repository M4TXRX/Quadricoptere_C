/*
 * camera.c
 *
 * Created: 07/03/2017 15:08:45
 *  Author: Mathieu
 */ 
#include <avr/io.h>
#include <util/delay.h>
void Wait()
{
	uint16_t i;
	for(i=0;i<50;i++)
	{
		_delay_loop_2(0);
		_delay_loop_2(0);
	}
}
void main()
{
	int AngleY, AngleX;
	//FOR TIMER1
	TCCR1A|=(1<<COM1A1)|(1<<COM1B1)|(1<<WGM11);        //NON Inverted PWM
	TCCR1B|=(1<<WGM13)|(1<<WGM12)|(1<<CS11)|(0<<CS10); //PRESCALER=8 MODE 14(FAST PWM)(460500Hz timer 1)
	//PRESCALER=64 pour 16*10^6Hz
	ICR1=9210;  //fPWM=50Hz, on règle la largeur d'impulsion //ICR1=4999 pour 16*10^6Hz
	DDRD|=(1<<PD4)|(1<<PD5);   //PWM Pins as Output //OC1A sur PD5 //OC1B sur PD4
	while(1)
	{
	OCR1A=0.32*AngleY+690; //valeur de comparaison //DS65HB
    OCR1B=0.28*AngleX+630; //valeur de comparaison //HK15298
	}
}
