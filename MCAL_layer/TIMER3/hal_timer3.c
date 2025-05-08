#include "hal_timer3.h"


static inline void Timer3_mode_select(const timer3_config_t *_timer );
static uint16 timer3_preload = ZERO_INIT;

#if INTERRUPT_FEATURE_ENABLE == TIMER3_INTERRUPT_FEATURE_ENABLE
static void (*TIMER3_InterruptHandler)(void) = NULL;
#endif

void TIMER3_ISR(void){
    TIMER3_INTERRUPT_CLEAR_FLAG();
    TMR3H = timer3_preload>>8;
    TMR3L = (uint8)timer3_preload;
    
    if (TIMER3_InterruptHandler){
        TIMER3_InterruptHandler();
    }
}


Std_ReturnType Timer3_Init(const timer3_config_t *_timer){
    Std_ReturnType ret = E_NOT_OK ;
    if (NULL == _timer){
        ret = E_NOT_OK ;
    }
    else{
        TIMER3_DISABLE();
        Timer3_mode_select(_timer);
        TIMER3_PRESCALER_SELECT(_timer->timer3_Prescaler_val);
        
        TMR3H = (_timer->timer3_preloaded_value)>>8;
        TMR3L = (uint8)(_timer->timer3_preloaded_value);
        timer3_preload = _timer->timer3_preloaded_value;
        
#if INTERRUPT_FEATURE_ENABLE == TIMER3_INTERRUPT_FEATURE_ENABLE
        TIMER3_INTERRUPT_ENABLE();
        TIMER3_INTERRUPT_CLEAR_FLAG();
        TIMER3_InterruptHandler = _timer->TIMER3_InterruptHandler;
#if INTERRUPT_FEATURE_ENABLE == INTERRUPT_PRIORITY_LEVELS_ENABLE
        INTERRUPT_InterruptPriorityEnable();
        if (INTERRUPT_HIGH_PRIORITY == _timer->timer3_priority){
            TIMER3_INTERRUPT_HIGH_PRIORITY();
            INTERRUPT_GlobalInterruptHighEnable();
        }
        else if(INTERRUPT_LOW_PRIORITY == _timer->timer3_priority){
            TIMER3_INTERRUPT_LOW_PRIORITY();
            INTERRUPT_GlobalInterruptLowEnable();
        }
        else{/*NOTHING*/}
#else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
        
#endif
#endif
        
        TIMER3_ENABLE();
        ret = E_OK;
    }
    
    return ret ;
}

Std_ReturnType Timer3_DeInit(const timer3_config_t *_timer){
    Std_ReturnType ret = E_NOT_OK ;
    if (NULL == _timer){
        ret = E_NOT_OK ;
    }
    else{
        TIMER3_DISABLE();
#if INTERRUPT_FEATURE_ENABLE == TIMER3_INTERRUPT_FEATURE_ENABLE
        TIMER3_INTERRUPT_DISABLE();
#endif
        ret = E_OK;
    }
    
    return ret ;
}

Std_ReturnType Timer3_ReadVal(const timer3_config_t *_timer , uint16 *readVal){
    Std_ReturnType ret = E_NOT_OK ;
    uint8 l_TMR3L = ZERO_INIT , l_TMR3H = ZERO_INIT ;
    if ((NULL == _timer) && (NULL == readVal)){
        ret = E_NOT_OK ;
    }
    else{
        l_TMR3L = TMR3L;
        l_TMR3H = TMR3H;
        
        *readVal = (uint16)(l_TMR3L + (l_TMR3H<<8));
        
        ret = E_OK;
    }
    
    return ret ;
}

Std_ReturnType Timer3_WriteVal(const timer3_config_t *_timer , uint16 writeVal){
    Std_ReturnType ret = E_NOT_OK ;
    if (NULL == _timer){
        ret = E_NOT_OK ;
    }
    else{
        
        TMR3H = writeVal>>8;
        TMR3L = (uint8) writeVal;
        
        ret = E_OK;
    }
    
    return ret ;
}

static inline void Timer3_mode_select(const timer3_config_t *_timer ){
    if(TIMER3_COUNTER_MODE_CONFIG == _timer->timer3_mode){
        TIMER3_COUNTER_MODE_ENABLE();
        if(TIMER3_ASYNCHRONOUS_COUNTER_CFG ==_timer->timer3_counter_Synchronization_select){
            TIMER3_ASYNCHRONOUS_COUNTER_ENABLE();
        }
        else if(TIMER3_SYNCHRONOUS_COUNTER_CFG == _timer->timer3_counter_Synchronization_select){
            TIMER3_SYNCHRONOUS_COUNTER_ENABLE();
        }
        else{/*NOTHING*/}   
    }
    else if (TIMER3_TIMER_MODE_CONFIG == _timer->timer3_mode){
        TIMER3_TIMER_MODE_ENABLE();
    }
    else{/*NOTHING*/} 
}