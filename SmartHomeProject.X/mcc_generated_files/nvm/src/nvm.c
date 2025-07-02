/**
 * @file nvm.c
 *
 * @ingroup nvm_driver
 *
 * @brief Contains the implementation file for the NVM driver.
 *
 * @version NVM Driver Version 1.0.2 
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

#include "../nvm.h"

/*
 * AoU: These variables are placed in the Access RAM using the "__near" qualifier.
 *      Additionally, "Address Qualifiers" must be configured to the "Require" under
 *      "Project Properties -> XC8 Compiler -> Optimizations".
 */
__near volatile static uint8_t unlockKeyLow;
__near volatile static uint8_t unlockKeyHigh;

void NVM_Initialize(void)
{
    NVM_StatusClear();
}

bool NVM_IsBusy(void)
{
    return (EECON1bits.WR || EECON1bits.RD);
}

nvm_status_t NVM_StatusGet(void)
{
    nvm_status_t nvmStatus;
    if (EECON1bits.WRERR == 1)
    {
        nvmStatus = NVM_ERROR;
    }
    else
    {
        nvmStatus = NVM_OK;
    }
    return nvmStatus;
}

void NVM_StatusClear(void)
{
    EECON1bits.WRERR = 0;
}

void NVM_UnlockKeySet(uint16_t unlockKey)
{
    unlockKeyHigh = (uint8_t) (unlockKey >> 8);
    unlockKeyLow = (uint8_t) unlockKey;
}

void NVM_UnlockKeyClear(void)
{
    unlockKeyHigh = 0x00;
    unlockKeyLow = 0x00;
}

flash_data_t FLASH_Read(flash_address_t address)
{
    //Save the table pointer
    uint32_t tablePointer = ((uint32_t) TBLPTRU << 16) | ((uint32_t) TBLPTRH << 8) | ((uint32_t) TBLPTRL);
    
    //Load table pointer with the target address of the byte  
    TBLPTRU = (uint8_t) (address >> 16);
    TBLPTRH = (uint8_t) (address >> 8);
    TBLPTRL = (uint8_t) address;

    asm("TBLRD");
    
    //Restore the table pointer
    TBLPTRU = (uint8_t) (tablePointer >> 16);
    TBLPTRH = (uint8_t) (tablePointer >> 8);
    TBLPTRL = (uint8_t) tablePointer;
    
    return (TABLAT);
}

nvm_status_t FLASH_RowWrite(flash_address_t address, flash_data_t *dataBuffer)
{    
    nvm_status_t writeStatus;
    uint8_t flashDataCount = PROGMEM_PAGE_SIZE;

     //Save the table pointer
    uint32_t tablePointer = ((uint32_t) TBLPTRU << 16) | ((uint32_t) TBLPTRH << 8) | ((uint32_t) TBLPTRL);
    
    //Save global interrupt enable bit value
    uint8_t globalInterruptBitValue = INTCONbits.GIE;   

    //Access program Flash memory
    EECON1bits.CFGS = 0;
    EECON1bits.EEPGD = 1;   
    
    //Enable write operation
    EECON1bits.WREN = 1;     
    
    //Load table pointer with the target address of the byte  
    TBLPTRU = (uint8_t) (address >> 16);
    TBLPTRH = (uint8_t) (address >> 8);
    TBLPTRL = (uint8_t) address;

    // Use a local pointer to iterate through the data buffer
    flash_data_t *localDataBuffer = dataBuffer;

    while (flashDataCount-- > 0U)
    {
         TABLAT = (uint8_t)*localDataBuffer;
        
        localDataBuffer++;
        
        //If last latch to be written
        if (flashDataCount == 0U)
        {
            //Write program Flash memory 
            asm("TBLWT");
        }
        else
        {
            asm("TBLWTPOSTINC");
        }   
        //Disable global interrupt
        INTCONbits.GIE = 0;    
        
        //Perform the unlock sequence
        EECON2 = unlockKeyLow;
        EECON2 = unlockKeyHigh;
        EECON1bits.WR = 1;
        NOP();
        NOP();
            
        //Restore global interrupt enable bit value
        INTCONbits.GIE = globalInterruptBitValue;        
    }
    
    //Disable write operation
    EECON1bits.WREN = 0;  

    //Restore the table pointer
    TBLPTRU = (uint8_t) (tablePointer >> 16);
    TBLPTRH = (uint8_t) (tablePointer >> 8);
    TBLPTRL = (uint8_t) tablePointer;    
    
    if (EECON1bits.WRERR == 1) 
    {
        writeStatus = NVM_ERROR;
    } 
    else 
    {
        writeStatus = NVM_OK;
    }
    return writeStatus;
}

