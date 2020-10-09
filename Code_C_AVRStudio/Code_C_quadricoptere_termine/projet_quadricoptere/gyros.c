//gyros.c
#include "gyros.h"


char gyros_init(void) {
	int i;
	if (gyros_set_sample_rate_div(GYROS_NOSRDIVIDER))
		return 1;
	if (gyros_set_power_management(GYROS_PLL_XGYRO_REF))
		return 2;
	if (gyros_set_fs_range((GYROS_RANGE2000 << 3) | GYROS_BW188_SR1))
		return 3;
	for (i=0; i<7; i++) {
		_delay_ms(10);
	}
	return 0;
}

char gyros_get_temp(char *temp){
	int t;
	unsigned char data[2];

	if (i2c_get_data(GYROS_ADDR_W, GYROS_ADDR_TEMP_H, 2, data) != 0)
		return -1;
	t = (data[0]<<8) | data[1];
	t = (t + 13200) / 280 + 35;
	*temp = (char)t;
	return 0;
}

char gyros_read_values_raw(struct vars_t *v) {
	unsigned char data[6];

	if (i2c_get_data(GYROS_ADDR_W, GYROS_ADDR_GYRO_X_H, 6, data) != 0) {
		return -1;
	}
	// X axis
	v->GyroX = ((data[0]<<8) | data[1]);
	// Y axis
	v->GyroY = ((data[2]<<8) | data[3]);
	// Z axis
	v->GyroZ = ((data[4]<<8) | data[5]);
	return 0;
}



/*char gyros_read_values(struct vars_t *v) {
	gyros_read_values_raw_cal(v);
	v->GyroXf =  (((float)v->GyroX) / 14.375) * v->GainGyroX;
	v->GyroYf =  (((float)v->GyroY) / 14.375) * v->GainGyroY;
	v->GyroZf =  (((float)v->GyroZ) / 14.375) * v->GainGyroZ;
	return 0;
}*/

void gyros_calibrate(struct vars_t *v) {
	// get 128 measures every 5 ms
	int i;
	int val[3] = {0, 0, 0};

	for (i=0; i<128; i++) {
		_delay_ms(5);
		gyros_read_values_raw(v);
		val[0] += v->GyroX;
		val[1] += v->GyroY;
		val[2] += v->GyroZ;

	}
	v->GyroXZero = val[0] / 128;
	v->GyroYZero = val[1] / 128;
	v->GyroZZero = val[2] / 128;
}

char gyros_set_fs_range(unsigned char state) {
	return i2c_set_data(GYROS_ADDR_W, GYROS_ADDR_DLPF_FS, 1, &state);
}

char gyros_set_sample_rate_div(unsigned char state) {
	return i2c_set_data(GYROS_ADDR_W, GYROS_ADDR_SMPLRT_DIV, 1, &state);
}

char gyros_set_power_management(unsigned char state) {
	return i2c_set_data(GYROS_ADDR_W, GYROS_ADDR_PWR_MGM, 1, &state);
}
