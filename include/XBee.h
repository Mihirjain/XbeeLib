/*
 * XBee.h
 *
 * Jul 2, 2016
 *
 */

#ifndef XBEELIB_02_07_2016_INCLUDE_XBEE_H_
#define XBEELIB_02_07_2016_INCLUDE_XBEE_H_

typedef enum {
	/**
	 * Set/Read the channel number used for transmitting and receiving data
	 * between RF modules (uses 802.15.4 protocol channel numbers).
	 */
	CH,

	/**
	 * Set/Read the PAN (Personal Area Network) ID.
	 * Use 0xFFFF to broadcast messages to all PANs.
	 */
	ID,

	/**
	 * Set/Read the upper 32 bits of the 64-bit destination
	 * address. When combined with DL, it defines the destination address used for
	 * transmission. To transmit using a 16-bit address, set DH parameter to zero and DL less
	 * than 0xFFFF. 0x000000000000FFFF is the broadcast address for the PAN.
	 */
	DH,

	/**
	 * Set/Read the lower 32 bits of the 64-bit destination
	 * address. When combined with DH, DL defines the destination address used for
	 * transmission. To transmit using a 16-bit address, set DH parameter to zero and DL less
	 * than 0xFFFF. 0x000000000000FFFF is the broadcast address for the PAN.
	 */
	DL,

	/*
	 * Set/Read the current Sleep Mode
	 * SM = 0 => Sleep Mode disabled
	 */
	SM

} XBeeParameters_t;

typedef struct {
	unsigned char CH;
	unsigned char ID[2];
	unsigned char DH[4];
	unsigned char DL[4];
	unsigned char MY[2];
} XBeeConfig;
XBeeConfig configVals;

void XBee_ATModeEnable();
void XBee_ATModeDisable();
void XBee_APIModeEnable( int );
void XBee_APIModeDisable();
void XBee_SetParameter( XBeeParameters_t, unsigned char*, unsigned char );
void XBee_WriteATCommand();
void XBee_Escape_Frame( unsigned char[], int );
int XBee_APISend_16bit( char[], unsigned char[], unsigned char, unsigned char );
int XBee_APISend_64bit( char[], unsigned char[], unsigned char, unsigned char );
void XBee_SleepModeEnable( int );
void XBee_SleepModeDisable( void );
int XBee_read( void );
unsigned char* XBee_getPayoad( void );
int XBee_getPayloadSize();
void XBee_readConfig( void );
void XBee_get16BitSourceAddress(unsigned char addr[]);
unsigned char XBee_getRSSI();
unsigned char XBee_getOption();
void XBee_getParameter(unsigned char value[]);
int XBee_getParameterSize();
#endif /* XBEELIB_02_07_2016_INCLUDE_XBEE_H_ */



