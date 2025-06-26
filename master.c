/* 
 * File:   application.c
 * Author: abdalrahman.ahmed
 *
 * Created on January 27, 2025, 2:15 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include "application.h"

#define slave_1 0x60
#define slave_2 0x61


Std_ReturnType ret = E_NOT_OK;
uint8 slave_ack ;


void i2c_DefaultInterruptHandler(void){
    
}

mssp_i2c_t i2c_test = {
    
    .i2c_cfg.i2c_mode = I2C_SLAVE_MODE_CFG,
    .i2c_cfg.i2c_mode_cfg = I2C_SLAVE_MODE_7BIT_CFG,
    .i2c_cfg.i2c_SMBus_control = I2C_SMBus_DISABLE_CFG,
    .i2c_cfg.i2c_slew_rate = I2C_SLEW_RATE_DISABLE_CFG,
    .i2c_cfg.i2c_general_call = I2C_GENERAL_CALL_DISABLE_CFG,
    .I2C_DefaultInterruptHandler = i2c_DefaultInterruptHandler,
    .I2C_REPORT_RECEIVE_OVERFLOW = NULL,
    .I2C_REPORT_WRITE_COLLISION = NULL,
    .i2c_cfg.i2c_slave_address = slave_1,
};




int main() {
    ret = I2c_Init(&i2c_test); 
    
    
    while(1){
        
   }
    
    return (EXIT_SUCCESS);
    
     
}



void application_initialize(void){
    Std_ReturnType ret = E_OK;
    
    
}







       


