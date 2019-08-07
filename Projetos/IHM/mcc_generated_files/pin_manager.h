/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for .
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.76
        Device            :  PIC18F46K20
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.00
        MPLAB 	          :  MPLAB X 5.10	
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

/**
  Section: Included Files
*/

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set oledD0 aliases
#define oledD0_TRIS                 TRISAbits.TRISA0
#define oledD0_LAT                  LATAbits.LATA0
#define oledD0_PORT                 PORTAbits.RA0
#define oledD0_ANS                  ANSELbits.ANS0
#define oledD0_SetHigh()            do { LATAbits.LATA0 = 1; } while(0)
#define oledD0_SetLow()             do { LATAbits.LATA0 = 0; } while(0)
#define oledD0_Toggle()             do { LATAbits.LATA0 = ~LATAbits.LATA0; } while(0)
#define oledD0_GetValue()           PORTAbits.RA0
#define oledD0_SetDigitalInput()    do { TRISAbits.TRISA0 = 1; } while(0)
#define oledD0_SetDigitalOutput()   do { TRISAbits.TRISA0 = 0; } while(0)
#define oledD0_SetAnalogMode()      do { ANSELbits.ANS0 = 1; } while(0)
#define oledD0_SetDigitalMode()     do { ANSELbits.ANS0 = 0; } while(0)

// get/set oledD1 aliases
#define oledD1_TRIS                 TRISAbits.TRISA1
#define oledD1_LAT                  LATAbits.LATA1
#define oledD1_PORT                 PORTAbits.RA1
#define oledD1_ANS                  ANSELbits.ANS1
#define oledD1_SetHigh()            do { LATAbits.LATA1 = 1; } while(0)
#define oledD1_SetLow()             do { LATAbits.LATA1 = 0; } while(0)
#define oledD1_Toggle()             do { LATAbits.LATA1 = ~LATAbits.LATA1; } while(0)
#define oledD1_GetValue()           PORTAbits.RA1
#define oledD1_SetDigitalInput()    do { TRISAbits.TRISA1 = 1; } while(0)
#define oledD1_SetDigitalOutput()   do { TRISAbits.TRISA1 = 0; } while(0)
#define oledD1_SetAnalogMode()      do { ANSELbits.ANS1 = 1; } while(0)
#define oledD1_SetDigitalMode()     do { ANSELbits.ANS1 = 0; } while(0)

// get/set oledD2 aliases
#define oledD2_TRIS                 TRISAbits.TRISA2
#define oledD2_LAT                  LATAbits.LATA2
#define oledD2_PORT                 PORTAbits.RA2
#define oledD2_ANS                  ANSELbits.ANS2
#define oledD2_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define oledD2_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define oledD2_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define oledD2_GetValue()           PORTAbits.RA2
#define oledD2_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define oledD2_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define oledD2_SetAnalogMode()      do { ANSELbits.ANS2 = 1; } while(0)
#define oledD2_SetDigitalMode()     do { ANSELbits.ANS2 = 0; } while(0)

// get/set oledD3 aliases
#define oledD3_TRIS                 TRISAbits.TRISA3
#define oledD3_LAT                  LATAbits.LATA3
#define oledD3_PORT                 PORTAbits.RA3
#define oledD3_ANS                  ANSELbits.ANS3
#define oledD3_SetHigh()            do { LATAbits.LATA3 = 1; } while(0)
#define oledD3_SetLow()             do { LATAbits.LATA3 = 0; } while(0)
#define oledD3_Toggle()             do { LATAbits.LATA3 = ~LATAbits.LATA3; } while(0)
#define oledD3_GetValue()           PORTAbits.RA3
#define oledD3_SetDigitalInput()    do { TRISAbits.TRISA3 = 1; } while(0)
#define oledD3_SetDigitalOutput()   do { TRISAbits.TRISA3 = 0; } while(0)
#define oledD3_SetAnalogMode()      do { ANSELbits.ANS3 = 1; } while(0)
#define oledD3_SetDigitalMode()     do { ANSELbits.ANS3 = 0; } while(0)

// get/set rtcSQO aliases
#define rtcSQO_TRIS                 TRISAbits.TRISA4
#define rtcSQO_LAT                  LATAbits.LATA4
#define rtcSQO_PORT                 PORTAbits.RA4
#define rtcSQO_SetHigh()            do { LATAbits.LATA4 = 1; } while(0)
#define rtcSQO_SetLow()             do { LATAbits.LATA4 = 0; } while(0)
#define rtcSQO_Toggle()             do { LATAbits.LATA4 = ~LATAbits.LATA4; } while(0)
#define rtcSQO_GetValue()           PORTAbits.RA4
#define rtcSQO_SetDigitalInput()    do { TRISAbits.TRISA4 = 1; } while(0)
#define rtcSQO_SetDigitalOutput()   do { TRISAbits.TRISA4 = 0; } while(0)

