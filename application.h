/* 
 * File:   application.h
 * Author: anaal
 *
 * Created on January 27, 2025, 2:51 AM
 */

#ifndef APPLICATION_H
#define	APPLICATION_H

/*Section : Includes */


#include "ECU_layer/ecu_layer_init.h"
#include "ECU_layer/LCD/ecu_chr_lcd.h"
#include "MCAL_layer/Interrupt/mcal_external_interrupt.h"
#include "MCAL_layer/EEPROM/hal_eeprom.h"
#include "MCAL_layer/ADC/hal_adc.h"
#include "MCAL_layer/TIMER0/hal_timer0.h"
#include "MCAL_layer/TIMER1/hal_timer1.h"
#include "MCAL_layer/TIMER2/hal_timer2.h"
#include "MCAL_layer/TIMER3/hal_timer3.h"

/* Section : Macro Declarations */

/* Section : Macro Functions Declarations */

/* Section : Data Type Declarations */



/* Section : Function Declarations */

void application_initialize(void);
#endif	/* APPLICATION_H */

