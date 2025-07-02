 /*
 * MAIN Generated Driver File
 * 
 * @file main.c
 * 
 * @defgroup main MAIN
 * 
 * @brief This is the generated driver implementation file for the MAIN driver.
 *
 * @version MAIN Driver Version 1.0.2
 *
 * @version Package Version: 3.1.2
*/

/*
© [2025] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/
#include "mcc_generated_files/system/system.h"
#include "AECUL_Modules/RealTimeClockDS1307/RealTimeClockDS1307.h"
#include "AECUL_Modules/UART_LoggingDebugData/UART_LoggingDebugData.h"
#include "AECUL_Modules/EEPROM_24C01C/EEPROM_24C01C.h"
#include "AECUL_Modules/TempSensor_TC74/TempSensor_TC74.h"
/*
    Main application
*/
#include <stdio.h>
#include <string.h>
RealTimeClockDS1307_T RealTimeClockDS1307;
uint8_t U4rec , U5rec = 0;
int8_t temp_data = 0;

int main(void)
{
    SYSTEM_Initialize();
    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts 
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global and Peripheral Interrupts 
    // Use the following macros to: 

    // Enable the Global High Interrupts 
    INTERRUPT_GlobalInterruptHighEnable(); 

    // Disable the Global High Interrupts 
    //INTERRUPT_GlobalInterruptHighDisable(); 

    // Enable the Global Low Interrupts 
    INTERRUPT_GlobalInterruptLowEnable(); 

    // Disable the Global Low Interrupts 
    //INTERRUPT_GlobalInterruptLowDisable(); 

    // Enable the Peripheral Interrupts 
    INTERRUPT_PeripheralInterruptEnable(); 

    // Disable the Peripheral Interrupts 
    //INTERRUPT_PeripheralInterruptDisable(); 
//    EUSART_Write('a');
//    UART_LoggingDebugData_Send_String("System Started\r" ,15 );
    
    
EEPROM_24C01C_Write_byte(0x51, 0x08, 0x05); // 0xA2 >> 1 = 0x51
EEPROM_24C01C_Write_byte(0x53, 0x08, 0x06); // 0xA6 >> 1 = 0x53
__delay_us(500);
U4rec = EEPROM_24C01C_Read_byte(0x51 , 0x08);
U5rec = EEPROM_24C01C_Read_byte(0x53 , 0x08);
__delay_us(500);
    
    while(1)
    {
//        RealTimeClockDS1307 = RealTimeClock_Get_Time_Date();
//        Print_RealTimeClock_Pack_Date();
            temp_data = TEMPSENSOR_TC74_Temp_Read(0x4F << 1);  // 7-bit address


    }    
}