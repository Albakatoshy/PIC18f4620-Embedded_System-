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

led_t led1 ={
    .led_status = GPIO_LOW,
    .pin        = GPIO_PIN0,
    .port_name  = PORTC_INDEX,
};

led_t led2 ={
    .led_status = GPIO_LOW,
    .pin        = GPIO_PIN1,
    .port_name  = PORTC_INDEX,
};

led_t led3 ={
    .led_status = GPIO_LOW,
    .pin        = GPIO_PIN2,
    .port_name  = PORTC_INDEX,
};

led_t led4 ={
    .led_status = GPIO_LOW,
    .pin        = GPIO_PIN3,
    .port_name  = PORTC_INDEX,
};

void RB4_int_ISR_HIGH(void){
    led_turn_on(&led1);
}

void RB4_int_ISR_LOW(void){
    led_turn_on(&led2);
}

void RB5_int_ISR_HIGH(void){
    led_turn_off(&led1);
}

void RB5_int_ISR_LOW(void){
    led_turn_off(&led2);
}

void RB6_int_ISR_HIGH(void){
    led_turn_on(&led3);
}

void RB6_int_ISR_LOW(void){
    led_turn_on(&led4);
}

void RB7_int_ISR_HIGH(void){
    led_turn_off(&led3);
}

void RB7_int_ISR_LOW(void){
    led_turn_off(&led4);
}



interrupt_RBx_t RB4_int ={
  .EXT_InterruprHandler_HIGH = RB4_int_ISR_HIGH ,
  .EXT_InterruprHandler_LOW = RB4_int_ISR_LOW  ,
  .mcu_pin.direction    =GPIO_DIRECTION_INPUT,
  .mcu_pin.logic        =GPIO_LOW,
  .mcu_pin.pin          =GPIO_PIN4,
  .mcu_pin.port         =PORTB_INDEX,
  .priority             =INTERRUPT_HIGH_PRIORITY,
};

interrupt_RBx_t RB5_int ={
  .EXT_InterruprHandler_HIGH = RB5_int_ISR_HIGH ,
  .EXT_InterruprHandler_LOW = RB5_int_ISR_LOW  ,
  .mcu_pin.direction    =GPIO_DIRECTION_INPUT,
  .mcu_pin.logic        =GPIO_LOW,
  .mcu_pin.pin          =GPIO_PIN5,
  .mcu_pin.port         =PORTB_INDEX,
  .priority             =INTERRUPT_HIGH_PRIORITY,
};

interrupt_RBx_t RB6_int ={
  .EXT_InterruprHandler_HIGH = RB6_int_ISR_HIGH ,
  .EXT_InterruprHandler_LOW = RB6_int_ISR_LOW  ,
  .mcu_pin.direction    =GPIO_DIRECTION_INPUT,
  .mcu_pin.logic        =GPIO_LOW,
  .mcu_pin.pin          =GPIO_PIN6,
  .mcu_pin.port         =PORTB_INDEX,
  .priority             =INTERRUPT_HIGH_PRIORITY,
};

interrupt_RBx_t RB7_int ={
  .EXT_InterruprHandler_HIGH = RB7_int_ISR_HIGH ,
  .EXT_InterruprHandler_LOW = RB7_int_ISR_LOW  ,
  .mcu_pin.direction    =GPIO_DIRECTION_INPUT,
  .mcu_pin.logic        =GPIO_LOW,
  .mcu_pin.pin          =GPIO_PIN7,
  .mcu_pin.port         =PORTB_INDEX,
  .priority             =INTERRUPT_HIGH_PRIORITY,
};


int main() {
    Std_ReturnType ret = E_OK;
    application_initialize();
    
    
    ret = led_initialize(&led1); 
    ret = led_initialize(&led2); 
    ret = led_initialize(&led3); 
    ret = led_initialize(&led4);
    ret = Interrupt_RBx_Init(&RB4_int);
    ret = Interrupt_RBx_Init(&RB5_int);
    ret = Interrupt_RBx_Init(&RB6_int);
    ret = Interrupt_RBx_Init(&RB7_int);


    while(1){

   }
    
    return (EXIT_SUCCESS);
    
     
}



void application_initialize(void){
    Std_ReturnType ret = E_OK;
    
    ecu_layer_initialize();
    
}
        
       


