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


uint8 lcd_counter = ZERO_INIT ;
uint8 lcd_counter_txt[4] ;

const uint8 customChar[] = {
  0x0E,
  0x0A,
  0x1B,
  0x11,
  0x11,
  0x11,
  0x1F,
  0x00
};

int main() {
    Std_ReturnType ret = E_OK;
    application_initialize();
//    ret = lcd_8bit_send_string_pos(&lcd2 , 1 , 1 , "Counter: ");
        
    while(1){
//        for (lcd_counter=0 ; lcd_counter<=99 ; lcd_counter++){
//            convert_byte_to_string(lcd_counter , lcd_counter_txt);
//            ret = lcd_8bit_send_string_pos(&lcd2 , 1 , 10 , lcd_counter_txt );
//            __delay_ms(100);
//        }
//        ret = lcd_8bit_send_string_pos(&lcd2 , 1 , 10 , "  ");
        ret = lcd_8bit_send_custom_char(&lcd2 , 1 , 1 , customChar ,0);
        ret = lcd_4bit_send_custom_char(&lcd1 , 1 , 1 , customChar ,0);

   }
    
    return (EXIT_SUCCESS);
    
     
}



void application_initialize(void){
    Std_ReturnType ret = E_OK;
    
    ecu_layer_initialize();
    
}
        
        


