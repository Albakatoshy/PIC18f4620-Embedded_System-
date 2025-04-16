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

int count1 =0, count2 =0 , count3 = 0;
int main() {
    Std_ReturnType ret = E_OK;
    application_initialize();
    
        
    while(1){
        for (count3=0; count3<=9 ; count3++){
            ret = gpio_port_write_logic(PORTA_INDEX , seg_value_with_decoder[count3]);
            __delay_ms(100);
        }
        
        
        for (count1 = 0; count1<=9 ; count1++){
            ret = gpio_port_write_logic(PORTD_INDEX , seg_common_anode_valuse[count1]);
            __delay_ms(100);
            for (count2 = 0; count2<=9 ; count2++){
                ret = gpio_port_write_logic(PORTC_INDEX , seg_common_anode_valuse[count2]);
                ret = gpio_port_write_logic(PORTA_INDEX , seg_value_with_decoder[count2]);
                __delay_ms(100);
            
            }
   }
    
     
}
}


void application_initialize(void){
    Std_ReturnType ret = E_OK;
    
    ret = gpio_port_direction_intialize(PORTC_INDEX , GPIO_DIRECTION_OUTPUT );
    ret = gpio_port_direction_intialize(PORTD_INDEX , GPIO_DIRECTION_OUTPUT );
    ret = gpio_port_direction_intialize(PORTA_INDEX , GPIO_DIRECTION_OUTPUT );

}
        
        


