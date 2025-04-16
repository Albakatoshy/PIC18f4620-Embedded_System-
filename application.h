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
#include "MCAL_layer/Interrupt/mcal_external_interrupt.h"


/* Section : Macro Declarations */

/* Section : Macro Functions Declarations */

/* Section : Data Type Declarations */
extern keypad_t keypad1 ;
extern chr_lcd_8bit_t lcd2 ;
extern chr_lcd_4bit_t lcd1 ;


/* Section : Function Declarations */

void application_initialize(void);
#endif	/* APPLICATION_H */

