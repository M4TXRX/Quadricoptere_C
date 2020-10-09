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
	//FOR TIMER1
	TCCR1A|=(1<<COM1A1)|(1<<COM1B1)|(1<<WGM11);        //NON Inverted PWM
	TCCR1B|=(1<<WGM13)|(1<<WGM12)|(1<<CS11)|(0<<CS10); //PRESCALER=8 MODE 14(FAST PWM)
	ICR1=9210;  //fPWM=50Hz
	DDRD|=(1<<PD4)|(1<<PD5);   //PWM Pins as Output
	while(1)
	{

		OCR1A=460;  //-45 degree 1ms
		Wait();
		OCR1A=690;   //0 degree 1,5ms
		Wait();
		OCR1A=920;  //45 degree 2ms
		Wait();
		OCR1A=690;   //0 degree 1,5ms
	}
}
