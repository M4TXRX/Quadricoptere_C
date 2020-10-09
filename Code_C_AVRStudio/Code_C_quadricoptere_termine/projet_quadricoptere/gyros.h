//gyros.h
#ifndef GYROS_H
#define GYROS_H

#include <avr/io.h>
#include <util/delay.h>
#include "vars.h"
#include "i2c.h"

#define GYROS_ADDR_W 0xD0
#define GYROS_ADDR_R 0xD1

#define GYROS_ADDR_SMPLRT_DIV	0x15  // RW   SETUP: Sample Rate Divider
#define GYROS_ADDR_DLPF_FS		0x16  // RW   SETUP: Digital Low Pass Filter/ Full Scale range
#define GYROS_ADDR_TEMP_H		0x1B
#define GYROS_ADDR_PWR_MGM		0x3E  // RW	Power Management

#define GYROS_ADDR_GYRO_X_H		0x1D
#define GYROS_ADDR_GYRO_Y_H		0x1F
#define GYROS_ADDR_GYRO_Z_H		0x21

/************************************/
/*    REGISTERS PARAMETERS    */
/************************************/
// Sample Rate Divider
#define GYROS_NOSRDIVIDER         0 // default    FsampleHz=SampleRateHz/(divider+1)
// Gyro Full Scale Range
#define GYROS_RANGE2000           0x3   // default
// Digital Low Pass Filter BandWidth and SampleRate
#define GYROS_BW256_SR8           0   // default    256Khz BW and 8Khz SR
#define GYROS_BW188_SR1           1
#define GYROS_BW098_SR1           2
#define GYROS_BW042_SR1           3
#define GYROS_BW020_SR1           4
#define GYROS_BW010_SR1           5
#define GYROS_BW005_SR1           6
// Interrupt Active logic lvl
#define GYROS_ACTIVE_ONHIGH       0 // default
#define GYROS_ACTIVE_ONLOW        1
// Interrupt drive type
#define GYROS_PUSH_PULL           0 // default
#define GYROS_OPEN_DRAIN          1
// Interrupt Latch mode
#define GYROS_PULSE_50US          0 // default
#define GYROS_UNTIL_INT_CLEARED   1
// Interrupt Latch clear method
#define GYROS_READ_STATUSREG      0 // default
#define GYROS_READ_ANYREG         1
// Power management
#define GYROS_NORMAL              0 // default
#define GYROS_STANDBY             1
// Clock Source - user parameters
#define GYROS_INTERNALOSC         0   // default
#define GYROS_PLL_XGYRO_REF       1
#define GYROS_PLL_YGYRO_REF       2
#define GYROS_PLL_ZGYRO_REF       3
#define GYROS_PLL_EXTERNAL32      4   // 32.768 kHz
#define GYROS_PLL_EXTERNAL19      5   // 19.2 Mhz


char gyros_init(void);
char gyros_get_temp(char *temp);
char gyros_read_values_raw(struct vars_t *v);
char gyros_read_values_raw_cal(struct vars_t *v);
char gyros_read_values(struct vars_t *v);
void gyros_calibrate(struct vars_t *v);
char gyros_set_fs_range(unsigned char state);
char gyros_set_sample_rate_div(unsigned char _SRateDiv);
char gyros_set_power_management(unsigned char state);

#endif
