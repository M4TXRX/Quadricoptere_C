#include "i2c.h"

void i2c_init(void) {
	TWBR = 12; // 16MHz/(16+2*12) = 400kHz
}

char i2c_start_bit(char status) {
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	while (!(TWCR & (1<<TWINT)));
	if ((TWSR & 0xF8) != status)
		return 1;
	return 0;
}

char i2c_send_data(char data, char status) {
	TWDR = data;
	TWCR = (1<<TWINT)|(1<<TWEN);
	while (!(TWCR & (1<<TWINT)));
	if ((TWSR & 0xF8) != status)
		return 1;
	return 0;
}

char i2c_read_data_ack(unsigned char *data) {
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);
	while (!(TWCR & (1<<TWINT)));
	if ((TWSR & 0xF8) != I2C_MR_DATA_ACK)
		return 1;
	*data = TWDR;
	return 0;
}

char i2c_read_data_nack(unsigned char *data) {
	TWCR = (1<<TWINT)|(1<<TWEN);
	while (!(TWCR & (1<<TWINT)));
	if ((TWSR & 0xF8) != I2C_MR_DATA_NACK)
		return 1;
	*data = TWDR;
	return 0;
}

void i2c_stop_bit(void) {
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
}

char i2c_get_data(char device_addr_w, char addr, unsigned char len, unsigned char *buff) {
	// start bit
	if (i2c_start_bit(I2C_START) != 0)
		return 1;

	// slave write addr
	if (i2c_send_data(device_addr_w, I2C_MT_SLA_ACK) != 0)
		return 1;

	// register addr
	if (i2c_send_data(addr, I2C_MT_DATA_ACK) != 0)
		return 1;

	// start
	if (i2c_start_bit(I2C_RESTART) != 0)
		return 1;

	// slave read addr
	if (i2c_send_data(device_addr_w + 1, I2C_MR_SLA_ACK) != 0)
		return 1;

	while (len) {
		// read first byte with ACK
		if (len > 1) {
			if (i2c_read_data_ack(buff) != 0)
				return 1;
		}
		else {
			if (i2c_read_data_nack(buff) != 0)
				return 1;
		}
		buff++;
		len--;
	}

	// send stop
	i2c_stop_bit();

	return 0; // no error
}

char i2c_set_data(char device_addr_w, char addr, unsigned char len, unsigned char *buff) {
	// start bit
	if (i2c_start_bit(I2C_START) != 0)
		return 1;

	// slave write addr
	if (i2c_send_data(device_addr_w, I2C_MT_SLA_ACK) != 0)
		return 2;

	// register addr
	if (i2c_send_data(addr, I2C_MT_DATA_ACK) != 0)
		return 3;

	while (len) {
		if (i2c_send_data(*buff, I2C_MT_DATA_ACK) != 0)
			return 4;
		buff++;
		len--;
	}

	// send stop
	i2c_stop_bit();

	return 0; // no error
}
