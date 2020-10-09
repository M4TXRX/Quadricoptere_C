#ifndef ACCELS_H
#define ACCELS_H

#include <avr/io.h>
#include "i2c.h"
#include "vars.h"

#define ACCELS_ADDR_W 0xA6
#define ACCELS_ADDR_R 0xA7

#define ACCELS_ADDR_ACCEL_X_L	0x32

#define ACCEL_REG_BW_RATE		0x2C
#define ACCEL_REG_POWER_CTL		0x2D
#define ACCEL_REG_DATA_FORMAT	0x31


void accels_init(void);
char accels_read_values_raw(struct vars_t *v);
char accels_read_values(struct vars_t *v);
void accels_calibrate(struct vars_t *v);

#endif
