/*
 * J1939_NML.h
 *
 *  Created on: 14 de jul de 2016
 *      Author: Giovani
 */

#ifndef J1939_NML_H_
#define J1939_NML_H_


#define TIM_250ms (uint16_t) 250;
#define TIM_1000ms (uint16_t) 1000;

#include <stdint.h>
typedef struct
{
	uint8_t Address;
	uint8_t Name[8];
	uint64_t Name_Cpt;
}Network_data;


void NML_init(void);
void NML_RqstAddr(void);
void NML_Periodic(void);




#endif /* J1939_NML_H_ */
