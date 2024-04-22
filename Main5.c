/*
 * Main.c
 *
 * Jul 2, 2016
 *
 */

#include "include/XBee.h"
//#include "include/XBeeFrame.h"
#include "include/ATMEGA328p.h"
#include <avr/io.h>
#include <string.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "hd44780/hd44780.h"

void debugDisplay3(int character);
void display();

int main( void ) {
	//DDRB |= ( 1<<PB5 );
	cli();
	serial_Init();
	//XBee_APIModeEnable(2);
	UCSR0B |= ( 1 << RXCIE0 );
	UCSR0A |= ( 1 << RXC0 );
	sei();
	PORTB |= ( 1<<PB5 );
	_delay_ms( 1000 );
	PORTB &= ~( 1<<PB5 );
	lcd_init();
	//lcd_puts("hi Mihir, Whats");
	lcd_command(0xC0);
	//lcd_puts("up my homie I am Manuel.");
	lcd_puts("Ready To Receive");
	//unsigned char temp[] = {0x7E, 0x00, 0x0A, 0x01, 0x01, 0x00, 0x10, 0x00, 0x68, 0x65, 0x6c, 0x6c, 0x6f, 0xD9};
	//XBee_setReadFlag(1);
	unsigned char value[]={0x0F};
	XBee_SetParameter(CH,value,0x4D);
	int readStatus;
	while (1) {
		//lcd_puts("Ready To Receive");
		//serial_WriteSizedString( temp, 14 );
		//lcd_puts("asd");
		//PORTB ^= ( 1<<PB5 );
		//

		//_delay_ms(1000);
		XBee_SetParameter(CH,NULL,0x4D);
		readStatus=XBee_read();
		if(readStatus==0)
			display();

		/*XBee_SetParameter(DH,NULL,0x4E);
		readStatus=XBee_read();
		if(readStatus==0)
			display();*/

		/*XBee_SetParameter(DL,NULL,0x4F);
		readStatus=XBee_read();
		if(readStatus==0)
			{display();
			 readStatus=1;
			}*/

		XBee_SetParameter(ID,NULL,0x4d);
		readStatus=XBee_read();
		if(readStatus==0)
			display();

	}
	return 0;

}

void debugDisplay3(int character) {

	int f = character/16 + 0x30;
	if (f > 0x39)
			f += 0x07;
	lcd_putc(f);
	int t = character%16 + 0x30;
	if (t > 0x39)
		t += 0x07;
	lcd_putc(t);
}

void display(){
	lcd_clrscr();
	unsigned char *value;
	XBee_getParameter(value);
	for(int i=0;i<XBee_getParameterSize();i++){
		debugDisplay3( value[i]);
	}
	_delay_ms(1000);
}