nvm_status_t FLASH_PageErase(flash_address_t address)
{
    nvm_status_t pageEraseStatus;
    //Save the table pointer
    uint32_t tablePointer = ((uint32_t) TBLPTRU << 16) | ((uint32_t) TBLPTRH << 8) | ((uint32_t) TBLPTRL);
    
    //Save global interrupt enable bit value
    uint8_t globalInterruptBitValue = INTCONbits.GIE;   
    
    //Load table pointer with the target address of the byte  
    TBLPTRU = (uint8_t) (address >> 16);
    TBLPTRH = (uint8_t) (address >> 8);
    TBLPTRL = (uint8_t) address;

    //Access program Flash memory EEPGD
    EECON1bits.EEPGD = 1;
    
    //Access Flash program or data EEPROM memory CFGS
    EECON1bits.CFGS = 0;

    //Allows write cycles to Flash program WREN
    EECON1bits.WREN = 1;

    //Erase the program memory row addressed by TBLPTR with the next WR command FREE
    EECON1bits.FREE = 1;     

    //Disable global interrupt
    INTCONbits.GIE = 0;
    
    //Perform the unlock sequence
    EECON2 = unlockKeyLow;
    EECON2 = unlockKeyHigh;
    
    //Start Erase
    EECON1bits.WR = 1;

    //Restore global interrupt enable bit value
    INTCONbits.GIE = globalInterruptBitValue;	

    //Inhibits write cycles to Flash program WREN
    EECON1bits.WREN = 0;      
    
    //Restore the table pointer
    TBLPTRU = (uint8_t) (tablePointer >> 16);
    TBLPTRH = (uint8_t) (tablePointer >> 8);
    TBLPTRL = (uint8_t) tablePointer;
    
    if (EECON1bits.WRERR == 1) 
    {
       pageEraseStatus = NVM_ERROR;
    }
    else
    {
        pageEraseStatus = NVM_OK;
    }
    return pageEraseStatus;
}

flash_address_t FLASH_PageAddressGet(flash_address_t address)
{
    return (flash_address_t) (address & ((PROGMEM_SIZE - 1U) ^ (PROGMEM_PAGE_SIZE - 1U)));
}

uint16_t FLASH_PageOffsetGet(flash_address_t address)
{
    return (uint16_t) (address & (PROGMEM_PAGE_SIZE - 1U));
}

eeprom_data_t EEPROM_Read(eeprom_address_t address)
{
    //Access EEPROM
    EECON1bits.CFGS = 0;
    EECON1bits.EEPGD = 0;  
    
    //Load EEADR with the EEPROM address
    EEADR = (uint8_t) address;
    
    //Initiate Read
    EECON1bits.RD = 1;
    NOP();  // NOPs may be required for latency at high frequencies
    NOP();

    return EEDATA;
}

void EEPROM_Write(eeprom_address_t address, eeprom_data_t data)
{
    //Save global interrupt enable bit value
    uint8_t globalInterruptBitValue = INTCONbits.GIE;

    //Access EEPROM
    EECON1bits.CFGS = 0;
    EECON1bits.EEPGD = 0;
    
    //Enable write operation
    EECON1bits.WREN = 1;

    //Load EEADR with the EEPROM address
    EEADR = (uint8_t) address;

    //Load NVMDAT with the desired value
    EEDATA = data;

    //Disable global interrupt
    INTCONbits.GIE = 0;

    //Perform the unlock sequence
    EECON2 = unlockKeyLow;
    EECON2 = unlockKeyHigh;
    EECON1bits.WR = 1;
    NOP();
    NOP();

    //Restore global interrupt enable bit value
    INTCONbits.GIE = globalInterruptBitValue; 

    //Disable write operation
    EECON1bits.WREN = 0;
}

device_id_data_t DeviceID_Read(device_id_address_t address)
{
    device_id_data_t deivceID;
    
    //Save the table pointer
    uint32_t tablePointer = ((uint32_t) TBLPTRU << 16) | ((uint32_t) TBLPTRH << 8) | ((uint32_t) TBLPTRL);
    
    //Access program Flash memory EEPGD
    EECON1bits.EEPGD = 1;
    
    //Access Flash program or data EEPROM memory CFGS
    EECON1bits.CFGS = 0;
    
    //Load table pointer with Device ID address 
    TBLPTRU = (uint8_t) (address >> 16);
    TBLPTRH = (uint8_t) (address >> 8);
    TBLPTRL = (uint8_t) address;
  
    //Execute table read and increment table pointer 
    asm("TBLRD*+");
    
    deivceID = (device_id_data_t) (TABLAT & 0xE0);
    
    //Execute table read 
    asm("TBLRD*");
    
    deivceID |=  (device_id_data_t) (TABLAT << 8);
    
    //Restore the table pointer
    TBLPTRU = (uint8_t) (tablePointer >> 16);
    TBLPTRH = (uint8_t) (tablePointer >> 8);
    TBLPTRL = (uint8_t) tablePointer;

    return deivceID;
}

configuration_data_t CONFIGURATION_Read(configuration_address_t address)
{
    //Save the table pointer
    uint32_t tablePointer = ((uint32_t) TBLPTRU << 16) | ((uint32_t) TBLPTRH << 8) | ((uint32_t) TBLPTRL);
    
    //Access program Flash memory EEPGD
    EECON1bits.EEPGD = 1;
    
    //Access Flash program or data EEPROM memory CFGS
    EECON1bits.CFGS = 0;
    
    //Load table pointer with the target address of the byte  
    TBLPTRU = (uint8_t) (address >> 16);
    TBLPTRH = (uint8_t) (address >> 8);
    TBLPTRL = (uint8_t) address;

    //Execute table read
    asm("TBLRD*");

    //Restore the table pointer
    TBLPTRU = (uint8_t) (tablePointer >> 16);
    TBLPTRH = (uint8_t) (tablePointer >> 8);
    TBLPTRL = (uint8_t) tablePointer;

    return TABLAT;
}
