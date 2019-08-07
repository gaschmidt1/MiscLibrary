/******************************************************************************/
/**
 * @file    Application.c
 * @author  gaschmidt1@gmail.com
 * @section DESCRIPTION
 * A HTU application implementation.
 */

/*******************************************************************************
 * Include Files
 */

#include "mcc_generated_files/mcc.h"
#include "Application.h"
#include "WS0010.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/*******************************************************************************
 * Private defines
 */
#define kProcessComands         3U
#define kMaxCommandSize         9U
#define kSendCXCommandPeriod    10000

/*******************************************************************************
 * Private prototypes
 */
void SendCX(void);
void SendSY(void);
void SendBT(void);
void SetProcessFunc(uint8_t Index, char Command[], uint8_t Size, void (*FunctionHandler)(void));

/*******************************************************************************
 * Private typedef
 */
typedef struct
{
  char Str485Command[kMaxCommandSize];
  uint8_t CommandSize;
  void 	(*PtrFunctionHandler)(void);
}ProcessStruct;

/*******************************************************************************
 * Private variables
 */
static ProcessStruct ProcessVector[kProcessComands];
static fifo_t AplicationQueue;

uint16_t CounterA = 0, CounterB = 0;
char StrTemp[5];
char StrRH[5];
uint8_t CxFlag = 0, RunFlag = 0;

void PrintLed(void);
void PrintData(uint8_t* StrTemp, uint8_t* StrRH);

/*
 * SetTick1S() - Control de time slot (Calback off the timer 1 (1ms))
 */
void SetTick1S(void)
{
    if(++CounterB > 500)
    {
       CounterB = 0; 
       RunFlag = 1;
    }
    
    if(++CounterA > kSendCXCommandPeriod)
    {
        CounterA = 0;
        CxFlag = 1;
    }
}

/*
 * SendCX() - Just a send Cx string over 485 interface
 */
void SendCX(void)
{
    PutsRS485((char*)"Cx");
}

/*
 * SendSY() - Just a send Sy string over 485 interface
 */
void SendSY(void)
{
    PutsRS485((char*)"Sy");
}

/*
 * SendBT() - Just a send Bt string over 485 interface
 */
void SendBT(void)
{
    PutsRS485((char*)"Bt");
}

/*
 * SetProcessFunc() - Applies a new command-line command interpreter
 * @Index: Number representing the command sequence in a vector struct
 * @Command[]: Constant string with received command
 * @Size: Number of characters constant string with received command
 * @*Function: Just a pointer a void function.
 */
void SetProcessFunc(uint8_t Index, char Command[], uint8_t Size, void (*FunctionHandler)(void))
{
  memcpy(ProcessVector[Index].Str485Command, Command, Size);
  ProcessVector[Index].CommandSize = Size;
  ProcessVector[Index].PtrFunctionHandler = FunctionHandler;  
}

/*
 * ProcessInit() - Just to configure and add new commands in Command interpreter (needs to be called in top off the main).
 */
void ProcessInit(void)
{
    TMR0_StopTimer();
    
    /* Add news commands */
    SetProcessFunc(0, "Cx", 2, SendCX);
    SetProcessFunc(1, "Ok", 2, SendSY);
    SetProcessFunc(2, "Bt", 2, SendBT);

    /* Initialize a Queue */
    fifo_init(&AplicationQueue, 4);
    
    /* Timer 1ms (set interrupt calback ar 1ms) */
    TMR0_SetInterruptHandler(SetTick1S);
  
    /* Init a oled display */
    Ws0010Init();
    
    //Ws0010BufString((const uint8_t*)"Hello Word !!!\n\a", 0, Ws0010Buf5x7Char);
    Ws0010PutGotoXY(1, 1);
    Ws0010BufGotoXY(1, 1);
    Ws0010BufBitmap(LogoClk, 180);
    Ws0010Refresh();
    DelayLongo();
    DelayLongo();
    Ws0010BufPatern(0x00, 200);
    Ws0010Refresh();
    TMR0_StartTimer();
    
    rs485EN_SetLow();
}
/*
 * RS485Periodic() - Run the command interpreter (needs to be called periodically in main).
 */
