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

volatile uint8 timer_flag = ZERO_INIT;
Std_ReturnType ret = E_OK;
volatile uint16 timer0_counter_val = ZERO_INIT ; 

led_t led1 = {
  .led_status = GPIO_LOW ,
  .pin        =GPIO_PIN0,
  .port_name  =PORTD_INDEX    
};

void timer_ISR(void){
    
    ret = led_turn_toggle(&led1);
}


timer0_config_t timer0_test_timer = {
  .TIMER0_InterruptHandler          = timer_ISR,
  .PrescalerEnable                  = TIMER0_PRESCALER_CONFIG_ENABLE,
  .timer0_mode                      = TIMER0_TIMER_MODE_CONFIG ,
  .timer0_control_register_size     = TIMER0_16_BIT_MODE_CONFIG ,
  .Prescaler_val                    =TIMER0_PRESCALER_DIV_8,
  .timer0_preload_value             =3036
};

timer0_config_t timer0_test_counter = {
  .TIMER0_InterruptHandler          = timer_ISR,
  .PrescalerEnable                  = TIMER0_PRESCALER_CONFIG_ENABLE,
  .timer0_mode                      = TIMER0_COUNTER_MODE_CONFIG ,
  .timer0_source_edge_select        = TIMER0_RISING_EDGE_CONFIG ,
  .timer0_control_register_size     = TIMER0_16_BIT_MODE_CONFIG ,
  .timer0_preload_value             =0
};


int main() {
    
    application_initialize();
    ret = Timer0_Init(&timer0_test_timer);
    ret = Timer0_Init(&timer0_test_counter);
    
    ret = led_initialize(&led1);
    while(1){
       
        ret = Timer0_ReadVal(&timer0_test_counter , &timer0_counter_val);
       
   }
    
    return (EXIT_SUCCESS);
    
     
}



void application_initialize(void){
    Std_ReturnType ret = E_OK;
    
    
}
        


       


