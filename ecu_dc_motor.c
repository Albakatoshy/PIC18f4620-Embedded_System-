#include "ECU_layer/DC_motor/ecu_dc_motor.h"




Std_ReturnType dc_motor_initialize(const dc_motor_t *_dc_motor){
    Std_ReturnType ret = E_OK;
    
    if(NULL == _dc_motor){
        Std_ReturnType ret = E_NOT_OK;
    }
    else{
//        pin_config_t dc_motor_pin1_initialize = {
//            .port     =_dc_motor->dc_motor[0].   dc_motor_port,
//            .pin      =_dc_motor->dc_motor[0].   dc_motor_pin,
//            .logic    =_dc_motor->dc_motor[0].   dc_motor_status,
//            .direction=GPIO_DIRECTION_OUTPUT,   
//        };
//    
//        pin_config_t dc_motor_pin2_initialize = {
//            .port     =_dc_motor->dc_motor[1].   dc_motor_port,
//            .pin      =_dc_motor->dc_motor[1].   dc_motor_pin,
//            .logic    =_dc_motor->dc_motor[1].   dc_motor_status,
//            .direction=GPIO_DIRECTION_OUTPUT,   
//        };
        
//        dc_motor_pin1_initialize.port     =_dc_motor->dc_motor[DC_MOTOR_PIN1].   dc_motor_port;
//        dc_motor_pin1_initialize.pin      =_dc_motor->dc_motor[DC_MOTOR_PIN1].   dc_motor_pin;
//        dc_motor_pin1_initialize.logic    =_dc_motor->dc_motor[DC_MOTOR_PIN1].   dc_motor_status;
//        dc_motor_pin1_initialize.direction=GPIO_DIRECTION_OUTPUT;
//        
//        dc_motor_pin2_initialize.port     =_dc_motor->dc_motor[DC_MOTOR_PIN2].   dc_motor_port;
//        dc_motor_pin2_initialize.pin      =_dc_motor->dc_motor[DC_MOTOR_PIN2].   dc_motor_pin;
//        dc_motor_pin2_initialize.logic    =_dc_motor->dc_motor[DC_MOTOR_PIN2].   dc_motor_status;
//        dc_motor_pin2_initialize.direction=GPIO_DIRECTION_OUTPUT;
        
        
        
        ret = gpio_pin_intialize(&(_dc_motor->dc_motor_pin[DC_MOTOR_PIN1]));
        ret = gpio_pin_intialize(&(_dc_motor->dc_motor_pin[DC_MOTOR_PIN2]));
    }
    return  ret;
}
Std_ReturnType dc_motor_move_forward(const dc_motor_t *_dc_motor){
    Std_ReturnType ret = E_OK;
    if(NULL == _dc_motor){
        Std_ReturnType ret = E_NOT_OK;
    }
    else{
        ret = gpio_pin_write_logic(&(_dc_motor->dc_motor_pin[DC_MOTOR_PIN1]) , GPIO_HIGH);
        ret = gpio_pin_write_logic(&(_dc_motor->dc_motor_pin[DC_MOTOR_PIN2]) , GPIO_LOW);    
    }
    
    return  ret;
    
}
Std_ReturnType dc_motor_move_backward(const dc_motor_t *_dc_motor){
    Std_ReturnType ret = E_OK;
    if(NULL == _dc_motor){
        Std_ReturnType ret = E_NOT_OK;
    }
    else{
        ret = gpio_pin_write_logic(&(_dc_motor->dc_motor_pin[DC_MOTOR_PIN1]) , GPIO_LOW);
        ret = gpio_pin_write_logic(&(_dc_motor->dc_motor_pin[DC_MOTOR_PIN2] ), GPIO_HIGH);
    }
    
    return  ret;
    
}
Std_ReturnType dc_motor_stop(const dc_motor_t *_dc_motor){
    Std_ReturnType ret = E_OK;
    if(NULL == _dc_motor){
        Std_ReturnType ret = E_NOT_OK;
    }
    else{
        ret = gpio_pin_write_logic(&(_dc_motor->dc_motor_pin[DC_MOTOR_PIN1]) , GPIO_LOW);
        ret = gpio_pin_write_logic(&(_dc_motor->dc_motor_pin[DC_MOTOR_PIN2]) , GPIO_LOW);
    }
    
    return  ret;
}
