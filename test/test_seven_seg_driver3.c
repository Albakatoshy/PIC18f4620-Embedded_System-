/* 
 * File:   application.c
 * Author: abdalrahman.ahmed
 *
 * Created on January 27, 2025, 2:15 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include "application.h"
#define _XTAL_FREQ 4000000  // 4 MHz clock

sev_segment_t seg1 ={
  .sev_segment_pins[0].port      = PORTC_INDEX,
  .sev_segment_pins[0].pin       = GPIO_PIN0,
  .sev_segment_pins[0].direction = GPIO_DIRECTION_OUTPUT,
  .sev_segment_pins[0].logic     = GPIO_LOW, 
  .sev_segment_pins[1].port      = PORTC_INDEX,
  .sev_segment_pins[1].pin       = GPIO_PIN1,
  .sev_segment_pins[1].direction = GPIO_DIRECTION_OUTPUT,
  .sev_segment_pins[1].logic     = GPIO_LOW,
  .sev_segment_pins[2].port      = PORTC_INDEX,
  .sev_segment_pins[2].pin       = GPIO_PIN2,
  .sev_segment_pins[2].direction = GPIO_DIRECTION_OUTPUT,
  .sev_segment_pins[2].logic     = GPIO_LOW,
  .sev_segment_pins[3].port      = PORTC_INDEX,
  .sev_segment_pins[3].pin       = GPIO_PIN3,
  .sev_segment_pins[3].direction = GPIO_DIRECTION_OUTPUT,
  .sev_segment_pins[3].logic     = GPIO_LOW,
  
  .sev_segment_type = SEVEN_SEG_COMMON_ANODE,
};

pin_config_t pin1 = {
    .port = PORTD_INDEX ,
    .pin  = GPIO_PIN0,
    .logic = GPIO_LOW,
    .direction = GPIO_DIRECTION_OUTPUT
};

pin_config_t pin2 = {
    .port = PORTD_INDEX ,
    .pin  = GPIO_PIN1,
    .logic = GPIO_LOW,
    .direction = GPIO_DIRECTION_OUTPUT
};

uint8 timer = 0 , counter = 0;

int main() {
    Std_ReturnType ret = E_OK;
    application_initialize();
    
        
    while(1){
        for (timer=0 ; timer<=50 ;timer++){
            ret = seven_seg_write_number(&seg1,(counter)%10);
            ret = gpio_pin_write_logic(&pin2,GPIO_HIGH);
            __delay_ms(10);
            ret = gpio_pin_write_logic(&pin2,GPIO_LOW);
            ret = seven_seg_write_number(&seg1,(counter)/10);
            ret = gpio_pin_write_logic(&pin1,GPIO_HIGH);
            __delay_ms(10);
            ret = gpio_pin_write_logic(&pin1,GPIO_LOW);
        }
        counter++;
        if (counter==99){
            counter==0;
        }
   }
    
    return (EXIT_SUCCESS);
    
     
}



void application_initialize(void){
    Std_ReturnType ret = E_OK;
    
    
    ret = seven_seg_initialize(&seg1);
    ret = gpio_pin_intialize(&pin1);
    ret = gpio_pin_intialize(&pin2);
}
        
        


