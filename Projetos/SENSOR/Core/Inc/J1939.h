#ifndef _J1939_H_
#define _J1939_H_

//#include "J1939_includes.h"
#define	J1939STACK_VERSION               130 //Version of the protocol stack , including the transport protocol function

#define  REQUEST_PGN                       0xEA00 
#define  REQUEST_PGN_NUM                   15


typedef volatile unsigned int   PGN_T;  /*unsigned 16 bit definition*/

#define  MUTIPLE_PACKAGE_TRANSPORT         0 // Whether to use multiple-packet transmission function   1:enable;  0:disable

// It used to define access to application layer filteringPGN
#define  PGN_NUM                          	10


#define NUMBER_TRANS_RX_BUFFERS            8
#define NUMBER_TRANS_TX_BUFFERS            8
#define NUMBER_PDU_BUFFERS                 8
#define BIG_E                              0 // If 0 is the Big-Endian, if 1 is Little-Endian
#define OUT_BUFFER_SIZE                    21
#define IN_BUFFER_SIZE                     21
#define CAN_MAX_BYTE_COUNT                 8
#define MIN_PDU2                           240
#define ADDR_NUM                           2

#define  J1939_FAULT_NUM                  (NUMBER_TRANS_RX_BUFFERS-2)/4  // May receive error code number

#define NODEADDR  							0x8E
#define GLOBADDR							0xFF
#define NULLADDR							0xFE


#define IDENTITY_NUMBER					0x00D001    //Product number(9bits) AND Serial Number (12bits)
#define MANUFACTURER_NUMBER				0x7D0
#define ECU_INSTANCE					0x00
#define FUNCTION_INSTANCE				0x00
#define FUNCTION_NUMBER					0x64
#define VEHICLE_SYS						0x00
#define VEHICLE_SYS_INST				0x00
#define INDUSTRY_GROUP					0x00
#define ARBITRARY_ADDRESS_CAPABLE   	0x00
#define RESERVED_BIT					0x00



//================================    Data type definitions    ===============================
typedef unsigned char   U08;    /*unsigned 8 bit definition */
typedef unsigned int    U16;    /*unsigned 16 bit definition*/
typedef unsigned long   U32;    /*unsigned 32 bit definition*/

typedef volatile unsigned char  VU08;   /*unsigned 8 bit definition */
typedef volatile unsigned int   VU16;   /*unsigned 16 bit definition*/
typedef volatile unsigned long  VU32;   /*unsigned 32 bit definition*/

typedef signed char     S08;    /*signed 8 bit definition */
typedef signed int      S16;    /*signed 16 bit definition*/
typedef signed long     S32;    /*signed 32 bit definition*/

typedef volatile signed char        VS08;   /*signed 8 bit definition */
typedef volatile signed int         VS16;   /*signed 16 bit definition*/
typedef volatile signed long        VS32;   /*signed 32 bit definition*/



/*
 * 	The number of allowed stack node address assignment ,
	this feature can be used if the future demand for change , then support multiple applications.
	The default is two nodes and broadcast addresses
 */


#define  WAIT_FOR_MESSAGE                 0//State Zero: Waiting for a BAM or RTS data packet to arrive
#define  INIT_REASSEMBLE_STRUCTURE        1//State One: Message reassemble structure and message timer are initialized.
#define  CHECK_PACKET                     2//State Two: The incoming message is for this node.
#define  SEND_ABORT                       3//State Three:  No more buffers to reassemble incoming message, Abort is sent.
#define  SEND_CTS_WITH_COUNT              4//State Four: Buffers are available to reassemble incoming message, send CTS back to sender to indicate number of packets between next CTS (TRANSPORT_PACKET_COUNT). 
#define	 WAIT_FOR_DATA                    5//State Five: Waiting for DATA type packet from source.
#define	 CHECK_TIMER                      6//State Six:  Message timer is checked for expiration.
#define	 RESET_REASSEMBLY_STRUCTURE       7//State Seven: Message reassemble structure is reset.
#define	 CHECK_DATA_PACKET                8//State Eight: A DATA type packet has arrived and checked.
#define	 SAVE_DATA                        9//State Nine: The data is saved in the message reassemble buffer
#define	 SEND_EOM                         10//State Ten:  EOM message is sent.
#define	 SEND_CTS                         11//State Eleven: CTS is sent to trigger more data from the sender. 
#define	 FILL_USER_MESSAGE                12//State Twelve: The J1939_RX_MESSAGE_T data structure is filled for user application.

#define  TP_CM                0xEC00       
#define  TP_CM_RTS            16
#define  TP_CM_CTS            17         
#define  TP_CM_ENDOFMSGACK    19
#define  TP_CM_ABORT          255
#define  TP_CM_BAM            32
#define  TP_DT                0xEB00
#define  TP_NONE		      0 


#define  PRIMED               1
#define  NOTPRIMED            0 

#ifndef NULL
#define  NULL                 0
#endif

#ifndef TRUE
#define  TRUE				  1
#endif

#ifndef FALSE				  
#define  FALSE			      0
#endif

typedef struct
{
  PGN_T PGN;
  VU08  data[NUMBER_TRANS_TX_BUFFERS];
  VU16  byte_count;
  VU08  priority;  // priority
  VU08  dest_addr; //Destination address
  VU08 	source_addr;
  VS08  status;
}J1939_TX_MESSAGE_T;

typedef struct
{
	PGN_T PGN;
	VU08  data[NUMBER_TRANS_RX_BUFFERS];
	VU16  byte_count;
	VU08  source_addr;
	VU08  dest_addr;
}J1939_RX_MESSAGE_T;

typedef struct
{
	PGN_T PGN;
	VU08  data[NUMBER_PDU_BUFFERS];
	VU16  byte_count;
	VU08  source_addr;
	VU08  dest_addr;
}J1939_PDU_T;

typedef struct
{
	PGN_T PGN;
	VU08  status;
	VU08  packet_number;
	VU08  total_packet_number;
	VU16  byte_count;
	VU16  timer_counter;
	VU08  source_addr;
	VU08  dest_addr;
	VU08  TP;
}RECEIVE_STATU_MACHINE_T;

typedef struct
{
   VU32 	identifier;
   VU08 	data[CAN_MAX_BYTE_COUNT];
   VU08 	byte_count;
}CAN_PACKET_T;

typedef struct
{
   CAN_PACKET_T *buffer;
   VU16 head;    //Unsigned short value of the head index.
   VU16 tail;    //Unsigned short value of the tail index.
   VU08 buffer_size;
}RING_T;

typedef enum J1939_Addr
{
	ADDR_CLAIMED = 0x01,
	ADDR_CANNOT_CLAIM = 0x02,
	CLAIMING_ADDR = 0x03,

}J1939_Addr_Signals;

typedef enum J1939_Status
{
	ONLINE = 0x01,
	OFFLINE = 0x02,
}J1939_Status_Signals;


typedef struct
{
	J1939_Addr_Signals Addr_Status ;
	J1939_Status_Signals General_status ;
	J1939_TX_MESSAGE_T * txJ1939;
	J1939_RX_MESSAGE_T * rxJ1939;

} J1939_STRUCTURE;

//========================================================================================
//protocol stack Interface Functions
//========================================================================================
void J1939_stk_init(void);//Stack Initialization function
void J1939_stk_periodic(void);//Stack cycle handler

extern J1939_STRUCTURE J1939;
//extern static J1939_TX_MESSAGE_T TxJ1939msg;
//extern static J1939_RX_MESSAGE_T RxJ1939msg;

#endif
