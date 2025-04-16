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


//pin_config_t led1 ={
//  .port=PORTC_INDEX,
//  .pin=GPIO_PIN0,
//  .logic=GPIO_HIGH,
//  .direction=GPIO_DIRECTION_OUTPUT
//};
//
//pin_config_t led2 ={
//  .port=PORTC_INDEX,
//  .pin=GPIO_PIN1,
//  .logic=GPIO_LOW,
//  .direction=GPIO_DIRECTION_OUTPUT
//};
//pin_config_t led3 ={
//  .port=PORTC_INDEX,
//  .pin=GPIO_PIN2,
//  .logic=GPIO_LOW,
//  .direction=GPIO_DIRECTION_OUTPUT
//};
//
//pin_config_t btn1 ={
//  .port=PORTD_INDEX,
//  .pin=GPIO_PIN0,
//  .logic=GPIO_LOW,
//  .direction=GPIO_DIRECTION_INPUT
//};


//Std_ReturnType ret = E_NOT_OK;
//
//direction_t led1_status;
//logic_t btn_status;
//
//uint8 port_status;
//uint8 port_read_status;


led_t led1 = {
    .port_name=PORTC_INDEX,
    .pin=GPIO_PIN0,
    .led_status=GPIO_LOW,
};

//led_t led2 = {
//    .port_name=PORTC_INDEX,
//    .pin=GPIO_PIN1,
//    .led_status=GPIO_LOW,
//};
//
//led_t led3 = {
//    .port_name=PORTC_INDEX,
//    .pin=GPIO_PIN2,
//    .led_status=GPIO_LOW,
//};
//
//led_t led4 = {
//    .port_name=PORTC_INDEX,
//    .pin=GPIO_PIN3,
//    .led_status=GPIO_LOW,
//};

button_t btn1 ={
    .button_pin.port=PORTC_INDEX,
    .button_pin.pin = GPIO_PIN2,
    .button_pin.direction= GPIO_DIRECTION_INPUT,
    .button_pin.logic = GPIO_LOW,
    .button_connection= BUTTON_ACTIVE_HIGH,
    .button_state = BUTTON_RELEASED,
};

//button_t btn2 ={
//    .button_pin.port=PORTD_INDEX,
//    .button_pin.pin = GPIO_PIN0,
//    .button_pin.direction= GPIO_DIRECTION_INPUT,
//    .button_pin.logic = GPIO_HIGH,
//    .button_connection= BUTTON_ACTIVE_LOW,
//    .button_state = BUTTON_RELEASED,
//};
button_state_t button1_status=BUTTON_RELEASED;
//button_state_t button2_status=BUTTON_RELEASED;
uint8 button1_status_flag = 0;
uint32 btn_high_valid = 0;
button_state_t button1_valid_status=BUTTON_RELEASED;
button_state_t button1_last_valid_status=BUTTON_RELEASED;

led_status_t led1_status = LED_OFF;

uint8 program_select = 0;

void prog1(void){
    led_turn_on(&led1);
    __delay_ms(500);
    led_turn_off(&led1);
    __delay_ms(500);
}

void prog2(void){
    uint8 counter=0;
    for(counter=0;counter<2;counter++){
        led_turn_on(&led1);
        __delay_ms(500);
        led_turn_off(&led1);
        __delay_ms(500);
    }
}

void prog3(void){
    uint8 counter=0;
    for(counter=0;counter<3;counter++){
        led_turn_on(&led1);
        __delay_ms(500);
        led_turn_off(&led1);
        __delay_ms(500);
    }
}

Std_ReturnType ret = E_OK;
int main() {
     
    application_initialize();
    while(1){
        ret = button_read_state(&btn1,&button1_status);
        if (button1_status == BUTTON_PRESSED){
            btn_high_valid++;
            if (btn_high_valid>500){
                button1_valid_status = BUTTON_PRESSED;
            }
        }
        else{
            btn_high_valid=0;
            button1_valid_status = BUTTON_RELEASED;
        }
        
        
        if (button1_valid_status != button1_last_valid_status){
            button1_last_valid_status=button1_valid_status;
            if (button1_valid_status == BUTTON_PRESSED){
                if (program_select==3){
                    program_select=0;
                }
                
                program_select++;
                switch (program_select){
            case 1 : 
                prog1();
                break;
            case 2 :
                prog2();
                break;
            
            case 3 :
                prog3();
                break;
            default:
                break;
        }
            }
        }
        
        
    }
        
        
//        ret = button_read_state(&btn2,&button2_status);
        
//        if (button1_status == BUTTON_PRESSED){
//            led_turn_on(&led1);
//        }
//        else{
//            led_turn_off(&led1);
//        }
//        if (button2_status == BUTTON_PRESSED){
//            led_turn_on(&led2);
//        }
//        else{
//            led_turn_off(&led2);
//        }
            
//        if (button1_valid_status == BUTTON_PRESSED && (0 == button1_status_flag)){
//            led_turn_on(&led1);
//            button1_status_flag = 1;
//        }
//        else if(button1_valid_status == BUTTON_PRESSED && (1 == button1_status_flag)) {
//            led_turn_off(&led1);
//            button1_status_flag = 0;
//        }
        
        
    
    
//    while(1){
//        led_turn_on(&led1);
//        led_turn_on(&led2);
//        led_turn_on(&led3);
//        led_turn_on(&led4);
//        __delay_ms(250);
//        led_turn_off(&led1);
//        led_turn_off(&led2);
//        led_turn_off(&led3);
//        led_turn_off(&led4);
//        
//    }
//    
//    while(1){
//        /*gpio_pin_read_logic(&btn1,&btn_status);
//        if (btn_status==GPIO_HIGH){
//            ret = gpio_pin_write_logic(&led1,GPIO_HIGH);
//        }
//        else{
//            ret = gpio_pin_write_logic(&led1,GPIO_LOW);
//        }
//    }*/
//        ret= gpio_port_toggle_logic(PORTC_INDEX);
//        __delay_ms(100);
//    }
    
    return (EXIT_SUCCESS);
}
void application_initialize(void){
////    ret = gpio_pin_intialize(&btn1);
////    
////    ret = gpio_pin_intialize(&led1);
////    ret = gpio_pin_intialize(&led2);
////    ret = gpio_pin_intialize(&led3);
////    
////    ret = gpio_pin_direction_intialize(NULL);
//    
//    ret = gpio_port_direction_intialize(PORTC_INDEX,0x00);
//    ret = gpio_port_get_direction_status(PORTC_INDEX ,&port_status );
//    ret = gpio_port_write_logic(PORTC_INDEX , 0x55);
//    ret = gpio_port_read_logic(PORTC_INDEX, &port_read_status);
//    __delay_ms(5000);
//    ret = gpio_port_write_logic(PORTC_INDEX , 0xAA);
//    ret = gpio_port_read_logic(PORTC_INDEX, &port_read_status);
//    

        Std_ReturnType ret = E_OK;
//        ret = led_initialize(&led1);
//        ret = led_initialize(&led2);    
//        ret = led_initialize(&led3);    
//        ret = led_initialize(&led4);
    
        ret = button_initialze(&btn1);
//        ret = button_initialze(&btn2);
        ret = led_initialize(&led1);
//        ret = led_initialize(&led2);
}

