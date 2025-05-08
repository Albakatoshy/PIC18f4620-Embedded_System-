/* 
 * File:   hal_eeprom.h
 * Author: Abdalrahman
 *
 * Created on April 18, 2025, 6:32 PM
 */

#ifndef HAL_EEPROM_H
#define	HAL_EEPROM_H



/*Section : Includes */

#include "pic18f4620.h"
#include "../GPIO/hal_gpio.h"
#include "../GPIO/mcal_std_types.h"
#include "../Interrupt/mcal_interrupt_config.h"

/* Section : Macro Declarations */

#define ACCESS_FLASH_PROGRAM_MEMORY         1
#define ACCESS_DATA_EEPROM_MEMORY           0

#define ACCESS_CONFIGURATION_REGISTERS      1
#define ACCESS_FLASH_EEPROM_MEMORY          0

#define ALLOWS_WRITE_CYCLE_FLASH_EEPROM     1
#define INHIBITS_WRITE_CYCLE_FLASH_EEPROM   0

#define INITIATE_DATA_EEPROM_WRITE_ERASE    1
#define DATA_EEPROM_WRITE_ERASE_COMPLETED   0

#define INITIATE_DATA_EEPROM_READ           1

/* Section : Macro Functions Declarations */

/* Section : Data Type Declarations */

/* Section : Function Declarations */
Std_ReturnType EEPROM_WriteByte(uint16 bAdd , uint8 bData);
Std_ReturnType EEPROM_ReadByte(uint16 bAdd , uint8 *bData); 

#endif	/* HAL_EEPROM_H */

