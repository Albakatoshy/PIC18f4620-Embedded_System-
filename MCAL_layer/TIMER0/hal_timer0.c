/* 
 * File:   hal_timer0.h
 * Author: Abood 
 *
 * Created on May 2, 2025, 10:07 PM
 */

#include "hal_timer0.h"

static inline void Timer0_prescaler_value_select(const timer0_config_t *_timer );

static inline void Timer0_mode_select(const timer0_config_t *_timer );
static inline void Timer0_control_register_size(const timer0_config_t *_timer );

#if  TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE 
static InterruptHandler TIMER0_InterruptHandler = NULL;
#endif

static uint8 timer0_preload = ZERO_INIT ;

void TIMER0_ISR(void){
    TIMER0_INTERRUPT_CLEAR_FLAG();
    TMR0H = (timer0_preload)>>8;
    TMR0L = (uint8)(timer0_preload);
    if(TIMER0_InterruptHandler){
      TIMER0_InterruptHandler();  
    }
}


Std_ReturnType Timer0_Init(const timer0_config_t *_timer){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _timer){
        Std_ReturnType ret = E_NOT_OK;
    }
    else{
        TIMER0_DISABLE();
        Timer0_prescaler_value_select(_timer);
        Timer0_mode_select(_timer);
        Timer0_control_register_size(_timer);
        TMR0H = (_timer->timer0_preload_value)>>8;
        TMR0L = (uint8)(_timer->timer0_preload_value);
        timer0_preload = _timer->timer0_preload_value; 
    #if  TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE 
        TIMER0_INTERRUPT_ENABLE();
        TIMER0_INTERRUPT_CLEAR_FLAG();
        TIMER0_InterruptHandler = _timer->TIMER0_InterruptHandler;
        
    #if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
        INTERRUPT_InterruptPriorityEnable();
        if(INTERRUPT_HIGH_PRIORITY == _timer->timer0_priority){
            INTERRUPT_GlobalInterruptHighEnable();
            TIMER0_INTERRUPT_HIGH_PRIORITY();
        }
        else if(INTERRUPT_LOW_PRIORITY == _timer->timer0_priority){
            INTERRUPT_GlobalInterruptLowEnable();
            TIMER0_INTERRUPT_LOW_PRIORITY();
        }
    #else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
    #endif
    #endif
        
        TIMER0_ENABLE();
        ret = E_OK;
    }
    
    return ret ;
    
}


Std_ReturnType Timer0_DeInit(const timer0_config_t *_timer){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _timer){
        Std_ReturnType ret = E_NOT_OK;
    }
    else{
        TIMER0_DISABLE();
#if  TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        TIMER0_INTERRUPT_DISABLE();
        
#endif        
        ret = E_OK;
    }
    return ret ;
}

Std_ReturnType Timer0_ReadVal(const timer0_config_t *_timer , uint16 *readVal){
    Std_ReturnType ret = E_NOT_OK;
    uint8 l_TMR0L = ZERO_INIT, l_TMR0H =ZERO_INIT ;
    if(NULL == _timer){
        Std_ReturnType ret = E_NOT_OK;
    }
    else{
        l_TMR0L = TMR0L; 
        l_TMR0H = TMR0H;
        *readVal = (uint16)(l_TMR0L + (l_TMR0H<<8));
        ret = E_OK;
    }
    return ret ;
}


Std_ReturnType Timer0_WriteVal(const timer0_config_t *_timer , uint16 writeVal){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _timer){
        Std_ReturnType ret = E_NOT_OK;
    }
    else{
        TMR0H = writeVal>>8;
        TMR0L = (uint8)writeVal;
  
        ret = E_OK;
    }
    return ret ;
}


static inline void Timer0_prescaler_value_select(const timer0_config_t *_timer ){
        if (_timer->PrescalerEnable == TIMER0_PRESCALER_CONFIG_ENABLE){
            TIMER0_PRESCALER_ENABLE();
            T0CONbits.T0PS = _timer->Prescaler_val;
        }
        else if (TIMER0_PRESCALER_CONFIG_DISABLE == _timer->PrescalerEnable ){
            TIMER0_PRESCALER_DISABLE();
        }
}



static inline void Timer0_mode_select(const timer0_config_t *_timer ){
    if(TIMER0_TIMER_MODE_CONFIG == _timer->timer0_mode){
        TIMER0_TIMER_MODE_ENABLE();
    }
    else if (TIMER0_COUNTER_MODE_CONFIG == _timer->timer0_mode){
        TIMER0_COUNTER_MODE_ENABLE();
        if (TIMER0_FAILING_EDGE_CONFIG == _timer->timer0_source_edge_select){
        TIMER0_FAILING_EDGE_ENABLE();
        }
        else if(TIMER0_RISING_EDGE_CONFIG ==  _timer->timer0_source_edge_select){
            TIMER0_RISING_EDGE_ENABLE();
        }
        else{/*NOTHING*/}
    }
    else{/*NOTHING*/}
}

static inline void Timer0_control_register_size(const timer0_config_t *_timer ){
    if (TIMER0_8_BIT_MODE_CONFIG == _timer->timer0_control_register_size){
        TIMER0_8_BIT_MODE_ENABLE();
    }
    else if (TIMER0_16_BIT_MODE_CONFIG ==  _timer->timer0_control_register_size){
        TIMER0_16_BIT_MODE_ENABLE();
    }
    else{/*NOTHING*/}
}

