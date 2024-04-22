///*
// * Main.c
// *
// * Jul 2, 2016
// *
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
//void pinInterrupt();
//ISR(PCINT0_vect)
//{
//	PORTB^=(1<<PB5);
//}
//
//int main( void ) {
//	//DDRB |= ( 1<<PB5 );
//	cli();
//	serial_Init();
//	//XBee_APIModeEnable(2);
//	UCSR0B |= ( 1 << RXCIE0 );
//	UCSR0A |= ( 1 << RXC0 );
//	sei();
//	PORTB |= ( 1<<PB5 );
//	_delay_ms( 1000 );
//	PORTB &= ~( 1<<PB5 );
//	lcd_init();
//	//lcd_puts("hi Mihir, Whats");
//	lcd_command(0xC0);
//	//lcd_puts("up my homie I am Manuel.");
//	lcd_puts("Ready To Receive");
//	//unsigned char temp[] = {0x7E, 0x00, 0x0A, 0x01, 0x01, 0x00, 0x10, 0x00, 0x68, 0x65, 0x6c, 0x6c, 0x6f, 0xD9};
//	//XBee_setReadFlag(1);
//	pinInterrupt();
//	while (1) {
//		//lcd_puts("Ready To Receive");
//		//serial_WriteSizedString( temp, 14 );
//		//lcd_puts("asd");
//		//PORTB ^= ( 1<<PB5 );
//		int readStatus;
//		readStatus=XBee_read();
//		if(readStatus==0)
//			display();
//
//	}
//	return 0;
//
//}
//
//void pinInterrupt(){
//	DDRB &= ~(1 << DDB0);     // Clear the PB0 pin
//    PORTB |= (1 << PORTB0);    // turn On the Pull-up
//    // PB0 is now an input with pull-up enabled
//    PCICR |= (1 << PCIE0);    // set PCIE0 to enable PCMSK0 scan
//    PCMSK0 |= (1 << PCINT0);  // set PCINT0 to trigger an interrupt on state change
//    sei();
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
