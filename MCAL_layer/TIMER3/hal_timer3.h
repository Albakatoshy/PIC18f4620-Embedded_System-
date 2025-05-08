/* 
 * File:   hal_timer3.h
 * Author: anaal
 *
 * Created on May 8, 2025, 5:53 AM
 */

#ifndef HAL_TIMER3_H
#define	HAL_TIMER3_H

/*Section : Includes */

#include "pic18f4620.h"
#include "../GPIO/hal_gpio.h"
#include "../GPIO/mcal_std_types.h"
#include "../Interrupt/mcal_internal_interrupt.h"

/* Section : Macro Declarations */
#define TIMER3_COUNTER_MODE_CONFIG                      1
#define TIMER3_TIMER_MODE_CONFIG                        0
#define TIMER3_SYNCHRONOUS_COUNTER_CFG                  0
#define TIMER3_ASYNCHRONOUS_COUNTER_CFG                 1
#define TIMER3_PRESCALER_DIV_1_CFG                      0
#define TIMER3_PRESCALER_DIV_2_CFG                      1
#define TIMER3_PRESCALER_DIV_4_CFG                      2
#define TIMER3_PRESCALER_DIV_8_CFG                      3
#define TIMER3_READ_WRITE_8_BIT_MODE_CFG                0
#define TIMER3_READ_WRITE_16_BIT_MODE_CFG               1

/* Section : Macro Functions Declarations */

#define TIMER3_ENABLE()                         (T3CONbits.TMR3ON = 1)
#define TIMER3_DISABLE()                        (T3CONbits.TMR3ON = 0)
#define TIMER3_COUNTER_MODE_ENABLE()            (T3CONbits.TMR3CS = 1)
#define TIMER3_TIMER_MODE_ENABLE()              (T3CONbits.TMR3CS = 0)
#define TIMER3_SYNCHRONOUS_COUNTER_ENABLE()     (T3CONbits.T3SYNC = 0)    
#define TIMER3_ASYNCHRONOUS_COUNTER_ENABLE()    (T3CONbits.T3SYNC = 1)
#define TIMER3_PRESCALER_SELECT(PRESCALER)      (T3CONbits.T3CKPS = PRESCALER)
#define TIMER3_READ_WRITE_8_BIT_MODE_ENABLE()   (T3CONbits.RD16 = 0)
#define TIMER3_READ_WRITE_16_BIT_MODE_ENABLE()  (T3CONbits.RD16 = 1)

/* Section : Data Type Declarations */
typedef struct {
#if INTERRUPT_FEATURE_ENABLE == TIMER3_INTERRUPT_FEATURE_ENABLE
    void(*TIMER3_InterruptHandler)(void) ;
    #if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
        interrupt_priority_cfg      timer3_priority ; 
    #endif
#endif
    uint8 timer3_mode                               :1;
    uint8 timer3_counter_Synchronization_select     :1;
    uint8 timer3_Prescaler_val                      :2;
    uint8 timer3_read_write_mode                    :1;
    uint8 timer3_preloaded_value                    ;
    uint8 timer3_preserved                          :3;              
}timer3_config_t;


/* Section : Function Declarations */

Std_ReturnType Timer3_Init(const timer3_config_t *_timer);
Std_ReturnType Timer3_DeInit(const timer3_config_t *_timer);
Std_ReturnType Timer3_ReadVal(const timer3_config_t *_timer , uint16 *readVal);
Std_ReturnType Timer3_WriteVal(const timer3_config_t *_timer , uint16 writeVal);


#endif	/* HAL_TIMER3_H */

