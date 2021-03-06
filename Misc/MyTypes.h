/*
 * MyTypes.h
 *
 *  Created on: 4 de jun de 2019
 *      Author: gerry
 */

#ifndef INC_MYTYPES_H_
#define INC_MYTYPES_H_

#define BitSet(var, pos)	(var |=  (1 << (pos)))
#define BitClear(var, pos)	(var &= ~(1 << (pos)))
#define BitToogle(var, pos)	(var ^=  (1 << (pos)))
#define BitCheck(var, pos)	(var &   (1 << (pos)))

#define MaskSet(var, mask)      (var |=  mask)
#define MaskClear(var, mask)    (var &= ~mask)
#define MaskToogle(var, mask)	(var ^=  mask)
#define MaskCheck(var, mask)    (var &   mask)

#define MultBy10(x) ((x << 1) + (x << 2))
#define DivBy10(x)  ((x >> 1) + (x >> 2))

#define SwapNibbles(x) ((x >> 4) & 0x0F) | ((x << 4) & 0xF0)


typedef union {
    unsigned char u8v;

    struct {
        uint8_t nb0: 4;
        uint8_t nb1: 4;
    } Nibbles;

    struct {
        uint8_t bt0 : 1;
        uint8_t bt1 : 1;
        uint8_t bt2 : 1;
        uint8_t bt3 : 1;
        uint8_t bt4 : 1;
        uint8_t bt5 : 1;
        uint8_t bt6 : 1;
        uint8_t bt7 : 1;
    } bits;
} u8t;

typedef union {
    uint16_t u16v;
    uint8_t  u8v[1];

    struct {
        uint8_t lo;
        uint8_t hi;
    } bytes;

    struct {
        uint8_t nb0: 4;
        uint8_t nb1: 4;
        uint8_t nb2: 4;
        uint8_t nb3: 4;
    } Nibbles;

    struct {
        uint8_t bt0 : 1;
        uint8_t bt1 : 1;
        uint8_t bt2 : 1;
        uint8_t bt3 : 1;
        uint8_t bt4 : 1;
        uint8_t bt5 : 1;
        uint8_t bt6 : 1;
        uint8_t bt7 : 1;
        uint8_t bt8 : 1;
        uint8_t bt9 : 1;
        uint8_t bt10 : 1;
        uint8_t bt11 : 1;
        uint8_t bt12 : 1;
        uint8_t bt13 : 1;
        uint8_t bt14 : 1;
        uint8_t bt15 : 1;
    } bits;
} u16t;

typedef union {
    uint32_t u32v;
    uint16_t u16v[2];
    uint8_t  u8v[4];

    struct {
    	uint16_t lo;
    	uint16_t hi;
    } words;

    struct {
    	uint8_t lolo;
    	uint8_t lohi;
    	uint8_t hilo;
    	uint8_t hihi;
    } bytes;

    struct {
        uint8_t nb0: 4;
        uint8_t nb1: 4;
        uint8_t nb2: 4;
        uint8_t nb3: 4;
        uint8_t nb4: 4;
        uint8_t nb5: 4;
        uint8_t nb6: 4;
        uint8_t nb7: 4;
    } Nibbles;

    struct {
        uint8_t bt0 : 1;
        uint8_t bt1 : 1;
        uint8_t bt2 : 1;
        uint8_t bt3 : 1;
        uint8_t bt4 : 1;
        uint8_t bt5 : 1;
        uint8_t bt6 : 1;
        uint8_t bt7 : 1;
        uint8_t bt8 : 1;
        uint8_t bt9 : 1;
        uint8_t bt10 : 1;
        uint8_t bt11 : 1;
        uint8_t bt12 : 1;
        uint8_t bt13 : 1;
        uint8_t bt14 : 1;
        uint8_t bt15 : 1;
        uint8_t bt16 : 1;
        uint8_t bt17 : 1;
        uint8_t bt18 : 1;
        uint8_t bt19 : 1;
        uint8_t bt20 : 1;
        uint8_t bt21 : 1;
        uint8_t bt22 : 1;
        uint8_t bt23 : 1;
        uint8_t bt24 : 1;
        uint8_t bt25 : 1;
        uint8_t bt26 : 1;
        uint8_t bt27 : 1;
        uint8_t bt28 : 1;
        uint8_t bt29 : 1;
        uint8_t bt30 : 1;
        uint8_t bt31 : 1;
    } bits;
} u32t;

#endif /* INC_MYTYPES_H_ */
