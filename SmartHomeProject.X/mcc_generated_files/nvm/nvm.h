/**
 * 
 * @file nvm.h
 *
 * @defgroup nvm_driver  Non-Volatile Memory
 *
 * @brief This file contains API prototypes and other data types for the Non-Volatile Memory (NVM) driver.
 *
 * @version NVM Driver Version 1.0.2
 */

/*
� [2025] Microchip Technology Inc. and its subsidiaries.

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

#ifndef NVM_H
#define NVM_H

#include <xc.h>
#include <stdbool.h>

/**
 * @ingroup nvm_driver
 * @def PROGMEM_PAGE_SIZE
 * Contains the size of a Flash page/row in 14-bit words.
 */
#define PROGMEM_PAGE_SIZE    (64U)

/**
 * @ingroup nvm_driver
 * @def NUMBER_OF_WRITE_LATCHES
 * Contains the number of write latches
 */
#define NUMBER_OF_WRITE_LATCHES    (64U)

/**
 * @ingroup nvm_driver
 * @def PROGMEM_SIZE
 * Contains the size of Flash in 14-bit words.
 */
#define PROGMEM_SIZE         (0x10000U)

/**
 * @ingroup nvm_driver
 * @def EEPROM_START_ADDRESS
 * Contains the starting address of EEPROM.
 */
#define EEPROM_START_ADDRESS (0xf00000U)

/**
 * @ingroup nvm_driver
 * @def EEPROM_SIZE
 * Contains the size of EEPROM in bytes.
 */
#ifndef EEPROM_SIZE
#define EEPROM_SIZE          (1024U)
#endif

/**
 * @ingroup nvm_driver
 * @def UNLOCK_KEY
 * Contains the unlock key required for the NVM operations.
 */
#define UNLOCK_KEY           (0xAA55U)

/**
 * @ingroup nvm_driver
 * @brief Data type for the Flash data.
 */
typedef uint8_t flash_data_t; //Flash data size is 14-bit. Two most significant bits are unused.
/**
 * @ingroup nvm_driver
 * @brief Data type for the Flash address.
 */
typedef uint24_t flash_address_t;

/**
 * @ingroup nvm_driver
 * @brief Data type for the EEPROM data.
 */
typedef uint8_t eeprom_data_t;
/**
 * @ingroup nvm_driver
 * @brief Data type for the EEPROM address.
 */
typedef uint24_t eeprom_address_t;

/**
 * @ingroup nvm_driver
 * @brief Data type for the Device ID data.
 */
typedef uint16_t device_id_data_t; //Device ID data size is 14-bit. Two most significant bits are unused.
/**
 * @ingroup nvm_driver
 * @brief Data type for the Device ID address.
 */
typedef uint24_t device_id_address_t;

/**
 * @ingroup nvm_driver
 * @brief Data type for the Configurations Settings data.
 */
typedef uint8_t configuration_data_t; //Configuration data size is 14-bit. Two most significant bits are unused.
/**
 * @ingroup nvm_driver
 * @brief Data type for the Configurations Settings address.
 */
typedef uint24_t configuration_address_t;

/**
 * @ingroup nvm_driver
 * @enum nvm_status_t
 * @brief Contains the return codes for the NVM driver APIs.
 */
typedef enum
{
    NVM_OK, /**<0 - The NVM operation succeeded.*/
    NVM_ERROR /**<1 - The NVM operation failed.*/
} nvm_status_t;

/**
 * @ingroup nvm_driver
 * @brief Initializes the NVM driver. 
 * @param None.
 * @return None.
 */
void NVM_Initialize(void);

/**
 * @ingroup nvm_driver
 * @brief Checks if the NVM is busy with the read/write/erase commands.
 * @param None.
 * @retval True - The NVM operation is being performed.
 * @retval False - The NVM operation is not being performed.
 */
bool NVM_IsBusy(void);

/**
 * @ingroup nvm_driver
 * @brief Returns the status of the last NVM operation.
 * @param None.
 * @retval NVM_OK - The NVM operation succeeded.
 * @retval NVM_ERROR - The NVM operation failed.
 */
nvm_status_t NVM_StatusGet(void);

/**
 * @ingroup nvm_driver
 * @brief Clears the NVM error status.
 * @param None.
 * @return None.
 */
void NVM_StatusClear(void);

/**
 * @ingroup nvm_driver
 * @brief Sets the unlock keys required to perform any erase or write operations on Flash and EEPROM.
 * @param [in] unlockKey - Unlock key value as specified in the device data sheet. 
 * @return None.
 */
