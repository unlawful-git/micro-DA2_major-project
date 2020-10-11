#include<reg51.h>
#include "Keypad.h"
#include "lcd.h"
void delay(unsigned int i){
unsigned int j;
for(;i>0;i--){
for(j=122;j>0;j--);
}
}

sbit R1=P2^4;
sbit R2=P2^5;
sbit R3=P2^6;
sbit R4=P2^7;
sbit C1=P2^1;
sbit C2=P2^2;
sbit C3=P2^3;

char keypad[4][3]={'3','2','1','6','5','4','9','8','7','#','0','*'};

unsigned char row_finder(int col){ //Function for finding the row for column 1
	unsigned char ch;
	R1=R2=R3=R4=1;
	C1=C2=C3=0;

	if(R1==0){
		//lcd_char(keypad[0][col]);
		ch=keypad[0][col];
	}
	else if(R2==0){
		//lcd_char(keypad[1][col]);
		ch=keypad[1][col];
	}
	else if(R3==0){
	//	lcd_char(keypad[2][col]);
		ch=keypad[2][col];
	}
	else if(R4==0){
	//	lcd_char(keypad[3][col]);
		ch=keypad[3][col];
	}
	return ch;
}

unsigned char keypad_input(){
	
	unsigned char pswd_char;
	//unsigned i/t pswd;
	C1=C2=C3=1;
	R1=R2=R3=R4=0;
	do{
		if(C1==0){
			pswd_char=row_finder(0);
			delay(500);
			break;
		}
		else if(C2==0){
			pswd_char=row_finder(1);
			delay(500);
			break;
		}
		else if(C3==0){
			pswd_char=row_finder(2);
			delay(500);
			break;
		}
	}while(C1==1 || C2==1 || C3==1);
	//pswd = (pswd_char-48);
	return pswd_char;
}
