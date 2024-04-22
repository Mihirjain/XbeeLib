///*
// * main4.c
// *
// *  Created on: 15.09.2016
// *      Author: Mihir
// */
//
//#include "include/XBee.h"
////#include "include/XBeeFrame.h"
//#include "include/ATMEGA328p.h"
//#include <avr/io.h>
//#include <string.h>
//#include <util/delay.h>
//#include <avr/interrupt.h>
//#include "hd44780/hd44780.h"
//
//void debugDisplay3(int character);
//void display();
//
//int main( void ) {
//	//DDRB |= ( 1<<PB5 );
//		cli();
//		serial_Init();
//		//XBee_APIModeEnable(2);
//		UCSR0B |= ( 1 << RXCIE0 );
//		UCSR0A |= ( 1 << RXC0 );
//		sei();
//		PORTB |= ( 1<<PB5 );
//		_delay_ms( 1000 );
//		PORTB &= ~( 1<<PB5 );
//		lcd_init();
//		lcd_puts("Ready...");
//		//unsigned char value[]={0x0D};
//		XBee_SetParameter(CH,NULL,0x4D);
//		_delay_ms(1000);
//		while (1) {
//			//lcd_puts("Ready To Receive");
//			//serial_WriteSizedString( temp, 14 );
//			//lcd_puts("asd");
//			//PORTB ^= ( 1<<PB5 );
//			int readStatus;
//			readStatus=XBee_read();
//			if(readStatus==0)
//				display();
//			_delay_ms(1000);
//
//		}
//		return 0;
//}
//
//void debugDisplay3(int character) {
//
//	int f = character/16 + 0x30;
//	if (f > 0x39)
//			f += 0x07;
//	lcd_putc(f);
//	int t = character%16 + 0x30;
//	if (t > 0x39)
//		t += 0x07;
//	lcd_putc(t);
//}
//
//void display(){
//	lcd_clrscr();
//	lcd_puts("ch: ");
unsigned char *value;
//	debugDisplay3(XBee_getParameterSize());
//	XBee_getParameter(value);
//	/*for(int i=0;i<XBee_getParameterSize();i++){
//		debugDisplay3( value[i]);
//	}*/
//	lcd_puts("HELLO");
//	_delay_ms(1000);
//
//}