void NVM_UnlockKeySet(uint16_t unlockKey);

/**
 * @ingroup nvm_driver
 * @brief Clears the previously configured unlock keys.
 * @param None. 
 * @return None.
 */
void NVM_UnlockKeyClear(void);

/**
 * @ingroup nvm_driver
 * @brief Reads a 14-bit word from the given Flash address.
 * @param [in] address - Address of the Flash location from which data is to be read.
 * @return 14-bit word read from the given Flash address.
 */
flash_data_t FLASH_Read(flash_address_t address);

/**
 * @ingroup nvm_driver
 * @brief Writes one entire Flash row from the given starting address of the row (the first word location).
 *        The size of the input buffer must be one Flash row and the address must be aligned with the row boundary.
 *        Use @ref FLASH_PageAddressGet() to obtain the starting address of the row.
 * @pre  Erase Flash row before calling this function.
 *       Set the unlock key using the @ref NVM_UnlockKeySet() API, if the key has been cleared before.
 *       AoU: **Address Qualifiers** must be configured to **Require** under *Project Properties>XC8 Compiler>Optimizations*.
 * @param [in] address - Starting address of the Flash row to be written. 
 * @param [in] *data - Pointer to a buffer which holds the data to be written.
 * @return Status of the Flash row write operation as described in @ref nvm_status_t.
 */
nvm_status_t FLASH_RowWrite(flash_address_t address, flash_data_t *dataBuffer);

/**
 * @ingroup nvm_driver
 * @brief Erases one Flash page/row containing the given address.
 * @pre Set the unlock key using the @ref NVM_UnlockKeySet() API, if the key has been cleared before.
*       AoU: **Address Qualifiers** must be configured to **Require** under *Project Properties>XC8 Compiler>Optimizations*.
 * @param [in] address - Any address in the Flash page to be erased. 
 * @return Status of the Flash page erase operation as described in @ref nvm_status_t.
 */
nvm_status_t FLASH_PageErase(flash_address_t address);

/**
 * @ingroup nvm_driver
 * @brief Returns the starting address of the page/row (the first word location) containing the given Flash address.
 * @param [in] address - Flash address for which the page starting address will be obtained.
 * @return Starting address of the page containing the given Flash address.
 */
flash_address_t FLASH_PageAddressGet(flash_address_t address);

/**
 * @ingroup nvm_driver
 * @brief Returns the offset from the starting address of the page/row (the first word location).
 * @param [in] address - Flash address for which the offset from the starting address of the page will be obtained.
 * @return Offset of the given address from the starting address of the page.
 */
uint16_t FLASH_PageOffsetGet(flash_address_t address);

//Below macros are added to provide backward compatibility. These will be deprecated in the future versions.
#define FLASH_ErasePageAddressGet FLASH_PageAddressGet
#define FLASH_ErasePageOffsetGet FLASH_PageOffsetGet

/**
 * @ingroup nvm_driver
 * @brief Reads one byte from the given EEPROM address.
 * @param [in] address - Address of the EEPROM location to be read.
 * @return Byte read from the given EEPROM address.
 */
eeprom_data_t EEPROM_Read(eeprom_address_t address);

/**
 * @ingroup nvm_driver
 * @brief Writes one byte to the given EEPROM address. 
 *      The NVM busy status must be checked using the @ref NVM_IsBusy() API to know if the write operation is completed.
 *      Use the @ref NVM_StatusGet() API to see the result of the write operation.
 * @pre Set the unlock key using the @ref NVM_UnlockKeySet() API, if the key has been cleared before. 
 *       AoU: **Address Qualifiers** must be configured to **Require** under *Project Properties>XC8 Compiler>Optimizations*.
 * @param [in] address - Address of the EEPROM location to be written.
 * @param [in] data - Byte to be written to the given EEPROM location.
 * @return None.
 */
void EEPROM_Write(eeprom_address_t address, eeprom_data_t data);

/**
 * @ingroup nvm_driver
 * @brief Reads the Device ID.
 * @param [in] address - Starting address of the Device ID.
 * @return Device ID.
 */
device_id_data_t DeviceID_Read(device_id_address_t address);

/**
 * @ingroup nvm_driver
 * @brief Reads one Configuration Word.
 * @param [in] address - Configuration Word address to be read.
 * @return Configuration Word data. 
 */
configuration_data_t CONFIGURATION_Read(configuration_address_t address);

#endif /* NVM_H */
