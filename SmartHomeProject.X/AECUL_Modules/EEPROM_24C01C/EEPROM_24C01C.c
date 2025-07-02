#include "EEPROM_24C01C.h"

extern const i2c_host_interface_t I2C1_Host;

void EEPROM_24C01C_Write_byte(uint16_t EEPROM_Address , uint8_t Byte_Adress , uint8_t _data){
    
    I2C_Write1ByteRegister_Interface(&I2C1_Host, EEPROM_Address , Byte_Adress ,_data);
    
    
}
uint8_t EEPROM_24C01C_Read_byte(uint16_t EEPROM_Address , uint8_t Byte_Adress ){
    uint8_t l_data = I2C1_Read1ByteRegister(EEPROM_Address , Byte_Adress);
    
    return l_data;
}