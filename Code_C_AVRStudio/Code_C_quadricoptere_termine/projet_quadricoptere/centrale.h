/*
 * centrale.h
 *
 * Created: 28/11/2014 16:33:02
 *  Author: sbejaou1
 */ 


#ifndef CENTRALE_H_
#define CENTRALE_H_

int init_usart_centrale(void);

void centrale_read_gyro(struct vars_t *v);
void centrale_read_angls(struct vars_t *v);

#endif /* CENTRALE_H_ */
