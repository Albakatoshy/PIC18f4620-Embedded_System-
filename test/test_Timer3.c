/* 
 * File:   application.c
 * Author: abdalrahman.ahmed
 *
 * Created on January 27, 2025, 2:15 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include "application.h"

#define _XTAL_FREQ 8000000  // 4 MHz clock

volatile uint32 timer3_flag= 0;
volatile uint16 timer3_counter_readVal;

Std_ReturnType ret = E_NOT_OK;
led_t led1={.port_name = PORTD_INDEX , .pin = GPIO_PIN0 , .led_status  = GPIO_LOW};

void Timer3_DefaultInterruptHandler(void){
    timer3_flag++;
}

timer3_config_t timer3_obj = {
  .TIMER3_InterruptHandler = Timer3_DefaultInterruptHandler ,
  .timer3_Prescaler_val    = TIMER3_PRESCALER_DIV_4_CFG,
  .timer3_mode             = TIMER3_TIMER_MODE_CONFIG,
  .timer3_read_write_mode  = TIMER3_READ_WRITE_16_BIT_MODE_CFG,
  .timer3_preloaded_value  = 15536,
};

timer3_config_t counter_obj = {
  .TIMER3_InterruptHandler = Timer3_DefaultInterruptHandler ,
  .timer3_Prescaler_val    = TIMER3_PRESCALER_DIV_1_CFG,
  .timer3_mode             = TIMER3_COUNTER_MODE_CONFIG,
  .timer3_counter_Synchronization_select = TIMER3_SYNCHRONOUS_COUNTER_CFG,
  .timer3_read_write_mode  = TIMER3_READ_WRITE_16_BIT_MODE_CFG,
  .timer3_preloaded_value  = 0,
};


int main() {
    
    application_initialize();
    ret = led_initialize(&led1);
    ret = Timer3_Init(&counter_obj);
    
    
    while(1){
       
        ret = Timer3_ReadVal(&counter_obj ,&timer3_counter_readVal );
       
   }
    
    return (EXIT_SUCCESS);
    
     
}



void application_initialize(void){
    Std_ReturnType ret = E_OK;
    
    
}
        


       


