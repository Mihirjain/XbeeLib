/*
 * ATMEGA328p.c
 *
 *  Created on: 19.07.2016
 *      Author: Mihir
 */

#include <avr/io.h>
#include <string.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "../include/ATMEGA328p.h"
#include "../hd44780/hd44780.h"

void serial_Init() {
	DDRD = _BV( 1 );
	UBRR0H = ( unsigned char )( MYUBRR>>8 );
	UBRR0L = ( unsigned char ) MYUBRR;
	// Enable receiver and transmitter
	UCSR0B = ( 1<<RXEN0 ) | ( 1<<TXEN0 );
	// Frame format: 8N1 ( 8data, No parity, 1stop bit )
	UCSR0C = ( 3<<UCSZ00 );
}

/*
 * Check if data is available for reading
 * Return 0 if no data is available
 */
unsigned char serial_ReadyToReceive() {
	return ( UCSR0A & _BV( RXC0 ) );
}

/*
 * Check if device is ready to send data
 * Return 0 if device is not ready to send
 */
unsigned char serial_ReadyToSend() {
	return ( UCSR0A & _BV( UDRE0 ) );
}

void serial_WriteChar( unsigned char data ) {
	while ( serial_ReadyToSend() == 0 ) {}
	UDR0 = data;
}

// For when strings are passed literally
void serial_WriteString( char data[] ) {
	for ( int i=0; i<strlen( data ); i++ ) {
		serial_WriteChar( data[i] );
	}
}

// For when sizeof and strlen are used
void serial_WriteSizedString( unsigned char data[], int size ) {
	for ( int i=0; i<size; i++ ) {
		serial_WriteChar( data[i] );
	}
}

unsigned char serial_ReadChar() {
	while ( serial_ReadyToReceive() == 0 ) {}
	return UDR0;
}

ISR( USART_RX_vect ) {
	PORTB|=(1<<PB5);
	unsigned char *readChars=bufferstring;
	int length = 0, loop = 4;
	unsigned char nextChar;

	while ( length < loop ) {
		nextChar = serial_ReadChar();
		readChars[length] = nextChar;
		length++;
		if ( length == 3 ) {
			loop = (int) nextChar + 4;
		}
	}

	buffersize=length;
	PORTB&=~(1<<PB5);
}
