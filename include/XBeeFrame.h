/*
 * XBeeFrame.h
 *
 * Jul 2, 2016
 *
 */

#ifndef XBEELIB_02_07_2016_INCLUDE_XBEEFRAME_H_
#define XBEELIB_02_07_2016_INCLUDE_XBEEFRAME_H_

typedef struct {
	unsigned char startDelimiter;			// 0x7e
	unsigned char lengthMSB;				// 0x00
	unsigned char lengthLSB;
	unsigned char apiIdentifier;			// 0x08
	unsigned char frameID;
	unsigned char ATCommandH;
	unsigned char ATCommandL;
	unsigned char parameter[];
} APIATCommandFrame;

typedef struct {
	unsigned char startDelimiter;			// 0x7E
	unsigned char lengthMSB;				// 0x00
	unsigned char lengthLSB;
	unsigned char apiIdentifier;
	unsigned char frameID;
	unsigned char destAddr[2];
	unsigned char option;
	unsigned char payload[];
} APITX16BitFrame;

typedef struct {
	unsigned char startDelimiter; 			// 0x7E
	unsigned char lengthMSB; 				// 0x00;
	unsigned char lengthLSB;
	unsigned char apiIdentifier;
	unsigned char frameID;
	unsigned char destAddr[8];
	unsigned char option;
	unsigned char payload[];
} APITX64BitFrame;

typedef struct {
	unsigned char sourceAddr16bit[2];
	unsigned char sourceAddr64bit[8];
	unsigned char frameid;
	unsigned char status;
	unsigned char rssi;
	unsigned char options;
	unsigned char command[2];
	unsigned char parameter[8];
	int parameterSize;
	unsigned char rfData[100];
	int rfdatasize;
} APIRXFrame; 

APIRXFrame globalframe;

unsigned char getChecksum( unsigned char[], int );
APIATCommandFrame* generateATCommandFrame( unsigned char[], unsigned char[], unsigned char, int );
APITX16BitFrame *generateTXFrame_16Bit( char[], unsigned char[], unsigned char, unsigned char );
APITX64BitFrame *generateTXFrame_64Bit( char[], unsigned char[], unsigned char, unsigned char );
void clearGlobalFrame( void );
int readBuffer_APIRXFrame( void );

#endif /* XBEELIB_02_07_2016_INCLUDE_XBEEFRAME_H_ */
