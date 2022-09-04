#define F_CPU 1000000UL

#define D4 eS_PORTB4
#define D5 eS_PORTB5
#define D6 eS_PORTB6
#define D7 eS_PORTB7
#define RS eS_PORTA6
#define EN eS_PORTA7

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "lcd.h"

char arr[10] = "0123456789";

char col[]={
	1,2,4,8,16,32,64,128
};

char row[][8]={
	
	{0xff,0x24,0x24,0x00,0x00,0x00,0x00,0x00},  // Mirror
	{0xff,0x92,0x92,0x00,0x00,0x00,0x00,0x00},
	{0xff,0x49,0x49,0x00,0x00,0x00,0x00,0x00},
	{0xff,0x49,0x49,0x00,0x00,0x00,0x00,0x00},
	{0xff,0x24,0x24,0x00,0x00,0x00,0x00,0x00},
	{0xff,0x92,0x92,0x00,0x00,0x00,0x00,0x00},
	{0xff,0x92,0x92,0x00,0x00,0x00,0x00,0x00},
	{0xff,0x49,0x49,0x00,0x00,0x00,0x00,0x00},
	{0xff,0x24,0x24,0x00,0x00,0x00,0x00,0x00}
	
};

char dino[][8]={
	
	{0x00,0x80,0x80,0x80,0x00,0x00,0x00,0x00},
	{0x00,0x00,0x00,0x80,0x80,0x80,0x00,0x00}
};
int cliflag = 0b00000000;

ISR(INT2_vect)
{
	cliflag = cliflag ^ 0b00000001;
}

int count = 0,score = 0,loop = 0;
int main(void)
{
	MCUCSR = (1<<JTD);
	MCUCSR = (1<<JTD);
	
	DDRD = 0xFF;
	DDRC = 0xFF;
	DDRA = 0xFF;
	DDRB = 0xFF;
	
	//DDRB=0;
	PORTB=0xFF;
	
	int i=0,j=0,k=0,m=0;
	GICR = 1<<INT2;		          /* Enable INT2*/
	MCUCSR = MCUCSR & 0b10111111; /*Falling Edge*/
	
	_delay_ms(500);
	Lcd4_Init();
	Lcd4_Set_Cursor(1,3);
	Lcd4_Write_String("Patience!");
	_delay_ms(1500);
	Lcd4_Clear();
	
	while (1)
	{
		loop++;
		sei();
		if( count < 561){
			if(cliflag == 1)
			{
				
				for(k=0;k<1120;k++)
				{
					PORTA = 0x01;
					PORTC = col[i];
					PORTD = row[j][i]  ;
					
					PORTA = 0x02;
					PORTC = col[i];
					PORTD = row[j+1][i] | dino[1][i];
					
					PORTA = 0x04;
					PORTC = col[i];
					PORTD = row[j+2][i] ;
					 _delay_ms(.75);
					
					if(loop <= 15){
						_delay_ms(0.50);
					}
					else if(loop > 15 && loop <=30){
						_delay_ms(0.45);
					}
					else if(loop > 30 && loop <=45){
						_delay_ms(0.40);
					}
					else if(loop > 45 && loop <=60){
						_delay_ms(0.35);
					}
					else if(loop > 60 && loop <=75){
						_delay_ms(0.30);
					}
					else if(loop > 75 && loop <=100){
						_delay_ms(0.25);
					}
					else if(loop > 100 && loop <=125){
						_delay_ms(0.20);
					}
					else{
						_delay_ms(0.15);
					}
					
					i += 1;
					if (i>7)
					i=0;
					
				}
				
				j+=3;
				if(j>8)
				j=0;
				cliflag = 0b00000000;
				_delay_ms(0.1);
			}

			else
			{
				
				for(k=0;k<1120;k++)
				{
					PORTA = 0x01;
					PORTC = col[i];
					PORTD = row[j][i]  ;
					
					PORTA = 0x02;
					PORTC = col[i];
					PORTD = row[j+1][i] | dino[0][i];
					
					PORTA = 0x04;
					PORTC = col[i];
					PORTD = row[j+2][i] ;
					 _delay_ms(.75);
					
					if( (row[j+1][i] & dino[0][i]) != 0b00){
						if(loop > 1){
						count++;
						PORTA = PORTA | (1<<5);
						_delay_us(10);
						PORTA = PORTA & ~(1<<5);
					   }
					}
					
					if(loop <= 15){
						_delay_ms(0.50);
					}
					else if(loop > 15 && loop <=30){
						_delay_ms(0.45);
					}
					else if(loop > 30 && loop <=45){
						_delay_ms(0.40);
					}
					else if(loop > 45 && loop <=60){
						_delay_ms(0.35);
					}
					else if(loop > 60 && loop <=75){
						_delay_ms(0.30);
					}
					else if(loop > 75 && loop <=100){
						_delay_ms(0.25);
					}
					else if(loop > 100 && loop <=125){
						_delay_ms(0.20);
					}
					else{
						_delay_ms(0.15);
					}
					
					i += 1;
					if (i>7)
					i=0;
					
				}
				
				j+=3;
				if(j>8)
				j=0;
				//cliflag = 0b00000000;
				//_delay_ms(0.25);
			}
		}

		else{
			
			score = loop - 2;
			Lcd4_Set_Cursor(1,3);
			Lcd4_Write_String("GAME OVER!");
			_delay_ms(1000);
			Lcd4_Clear();
			Lcd4_Set_Cursor(2,2);
			Lcd4_Write_String("SCORE: ");
			Lcd4_Write_Char(arr[score/1000%10]);
			Lcd4_Write_Char(arr[score/100%10]);
			Lcd4_Write_Char(arr[score/10%10]);
			Lcd4_Write_Char(arr[score%10]);
			_delay_ms(1500);
			Lcd4_Clear();
			break;
		}
	}
}

