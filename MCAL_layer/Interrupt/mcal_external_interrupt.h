/* 
 * File:   mcal_external_interrupt.h
 * Author: Abdalrahman
 *
 * Created on April 13, 2025, 4:14 PM
 */

#ifndef MCAL_EXTERNAL_INTERRUPT_H
#define	MCAL_EXTERNAL_INTERRUPT_H




/*Section : Includes */
#include "mcal_interrupt_config.h"

/* Section : Macro Declarations */

/* Section : Macro Functions Declarations */
#if EXTERNAL_INTERRUPT_INTx_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

/*this macro functions enable and disable INT0 */
#define EXTERNAL_INTERRUPT_INT0_InterruptEnable()           (INTCONbits.INT0IE=1)
#define EXTERNAL_INTERRUPT_INT0_InterruptDisable()          (INTCONbits.INT0IE=0)
#define EXTERNAL_INTERRUPT_INT0_ClearInterruptFlag()        (INTCONbits.INT0IF=0)
#define EXTERNAL_INTERRUPT_INT0_RisingEdgeSelect()          (INTCON2bits.INTEDG0=1)    
#define EXTERNAL_INTERRUPT_INT0_FallingEdgeSelect()         (INTCON2bits.INTEDG0=0)    

#define EXTERNAL_INTERRUPT_INT1_InterruptEnable()           (INTCON3bits.INT1IE=1)
#define EXTERNAL_INTERRUPT_INT1_InterruptDisable()          (INTCON3bits.INT1IE=0)  
#define EXTERNAL_INTERRUPT_INT1_ClearInterruptFlag()        (INTCON3bits.INT1IF=0)
#define EXTERNAL_INTERRUPT_INT1_RisingEdgeSelect()          (INTCON2bits.INTEDG1=1)    
#define EXTERNAL_INTERRUPT_INT1_FallingEdgeSelect()         (INTCON2bits.INTEDG1=0)

#define EXTERNAL_INTERRUPT_INT2_InterruptEnable()           (INTCON3bits.INT2IE=1)
#define EXTERNAL_INTERRUPT_INT2_InterruptDisable()          (INTCON3bits.INT2IE=0)  
#define EXTERNAL_INTERRUPT_INT2_ClearInterruptFlag()        (INTCON3bits.INT2IF=0)
#define EXTERNAL_INTERRUPT_INT2_RisingEdgeSelect()          (INTCON2bits.INTEDG2=1)    
#define EXTERNAL_INTERRUPT_INT2_FallingEdgeSelect()         (INTCON2bits.INTEDG2=0)

/*this check if the PRIORITY_LEVELS enable or disable*/
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
#define EXTERNAL_INTERRUPT_INT1_InterruptHighPriority()     (INTCON3bits.INT1IP=1)
#define EXTERNAL_INTERRUPT_INT1_InterruptLowPriority()      (INTCON3bits.INT1IP=0)

#define EXTERNAL_INTERRUPT_INT2_InterruptHighPriority()     (INTCON3bits.INT2IP=1)
#define EXTERNAL_INTERRUPT_INT2_InterruptLowPriority()      (INTCON3bits.INT2IP=0)
#endif

#endif

#if EXTERNAL_INTERRUPT_OnChange_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
#define EXTERNAL_INTERRUPT_RBx_InterruptEnable()            (INTCONbits.RBIE=1)
#define EXTERNAL_INTERRUPT_RBx_InterruptDisable()           (INTCONbits.RBIE=0)
#define EXTERNAL_INTERRUPT_RBx_ClearInterruptFlag()         (INTCONbits.RBIF=0)    

#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE

#define EXTERNAL_INTERRUPT_RBx_InterruptHighPriority()      (INTCON2bits.RBIP=1)
#define EXTERNAL_INTERRUPT_RBx_InterruptLowPriority()       (INTCON2bits.RBIP=0)   
#endif

#endif


/* Section : Data Type Declarations */

typedef void (*InterruptHandler)(void);

typedef enum{
    INTERRUPT_FALLING_EDGE = 0 ,
    INTERRUPT_RISING_EDGE  = 1 ,       
}interrupt_INTx_edge;

typedef enum{
    INTERRUPT_EXTERNAL_INT0 = 0,
    INTERRUPT_EXTERNAL_INT1 ,
    INTERRUPT_EXTERNAL_INT2 ,       
}interrupt_INTx_src;



typedef struct{
    void(* EXT_InterruprHandler)(void);
    interrupt_INTx_edge     edge;
    interrupt_INTx_src      source;
    interrupt_priority_cfg  priority;
    pin_config_t            mcu_pin;
    
}interrupt_INTx_t;
    
    
typedef struct{
    void(* EXT_InterruprHandler_HIGH)(void);
    void(* EXT_InterruprHandler_LOW)(void);
    pin_config_t            mcu_pin;
    interrupt_priority_cfg  priority;
}interrupt_RBx_t;

/* Section : Function Declarations */
Std_ReturnType Interrupt_INTx_Init(const interrupt_INTx_t *int_obj);
Std_ReturnType Interrupt_INTx_DeInit(const interrupt_INTx_t *int_obj);

Std_ReturnType Interrupt_RBx_Init(const interrupt_RBx_t *int_obj);
Std_ReturnType Interrupt_RBx_DeInit(const interrupt_RBx_t *int_obj);



#endif	/* MCAL_EXTERNAL_INTERRUPT_H */

