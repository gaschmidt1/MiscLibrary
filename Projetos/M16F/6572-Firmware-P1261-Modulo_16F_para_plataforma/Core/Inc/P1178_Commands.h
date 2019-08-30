/*
 * P1178_Commands.h
 *
 *  Created on: 12 de fev de 2019
 *      Author: giovani
 */

#ifndef INC_P1178_COMMANDS_H_
#define INC_P1178_COMMANDS_H_

#include "Utilities.h"

void RecebeParametrosTubo(uint8_t *params, uint16_t size_of_params);
void RecebeParametrosRoscaDeElevacao(uint8_t *params, uint16_t size_of_params);
void RecebeParametrosOutros(uint8_t *params, uint16_t size_of_params);
void RecebeParametrosRoscaInferior(uint8_t *params, uint16_t size_of_params);
void RecebeParamatrosRoscaDoTubo(uint8_t *params, uint16_t size_of_params);
void LeParametrosRoscaDoTubo(uint8_t *params, uint16_t size_of_params);
void LeParametrosRoscaDeElevacao(uint8_t *params, uint16_t size_of_params);
void LeParametrosRoscaInferior(uint8_t *params, uint16_t size_of_params);
void LeParametrosTubo(uint8_t *params, uint16_t size_of_params);
void LeParametrosOutros(uint8_t *params, uint16_t size_of_params);

#endif /* INC_P1178_COMMANDS_H_ */
