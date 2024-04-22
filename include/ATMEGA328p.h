/*
 * ATMEGA328p.h
 *
 *  Created on: 19.07.2016
 *      Author: Mihir
 */

#ifndef INCLUDE_ATMEGA328P_H_
#define INCLUDE_ATMEGA328P_H_

#define FCPU 16000000
#define BAUD 38400
#define MYUBRR ( FCPU / 16 / BAUD ) - 1

unsigned char bufferstring[128];
int buffersize;

void serial_Init( void );
unsigned char serial_ReadyToReceive( void );
unsigned char serial_ReadyToSend( void );
void serial_WriteChar( unsigned char );
void serial_WriteString( char[] );
void serial_WriteSizedString( unsigned char[], int );
unsigned char serial_ReadChar( void );

#endif /* INCLUDE_ATMEGA328P_H_ */
