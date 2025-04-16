#include "ecu_relay.h"


Std_ReturnType relay_initialize(const relay_t *relay){
    Std_ReturnType ret = E_OK ;
    pin_config_t relay_initialize = {
        .pin=relay->relay_pin , 
        .port=relay->relay_port,
        .direction=GPIO_DIRECTION_OUTPUT,
        .logic    = relay->relay_status,
    };
    
    if (NULL == relay){
        ret = E_NOT_OK;
    }
    else{
        ret = gpio_pin_intialize(&(relay_initialize));
    }
}


Std_ReturnType relay_turn_on(const relay_t *relay){
    Std_ReturnType ret = E_OK ;
    pin_config_t relay_initialize = {
        .pin=relay->relay_pin , 
        .port=relay->relay_port,
        .direction=GPIO_DIRECTION_OUTPUT,
        .logic    = relay->relay_status,
    };
    
    if (NULL == relay){
        ret = E_NOT_OK;
    }
    else{
        ret = gpio_pin_write_logic(&(relay_initialize),GPIO_HIGH);
    }
    
}


Std_ReturnType relay_turn_off(const relay_t *relay){
    Std_ReturnType ret = E_OK ;
    pin_config_t relay_initialize = {
        .pin=relay->relay_pin , 
        .port=relay->relay_port,
        .direction=GPIO_DIRECTION_OUTPUT,
        .logic    = relay->relay_status,
    };
    
    if (NULL == relay){
        ret = E_NOT_OK;
    }
    else{
        ret = gpio_pin_write_logic(&(relay_initialize),GPIO_LOW);
    }
}

    