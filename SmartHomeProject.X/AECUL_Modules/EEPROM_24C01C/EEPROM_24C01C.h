/* 
 * File:   EEPROM_24C01C.h
 * Author: anaal
 *
 * Created on July 2, 2025, 11:11 AM
 */

#ifndef EEPROM_24C01C_H
#define	EEPROM_24C01C_H

#include <stdint.h>
#include <stdbool.h>
#include "../../mcc_generated_files/system/system.h"
#include "../../mcc_generated_files/nvm/nvm.h"

void EEPROM_24C01C_Write_byte(uint16_t EEPROM_Address , uint8_t Byte_Adress , uint8_t _data);
uint8_t EEPROM_24C01C_Read_byte(uint16_t EEPROM_Address , uint8_t Byte_Adress );

#endif	/* EEPROM_24C01C_H */

