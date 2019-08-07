/*
 * Process.c
 *
 *  Created on: 16 de abr de 2019
 *      Author: gerry
 */

/* Includes ------------------------------------------------------------------*/
#include "Process.h"
#include "main.h"
#include "i2c.h"
#include "string.h"
#include "usart.h"
#include "sht21.h"
#include "hdc1080.h"
#include "J1939.h"
#include "J1939_FRAMES.h"
#include "J1939_NML.h"
#include "fifo.h"

/* Private define ------------------------------------------------------------*/
#define kProcessComands 4U
#define kMaxCommandSize 3U

/* Private typedef -----------------------------------------------------------*/
typedef struct {
	char Str485Command[kMaxCommandSize];
	uint8_t CommandSize;
	void (*PtrFunction)(void);
} ProcessStruct;

/* Private variables ---------------------------------------------------------*/
static ProcessStruct ProcessVector[kProcessComands];

static uint8_t aTxbuffer[20] = { "485" };
static uint8_t bTxbuffer[20] = { "CAN" };

float Temperatura = 12.3;
float Umidade = 56.7;
uint8_t Bateria = 0;
extern Network_data Net;

/* Private enumerations ------------------------------------------------------*/
const enum {
	ST, DT, UT, PT, CT, DU, UU, CK
} Htu;

/* Private function prototypes -----------------------------------------------*/
void SendOK(void);
void SendData(void);
void ConvertAnSendOverCAN(void);
void SetProcessFunc(uint8_t Index, char Command[], uint8_t Size, void *Function);
uint8_t ProcessTask(uint8_t *Command);

/* Private function ----------------------------------------------------------*/

/*
 * SendBT() - Convert sensors, store in a buffer and send status off batery over RS485.
 */
void SendBT(void) {
	Bateria = 0u;
	Temperatura = 0.0f;
	Umidade = 0.0f;

	if (sht21_measure(&hi2c1, SHT21_RES_12_14BIT, SHT21_HEATER_OFF, &Bateria,
			&Temperatura, &Umidade) == HAL_OK) {
		HAL_GPIO_WritePin(LED_VD_GPIO_Port, LED_VD_Pin, GPIO_PIN_SET);
		if (Bateria == 0) {
			aTxbuffer[0] = 'B';
			aTxbuffer[1] = 't';
			aTxbuffer[2] = 'O';
			aTxbuffer[3] = 'K';
			Usart1Send485(aTxbuffer, 4);
		} else {
			aTxbuffer[0] = 'B';
			aTxbuffer[1] = 't';
			aTxbuffer[2] = 'E';
			aTxbuffer[3] = 'R';
			aTxbuffer[4] = 'R';
			Usart1Send485(aTxbuffer, 5);
		}
		HAL_GPIO_WritePin(LED_VD_GPIO_Port, LED_VD_Pin, GPIO_PIN_RESET);
	}

	else if (hdc1080_measure(&hi2c1, HDC1080_T_RES_14, HDC1080_RH_RES_14, 0,
			&Bateria, &Temperatura, &Umidade) == HAL_OK) {
		HAL_GPIO_WritePin(LED_VD_GPIO_Port, LED_VD_Pin, GPIO_PIN_SET);
		if (Bateria == 0) {
			aTxbuffer[0] = 'B';
			aTxbuffer[1] = 't';
			aTxbuffer[2] = 'O';
			aTxbuffer[3] = 'K';
			Usart1Send485(aTxbuffer, 4);
		} else {
			aTxbuffer[0] = 'B';
			aTxbuffer[1] = 't';
			aTxbuffer[2] = 'E';
			aTxbuffer[3] = 'R';
			aTxbuffer[4] = 'R';
			Usart1Send485(aTxbuffer, 5);
		}
		HAL_GPIO_WritePin(LED_VD_GPIO_Port, LED_VD_Pin, GPIO_PIN_RESET);
	}
}

/*
 * SendOK() - Convert sensors, store in a buffer and send status off convertions over RS485.
 */
