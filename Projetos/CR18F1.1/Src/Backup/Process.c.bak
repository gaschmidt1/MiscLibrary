/*
 * Process.c
 *
 *  Created on: Aug 2, 2019
 *      Author: gerry
 */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "Process.h"
#include "fifo.h"
#include "string.h"


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

/* Private enumerations ------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
void SetProcessFunc(uint8_t Index, char Command[], uint8_t Size, void *Function);
uint8_t ProcessTask(uint8_t *Command);

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


void ProcessInit(void) {
//	SetProcessFunc(0, "Cx", 2, &SendOK);
//	SetProcessFunc(1, "Sy", 2, &SendData);
//	SetProcessFunc(2, "Bt", 2, &SendBT);
//	SetProcessFunc(3, "Can", 3, &ConvertAnSendOverCAN);
//
//	StartUsart1Receive485();
//
	fifo_init(&RS485FifoQueue, 8);
}

/*
 * RS485Periodic() - Run the command interpreter (needs to be called preriodically in main).
 */
void ProcessPeriodic(void) {
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

				if (memcmp(pf, ProcessVector[Index].Str485Command, ProcessVector[Index].CommandSize) == 0) {
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




/* Private function ----------------------------------------------------------*/
void ProcessCheck(void)
{

}


/*
 * pegar interpretador do jan termo higrometro 485
 *
 */
