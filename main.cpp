#include "mbed.h"
#include "config.h"
#include "main.h"
#include "RF24.h"
#include "wemos_mc.h"

/*
* Constructors and pin settings
*/
DigitalOut myled(ledpin);
RF24 radio(spi_MOSI, spi_MISO, spi_SCK, nrf_CE, nrf_CSN );

I2C ms(i2c_sda, i2c_scl);

InterruptIn receive(nrf_irq);
InterruptIn bumper(bump);
//InterruptIn odomet(odom);

DigitalOut strip_red(red);
DigitalOut strip_blue(green);
DigitalOut strip_green(blue);

/*
* Global variables
*/
volatile char rec;
volatile float _pwm = 0;
volatile bool newmsg_flag=0;
volatile bool stop_flag=0;
volatile dataIN input;
volatile uint32_t roll_counter = 0;

/*
* Private function prototypes
*/
void RadioSetup();
void change_strip(uint16_t col);
void startAnimation();
void hitAnimation();
void fastAnimation();


/*
* Interrupt callbacks
*/
void read_radio(){
    dataIN tmp;     
    myled = !myled;
    radio.read(&tmp,sizeof(tmp));
    if(tmp.ID == OWN_ID){
        input.dir_L = tmp.dir_L;
        input.pwm_L = tmp.pwm_L;
        input.dir_R = tmp.dir_R;
        input.pwm_R = tmp.pwm_R;
        input.led = tmp.led;
        newmsg_flag=1;
        }     
    }
         
void front_hit(){
         //blinking_flag = 1;
         //blinking_phase = 0;
         
         stop_flag=1;
         }         

void roll(){
         roll_counter++;
         
         if(roll_counter % 2) change_strip(GREEN);
         if(roll_counter % 3) change_strip(OFF);
         
         }
         
int main(){
    ms.frequency(100000);
    setfreq(ms, 1000);
    
    setmotor(ms, _MOTOR_L, _STOP, 0);
    setmotor(ms, _MOTOR_R, _STOP, 0);
    change_strip(OFF);
   
    RadioSetup();
    radio.startListening();
    wait_ms(250);
    startAnimation();
    
    
    receive.fall(&read_radio);
    bumper.rise(&front_hit);
 //   odomet.rise(&roll);
    


    
     while(1){
        
                if(newmsg_flag == 1){       
                     setmotor(ms, _MOTOR_L, (uint8_t)input.dir_L, input.pwm_L);
                     wait_ms(10);
                     setmotor(ms, _MOTOR_R, (uint8_t)input.dir_R, input.pwm_R);  
                     change_strip(input.led);
                     newmsg_flag = 0;
                    }        
               
                 if(stop_flag == 1){
                     setmotor(ms, _MOTOR_L, _STOP, 0);
                     setmotor(ms, _MOTOR_R, _STOP, 0);
                     hitAnimation(); // 2s wait
                     stop_flag = 0;
                   }
        
        /*
               if(blinking_phase<5 && blinking_flag == 1){
                   change_strip(current_col);
                   wait_ms(250);
                   change_strip(OFF);
                   wait_ms(250);
                    blinking_phase++;
                   }      
          */     
                         
        }
        
    
    }
    
void RadioSetup(){
    
    radio.begin();
    radio.setPALevel(RF24_PA_HIGH);
    radio.setChannel(RadioChannel);
    radio.setRetries(0,2);
    radio.enableDynamicAck();
    radio.enableDynamicPayloads();
    radio.openReadingPipe(1,DataAddress);
    radio.maskIRQ(1,1,0);
    }
    
void change_strip(uint16_t col){
      
    switch(col){
        case RED:
             strip_red = 1;
             strip_blue = 0;
             strip_green=0;
            break;
        case GREEN:
             strip_red = 0;
             strip_blue = 0;
             strip_green = 1;
            break;
        case BLUE:
             strip_red = 0;
             strip_blue = 1;
             strip_green = 0;
            break;
        case YELLOW:
             strip_red = 1;
             strip_blue = 0;
             strip_green = 1;
            break;
        case MAGENTA:
             strip_red = 1;
             strip_blue = 1;
             strip_green = 0;
            break;
        case CYAN:
             strip_red = 0;
             strip_blue = 1;
             strip_green = 1;
            break;
        case WHITE:
             strip_red = 1;
             strip_blue = 1;
             strip_green = 1;
            break;
        case OFF:
             strip_red = 0;
             strip_blue = 0;
             strip_green = 0;
            break;
        case 8:
             fastAnimation();
            break;      
        }
    
    }
    
void startAnimation(){
        
        change_strip(RED);
        wait_ms(250);
        change_strip(YELLOW);
        wait_ms(250);
        change_strip(GREEN);
        wait_ms(250);
        change_strip(CYAN);
        wait_ms(250);
        change_strip(BLUE);
        wait_ms(250);
        change_strip(MAGENTA);
        wait_ms(250);
        change_strip(WHITE);
        wait_ms(250);
        change_strip(OFF);
        }
        
void hitAnimation(){
    for(int i=0; i<5; i++){
        change_strip(RED);
        wait_ms(300);
        change_strip(OFF);
        wait_ms(100);
        }
    }
    
void fastAnimation(){
    
    for(int i=0; i<10; i++){
        change_strip(RED);
        wait_ms(100);
        change_strip(OFF);
        wait_ms(50);
        change_strip(GREEN);
        wait_ms(100);
        change_strip(OFF);
        wait_ms(50);
        change_strip(BLUE);
        wait_ms(100);
        change_strip(OFF);
        
        
        }
    
    }
    
