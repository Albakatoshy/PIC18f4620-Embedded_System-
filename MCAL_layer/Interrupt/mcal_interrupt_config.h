/* 
 * File:   mcal_interrupt_config.h
 * Author: anaal
 *
 * Created on April 13, 2025, 4:12 PM
 */

#ifndef MCAL_INTERRUPT_CONFIG_H
#define	MCAL_INTERRUPT_CONFIG_H

/*Section : Includes */
#include <pic18f4620.h>
#include "../GPIO/mcal_std_types.h"
#include "mcal_interrupt_gen_cfg.h"
#include "../GPIO/hal_gpio.h"

/* Section : Macro Declarations */

#define INTERRUPT_ENABLE            1
#define INTERRUPT_DISABLE           0
#define INTERRUPT_OCCUR             1
#define INTERRUPT_NOT_OCCUR         0
#define INTERRUPT_PRIORITY_ENABLE   1
#define INTERRUPT_PRIORITY_DISABLE  0


/* Section : Macro Functions Declarations */

#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
/*this macro functions enable and disable the priority feature */
#define INTERRUPT_InterruptPriorityEnable()        (RCONbits.IPEN=1)
#define INTERRUPT_InterruptPriorityDisable()        (RCONbits.IPEN=0)

/*this macro functions enable and disable global high priority interrupt */
#define INTERRUPT_GlobalInterruptHighEnable()       (INTCONbits.GIEH=1)
#define INTERRUPT_GlobalInterruptHighDisable()      (INTCONbits.GIEH=0)

/*this macro functions enable and disable global low priority interrupt */
#define INTERRUPT_GlobalInterruptLowEnable()        (INTCONbits.GIEL=1)
#define INTERRUPT_GlobalInterruptLowDisable()        (INTCONbits.GIEL=0)

#else
/*this macro function will work if the priority levels feature disable */

/*this macro functions enable and disable global interrupt */
#define INTERRUPT_GlobalInterruptEnable()       (INTCONbits.GIE=1)
#define INTERRUPT_GlobalInterruptDisable()      (INTCONbits.GIE=0)

/*this macro function will enable and disable Peripheral Interrupt */
#define INTERRUPT_PeripheralInterruptEnable()       (INTCONbits.PEIE=1)
#define INTERRUPT_PeripheralInterruptDisable()      (INTCONbits.PEIE=0) 

#endif

 


/* Section : Data Type Declarations */

typedef enum{
    INTERRUPT_LOW_PRIORITY = 0 ,
    INTERRUPT_HIGH_PRIORITY,
        
}interrupt_priority_cfg;

/* Section : Function Declarations */

#endif	/* MCAL_INTERRUPT_CONFIG_H */

