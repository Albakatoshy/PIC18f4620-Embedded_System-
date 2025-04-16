/* 
 * File:   ecu_button.h
 * Author: anaal
 *
 * Created on February 18, 2025, 7:01 PM
 */

#ifndef ECU_BUTTON_H
#define	ECU_BUTTON_H


/*Section : Includes */
#include "ecu_button_cfg.h"
#include "../../MCAL_layer/GPIO/hal_gpio.h"




/* Section : Macro Declarations */

/* Section : Macro Functions Declarations */

/* Section : Data Type Declarations */

typedef enum{
    BUTTON_PRESSED,
    BUTTON_RELEASED,
}button_state_t;

typedef enum{
    BUTTON_ACTIVE_HIGH,
    BUTTON_ACTIVE_LOW,
}button_active_t;
 

typedef struct{
    pin_config_t button_pin;
    button_state_t button_state;
    button_active_t button_connection;
}button_t;



/* Section : Function Declarations */

Std_ReturnType button_initialze(const button_t *btn);
Std_ReturnType button_read_state(const button_t *btn , button_state_t *btn_state);



#endif	/* ECU_BUTTON_H */

