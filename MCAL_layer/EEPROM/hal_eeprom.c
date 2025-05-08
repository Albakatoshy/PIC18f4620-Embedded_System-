/* 
 * File:   hal_eeprom.c
 * Author: Abdalrahman
 *
 * Created on April 18, 2025, 6:32 PM
 */


#include "hal_eeprom.h"


Std_ReturnType EEPROM_WriteByte(uint16 bAdd , uint8 bData){
    Std_ReturnType ret = E_OK;
    /*Read the Interruot status Enabled or disabled*/
    uint8 Global_Interrupt_status = INTCONbits.GIE ; 
    
    /*Update the address registers*/
    EEADRH = (uint8)((bAdd>>8)&0x03);
    EEADR  = (uint8)(bAdd & 0xFF);
    
    /*Update the address registers*/
    EEDATA = bData ;
    
    /*Select acess data eeprom memory */
    EECON1bits.EEPGD = ACCESS_DATA_EEPROM_MEMORY ;
    EECON1bits.CFGS  = ACCESS_FLASH_EEPROM_MEMORY ;   
    
    /*set WR bit Additionally, the WREN bit in EECON1 must be set to enable writes. */
    EECON1bits.WREN=ALLOWS_WRITE_CYCLE_FLASH_EEPROM;
    
    /*Disable all interrupts (general interrupts)*/
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
    INTERRUPT_GlobalInterruptHighDisable();
    INTERRUPT_GlobalInterruptLowDisable();
#else
    INTERRUPT_GlobalInterruptDisable();
#endif   
    
    /*(write 55h to EECON2, write 0AAh to EECON2 */
    EECON2 = 0x55;
    EECON2 = 0xAA;
    /*Initiates a data EEPROM erase/write cycle */
    EECON1bits.WR = INITIATE_DATA_EEPROM_WRITE_ERASE;
    
    /*wait for Write cycle to the EEPROM is complete */
    while(EECON1bits.WR);
    
    /*INHIBITS_WRITE_CYCLE_FLASH_EEPROM*/
    EECON1bits.WREN=INHIBITS_WRITE_CYCLE_FLASH_EEPROM ;
    
    /*restore the interrupt state*/
    INTCONbits.GIE = Global_Interrupt_status ;
            
    return      ret;
    
}


Std_ReturnType EEPROM_ReadByte(uint16 bAdd , uint8 *bData){
    Std_ReturnType ret = E_OK;
    if(bData==NULL){
        ret= E_NOT_OK;
    }
    else{
        /*Update the address registers*/
        EEADRH = (uint8)((bAdd>>8)&0x03);
        EEADR  = (uint8)(bAdd & 0xFF);
        
        /*Select acess data eeprom memory */
        EECON1bits.EEPGD = ACCESS_DATA_EEPROM_MEMORY ;
        EECON1bits.CFGS  = ACCESS_FLASH_EEPROM_MEMORY ;
        
        /*set control bit, RD (EECON1<0>). */
        EECON1bits.RD = INITIATE_DATA_EEPROM_READ ; 
        NOP(); 
        NOP();
        
        /**/
        *bData = EEDATA ;
        
    }
    return      ret;
    
}