void SendOK(void) {

	Bateria = 0u;
	Temperatura = 0.0f;
	Umidade = 0.0f;

	aTxbuffer[0] = 'O';
	aTxbuffer[1] = 'k';

	if (sht21_measure(&hi2c1, SHT21_RES_12_14BIT, SHT21_HEATER_OFF, &Bateria,
			&Temperatura, &Umidade) == HAL_OK) {
		HAL_GPIO_WritePin(LED_VD_GPIO_Port, LED_VD_Pin, GPIO_PIN_SET);
		Usart1Send485(aTxbuffer, 2);
		HAL_GPIO_WritePin(LED_VD_GPIO_Port, LED_VD_Pin, GPIO_PIN_RESET);
	}

	else if (hdc1080_measure(&hi2c1, HDC1080_T_RES_14, HDC1080_RH_RES_14, 0,
			&Bateria, &Temperatura, &Umidade) == HAL_OK) {
		HAL_GPIO_WritePin(LED_VD_GPIO_Port, LED_VD_Pin, GPIO_PIN_SET);
		Usart1Send485(aTxbuffer, 2);
		HAL_GPIO_WritePin(LED_VD_GPIO_Port, LED_VD_Pin, GPIO_PIN_RESET);
	}
}

/*
 * SendData() - Sends Temperatura and Umidade data buffers over RS485 in HTU format.
 */
void SendData(void) {
	uint8_t i;
	volatile uint16_t Aux = 0;
	if (Temperatura > 0.0f) {
		aTxbuffer[ST] = '+';

		Aux = (uint16_t) (Temperatura * 10.0f);
	} else {
		aTxbuffer[ST] = '-';
		Aux = (uint16_t) (Temperatura * -10.0f);
	}

	aTxbuffer[DT] = ((uint8_t) (Aux / 100)) + '0';
	Aux = (uint16_t) (Aux % 100);

	aTxbuffer[UT] = ((uint8_t) (Aux / 10)) + '0';
	aTxbuffer[PT] = ('.');
	aTxbuffer[CT] = ((uint8_t) (Aux % 10) + '0');
	Aux = (uint16_t) Umidade;

	aTxbuffer[DU] = ((uint8_t) (Aux / 10)) + '0';
	aTxbuffer[UU] = ((uint8_t) (Aux % 10)) + '0';
	aTxbuffer[CK] = 0;

	for (i = 0; i < 7; i++) {
		aTxbuffer[CK] ^= aTxbuffer[i];
	}
	HAL_GPIO_WritePin(LED_VD_GPIO_Port, LED_VD_Pin, GPIO_PIN_SET);
	Usart1Send485(aTxbuffer, 8);
	HAL_GPIO_WritePin(LED_VD_GPIO_Port, LED_VD_Pin, GPIO_PIN_RESET);
}

/*
 * SetProcessFunc() - Applies a new command-line command interpreter
 * @Index: Number representing the command sequence in a vector struct
 * @Command[]: Constant string with received command
 * @Size: Number of characters constant string with received command
 * @*Function: Just a pointer a void function.
 */
void SetProcessFunc(uint8_t Index, char Command[], uint8_t Size, void *Function) {
	memcpy(ProcessVector[Index].Str485Command, Command, Size);
	ProcessVector[Index].CommandSize = Size;
	ProcessVector[Index].PtrFunction = Function;
}

/*
 * SendData() - Configures the interpreter commands.
 */
void ProcessInit(void) {
	SetProcessFunc(0, "Cx", 2, &SendOK);
	SetProcessFunc(1, "Sy", 2, &SendData);
	SetProcessFunc(2, "Bt", 2, &SendBT);
	SetProcessFunc(3, "Can", 3, &ConvertAnSendOverCAN);

	StartUsart1Receive485();

	fifo_init(&RS485FifoQueue, 8);

	J1939_ProtocolInit();
	J1939_stk_init();
}

/*
 * RS485Periodic() - Run the command interpreter (needs to be called preriodically in main).
 */
