#include <reg51.h>

#include "lcd.h"
#include "keypad.h"
#include "i2c.h"

void delay_ms (unsigned int i){  //software delay. uncalibrated. Could use Timer but hectic
	unsigned int j;

	for (; i>0; i--){
		for (j=122; j>0;j--);
	}
}
	unsigned int i=0;
void main(void){
	lcd_init();   //initialization sequence
	lcd_cmd(0x80);
	
	//i is 0 initially. I is incremented signifying increament in position address of the memory register of eeprom
	while(i>=0){
		// take data and store in eeprom
		unsigned char t=keypad_input();
		i2c_device_write(0xa0,i,t);

		//read data from eeprom and display in lcd
		t=i2c_device_read(0xa0,i);
		lcd_char(t);

		i++;
	}
}

