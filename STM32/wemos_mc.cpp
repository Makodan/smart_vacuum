#include "wemos_mc.h"


/* setfreq() -- set PWM's frequency
freq:
    PWM's frequency 
*/
void setfreq(I2C& i2c, uint32_t freq){
        
        char data[4];
        
        data[0]=(((char)(freq >> 16)) & (char)0x0f);
        data[1]=((char)(freq >> 16));
        data[2]=((char)(freq >> 8));
        data[3]=((char)freq);
        
        //__disable_irq(); 
        i2c.write( _ADDRESS, data, 4 );
        //__enable_irq(); 
        wait_ms(5);

}

/* setmotor() -- set motor
motor:
    _MOTOR_A    0   Motor A
    _MOTOR_B    1   Motor B
dir:
    _SHORT_BRAKE    0
    _CW            1
    _CCW            2
    _STOP           3
    _STANDBY        4
pwm_val:
    0.00 - 100.00  (%)
*/
void setmotor(I2C& i2c,uint8_t motor, uint8_t dir, float pwm_val){
        
        uint16_t _pwm_val = (uint16_t)pwm_val * 100;
        
        if(_pwm_val>10000)
            _pwm_val=10000;
        
        char data[4];
         
        data[0] = ( motor | (char)0x10);
        data[1] = ( dir );
        data[2] = ((char)(_pwm_val >> 8));
        data[3] = ((char)_pwm_val);
        
        //__disable_irq(); 
        i2c.write( _ADDRESS, data, 4 );
        //__enable_irq(); 
        wait_ms(5);
        
        }

void setmotor(I2C& i2c, uint8_t motor, uint8_t dir){
        
        setmotor(i2c,motor,dir,100);
}