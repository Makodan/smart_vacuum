#ifndef CONFIG_H
#define CONFIG_H



    #define OWN_ID      1
 
    #define RadioChannel 0x4C
    #define DataAddress 0xF0F0F0F0D2 //0xc2c2c2c2c2

    #define ledpin      PA_8
    #define unused_pin  PA_1
    
    #define bump        PA_11
    #define odom        PA_12
    
    #define red         PA_0
    #define green       PA_3
    #define blue        PA_2
    
    #define nrf_CE      PB_4
    #define nrf_CSN     PB_3
    #define spi_SCK     PA_5
    #define spi_MOSI    PA_7
    #define spi_MISO    PA_6
    #define nrf_irq     PA_15 
    
    #define i2c_sda     PB_7 
    #define i2c_scl     PB_6
    
    #define RXD         PA_3
    #define TXD         PA_2
    


#endif