// get/set qeSW aliases
#define qeSW_TRIS                 TRISBbits.TRISB1
#define qeSW_LAT                  LATBbits.LATB1
#define qeSW_PORT                 PORTBbits.RB1
#define qeSW_WPU                  WPUBbits.WPUB1
#define qeSW_ANS                  ANSELHbits.ANS10
#define qeSW_SetHigh()            do { LATBbits.LATB1 = 1; } while(0)
#define qeSW_SetLow()             do { LATBbits.LATB1 = 0; } while(0)
#define qeSW_Toggle()             do { LATBbits.LATB1 = ~LATBbits.LATB1; } while(0)
#define qeSW_GetValue()           PORTBbits.RB1
#define qeSW_SetDigitalInput()    do { TRISBbits.TRISB1 = 1; } while(0)
#define qeSW_SetDigitalOutput()   do { TRISBbits.TRISB1 = 0; } while(0)
#define qeSW_SetPullup()          do { WPUBbits.WPUB1 = 1; } while(0)
#define qeSW_ResetPullup()        do { WPUBbits.WPUB1 = 0; } while(0)
#define qeSW_SetAnalogMode()      do { ANSELHbits.ANS10 = 1; } while(0)
#define qeSW_SetDigitalMode()     do { ANSELHbits.ANS10 = 0; } while(0)

// get/set qeB aliases
#define qeB_TRIS                 TRISBbits.TRISB4
#define qeB_LAT                  LATBbits.LATB4
#define qeB_PORT                 PORTBbits.RB4
#define qeB_WPU                  WPUBbits.WPUB4
#define qeB_ANS                  ANSELHbits.ANS11
#define qeB_SetHigh()            do { LATBbits.LATB4 = 1; } while(0)
#define qeB_SetLow()             do { LATBbits.LATB4 = 0; } while(0)
#define qeB_Toggle()             do { LATBbits.LATB4 = ~LATBbits.LATB4; } while(0)
#define qeB_GetValue()           PORTBbits.RB4
#define qeB_SetDigitalInput()    do { TRISBbits.TRISB4 = 1; } while(0)
#define qeB_SetDigitalOutput()   do { TRISBbits.TRISB4 = 0; } while(0)
#define qeB_SetPullup()          do { WPUBbits.WPUB4 = 1; } while(0)
#define qeB_ResetPullup()        do { WPUBbits.WPUB4 = 0; } while(0)
#define qeB_SetAnalogMode()      do { ANSELHbits.ANS11 = 1; } while(0)
#define qeB_SetDigitalMode()     do { ANSELHbits.ANS11 = 0; } while(0)

// get/set qeA aliases
#define qeA_TRIS                 TRISBbits.TRISB5
#define qeA_LAT                  LATBbits.LATB5
#define qeA_PORT                 PORTBbits.RB5
#define qeA_WPU                  WPUBbits.WPUB5
#define qeA_SetHigh()            do { LATBbits.LATB5 = 1; } while(0)
#define qeA_SetLow()             do { LATBbits.LATB5 = 0; } while(0)
#define qeA_Toggle()             do { LATBbits.LATB5 = ~LATBbits.LATB5; } while(0)
#define qeA_GetValue()           PORTBbits.RB5
#define qeA_SetDigitalInput()    do { TRISBbits.TRISB5 = 1; } while(0)
#define qeA_SetDigitalOutput()   do { TRISBbits.TRISB5 = 0; } while(0)
#define qeA_SetPullup()          do { WPUBbits.WPUB5 = 1; } while(0)
#define qeA_ResetPullup()        do { WPUBbits.WPUB5 = 0; } while(0)

// get/set buzzer aliases
#define buzzer_TRIS                 TRISCbits.TRISC2
#define buzzer_LAT                  LATCbits.LATC2
#define buzzer_PORT                 PORTCbits.RC2
#define buzzer_SetHigh()            do { LATCbits.LATC2 = 1; } while(0)
#define buzzer_SetLow()             do { LATCbits.LATC2 = 0; } while(0)
#define buzzer_Toggle()             do { LATCbits.LATC2 = ~LATCbits.LATC2; } while(0)
#define buzzer_GetValue()           PORTCbits.RC2
#define buzzer_SetDigitalInput()    do { TRISCbits.TRISC2 = 1; } while(0)
#define buzzer_SetDigitalOutput()   do { TRISCbits.TRISC2 = 0; } while(0)

