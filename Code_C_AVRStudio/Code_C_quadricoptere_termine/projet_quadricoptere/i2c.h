#ifndef I2C_H
#define I2C_H

#include <avr/io.h>

#define I2C_START			0x08
#define I2C_MT_SLA_ACK		0x18
#define I2C_MT_DATA_ACK		0x28
#define I2C_RESTART			0x10
#define I2C_MR_SLA_ACK		0x40
#define I2C_MR_DATA_ACK		0x50
#define I2C_MR_DATA_NACK	0x58

void i2c_init(void);
char i2c_start_bit(char status);
char i2c_send_data(char data, char status);
char i2c_read_data_ack(unsigned char *data);
char i2c_read_data_nack(unsigned char *data);
void i2c_stop_bit(void);
char i2c_get_data(char device_addr_w, char addr, unsigned char len, unsigned char *buff);
char i2c_set_data(char device_addr_w, char addr, unsigned char len, unsigned char *buff);

#endif
