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

uint8 second=45 , min = 12 , hours=23 ;

uint8 counter= 0 ;

int main() {
    Std_ReturnType ret = E_OK;
    application_initialize();
    
        
    while(1){
        for (counter=0 ; counter<20 ; counter++){
            ret = gpio_port_write_logic(PORTD_INDEX , 0x3E );
            ret = gpio_port_write_logic(PORTC_INDEX , ((uint8)(hours/10)));
            __delay_ms(8.3);
        
            ret = gpio_port_write_logic(PORTD_INDEX , 0x3D );        
            ret = gpio_port_write_logic(PORTC_INDEX , (uint8)(hours%10));
            __delay_ms(8.3);
        
            ret = gpio_port_write_logic(PORTD_INDEX , 0x3B );
            ret = gpio_port_write_logic(PORTC_INDEX , (uint8)(min/10));
            __delay_ms(8.3);
        
            ret = gpio_port_write_logic(PORTD_INDEX , 0x37 );
            ret = gpio_port_write_logic(PORTC_INDEX , (uint8)(min%10));
            __delay_ms(8.3);
        
            ret = gpio_port_write_logic(PORTD_INDEX , 0x2F );
            ret = gpio_port_write_logic(PORTC_INDEX , (uint8)(second/10));
            __delay_ms(8.3);
        
            ret = gpio_port_write_logic(PORTD_INDEX , 0x1F );
            ret = gpio_port_write_logic(PORTC_INDEX , (uint8)(second%10));
            __delay_ms(8.3);
        }
        second++;
        if (second==60){
            min++;
            second=0;
        }
        if(min==60){
            hours++;
            min=0;
        }
        if(hours==24){
            hours=0;
        }
   }
    
    return (EXIT_SUCCESS);
    
     
}



void application_initialize(void){
    Std_ReturnType ret = E_OK;
    
    ret = gpio_port_direction_intialize(PORTC_INDEX , GPIO_DIRECTION_OUTPUT );
    ret = gpio_port_direction_intialize(PORTD_INDEX , 0xC0 );
    
}
        
        


