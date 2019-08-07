/* 
 * File:   WS0010.h
 * Author: gerry
 *
 * Created on May 24, 2019, 10:22 AM
 */

#ifndef WS0010_H
#define	WS0010_H

#include "mcc_generated_files/mcc.h"
#include "Ascii.h"

#ifdef	__cplusplus
extern "C"
{
#endif

/*------------------------------------------------------------------------------
 ***   ROTINA DE COMUNICAÇÃO COM Ws0010  ***
 ***   Gerry Adriano Schmidt    ***
 ***      STATUS OK       ***
--------------------------------------------------------------------------------
                               REV: 29-11-2010
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
 ***   Definições do Ws0010   ***
------------------------------------------------------------------------------*/

#define TrisLcdEn oledEN_TRIS
#define TrisLcdRs oledRS_TRIS
#define EnLcd     oledEN_LAT
#define RsLcd     oledRS_LAT

#define USE_PORTA_LCD
#define USE_LOW_NIBBLE_LCD

#define DelayWs0010()    __delay_us(10)

#define LcdBufferLen  200
#define LcdNbrLines     2


//extern uint16_t reinit_cnt;

extern uint8_t Ws0010_buffer[LcdBufferLen];
//extern uint8_t ScrollBuffer[LcdBufferLen];

extern uint16_t ptr;

#if defined(USE_PORTA_LCD)
#define    PortLcd   LATA
#define    TrisLcd   TRISA
#elif  defined(USE_PORTB_LCD)
#define    PortLcd   LATB
#define    TrisLcd   TRISB
#elif defined(USE_PORTC_LCD)
#define    PortLcd   LATC
#define    TrisLcd   TRISC
#elif defined(USE_PORTD_LCD)
#define    PortLcd   LATD
#define    TrisLcd   TRISD
#endif

#if   defined(USE_LOW_NIBBLE_LCD)
#define NIBBLE1              0xF0
#define NIBBLE2              0x0F
#elif defined(USE_HIGH_NIBBLE_LCD)
#define NIBBLE1              0x0F
#define NIBBLE2              0xF0
#else
#define NIBBLE1              0x00
#define NIBBLE2              0xFF
#endif

#define LIMPA                0x01       // Clear Display
#define HOME                 0x02       // Cursor to Home position
#define NORMAL               0x06       // Normal entry mode
#define REVERSO              0x04       // Normal entry mode  -reverse direction
#define SCROLL               0x07       // - with shift
#define REV_SCROLL           0x05       // reverse direction

#define DISPLAY_ON           0x0C       // Display ON - 2 line mode
#define DISPLAY_OFF          0x08       // Display off

#define CURSOR_OFF           0x0C       // Sem cursor
#define CURSOR_PISCA         0x0D
#define CURSOR_ON            0x0E       // Cursor tipo barra
#define CURSOR_ALT           0x0F       // Cursor barra pisca

#define CURSOR_DIR           0x14       // Move cursor right
#define CURSOR_ESQ           0x10       // Move cursor left
#define DISPLAY_DIR          0x1C       // Scroll display right
#define DISPLAY_ESQ          0x18       // Scroll display left

#define TIME   5 //1
#define REINIT 6240 // aprox 30 segundos

#define envia_nibble(x) (PortLcd |= (x & NIBBLE2))
#define SwapNibbles(x) ((x & 0x0F) << 4 | (x & 0xF0) >> 4) 

void DelayLongo(void);

/*------------------------------------------------------------------------------
 ***     Rotina que envia o byte   ***
------------------------------------------------------------------------------*/
void Ws0010PutByte(uint8_t end, uint8_t fras);
/*------------------------------------------------------------------------------
 ***     Rotina que inicializa o LCD   ***
------------------------------------------------------------------------------*/
void Ws0010Init(void);
/*------------------------------------------------------------------------------
 ***     Rotina que posiciona LCD   ***
------------------------------------------------------------------------------*/
void Ws0010PutGotoXY(uint8_t posx, uint8_t posy);
/*------------------------------------------------------------------------------
 ***     operações com buffer     ***
------------------------------------------------------------------------------*/
void Ws0010BufGotoXY(uint8_t posx, uint8_t posy);
/*------------------------------------------------------------------------------
                        Rotina para escrever no display
------------------------------------------------------------------------------*/
void Ws0010Buf5x7Char(uint8_t carac, uint8_t inv);
void Ws0010Buf4x6Char(uint8_t carac, uint8_t inv);
void Ws0010Buf9x16Char(uint8_t carac, uint8_t inv);
/*------------------------------------------------------------------------------
                        Rotina para escrever no display
------------------------------------------------------------------------------*/
void Ws0010BufString(const uint8_t *frase, uint8_t inv, void(*Ptr2Func)(uint8_t, uint8_t));
/*------------------------------------------------------------------------------
                        Rotina para escrever no display
------------------------------------------------------------------------------*/
void Ws0010Bufu8(uint8_t inteiro, uint8_t nro, uint8_t inv, void(*Ptr2Func)(uint8_t, uint8_t));
void Ws0010Bufu16(uint16_t inteiro, uint8_t nro, uint8_t inv, void(*Ptr2Func)(uint8_t, uint8_t));
void Ws0010Bufu32(uint32_t inteiro, uint8_t nro, uint8_t inv, void(*Ptr2Func)(uint8_t, uint8_t));
/*------------------------------------------------------------------------------
 ***                           ***
------------------------------------------------------------------------------*/
void Ws0010BufPatern(uint8_t dado, uint8_t count);
/*------------------------------------------------------------------------------
            escreve uma barra de progresso
------------------------------------------------------------------------------*/
void Ws0010BufBargraph(uint8_t percent, uint8_t size);
/*------------------------------------------------------------------------------
                        Rotina para escrever no display
------------------------------------------------------------------------------*/
void Ws0010Refresh(void);
/*------------------------------------------------------------------------------
                        Rotina para desenhar o logo no display
------------------------------------------------------------------------------*/
void Ws0010BufBitmap(const uint8_t* Image, uint8_t Size);
/*------------------------------------------------------------------------------
                        Rotina para escrever um cursor
------------------------------------------------------------------------------*/
void Ws0010BufCursor(uint8_t comp);
/*------------------------------------------------------------------------------
                        Rotina para escrever um cursor
------------------------------------------------------------------------------*/
void Ws0010BufBinary(uint16_t data, uint8_t nro);

#ifdef	__cplusplus
}
#endif

#endif	/* WS0010_H */