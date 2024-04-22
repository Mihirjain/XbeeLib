/*
 * XBee.c
 *
 * Jul 2, 2016
 *
 */

#include <string.h>
#include <stdlib.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "../include/XBee.h"
#include "../include/XBeeFrame.h"
#include "../include/ATMEGA328p.h"
#include "../hd44780/hd44780.h"

void XBee_ATModeEnable() {
	_delay_ms( 1500 );
	serial_WriteString( ( char* ) "+++" );
	_delay_ms( 1500 );
}

void XBee_ATModeDisable() {
	serial_WriteString( ( char* ) "ATCN" );
	serial_WriteString( ( char* ) "\r" );
}

/*
 *	1 for simple API operation
 *	2 for API with escape characters
 */
void XBee_APIModeEnable( int mode ) {
	_delay_ms(5000);
	_delay_ms(5000);
	XBee_ATModeEnable();
	if ( mode==2 )
		serial_WriteString( ( char*) "ATAP2\r" );
	else
		serial_WriteString( ( char*) "ATAP1\r" );
	serial_WriteString( (char*) "ATWR\r" );
	XBee_ATModeDisable();
}

void XBee_APIModeDisable() {
	_delay_ms(1500);
	serial_WriteString( ( char* ) "AP0" );
}

void XBee_WriteATCommand() {
	unsigned char temp[] = { 0x7e, 0x00, 0x04, 0x08, 0x55, 0x57, 0x52, 0xf9 }; // 57=W 52=R
	serial_WriteSizedString( temp, sizeof( temp ) );
}

void XBee_SetParameter( XBeeParameters_t parameter, unsigned char *parameterValue, unsigned char frameID ) {
	char *command;
	int parameterSize;
	APIATCommandFrame *frame = NULL;
	int size;
	unsigned char checksum;
	switch ( parameter ) {
	case CH:
		command = "CH";
		parameterSize=1;
		break;
	case ID:
		command = "ID";
		parameterSize=2;
		break;
	case DH:
		command = "DH";
		parameterSize=4;
		break;
	case DL:
		command = "DL";
		parameterSize=4;
		break;
	case SM:
		command = "SM";
		parameterSize=1;
		break;
	default :return;
	}
	if(parameterValue==NULL)
	    parameterSize=0;
	frame = generateATCommandFrame( ( unsigned char* ) command, parameterValue, frameID, parameterSize);
	size = sizeof( APIATCommandFrame ) +parameterSize;
	checksum = getChecksum( ( unsigned char* ) frame, size );
	serial_WriteSizedString( ( unsigned char* ) frame, size );
	serial_WriteSizedString( &checksum, 1 );
	if(parameterSize!=0)
		XBee_WriteATCommand();
	_delay_ms(100);
	free( frame );
}

void XBee_Escape_Frame( unsigned char frame[], int size ) {
    for ( int i=0; i<size; i++ ) {
        // bytes 7E, 7D, 11, 13 must be escaped
        // 7E only if it's not the first byte in the sequence
        if ( ( frame[i] == 0x7E && i != 0 ) ||
                frame[i] == 0x7D ||
                frame[i] == 0x11 ||
                frame[i] == 0x13 ) {
            unsigned char escape = 0x7D;
            unsigned char xord = frame[i] ^ 0x20;
            serial_WriteChar( escape );
            serial_WriteChar( xord );
        } else {
            serial_WriteChar( frame[i] );
        }
    }
}

int XBee_APISend_16bit( char payload[], unsigned char destAddr[], unsigned char frameID, unsigned char option ) {
	int payloadSize=strlen( payload );
	if(payloadSize>100)
		return -1;
	APITX16BitFrame *frame = generateTXFrame_16Bit( payload, destAddr, frameID, option );
	int frameSize = sizeof( APITX16BitFrame ) + payloadSize;
	unsigned char checksum = getChecksum( ( unsigned char* ) frame, frameSize );
	XBee_Escape_Frame( ( unsigned char* ) frame, frameSize );
	serial_WriteSizedString( &checksum, sizeof( checksum ) );
	free( frame );
	return 0;
}

int XBee_APISend_64bit( char payload[], unsigned char destAddr[], unsigned char frameId, unsigned char option ) {
	int payloadSize=strlen( payload );
	if(payloadSize>100)
		return -1;
	APITX64BitFrame *frame = generateTXFrame_64Bit( payload, destAddr, frameId, option );
	int frameSize = sizeof( APITX64BitFrame ) + payloadSize;
	unsigned char checksum = getChecksum( ( unsigned char* ) frame, frameSize );
	XBee_Escape_Frame( ( unsigned char* ) frame, frameSize );
	serial_WriteSizedString( &checksum, sizeof( checksum ) );
	free( frame );
	return 0;
}

void XBee_SleepModeEnable( int mode ) {
	XBee_SetParameter( SM, (unsigned char)mode, 0 );
}

void XBee_SleepModeDisable() {
	XBee_SetParameter( SM, (unsigned char)"0", 0 );
}

int XBee_read() {
	return readBuffer_APIRXFrame();
}

unsigned char *XBee_getPayoad() {
	return globalframe.rfData;
}

int XBee_getPayloadSize() {
	return globalframe.rfdatasize;
}

void XBee_get16BitSourceAddress(unsigned char addr[]) {
	addr[0]=globalframe.sourceAddr16bit[0];
	addr[1]=globalframe.sourceAddr16bit[1];
}

unsigned char XBee_getRSSI() {
	return globalframe.rssi;
}

unsigned char XBee_getOption() {
	return globalframe.options;
}

int XBee_getParameterSize(){
	return globalframe.parameterSize;
}

void XBee_getParameter(unsigned char value[]){
	for(int i=0;i<XBee_getParameterSize();i++){
		value[i]=globalframe.parameter[i];
	}
}

void XBee_readConfig() {
	XBee_ATModeEnable();
	int j;
	lcd_putc('a');
	serial_WriteString( ( char* )"ATCH" );
	for ( j=0; j<8; j++ ) { serial_ReadChar(); }	// data starts at byte 9
	configVals.CH = serial_ReadChar();
	lcd_putc('b');
	serial_WriteString( ( char* )"ATID" );
	for ( j=0; j<8; j++ ) { serial_ReadChar(); }
	for ( j=0; j<2; j++ ) { configVals.ID[j] = serial_ReadChar(); }
	lcd_putc('c');
	serial_WriteString( ( char* )"ATDH" );
	for ( j=0; j<8; j++ ) { serial_ReadChar(); }
	for ( j=0; j<4; j++ ) { configVals.DH[j] = serial_ReadChar(); }
	lcd_putc('d');
	serial_WriteString( ( char* )"ATDL" );
	for ( j=0; j<8; j++ ) { serial_ReadChar(); }
	for ( j=0; j<4; j++ ) { configVals.DL[j] = serial_ReadChar(); }
	lcd_putc('e');
	serial_WriteString( ( char* )"ATMY" );
	for ( j=0; j<8; j++ ) { serial_ReadChar(); }
	for ( j=0; j<2; j++ ) { configVals.MY[j] = serial_ReadChar(); }
	lcd_putc('f');
	void XBee_ATModeDisable();
}
