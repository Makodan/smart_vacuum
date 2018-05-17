#ifndef __WEMOS_MC_H
#define __WEMOS_MC_H

#include "mbed.h"
#define _MOTOR_L 0
#define _MOTOR_R 1

#define _ADDRESS 0x60

#define _SHORT_BRAKE 0
#define _CCW  1    //rearward
#define _CW     2 //forward
#define _STOP 3
#define _STANDBY 4



    void setfreq(I2C& i2c, uint32_t freq);
    void setmotor(I2C& i2c, uint8_t motor, uint8_t dir, float pwm_val);
    void setmotor(I2C& i2c, uint8_t motor, uint8_t dir);

   



#endif