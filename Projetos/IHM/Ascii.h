/* 
 * File:   Ascii.h
 * Author: gerry
 *
 * Created on May 24, 2019, 10:21 AM
 */

#ifndef ASCII_H
#define	ASCII_H

#ifdef	__cplusplus
extern "C"
{
#endif

#include "mcc_generated_files/mcc.h"

extern const uint8_t ascii_table9x16[12][18];
extern const uint8_t ascii_table5x7[97][5];
extern const uint8_t ascii_table4x6[95][4];

#define SizeOffLogoClk 180
extern const uint8_t LogoClk[SizeOffLogoClk];
//#define SizeOffLogoSebras 142
//extern u8r LogoSebras[SizeOffLogoSebras];

#ifdef	__cplusplus
}
#endif

#endif	/* ASCII_H */

