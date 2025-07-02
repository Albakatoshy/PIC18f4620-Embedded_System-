#include <stddef.h>

#include "TempSensor_TC74.h"

extern const i2c_host_interface_t I2C1_Host;

int8_t TEMPSENSOR_TC74_Temp_Read(uint16_t SensorAddress ){
    int8_t temp_data ;
    __delay_ms(300);  // Wait after power on

// Wake from standby
    uint8_t config = I2C1_Read1ByteRegister(0x4F << 1, 0x01);
    config &= ~(1 << 7);  // Clear SHDN
    I2C_Write1ByteRegister_Interface(&I2C1_Host ,0x4F << 1, 0x01, config);

    // Wait until temperature conversion is ready
    do {
        config = I2C1_Read1ByteRegister(0x4F << 1, 0x01);
    } while ((config & 0x40) == 0);  // DATA_RDY == 1

    // Now read temperature
    int8_t temp = I2C1_Read1ByteRegister(0x4F << 1, 0x00);  // TEMP reg
    
    return temp_data;
}