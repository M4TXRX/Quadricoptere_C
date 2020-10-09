/* interruptions.h
 * Created: 09/03/2012 14:30:16
 *  Author: Gautier
 */

#ifndef INTERRUPTIONS_H_
#define INTERRUPTIONS_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include "main.h"

#define RECEPT_TEL 7 //Port E

void init_interruptions();

#endif /* INTERRUPTIONS_H_ */
