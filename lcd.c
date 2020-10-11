#include <reg51.h>
void delay_ms (unsigned int);

sbit rs=P1^4;
sbit rw=P1^5;
sbit en=P1^6;

void lcd_display(unsigned char ch)   // pass display
{
P3=ch;
rw=0;
	en=1;
delay_ms(2);
en=0;
}
void lcd_cmd(unsigned char ch)   // command mode
{
rs=0;
lcd_display(ch);
}
void lcd_init(void)   //initialize
{
lcd_cmd(0x30);    // visit instructions in datasheet
delay_ms(150);
lcd_cmd(0x30);
delay_ms(150);
lcd_cmd(0x30);
delay_ms(150);
lcd_cmd(0x38);
lcd_cmd(0x10);
lcd_cmd(0x01);
lcd_cmd(0x06);
lcd_cmd(0x0f);
}

void lcd_char(unsigned char ch)  //character receive
	{
rs=1;
lcd_display(ch);
}

/*void lcd_str(unsigned char *ch)   // string receive. Not used here (coded for future uses)
{
while(*ch)
{
lcd_display(*ch);
ch++;
}
}
*/
