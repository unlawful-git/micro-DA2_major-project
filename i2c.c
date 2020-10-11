#include <reg51.h>

void delay_ms (unsigned int);

sbit scl=P1^0;
sbit sda=P1^1;

void i2c_delay(void){
	TMOD=0x02;   //8 bit autoreload mode
	TL0=-5;
	TH0=-5;
	TR0=1;
	while(TF0!=1);
	TR0=0;
}
void i2c_start(void){
	scl=0;
	i2c_delay();
	sda=1;
	delay_ms(200);
	scl=1;
	i2c_delay();
	sda=0;
	delay_ms(200);
}
void i2c_write(unsigned char DATA){
	unsigned char i;
	for(i=0;i<8;i++){
		scl=0;
		i2c_delay();
		sda=(DATA&0x80>>i)?1:0; // send BIT by BIT to sda line
		scl=1;
	}
}

unsigned char i2c_read(void){
	unsigned char i,buff=0;
	for(i=0;i<8;i++){
	scl=0;
	scl=1;
	i2c_delay();
	if(sda)
		buff=buff | (0x80>>i);
	}
	return buff;
}

void i2c_ack(void){
	scl=0;
	i2c_delay();   // delay for start up time
	sda=1;
	i2c_delay();
	scl=1;
	while(sda==1);
}
void i2c_noack(void){
	scl=0;
	delay_ms(200);
	sda=1;
	delay_ms(200);
	scl=1;
	delay_ms(200);
}

void i2c_stop(){
	scl=0;
	i2c_delay();
	sda=0;
	delay_ms(200);
	scl=1;
	delay_ms(200);
	sda=1;
	delay_ms(200);
}
void i2c_device_write(unsigned char slave_addr,unsigned char buff_addr,unsigned char dat){
	i2c_start();
	delay_ms(200);
	i2c_write(slave_addr);
	delay_ms(200);
	i2c_ack();
	delay_ms(200);
	i2c_write(buff_addr);
	delay_ms(200);
	i2c_ack();
	delay_ms(200);
	i2c_write(dat);
	delay_ms(200);
	i2c_ack();
	delay_ms(200);
	i2c_stop();
	delay_ms(10);
}
unsigned char i2c_device_read(unsigned char sa,unsigned char addr){
	unsigned char buff;
	i2c_start();
	i2c_write(sa);
	i2c_ack();
	i2c_write(addr);
	i2c_ack();
	i2c_start();
	i2c_write(sa|1); // higher 7 bit have slave address and setting LSB(0th bit) to 1
	i2c_ack();
	buff=i2c_read();
	i2c_noack();
	i2c_stop();
	return buff;
}
