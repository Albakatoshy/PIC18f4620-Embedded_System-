/* 
 * File:   hal_timer0.h
 * Author: anaal
 *
 * Created on May 2, 2025, 10:07 PM
 */

#ifndef HAL_TIMER0_H
#define	HAL_TIMER0_H



/*Section : Includes */
#include "../GPIO/hal_gpio.h"
#include "pic18f4620.h"
#include "../Interrupt/mcal_internal_interrupt.h"
#include "../GPIO/mcal_std_types.h"

/* Section : Macro Declarations */

#define TIMER0_PRESCALER_CONFIG_ENABLE              1
#define TIMER0_PRESCALER_CONFIG_DISABLE             0
#define TIMER0_RISING_EDGE_CONFIG                   0
#define TIMER0_FAILING_EDGE_CONFIG                  1
#define TIMER0_COUNTER_MODE_CONFIG                  1
#define TIMER0_TIMER_MODE_CONFIG                    0
#define TIMER0_16_BIT_MODE_CONFIG                   0
#define TIMER0_8_BIT_MODE_CONFIG                    1


/* Section : Macro Functions Declarations */

#define TIMER0_ENABLE()                     (T0CONbits.TMR0ON = 1)
#define TIMER0_DISABLE()                     (T0CONbits.TMR0ON = 0)

#define TIMER0_16_BIT_MODE_ENABLE()         (T0CONbits.T08BIT = 0)
#define TIMER0_8_BIT_MODE_ENABLE()          (T0CONbits.T08BIT = 1)
#define TIMER0_COUNTER_MODE_ENABLE()        (T0CONbits.T0CS   = 1)
#define TIMER0_TIMER_MODE_ENABLE()          (T0CONbits.T0CS   = 0)
#define TIMER0_RISING_EDGE_ENABLE()         (T0CONbits.T0SE   = 0)
#define TIMER0_FAILING_EDGE_ENABLE()        (T0CONbits.T0SE   = 1)
#define TIMER0_PRESCALER_ENABLE()           (T0CONbits.PSA    = 0)
#define TIMER0_PRESCALER_DISABLE()          (T0CONbits.PSA    = 1)

/* Section : Data Type Declarations */
typedef enum{
    TIMER0_PRESCALER_DIV_2 = 0  ,
    TIMER0_PRESCALER_DIV_4      ,
    TIMER0_PRESCALER_DIV_8      ,
    TIMER0_PRESCALER_DIV_16     ,
    TIMER0_PRESCALER_DIV_32     ,
    TIMER0_PRESCALER_DIV_64     ,
    TIMER0_PRESCALER_DIV_128    ,
    TIMER0_PRESCALER_DIV_256    ,          
}timer0_Prescaler_select_t;

typedef struct{
#if INTERRUPT_FEATURE_ENABLE 
    void(*TIMER0_InterruptHandler)(void) ;
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
    interrupt_priority_cfg      timer0_priority ; 
#endif
#endif
    timer0_Prescaler_select_t               Prescaler_val;
    uint8 PrescalerEnable                   :1;
    uint8 timer0_source_edge_select         :1;
    uint8 timer0_mode                       :1;    
    uint8 timer0_control_register_size      :1;
    uint16 timer0_preload_value             ;
    uint8 timer0_reserved                   :4;
    
}timer0_config_t;

typedef void (*InterruptHandler)(void);

/* Section : Function Declarations */

Std_ReturnType Timer0_Init(const timer0_config_t *_timer);
Std_ReturnType Timer0_DeInit(const timer0_config_t *_timer);
Std_ReturnType Timer0_ReadVal(const timer0_config_t *_timer , uint16 *readVal);
Std_ReturnType Timer0_WriteVal(const timer0_config_t *_timer , uint16 writeVal);


#endif	/* HAL_TIMER0_H */

