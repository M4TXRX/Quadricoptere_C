//annexe.h

#ifndef ANNEXE_H_
#define ANNEXE_H_

#include "main.h"
#include "gyros.h"

//UART Function
void init_uart(void);
int uart_putchar(char c, FILE *stream);
int uart_getchar(FILE *stream);

//Initializing all port of the UC
void init_port(void);

//Leds Flashing functions
void cli_led1 (int nb);
void set_led1 ();
void reset_led1();

void cli_led2 (int nb);
void set_led2 ();
void reset_led2();

void ConvertRxChannels (struct vars_t *v);
void init_vars(struct vars_t *v);

#endif /* ANNEXE_H_ */
