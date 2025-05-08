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

volatile uint32 timer1_counter_val = 0 ;
Std_ReturnType ret = E_NOT_OK;
led_t led1={.port_name = PORTD_INDEX , .pin = GPIO_PIN0 , .led_status  = GPIO_LOW};

void TIMER1_DefaultInterruptHandler(void){
        
    ret = led_turn_toggle(&led1);
}


void timer1_timer_init(void){
    timer1_config_t timer_obj = {
      .TIMER1_InterruptHandler = TIMER1_DefaultInterruptHandler,
      //.timer1_priority         = INTERRUPT_LOW_PRIORITY, 
      .timer1_Prescaler_val    = TIMER1_PRESCALER_DIV_4_CFG,
      .timer1_mode             = TIMER1_TIMER_MODE_CONFIG,
      .timer1_read_write_mode  =  TIMER0_16_BIT_MODE_CONFIG,
      .timer1_preloaded_value  = 15536
    };
    Timer1_Init(&timer_obj);
}
timer1_config_t counter_obj = {
      .TIMER1_InterruptHandler = NULL,
     // .timer1_priority         = INTERRUPT_LOW_PRIORITY,
      .timer1_Prescaler_val    = TIMER1_PRESCALER_DIV_1_CFG,
      .timer1_mode             = TIMER1_COUNTER_MODE_CONFIG,
      .timer1_read_write_mode  =  TIMER0_16_BIT_MODE_CONFIG,
      .timer1_preloaded_value  = 0,
      .timer1_counter_Synchronization_select = TIMER1_SYNCHRONOUS_COUNTER_CFG , 
      
    };
void timer1_counter_init(void){
    
    Timer1_Init(&counter_obj);
}

int main() {
    
    application_initialize();
    ret = led_initialize(&led1);
    //timer1_timer_init();
    timer1_counter_init();
    
    
    while(1){
       
        ret = Timer1_ReadVal(&counter_obj , &timer1_counter_val);
       
   }
    
    return (EXIT_SUCCESS);
    
     
}



void application_initialize(void){
    Std_ReturnType ret = E_OK;
    
    
}
        


       


