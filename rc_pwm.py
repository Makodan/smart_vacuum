#!/usr/bin/env python
#
# Example using Dynamic Payloads
# 
#  This is an example of how to use payloads of a varying (dynamic) size.
# 

from __future__ import print_function
import time
from RF24 import *
import RPi.GPIO as GPIO
import struct
irq_gpio_pin = None

########### USER CONFIGURATION ###########
# See https://github.com/TMRh20/RF24/blob/master/RPi/pyRF24/readme.md

# CE Pin, CSN Pin, SPI Speed

# Setup for GPIO 22 CE and CE0 CSN with SPI Speed @ 8Mhz
#radio = RF24(RPI_V2_GPIO_P1_15, BCM2835_SPI_CS0, BCM2835_SPI_SPEED_8MHZ)

#RPi B
# Setup for GPIO 15 CE and CE1 CSN with SPI Speed @ 8Mhz
#radio = RF24(RPI_V2_GPIO_P1_15, BCM2835_SPI_CS0, BCM2835_SPI_SPEED_8MHZ)

#RPi B+
# Setup for GPIO 22 CE and CE0 CSN for RPi B+ with SPI Speed @ 8Mhz
#radio = RF24(RPI_BPLUS_GPIO_J8_15, RPI_BPLUS_GPIO_J8_24, BCM2835_SPI_SPEED_8MHZ)

# RPi Alternate, with SPIDEV - Note: Edit RF24/arch/BBB/spi.cpp and  set 'this->device = "/dev/spidev0.0";;' or as listed in /dev
radio = RF24(5, 6);


# Setup for connected IRQ pin, GPIO 24 on RPi B+; uncomment to activate
#irq_gpio_pin = RPI_BPLUS_GPIO_J8_18
#irq_gpio_pin = 24

##########################################

def getch():
    import termios
    import sys, tty
    def _getch():
        fd = sys.stdin.fileno()
        old_settings = termios.tcgetattr(fd)
        try:
            tty.setraw(fd)
            ch = sys.stdin.read(1)
        finally:
            termios.tcsetattr(fd, termios.TCSADRAIN, old_settings)
        return ch
    return _getch()


pipes = [0xF0F0F0F0E1, 0xF0F0F0F0D2]


radio.begin()
radio.setPALevel(RF24_PA_MAX)
radio.setDataRate(RF24_2MBPS)
radio.setChannel(0x4C)
radio.enableDynamicPayloads()
radio.setRetries(5,15)
radio.printDetails()

#radio.openReadingPipe(1,pipes[1])
radio.openWritingPipe(pipes[1])
radio.stopListening()
# forever loop
ID = int(raw_input('ID of the car: '))
while 1:


	message = getch()
	
	if message == 'x':
		radio.write(struct.pack('HHfHfH', ID,3,0.0,3,0.0,0))
		exit()
		
    	if message == 'w':
		radio.write(struct.pack('HHfHfH', ID,2,float(40.0),2,float(40.0),0))
		time.sleep(0.08)
		radio.write(struct.pack('HHfHfH', ID,2,float(80.0),2,float(80.0),0))
		time.sleep(0.05)
                radio.write(struct.pack('HHfHfH', ID,2,float(100.0),2,float(100.0),0))
	if message == 'a':
   		radio.write(struct.pack('HHfHfH', ID,1,60,2,60,0))
			
	if message == 'd':
		radio.write(struct.pack('HHfHfH', ID,2,60,1,60,0))
		
	if message == 's':
		radio.write(struct.pack('HHfHfH', ID,3,0,3,0,0))

	if message == 'q':
                radio.write(struct.pack('HHfHfH', ID,2,float(40.0),2,float(100.0),4))

	if message == 'e':
                radio.write(struct.pack('HHfHfH', ID,2,float(100.0),2,float(40.0),5))
