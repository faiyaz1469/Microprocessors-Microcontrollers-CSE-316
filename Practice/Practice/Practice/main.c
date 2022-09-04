/*
 * Practice.c
 *
 * Created: 4/4/2021 1:02:48 PM
 * Author : Faiyaz Nabil
 */ 

#include <avr/io.h>
//#define F_CPU 1000000
//#include <util/delay.h>


int main(void)
{
    /* Replace with your application code */
	
  // DDRA = 0b00000000;
   DDRB = 0x00;
   DDRC = 0xFF;
   //unsigned char count =0;
   PORTC = 0x00;
   PINB = 0x10;
   short c = 0;

    while (1) 
    {
		//unsigned char in = PINB;
		if(!(PINB & 1<<7))
		{
			c = PINB & (1<<0);
			c += (PINB & (1<<2)) ? 1 : 0;
			c += (PINB & (1<<4)) ? 1 : 0;
			
			PORTC = c & 1;
			if(c>1)
			{
				PORTC |= (1<<3);
			}
			
		}
		/*if(in & 0b00000001)
		{
			count=1;
		}
		if(in & 0b00000101)
		{
			count=2;
		}
		if(in & 0b00010101)
		{
			count++;
		}
		PORTC = count;
		_delay_ms(500);*/
    }
}

