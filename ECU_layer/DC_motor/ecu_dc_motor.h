/* 
 * File:   ecu_dc_motor.h
 * Author: anaal
 *
 * Created on February 27, 2025, 5:13 PM
 */

#ifndef ECU_DC_MOTOR_H
#define	ECU_DC_MOTOR_H



/*Section : Includes */
#include "../../MCAL_layer/GPIO/hal_gpio.h"
#include"ecu_dc_motor_cfg.h"

/* Section : Macro Declarations */

#define DC_MOTOR_ON_STATUS      0x01U
#define DC_MOTOR_OFF_STATUS     0x00U

#define DC_MOTOR_PIN1           0x00U
#define DC_MOTOR_PIN2           0x01U

/* Section : Macro Functions Declarations */

/* Section : Data Type Declarations */


typedef struct{
        pin_config_t dc_motor_pin[2];
}dc_motor_t;

/* Section : Function Declarations */

Std_ReturnType dc_motor_initialize(const dc_motor_t *_dc_motor);
Std_ReturnType dc_motor_move_forward(const dc_motor_t *_dc_motor);
Std_ReturnType dc_motor_move_backward(const dc_motor_t *_dc_motor);
Std_ReturnType dc_motor_stop(const dc_motor_t *_dc_motor);



#endif	/* ECU_DC_MOTOR_H */

