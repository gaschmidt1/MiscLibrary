/******************************************************************************/
/**
 * @file    Rs485.c
 * @author  gaschmidt1@gmail.com
 * @section DESCRIPTION
 * A generic rs485 implementation.
 */

/*******************************************************************************
 * Include Files
 */

#include "mcc_generated_files/mcc.h"
#include "Rs485.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void PutsRS485( char* s ) 
{
    rs485EN_SetHigh();
    //__delay_ms(2);
    for( int i = 0; i < strlen(s); i++ )
    {
        EUSART_Write(s[i]);
    }
    
    while(!EUSART_is_tx_done())
    {
    //    __delay_ms(2);
    }
    //__delay_ms(2);
    rs485EN_SetLow();
}

uint8_t GetsRS485(uint8_t* RxData)
{
    //volatile uint8_t RxData;
    volatile eusart_status_t RxStatus;  
    uint8_t Ret = 0; 
    if(EUSART_is_rx_ready())
    {
        *RxData = EUSART_Read();  
        Ret = 1;
        RxStatus = EUSART_get_last_status();        
        if (RxStatus.ferr) 
        {
            Ret = 0;
        }
    } 
    return(Ret);
}
