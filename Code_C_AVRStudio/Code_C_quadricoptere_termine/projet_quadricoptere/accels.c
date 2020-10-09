#include "accels.h"

void accels_init(void) {
	char r;
	unsigned char c;
	c = 0x08;
	do {
		r = i2c_set_data(ACCELS_ADDR_W, ACCEL_REG_POWER_CTL, 1, &c);
	} while (r != 0);
//	c = 0x00; // +/- 2g
//	do {
//		r = i2c_set_data(ACCELS_ADDR_W, ACCEL_REG_DATA_FORMAT, 1, &c);
//	} while (r != 0);
}

char accels_read_values_raw(struct vars_t *v){
	unsigned char data[6];

	if (i2c_get_data(ACCELS_ADDR_W, ACCELS_ADDR_ACCEL_X_L, 6, data) != 0)
		return -1;
	// X axis
	v->AccelX = ((data[1]<<8) | data[0]);
	// Y axis
	v->AccelY = ((data[3]<<8) | data[2]);
	// Z axis
	v->AccelZ = ((data[5]<<8) | data[4]);
	return 0;
}

char accels_read_values(struct vars_t *v){
	accels_read_values_raw(v);
//	v->AccelXf = ((float)v->AccelX) * v->GainAccelX;
//	v->AccelYf = ((float)v->AccelY) * v->GainAccelY;
//	v->AccelZf = ((float)v->AccelZ) * v->GainAccelZ;
	return 0;
}
