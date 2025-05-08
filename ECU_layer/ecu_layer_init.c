#include "ecu_layer_init.h"

#define _XTAL_FREQ 8000000  // 4 MHz clock

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


chr_lcd_8bit_t lcd2 = {
    .lcd_rs_pin.port        = PORTC_INDEX,
    .lcd_rs_pin.pin         =GPIO_PIN6,
    .lcd_rs_pin.logic       =GPIO_LOW,
    .lcd_rs_pin.direction   =GPIO_DIRECTION_OUTPUT,
    .lcd_en_pin.port        = PORTC_INDEX,
    .lcd_en_pin.pin         =GPIO_PIN7,
    .lcd_en_pin.logic       =GPIO_LOW,
    .lcd_en_pin.direction   =GPIO_DIRECTION_OUTPUT,
    .lcd_data[0].port       =PORTD_INDEX,
    .lcd_data[0].pin        =GPIO_PIN0,
    .lcd_data[0].logic      =GPIO_LOW,
    .lcd_data[0].direction  =GPIO_DIRECTION_OUTPUT,
    .lcd_data[1].port       =PORTD_INDEX,
    .lcd_data[1].pin        =GPIO_PIN1,
    .lcd_data[1].logic      =GPIO_LOW,
    .lcd_data[1].direction  =GPIO_DIRECTION_OUTPUT,
    .lcd_data[2].port       =PORTD_INDEX,
    .lcd_data[2].pin        =GPIO_PIN2,
    .lcd_data[2].logic      =GPIO_LOW,
    .lcd_data[2].direction  =GPIO_DIRECTION_OUTPUT,
    .lcd_data[3].port       =PORTD_INDEX,
    .lcd_data[3].pin        =GPIO_PIN3,
    .lcd_data[3].logic      =GPIO_LOW,
    .lcd_data[3].direction  =GPIO_DIRECTION_OUTPUT,
    .lcd_data[4].port       =PORTD_INDEX,
    .lcd_data[4].pin        =GPIO_PIN4,
    .lcd_data[4].logic      =GPIO_LOW,
    .lcd_data[4].direction  =GPIO_DIRECTION_OUTPUT,
    .lcd_data[5].port       =PORTD_INDEX,
    .lcd_data[5].pin        =GPIO_PIN5,
    .lcd_data[5].logic      =GPIO_LOW,
    .lcd_data[5].direction  =GPIO_DIRECTION_OUTPUT,
    .lcd_data[6].port       =PORTD_INDEX,
    .lcd_data[6].pin        =GPIO_PIN6,
    .lcd_data[6].logic      =GPIO_LOW,
    .lcd_data[6].direction  =GPIO_DIRECTION_OUTPUT,
    .lcd_data[7].port       =PORTD_INDEX,
    .lcd_data[7].pin        =GPIO_PIN7,
    .lcd_data[7].logic      =GPIO_LOW,
    .lcd_data[7].direction  =GPIO_DIRECTION_OUTPUT,
};




keypad_t keypad1= {
    .keypad_row_pins[0].port        =PORTC_INDEX,
    .keypad_row_pins[0].pin         =GPIO_PIN0, 
    .keypad_row_pins[0].logic       =GPIO_LOW,
    .keypad_row_pins[0].direction   =GPIO_DIRECTION_OUTPUT,
    .keypad_row_pins[1].port        =PORTC_INDEX,
    .keypad_row_pins[1].pin         =GPIO_PIN1, 
    .keypad_row_pins[1].logic       =GPIO_LOW,
    .keypad_row_pins[1].direction   =GPIO_DIRECTION_OUTPUT,
    .keypad_row_pins[2].port        =PORTC_INDEX,
    .keypad_row_pins[2].pin         =GPIO_PIN2, 
    .keypad_row_pins[2].logic       =GPIO_LOW,
    .keypad_row_pins[2].direction   =GPIO_DIRECTION_OUTPUT,
    .keypad_row_pins[3].port        =PORTC_INDEX,
    .keypad_row_pins[3].pin         =GPIO_PIN3, 
    .keypad_row_pins[3].logic       =GPIO_LOW,
    .keypad_row_pins[3].direction   =GPIO_DIRECTION_OUTPUT,
    
    .kepyad_col_pins[0].port        =PORTC_INDEX,
    .kepyad_col_pins[0].pin         =GPIO_PIN4,
    .kepyad_col_pins[0].logic       =GPIO_LOW,
    .kepyad_col_pins[0].direction   =GPIO_DIRECTION_INPUT,        
    .kepyad_col_pins[1].port        =PORTC_INDEX,
    .kepyad_col_pins[1].pin         =GPIO_PIN5,
    .kepyad_col_pins[1].logic       =GPIO_LOW,
    .kepyad_col_pins[1].direction   =GPIO_DIRECTION_INPUT,        
    .kepyad_col_pins[2].port        =PORTC_INDEX,
    .kepyad_col_pins[2].pin         =GPIO_PIN6,
    .kepyad_col_pins[2].logic       =GPIO_LOW,
    .kepyad_col_pins[2].direction   =GPIO_DIRECTION_INPUT,
    .kepyad_col_pins[3].port        =PORTC_INDEX,
    .kepyad_col_pins[3].pin         =GPIO_PIN7,
    .kepyad_col_pins[3].logic       =GPIO_LOW,
    .kepyad_col_pins[3].direction   =GPIO_DIRECTION_INPUT,
};


void ecu_layer_initialize(void){
    Std_ReturnType ret = E_OK;
    
    ret = keypad_initialize(&keypad1);
    ret = lcd_4bit_initialize(&lcd1);
    ret = lcd_8bit_initialize(&lcd2);
}