void RS485Periodic(void) {
	static int8_t Index, Mask = 0;
	uint8_t *pf;
	static uint8_t StrCommand[kMaxCommandSize * 4U];
	static uint8_t RS485Data;

	while (fifo_dequeue(&RS485FifoQueue, &RS485Data) == 1) {
		StrCommand[0] = StrCommand[1];
		StrCommand[1] = StrCommand[2];
		StrCommand[2] = StrCommand[3];
		StrCommand[3] = RS485Data;

		for (Index = 0; Index < kProcessComands; Index++) {
			for (Mask = 0; Mask < 3; Mask++) {
				pf = &StrCommand[Mask];

				if (memcmp(pf, ProcessVector[Index].Str485Command,
						ProcessVector[Index].CommandSize) == 0) {
					StrCommand[0] = 0;
					StrCommand[1] = 0;
					StrCommand[2] = 0;
					StrCommand[3] = 0;

					(*ProcessVector[Index].PtrFunction)();
					break;
				}
			}
		}
	}
}

/*
 * StkPeriodic() - Run the j1939 interpreter (needs to be called preriodically at 1ms).
 */
inline void StkPeriodic(void) {
	J1939_stk_periodic();
}

/*
 * StartConversion() - Run the j1939 interpreter (needs to be called preriodically at 1ms).
 */
void StartConversion(void) {
	static uint8_t CanBuffer[3];
	CanBuffer[0] = 'C';
	CanBuffer[1] = 'a';
	CanBuffer[2] = 'n';
	fifo_queue(&RS485FifoQueue, CanBuffer[0]);
	fifo_queue(&RS485FifoQueue, CanBuffer[1]);
	fifo_queue(&RS485FifoQueue, CanBuffer[2]);
}

/*
 * ConvertAnSendOverCAN() - Convert sensors, store in a buffer and send status off convertion over CAN J1939.
 */
void ConvertAnSendOverCAN(void) {
	if (sht21_measure(&hi2c1, SHT21_RES_12_14BIT, SHT21_HEATER_OFF, &Bateria,
			&Temperatura, &Umidade) == HAL_OK) {
		HAL_GPIO_WritePin(LED_VD_GPIO_Port, LED_VD_Pin, GPIO_PIN_SET);
		bTxbuffer[0] = (int8_t) (Temperatura + 40.0f);
		bTxbuffer[1] = (int8_t) (Umidade * 2.5f);
		HAL_Delay(50);
		J1939_ProtocolRun(65164, bTxbuffer, GLOBADDR, Net.Address);
		HAL_GPIO_WritePin(LED_VD_GPIO_Port, LED_VD_Pin, GPIO_PIN_RESET);
	}

	if (hdc1080_measure(&hi2c1, HDC1080_T_RES_14, HDC1080_RH_RES_14,
	HDC1080_HEATER_OFF, &Bateria, &Temperatura, &Umidade) == HAL_OK) {
		HAL_GPIO_WritePin(LED_VD_GPIO_Port, LED_VD_Pin, GPIO_PIN_SET);

		bTxbuffer[0] = (int8_t) (Temperatura + 40.0f);
		bTxbuffer[1] = (int8_t) (Umidade * 2.5f);
		HAL_Delay(50);
		J1939_ProtocolRun(65164, bTxbuffer, GLOBADDR, Net.Address);
		HAL_GPIO_WritePin(LED_VD_GPIO_Port, LED_VD_Pin, GPIO_PIN_RESET);
	}

//	else {
//	HAL_GPIO_WritePin(LED_VD_GPIO_Port, LED_VD_Pin, GPIO_PIN_SET);
//		bTxbuffer[0] = 0xFF;
//		bTxbuffer[1] = 0xFF;
//		J1939_ProtocolRun(65164, bTxbuffer, GLOBADDR, Net.Address);
//	HAL_GPIO_WritePin(LED_VD_GPIO_Port, LED_VD_Pin, GPIO_PIN_RESET);
//	}
}

