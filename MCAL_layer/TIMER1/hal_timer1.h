/* 
 * File:   hal_timer1.h
 * Author: anaal
 *
 * Created on May 4, 2025, 2:16 AM
 */

#ifndef HAL_TIMER1_H
#define	HAL_TIMER1_H



/*Section : Includes */

#include <pic18f4620.h>
#include "../GPIO/hal_gpio.h"
#include "../GPIO/mcal_std_types.h"
#include "../Interrupt/mcal_internal_interrupt.h"

/* Section : Macro Declarations */

#define TIMER1_COUNTER_MODE_CONFIG                  1
#define TIMER1_TIMER_MODE_CONFIG                    0
#define TIMER1_SYNCHRONOUS_COUNTER_CFG              0
#define TIMER1_ASYNCHRONOUS_COUNTER_CFG             1
#define TIMER1_OSCILLATOR_ENABLE_CFG                1
#define TIMER1_OSCILLATOR_DISABLE_CFG               0
#define TIMER1_READ_WRITE_8_BIT_MODE_CFG            0
#define TIMER1_READ_WRITE_16_BIT_MODE_CFG           1
#define TIMER1_PRESCALER_DIV_1_CFG                  0
#define TIMER1_PRESCALER_DIV_2_CFG                  1
#define TIMER1_PRESCALER_DIV_4_CFG                  2
#define TIMER1_PRESCALER_DIV_8_CFG                  3


/* Section : Macro Functions Declarations */
#define TIMER1_ENABLE()                             (T1CONbits.TMR1ON = 1)
#define TIMER1_DISABLE()                            (T1CONbits.TMR1ON = 0)
#define TIMER1_COUNTER_MODE_ENABLE()                (T1CONbits.TMR1CS = 1)
#define TIMER1_TIMER_MODE_ENABLE()                  (T1CONbits.TMR1CS = 0)
#define TIMER1_SYNCHRONOUS_COUNTER_ENABLE()         (T1CONbits.T1SYNC = 0)       
#define TIMER1_ASYNCHRONOUS_COUNTER_ENABLE()        (T1CONbits.T1SYNC = 1)       
#define TIMER1_OSCILLATOR_ENABLE()                  (T1CONbits.T1OSCEN= 1)
#define TIMER1_OSCILLATOR_DISABLE()                 (T1CONbits.T1OSCEN= 0)
#define TIMER1_READ_WRITE_8_BIT_MODE_ENABLE()       (T1CONbits.RD16   = 0)
#define TIMER1_READ_WRITE_16_BIT_MODE_ENABLE()      (T1CONbits.RD16   = 1)
#define TIMER1_PRESCALER_SELECT(PRESCALER_VAL)      (T1CONbits.T1CKPS = PRESCALER_VAL )
#define TIMER1_SYSTEM_CLOCK_STATUS()                (T1CONbits.T1RUN)    



/* Section : Data Type Declarations */



typedef struct {
    #if INTERRUPT_FEATURE_ENABLE == TIMER1_INTERRUPT_FEATURE_ENABLE
    void(*TIMER1_InterruptHandler)(void) ;
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
    interrupt_priority_cfg      timer1_priority ; 
#endif
#endif
    uint8 timer1_Prescaler_val                      :2;
    uint8 timer1_mode                               :1;
    uint8 timer1_counter_Synchronization_select     :1;
    uint8 timer1_read_write_mode                    :1;
    uint8 timer1_oscillator_cfg                     :1;
    uint16 timer1_preloaded_value                     ;   
    uint8 timer1_reserved                           :2;
}timer1_config_t;

/* Section : Function Declarations */
Std_ReturnType Timer1_Init(const timer1_config_t *_timer);
Std_ReturnType Timer1_DeInit(const timer1_config_t *_timer);
Std_ReturnType Timer1_ReadVal(const timer1_config_t *_timer , uint16 *readVal);
Std_ReturnType Timer1_WriteVal(const timer1_config_t *_timer , uint16 writeVal);



#endif	/* HAL_TIMER1_H */

