/* 
 * File:   hal_timer2.h
 * Author: anaal
 *
 * Created on May 8, 2025, 5:50 AM
 */

#ifndef HAL_TIMER2_H
#define	HAL_TIMER2_H



/*Section : Includes */

#include "pic18f4620.h"
#include "../GPIO/hal_gpio.h"
#include "../GPIO/mcal_std_types.h"
#include "../Interrupt/mcal_internal_interrupt.h"

/* Section : Macro Declarations */

#define TIMER2_PRESCALER_DIV_1_CFG          0
#define TIMER2_PRESCALER_DIV_4_CFG          1
#define TIMER2_PRESCALER_DIV_16_CFG         2


#define TIMER2_POSTSCALER_DIV_1_CFG          0
#define TIMER2_POSTSCALER_DIV_2_CFG          1
#define TIMER2_POSTSCALER_DIV_3_CFG          2
#define TIMER2_POSTSCALER_DIV_4_CFG          3
#define TIMER2_POSTSCALER_DIV_5_CFG          4
#define TIMER2_POSTSCALER_DIV_6_CFG          5
#define TIMER2_POSTSCALER_DIV_7_CFG          6
#define TIMER2_POSTSCALER_DIV_8_CFG          7
#define TIMER2_POSTSCALER_DIV_9_CFG          8
#define TIMER2_POSTSCALER_DIV_10_CFG         9
#define TIMER2_POSTSCALER_DIV_11_CFG         10
#define TIMER2_POSTSCALER_DIV_12_CFG         11
#define TIMER2_POSTSCALER_DIV_13_CFG         12
#define TIMER2_POSTSCALER_DIV_14_CFG         13
#define TIMER2_POSTSCALER_DIV_15_CFG         14
#define TIMER2_POSTSCALER_DIV_16_CFG         15


/* Section : Macro Functions Declarations */
#define TIMER2_ENABLE()                         (T2CONbits.TMR2ON = 1)
#define TIMER2_DISABLE()                        (T2CONbits.TMR2ON = 0)
#define TIMER2_POSTSCALER_SELECT(POSTSCALER)    (T2CONbits.TOUTPS = POSTSCALER)
#define TIMER2_PRESCALER_SELECT(PRESCALER)      (T2CONbits.T2CKPS = PRESCALER)

/* Section : Data Type Declarations */

typedef struct {
#if INTERRUPT_FEATURE_ENABLE == TIMER2_INTERRUPT_FEATURE_ENABLE
    void(*TIMER2_InterruptHandler)(void) ;
    #if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
        interrupt_priority_cfg      timer2_priority ; 
    #endif
#endif 
    
    uint8 Timer2_Postscale_Select       :4;
    uint8 Timer2_Prescaler_Select       :2;
    uint8 Timer2_preloaded_value        ;
    uint8 Timer2_reserved               :2;
}timer2_config_t;

/* Section : Function Declarations */

Std_ReturnType Timer2_Init(const timer2_config_t *_timer);
Std_ReturnType Timer2_DeInit(const timer2_config_t *_timer);
Std_ReturnType Timer2_ReadVal(const timer2_config_t *_timer , uint8 *readVal);
Std_ReturnType Timer2_WriteVal(const timer2_config_t *_timer , uint8 writeVal);

#endif	/* HAL_TIMER2_H */

