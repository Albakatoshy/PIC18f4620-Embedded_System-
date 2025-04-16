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


uint8 counter = ZERO_INIT ;


int main() {
    Std_ReturnType ret = E_OK;
    application_initialize();
    
        ret = lcd_8bit_send_string_pos(&lcd2, 1,1,"Loading");
        ret = lcd_4bit_send_string_pos(&lcd1, 2,8,"ABOOOD");
    while(1){
        
        for (counter = 5 ; counter <= 8 ;counter++){
            ret = lcd_4bit_send_string_pos(&lcd1 , 1 , counter ,"HELLO" );
            ret = lcd_4bit_send_char_data_pos(&lcd1 ,1,counter-1 , ' ' );
            __delay_ms(250);
        }
        ret = lcd_4bit_send_string_pos(&lcd1 ,1, 1 ,"                " );
        for (counter = 8 ; counter >= 5 ;counter--){
            ret = lcd_4bit_send_string_pos(&lcd1 , 1 , counter ,"HELLO" );
            ret = lcd_4bit_send_char_data_pos(&lcd1 ,1,counter + 5 , ' ' );
            __delay_ms(250);
        }
        ret = lcd_4bit_send_string_pos(&lcd1 ,1, 1 ,"                " );
        
        
   }
    
    return (EXIT_SUCCESS);
    
     
}



void application_initialize(void){
    Std_ReturnType ret = E_OK;
    
    ecu_layer_initialize();
    
}
        
        


