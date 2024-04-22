/*
 * XBeeFrame.c
 *
 * Jul 2, 2016
 *
 */

#include <stdlib.h>
#include <string.h>
#include <avr/interrupt.h>
#include "../include/XBeeFrame.h"
#include "../include/ATMEGA328p.h"

unsigned char getChecksum( unsigned char frame[], int dataSize ) {
	int sum = 0;
	unsigned char checksum;
	for ( int i=3; i<dataSize; i++ )
		sum += frame[i];	// Add bytes apart from start delimiter and length
	sum &= 0xFF;										// Take lowest 8 bits
	checksum = 0xFF - sum;								// Subtract from 0xFF
	return checksum;
}

// Construct new AT Command frame
APIATCommandFrame* generateATCommandFrame( unsigned char command[], unsigned char parameterValue[], unsigned char frameID, int parameterSize ) {
	APIATCommandFrame *frame = malloc( sizeof( APIATCommandFrame ) + parameterSize );
	frame->startDelimiter = 0x7e;
	frame->lengthMSB = 0x00;
	frame->lengthLSB = 0x04 + parameterSize;
	frame->apiIdentifier = 0x08;
	frame->frameID = frameID;
	frame->ATCommandH = command[0];
	frame->ATCommandL = command[1];
	for ( int i=0; i<parameterSize; i++ )
		frame->parameter[i] = parameterValue[i];
	return frame;
}

APITX16BitFrame *generateTXFrame_16Bit( char payload[], unsigned char destAddr[], unsigned char frameId, unsigned char option ) {
	int payloadSize = strlen( payload );
	int frameSize = sizeof( APITX16BitFrame ) + payloadSize;
	APITX16BitFrame *frame = malloc ( frameSize );
	frame->startDelimiter = 0x7E;
	frame->apiIdentifier = 0x01;
	frame->frameID = frameId;
	frame->destAddr[0] = destAddr[0];
	frame->destAddr[1] = destAddr[1];
	frame->option = option;
	short length = sizeof( unsigned char ) *5 + payloadSize;
	frame->lengthLSB = length & 0xFF;
	frame->lengthMSB = length >> 8;
	for ( int i=0; i<payloadSize; i++ )
		frame->payload[i] = ( unsigned char ) payload[i];
	return frame;
}

APITX64BitFrame *generateTXFrame_64Bit( char payload[], unsigned char destAddr[], unsigned char frameId, unsigned char option ) {
	int payloadSize = strlen( payload );
	int frameSize = sizeof( APITX64BitFrame ) + payloadSize;
	APITX64BitFrame *frame = malloc ( frameSize );
	frame->startDelimiter = 0x7E;
	frame->apiIdentifier = 0x00;
	frame->frameID = frameId;
	for ( int i=0; i<8;i++ )
		frame->destAddr[i] = destAddr[i];
	frame->option = option;
	short length = sizeof ( unsigned char ) *11 + payloadSize;
	frame->lengthLSB = length & 0xFF;
	frame->lengthMSB = length >> 8;
	for ( int i=0; i<payloadSize; i++ )
		frame->payload[i] = ( unsigned char ) payload[i];
	return frame;
}

void clearGlobalFrame() {
	globalframe.frameid=0;
	globalframe.status=0;
	globalframe.rssi=0;
	globalframe.options=0;
	globalframe.rfdatasize=0;
}

int readBuffer_APIRXFrame() {

	unsigned char buffer[127];
    int size=0;
    cli();
	for (int i=0; i<buffersize; i++ ) {
        if (bufferstring[i] == 0x7D ) {
			buffer[size]=bufferstring[i+1]^0x20;
			size++;
			i+=1;
        } else {
            buffer[size]=bufferstring[i];
            size++;
        }
    }
    sei();
	unsigned char checksum = getChecksum( buffer, size-1);
	if ( buffer[size-1] != checksum )
		return -1;

	clearGlobalFrame();

	switch(buffer[3]){
		case 0x89 :	globalframe.frameid=buffer[4];
					globalframe.status=buffer[5];
					break;
		case 0x80 :	for ( int i=0; i<8; i++ )
						globalframe.sourceAddr64bit[i]= buffer[i+4];
					globalframe.rssi=buffer[12];
					globalframe.options=buffer[13];
					globalframe.rfdatasize=size-15;
					for (int i=0;i<globalframe.rfdatasize;i++)
						globalframe.rfData[i]=buffer[14+i];
					break;
		case 0x81 : for ( int i=0; i<2; i++ )
						globalframe.sourceAddr16bit[i] = buffer[i+4];
					globalframe.rssi=buffer[6];
					globalframe.options=buffer[7];
					globalframe.rfdatasize=size-9;
					for ( int i=0; i<globalframe.rfdatasize; i++ )
						globalframe.rfData[i] = buffer[8+i];
					break;
		case 0x88 : globalframe.frameid=buffer[4];
		            globalframe.command[0]=buffer[5];
		            globalframe.command[1]=buffer[6];
		            globalframe.status=buffer[7];
		            int i;
		            for(i=0;buffer[8+i]!=checksum;i++){
		                globalframe.parameter[i]=buffer[8+i];
		            }
		            globalframe.parameterSize=i;
		            break;
		default : return -2;
	}
	return 0;
}

