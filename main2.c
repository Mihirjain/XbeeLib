///*
// * main2.c
// *
// *  Created on: 19.07.2016
// *      Author: Mihir
// */
//
//#include <avr/io.h>
//#include <string.h>
//#include <util/delay.h>
//#include "include/XBee.h"
//#include "include/ATMEGA328p.h"
//#include "hd44780/hd44780.h"
//
//void debugDisplay3(int character);
//void display();
//
//int main( void ) {
//	DDRB |= ( 1<<PB5 );
//	//lcd_puts("Uart Initializing...");
//	serial_Init();
//	//XBee_APIModeEnable(2);
//	//lcd_clrscr();
//	//lcd_puts("API Initializing...");
//	lcd_init();
//	lcd_clrscr();
//	lcd_puts("Ready To Send...");
//	_delay_ms(1000);
//	unsigned char temp[] = {0x7E, 0x00, 0x0A, 0x01, 0x01, 0x00, 0x10, 0x00, 0x68, 0x65, 0x6c, 0x6c, 0x6f, 0xD9};
//
//	unsigned char dest16[]={0x00,0x15};
//	int i;
//	unsigned char dest64[]={0x00,0x13,0xA2,0x00,0x40,0xC3,0x48,0xAB};//CF
//	while (1) {
//		lcd_clrscr();
//		lcd_puts("sending 16 bit...");
//		_delay_ms(1000);
//		i=XBee_APISend_16bit(":D~}bbbbbb",dest16,0x4D,0x00);
//		if(i==0){
//			lcd_clrscr();
//			lcd_puts("16 bit sending success");
//			_delay_ms(2000);
//			lcd_clrscr();
//		}
//		else if(i==-1)
//			{lcd_puts("Payload bigger ");
//			 lcd_command(0xC0);
//			 lcd_puts("than 100");
//			 _delay_ms(2000);
//		}
//
//		lcd_clrscr();
//		lcd_puts("sending 64 bit...");
//		_delay_ms(1000);
//		i=XBee_APISend_64bit("HELLO WORLD :D~}	^",dest64,0x4D,0x00);
//		if(i==0){
//			lcd_clrscr();
//			lcd_puts("64 bit sending success");
//			_delay_ms(2000);
//			lcd_clrscr();
//		}
//		else if(i==-1)
//		 {lcd_puts("Payload bigger ");
//		  lcd_command(0xC0);
//		  lcd_puts("than 100");
//		  _delay_ms(2000);
//		 }
//
//		//serial_WriteSizedString( temp, 14 );
//	}
//
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
//	lcd_puts("s: ");
//	unsigned char addr[2];
//	XBee_get16BitSourceAddress(addr);
//	debugDisplay3( addr[0] );
//	debugDisplay3( addr[1] );
//	_delay_ms(1000);
//	lcd_clrscr();
//	lcd_puts("rssi: ");
//	debugDisplay3(XBee_getRSSI());
//	_delay_ms(1000);
//	lcd_clrscr();
//	lcd_puts("Option: ");
//	debugDisplay3(XBee_getOption());
//	_delay_ms(1000);
//	lcd_clrscr();
//	unsigned char *payload=XBee_getPayoad();
//	lcd_puts("RF:");
//	for(int i=0;i<XBee_getPayloadSize();i++){
//		if (i == 13) lcd_command(0xC0);
//		lcd_putc((char)*(payload+i));
//	}
//	_delay_ms(1000);
//}