// get/set RC6 procedures
#define RC6_SetHigh()            do { LATCbits.LATC6 = 1; } while(0)
#define RC6_SetLow()             do { LATCbits.LATC6 = 0; } while(0)
#define RC6_Toggle()             do { LATCbits.LATC6 = ~LATCbits.LATC6; } while(0)
#define RC6_GetValue()              PORTCbits.RC6
#define RC6_SetDigitalInput()    do { TRISCbits.TRISC6 = 1; } while(0)
#define RC6_SetDigitalOutput()   do { TRISCbits.TRISC6 = 0; } while(0)

// get/set RC7 procedures
#define RC7_SetHigh()            do { LATCbits.LATC7 = 1; } while(0)
#define RC7_SetLow()             do { LATCbits.LATC7 = 0; } while(0)
#define RC7_Toggle()             do { LATCbits.LATC7 = ~LATCbits.LATC7; } while(0)
#define RC7_GetValue()              PORTCbits.RC7
#define RC7_SetDigitalInput()    do { TRISCbits.TRISC7 = 1; } while(0)
#define RC7_SetDigitalOutput()   do { TRISCbits.TRISC7 = 0; } while(0)

// get/set rs485EN aliases
#define rs485EN_TRIS                 TRISDbits.TRISD0
#define rs485EN_LAT                  LATDbits.LATD0
#define rs485EN_PORT                 PORTDbits.RD0
#define rs485EN_SetHigh()            do { LATDbits.LATD0 = 1; } while(0)
#define rs485EN_SetLow()             do { LATDbits.LATD0 = 0; } while(0)
#define rs485EN_Toggle()             do { LATDbits.LATD0 = ~LATDbits.LATD0; } while(0)
#define rs485EN_GetValue()           PORTDbits.RD0
#define rs485EN_SetDigitalInput()    do { TRISDbits.TRISD0 = 1; } while(0)
#define rs485EN_SetDigitalOutput()   do { TRISDbits.TRISD0 = 0; } while(0)

// get/set ledN aliases
#define ledN_TRIS                 TRISDbits.TRISD2
#define ledN_LAT                  LATDbits.LATD2
#define ledN_PORT                 PORTDbits.RD2
#define ledN_SetHigh()            do { LATDbits.LATD2 = 1; } while(0)
#define ledN_SetLow()             do { LATDbits.LATD2 = 0; } while(0)
#define ledN_Toggle()             do { LATDbits.LATD2 = ~LATDbits.LATD2; } while(0)
#define ledN_GetValue()           PORTDbits.RD2
#define ledN_SetDigitalInput()    do { TRISDbits.TRISD2 = 1; } while(0)
#define ledN_SetDigitalOutput()   do { TRISDbits.TRISD2 = 0; } while(0)

// get/set ledL aliases
#define ledL_TRIS                 TRISDbits.TRISD3
#define ledL_LAT                  LATDbits.LATD3
#define ledL_PORT                 PORTDbits.RD3
#define ledL_SetHigh()            do { LATDbits.LATD3 = 1; } while(0)
#define ledL_SetLow()             do { LATDbits.LATD3 = 0; } while(0)
#define ledL_Toggle()             do { LATDbits.LATD3 = ~LATDbits.LATD3; } while(0)
#define ledL_GetValue()           PORTDbits.RD3
#define ledL_SetDigitalInput()    do { TRISDbits.TRISD3 = 1; } while(0)
#define ledL_SetDigitalOutput()   do { TRISDbits.TRISD3 = 0; } while(0)

// get/set ledS aliases
#define ledS_TRIS                 TRISDbits.TRISD4
#define ledS_LAT                  LATDbits.LATD4
#define ledS_PORT                 PORTDbits.RD4
#define ledS_SetHigh()            do { LATDbits.LATD4 = 1; } while(0)
#define ledS_SetLow()             do { LATDbits.LATD4 = 0; } while(0)
#define ledS_Toggle()             do { LATDbits.LATD4 = ~LATDbits.LATD4; } while(0)
#define ledS_GetValue()           PORTDbits.RD4
#define ledS_SetDigitalInput()    do { TRISDbits.TRISD4 = 1; } while(0)
#define ledS_SetDigitalOutput()   do { TRISDbits.TRISD4 = 0; } while(0)