void ProcessPeriodic(void) 
{
    static int8_t Index, Mask = 0;
    uint8_t *pf;
    static uint8_t StrCommand[kMaxCommandSize * 5U];
    static uint8_t RS485Data, RxData, RxCks, i;
    
    PrintLed();
    
    if(rs485EN_GetValue() == 0)
    {
        if(GetsRS485(&RxData) == 1)
        {
            fifo_queue(&AplicationQueue, RxData);
        }else
        {
           if(CxFlag == 1)
           {
               CxFlag = 0;
               fifo_queue(&AplicationQueue, 'C');
               fifo_queue(&AplicationQueue, 'x');
           }
        }
    }
    
    while(fifo_dequeue(&AplicationQueue, &RS485Data) == 1) 
    {
        StrCommand[0] = StrCommand[1];
        StrCommand[1] = StrCommand[2];
        StrCommand[2] = StrCommand[3];
        StrCommand[3] = StrCommand[4];
        StrCommand[4] = StrCommand[5];
        StrCommand[5] = StrCommand[6];
        StrCommand[6] = StrCommand[7];
        StrCommand[7] = StrCommand[8];
        StrCommand[8] = StrCommand[9];
        StrCommand[9] = RS485Data;
        //StrCommand[10] = 0;
        
        for(Index = 0; Index < kProcessComands; Index++) 
        {
            for(Mask = 0; Mask < kMaxCommandSize; Mask++) 
            {
                pf = &StrCommand[Mask];

                if(memcmp(pf, ProcessVector[Index].Str485Command, ProcessVector[Index].CommandSize) == 0) 
                {
                    StrCommand[0] = 0;
                    StrCommand[1] = 0;
                    StrCommand[2] = 0;//+ 0
                    StrCommand[3] = 0;//1 1
                    StrCommand[4] = 0;//2 2
                    StrCommand[5] = 0;//. 3 
                    StrCommand[6] = 0;//3 4
                    StrCommand[7] = 0;//4 5 0
                    StrCommand[8] = 0;//5 6 1
                    StrCommand[9] = 0;//x 7 2
                    //StrCommand[10] = 0;
                    ProcessVector[Index].PtrFunctionHandler();                    
                    break;
                }
                else
                {
                    RxCks = 0;
                                       
                    if(((StrCommand[2] == '+') || (StrCommand[2] == '-')) && (StrCommand[5] == '.'))
                    {
                        for(i = 0; i < 8; i++)
                        {
                            RxCks ^= StrCommand[2 + i];                            
                        }
                        if(RxCks == 0)
                        {
                            for(i = 0; i < 5; i++)
                            {
                                StrTemp[i] = StrCommand[2 + i];
                            }
                            for(i = 0; i < 2; i++)
                            {
                                StrRH[i] = StrCommand[7 + i];
                            }
                            PrintData((uint8_t*)StrTemp, (uint8_t*)StrRH);
                            
                            StrCommand[0] = 0;
                            StrCommand[1] = 0;
                            StrCommand[2] = 0;//+ 0
                            StrCommand[3] = 0;//1 1
                            StrCommand[4] = 0;//2 2
                            StrCommand[5] = 0;//. 3 
                            StrCommand[6] = 0;//3 4
                            StrCommand[7] = 0;//4 5 0
                            StrCommand[8] = 0;//5 6 1
                            StrCommand[9] = 0;//x 7 2
                        }
                    }
                }
            }
        }
    }
}

void PrintLed(void)
{    
    static uint8_t flag;
    if(RunFlag == 1)
    {
        RunFlag = 0;
         Ws0010BufGotoXY(1, 1);
        if(flag == 1)
        {
            Ws0010BufPatern(0x06, 1);
            Ws0010BufPatern(0x0F, 2);
            Ws0010BufPatern(0x06, 1);
        }
        else
        {
            Ws0010BufPatern(0x06, 1);
            Ws0010BufPatern(0x09, 2);
            Ws0010BufPatern(0x06, 1);
        }
        Ws0010Refresh();
        flag = ! flag;
    }
}

void PrintData(uint8_t* StrTemp, uint8_t* StrRH)
{
    Ws0010PutGotoXY(1, 1);
    Ws0010BufGotoXY(1, 1);
    Ws0010BufPatern(0x00, 200);
    Ws0010PutGotoXY(1, 1);
    Ws0010BufGotoXY(1, 1);
    Ws0010BufPatern(0x0F, 1);
    Ws0010BufPatern(0x09, 2);
    Ws0010BufPatern(0x0F, 1);
    Ws0010BufGotoXY(1, 2);
    Ws0010Buf5x7Char((uint8_t)StrTemp[0], 0);
    Ws0010BufGotoXY(8, 1);
    Ws0010Buf9x16Char(StrTemp[1], 0);
    Ws0010Buf9x16Char(StrTemp[2], 0);
    Ws0010BufGotoXY(28, 2);
    Ws0010Buf5x7Char('.', 0);
    Ws0010BufGotoXY(33, 1);
    Ws0010Buf9x16Char(StrTemp[4], 0);
    Ws0010BufGotoXY(44, 1);
    Ws0010BufPatern(0x06, 1);
    Ws0010BufPatern(0x09, 2);
    Ws0010BufPatern(0x06, 1);
    Ws0010BufGotoXY(49, 1);
    Ws0010Buf5x7Char('C', 0);
    Ws0010BufGotoXY(66, 1);
    Ws0010Buf9x16Char(StrRH[0], 0);
    Ws0010Buf9x16Char(StrRH[1], 0);
    Ws0010BufGotoXY(88, 1);
    Ws0010Buf5x7Char('%', 0);
    Ws0010BufGotoXY(88, 2);
    Ws0010Buf5x7Char('R', 0);
    Ws0010Buf5x7Char('H', 0);
    Ws0010Refresh();
}
