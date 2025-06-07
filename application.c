/* 
 * File:   application.c
 * Author: abdalrahman.ahmed
 *
 * Created on January 27, 2025, 2:15 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include "application.h"
#include "MCAL_layer/SPI/hal_spi.h"
Std_ReturnType ret = E_NOT_OK;

uint8 test_recieve = ZERO_INIT;

SPI_Config test_spi = {
    .spi_config.ClockPolarity = SPI_CLOCK_POLARITY_HIGH_LEVEL_CFG,
    .spi_config.ClockSelect   = SPI_CLOCK_SELECT_ACTIVE_TO_IDLE_CFG,
    .spi_config.SampleSelect  = SPI_DATA_SAMPLED_AT_END_OF_DATA_CFG,
    .spi_mode                 =  SPI_SLAVE_MODE_FOSC_SS_DISABLED ,
};

pin_config_t D0 ={
  .direction = GPIO_DIRECTION_OUTPUT ,
  .logic     = GPIO_LOW,
  .pin       = GPIO_PIN0,
  .port      = PORTD_INDEX,
}; 



int main() {
    
    ret = SPI_Init(&test_spi);
    ret = gpio_pin_intialize(&D0);
    
    while(1){
        ret = SPI_Read_VAL(&test_spi , &test_recieve);
   }
    
    return (EXIT_SUCCESS);
    
     
}



void application_initialize(void){
    Std_ReturnType ret = E_OK;
    
    
}







       


