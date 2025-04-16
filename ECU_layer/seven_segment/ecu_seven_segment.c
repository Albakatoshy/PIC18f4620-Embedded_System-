#include "ecu_seven_segment.h"


Std_ReturnType seven_seg_initialize(const sev_segment_t *sev_seg){
    Std_ReturnType ret = E_OK;
    if (NULL == sev_seg){
        ret = E_NOT_OK;
    }
    else {
        ret = gpio_pin_intialize(&(sev_seg->sev_segment_pins[SEVEN_SEG_PIN0]));
        ret = gpio_pin_intialize(&(sev_seg->sev_segment_pins[SEVEN_SEG_PIN1]));
        ret = gpio_pin_intialize(&(sev_seg->sev_segment_pins[SEVEN_SEG_PIN2]));
        ret = gpio_pin_intialize(&(sev_seg->sev_segment_pins[SEVEN_SEG_PIN3]));
    }
    
    return ret ;
}


Std_ReturnType seven_seg_write_number(const sev_segment_t *sev_seg , uint8 number){
    Std_ReturnType ret = E_OK;
    if ((NULL == sev_seg) && (number > 9)){
        ret = E_NOT_OK;
    }
    else{
        gpio_pin_write_logic(&(sev_seg->sev_segment_pins[SEVEN_SEG_PIN0]),(number) & 0x01);
        gpio_pin_write_logic(&(sev_seg->sev_segment_pins[SEVEN_SEG_PIN1]),(number>>1) & 0x01);
        gpio_pin_write_logic(&(sev_seg->sev_segment_pins[SEVEN_SEG_PIN2]),(number>>2) & 0x01);
        gpio_pin_write_logic(&(sev_seg->sev_segment_pins[SEVEN_SEG_PIN3]),(number>>3) & 0x01);   
    }
    
    return ret ;
}