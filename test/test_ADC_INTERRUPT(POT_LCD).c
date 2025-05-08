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

uint16 ADC_res1 ,ADC_res2,ADC_res3,ADC_res4;
uint8 print_res1[6] , print_res2[6] , print_res3[6] ,print_res4[6] ;
uint8 ADC_req = 0;

void ADC_test_INTERRUPT(void);


chr_lcd_4bit_t lcd1 = {
    .lcd_rs_pin.port        = PORTC_INDEX,
    .lcd_rs_pin.pin         =GPIO_PIN0,
    .lcd_rs_pin.logic       =GPIO_LOW,
    .lcd_rs_pin.direction   =GPIO_DIRECTION_OUTPUT,
    .lcd_en_pin.port        = PORTC_INDEX,
    .lcd_en_pin.pin         =GPIO_PIN1,
    .lcd_en_pin.logic       =GPIO_LOW,
    .lcd_en_pin.direction   =GPIO_DIRECTION_OUTPUT,
    .lcd_data[0].port       =PORTC_INDEX,
    .lcd_data[0].pin        =GPIO_PIN2,
    .lcd_data[0].logic      =GPIO_LOW,
    .lcd_data[0].direction  =GPIO_DIRECTION_OUTPUT,
    .lcd_data[1].port       =PORTC_INDEX,
    .lcd_data[1].pin        =GPIO_PIN3,
    .lcd_data[1].logic      =GPIO_LOW,
    .lcd_data[1].direction  =GPIO_DIRECTION_OUTPUT,
    .lcd_data[2].port       =PORTC_INDEX,
    .lcd_data[2].pin        =GPIO_PIN4,
    .lcd_data[2].logic      =GPIO_LOW,
    .lcd_data[2].direction  =GPIO_DIRECTION_OUTPUT,
    .lcd_data[3].port       =PORTC_INDEX,
    .lcd_data[3].pin        =GPIO_PIN5,
    .lcd_data[3].logic      =GPIO_LOW,
    .lcd_data[3].direction  =GPIO_DIRECTION_OUTPUT,
};

adc_configuration_t ADC1 ={
  .ADC_InterruptHandler = ADC_test_INTERRUPT  ,
  //.adc_priority         = INTERRUPT_HIGH_PRIORITY,
  .adc_channel          = ADC_CHANNEL_AN0 ,
  .acquisition_time     = ADC_12_TAD       ,
  .conversion_clock     = ADC_CONVERSION_CLOCK_FOSC_DIV_16,
  .result_format       = ADC_RESULT_FORMAT_RIGHT,
  .voltage_reference    = ADC_VOLTAGE_REFERENCE_DISABLE ,
};




int main() {
    Std_ReturnType ret = E_OK;
    application_initialize();
    
    ret = lcd_4bit_send_string_pos(&lcd1 , 1, 7 , "ADC TEST");
    __delay_ms(2000);
    ret = lcd_4bit_send_command(&lcd1 , _LCD_CLEAR);
    
    ret = lcd_4bit_send_string_pos(&lcd1 , 1, 1 , "pot0: ");
    ret = lcd_4bit_send_string_pos(&lcd1 , 2, 1 , "pot1: ");
    ret = lcd_4bit_send_string_pos(&lcd1 , 3, 1 , "pot2: ");
    ret = lcd_4bit_send_string_pos(&lcd1 , 4, 1 , "pot3: ");
    while(1){
        if(0==ADC_req){
            ret = ADC_StartConversion_Interrupt(&ADC1 , ADC_CHANNEL_AN0);
            ADC_req=1;
        }
        else if(1==ADC_req){
             ret = ADC_StartConversion_Interrupt(&ADC1 , ADC_CHANNEL_AN1);
             ADC_req=2;
        }
        else if(2==ADC_req){
             ret = ADC_StartConversion_Interrupt(&ADC1 , ADC_CHANNEL_AN2);
             ADC_req=3;
        }
        else if(3==ADC_req){
             ret = ADC_StartConversion_Interrupt(&ADC1 , ADC_CHANNEL_AN3);
             ADC_req=0;
        }
        else{
            /*NOTHING*/
        }
       
       ret = convert_short_to_string(ADC_res1 , print_res1);
       ret = convert_short_to_string(ADC_res2 , print_res2);
       ret = convert_short_to_string(ADC_res3 , print_res3);
       ret = convert_short_to_string(ADC_res4 , print_res4);
       
       ret =  lcd_4bit_send_string_pos(&lcd1,1, 8 , print_res1);
       ret = lcd_4bit_send_string_pos(&lcd1 , 2, 8 , print_res2);
       ret = lcd_4bit_send_string_pos(&lcd1 , 3, 8 , print_res3);
       ret = lcd_4bit_send_string_pos(&lcd1 , 4, 8 , print_res4);
       
       
   }
    
    return (EXIT_SUCCESS);
    
     
}



void application_initialize(void){
    Std_ReturnType ret = E_OK;
    ret = ADC_Init(&ADC1);
    ret = lcd_4bit_initialize(&lcd1);
    ecu_layer_initialize();
    
}
        

void ADC_test_INTERRUPT(void){
    Std_ReturnType ret = E_OK;
    if(0==ADC_req){
        ret = ADC_GetConversionResult(&ADC1 , &ADC_res1);
    }
    else if(1==ADC_req){
         ret = ADC_GetConversionResult(&ADC1 , &ADC_res2);
    }
    else if(2==ADC_req){
         ret = ADC_GetConversionResult(&ADC1 , &ADC_res3);
    }
    else if(3==ADC_req){
         ret = ADC_GetConversionResult(&ADC1 , &ADC_res4);
    }
    else{
        /*NOTHING*/
    } 
    
}
       


