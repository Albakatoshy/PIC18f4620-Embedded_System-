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

uint8 seg_common_anode_valuse[10] = {0xC0 , 0xF9 , 0xA4 , 0xB0 , 0x99 , 0x92 , 0x82 , 0xF8 , 0x80 , 0x90};
uint8 seg_value_with_decoder[10]  = {0x00 , 0x01 , 0x02 , 0x03 , 0x04 , 0x05 , 0x06 , 0x07 , 0x08 , 0x09}; 

int count2 =0 , count3 = 0;

uint8 number = 0 , number_bcd = 0;


int main() {
    Std_ReturnType ret = E_OK;
    application_initialize();
    
        
    while(1){

       number_bcd = ((uint8)(number % 10) | ((uint8)(number / 10)) << 4);
       ret = gpio_port_write_logic(PORTB_INDEX , number_bcd );
       __delay_ms(250);
       number++;
   }
    
     
}



void application_initialize(void){
    Std_ReturnType ret = E_OK;
    
    ret = gpio_port_direction_intialize(PORTC_INDEX , GPIO_DIRECTION_OUTPUT );
    ret = gpio_port_direction_intialize(PORTD_INDEX , GPIO_DIRECTION_OUTPUT );
    ret = gpio_port_direction_intialize(PORTA_INDEX , 0x00  );
    ret = gpio_port_direction_intialize(PORTB_INDEX , 0x00);
}
        
        