// get/set ledO aliases
#define ledO_TRIS                 TRISDbits.TRISD5
#define ledO_LAT                  LATDbits.LATD5
#define ledO_PORT                 PORTDbits.RD5
#define ledO_SetHigh()            do { LATDbits.LATD5 = 1; } while(0)
#define ledO_SetLow()             do { LATDbits.LATD5 = 0; } while(0)
#define ledO_Toggle()             do { LATDbits.LATD5 = ~LATDbits.LATD5; } while(0)
#define ledO_GetValue()           PORTDbits.RD5
#define ledO_SetDigitalInput()    do { TRISDbits.TRISD5 = 1; } while(0)
#define ledO_SetDigitalOutput()   do { TRISDbits.TRISD5 = 0; } while(0)

// get/set ledC aliases
#define ledC_TRIS                 TRISDbits.TRISD6
#define ledC_LAT                  LATDbits.LATD6
#define ledC_PORT                 PORTDbits.RD6
#define ledC_SetHigh()            do { LATDbits.LATD6 = 1; } while(0)
#define ledC_SetLow()             do { LATDbits.LATD6 = 0; } while(0)
#define ledC_Toggle()             do { LATDbits.LATD6 = ~LATDbits.LATD6; } while(0)
#define ledC_GetValue()           PORTDbits.RD6
#define ledC_SetDigitalInput()    do { TRISDbits.TRISD6 = 1; } while(0)
#define ledC_SetDigitalOutput()   do { TRISDbits.TRISD6 = 0; } while(0)

// get/set ledCOM aliases
#define ledCOM_TRIS                 TRISDbits.TRISD7
#define ledCOM_LAT                  LATDbits.LATD7
#define ledCOM_PORT                 PORTDbits.RD7
#define ledCOM_SetHigh()            do { LATDbits.LATD7 = 1; } while(0)
#define ledCOM_SetLow()             do { LATDbits.LATD7 = 0; } while(0)
#define ledCOM_Toggle()             do { LATDbits.LATD7 = ~LATDbits.LATD7; } while(0)
#define ledCOM_GetValue()           PORTDbits.RD7
#define ledCOM_SetDigitalInput()    do { TRISDbits.TRISD7 = 1; } while(0)
#define ledCOM_SetDigitalOutput()   do { TRISDbits.TRISD7 = 0; } while(0)

// get/set oledRS aliases
#define oledRS_TRIS                 TRISEbits.TRISE0
#define oledRS_LAT                  LATEbits.LATE0
#define oledRS_PORT                 PORTEbits.RE0
#define oledRS_ANS                  ANSELbits.ANS5
#define oledRS_SetHigh()            do { LATEbits.LATE0 = 1; } while(0)
#define oledRS_SetLow()             do { LATEbits.LATE0 = 0; } while(0)
#define oledRS_Toggle()             do { LATEbits.LATE0 = ~LATEbits.LATE0; } while(0)
#define oledRS_GetValue()           PORTEbits.RE0
#define oledRS_SetDigitalInput()    do { TRISEbits.TRISE0 = 1; } while(0)
#define oledRS_SetDigitalOutput()   do { TRISEbits.TRISE0 = 0; } while(0)
#define oledRS_SetAnalogMode()      do { ANSELbits.ANS5 = 1; } while(0)
#define oledRS_SetDigitalMode()     do { ANSELbits.ANS5 = 0; } while(0)

// get/set oledEN aliases
#define oledEN_TRIS                 TRISEbits.TRISE1
#define oledEN_LAT                  LATEbits.LATE1
#define oledEN_PORT                 PORTEbits.RE1
#define oledEN_ANS                  ANSELbits.ANS6
#define oledEN_SetHigh()            do { LATEbits.LATE1 = 1; } while(0)
#define oledEN_SetLow()             do { LATEbits.LATE1 = 0; } while(0)
#define oledEN_Toggle()             do { LATEbits.LATE1 = ~LATEbits.LATE1; } while(0)
#define oledEN_GetValue()           PORTEbits.RE1
#define oledEN_SetDigitalInput()    do { TRISEbits.TRISE1 = 1; } while(0)
#define oledEN_SetDigitalOutput()   do { TRISEbits.TRISE1 = 0; } while(0)
#define oledEN_SetAnalogMode()      do { ANSELbits.ANS6 = 1; } while(0)
#define oledEN_SetDigitalMode()     do { ANSELbits.ANS6 = 0; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/