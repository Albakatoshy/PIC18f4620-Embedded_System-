#include "hal_timer2.h"

#if TIMER2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE 
static void (*TIMER2_InterruptHandler)(void) = NULL;
#endif

static uint8 timer1_preload = ZERO_INIT;


void TIMER2_ISR(void){
    TIMER2_INTERRUPT_CLEAR_FLAG();
    TMR2 = timer1_preload ;
    
    if(TIMER2_InterruptHandler){
        TIMER2_InterruptHandler();
    }
}


Std_ReturnType Timer2_Init(const timer2_config_t *_timer){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _timer){
        ret = E_NOT_OK;
    }
    else{
        TIMER2_DISABLE();
        TIMER2_POSTSCALER_SELECT(_timer->Timer2_Postscale_Select);
        TIMER2_PRESCALER_SELECT(_timer->Timer2_Prescaler_Select);
        
        TMR2 = _timer->Timer2_preloaded_value;
        timer1_preload = _timer->Timer2_preloaded_value;
#if TIMER2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE 
        TIMER2_INTERRUPT_ENABLE();
        TIMER2_INTERRUPT_CLEAR_FLAG();
        TIMER2_InterruptHandler = _timer->TIMER2_InterruptHandler;
#if INTERRUPT_FEATURE_ENABLE == INTERRUPT_PRIORITY_LEVELS_ENABLE
        INTERRUPT_InterruptPriorityEnable();
        if (INTERRUPT_HIGH_PRIORITY == _timer->timer2_priority){
            TIMER2_INTERRUPT_HIGH_PRIORITY();
            INTERRUPT_GlobalInterruptHighEnable();
        }
        else if(INTERRUPT_LOW_PRIORITY == _timer->timer2_priority){
            TIMER2_INTERRUPT_LOW_PRIORITY();
            INTERRUPT_GlobalInterruptLowEnable();
        }
        else{/*NOTHING*/}
#else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();        
        
#endif
#endif        
        
        TIMER2_ENABLE();
        ret = E_OK;
    }
    
    return ret ;
}

Std_ReturnType Timer2_DeInit(const timer2_config_t *_timer){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _timer){
        ret = E_NOT_OK;
    }
    else{
        TIMER2_DISABLE();
#if TIMER2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE 
        TIMER2_INTERRUPT_DISABLE();
#endif
        ret = E_OK;
    }
    
    return ret ;
}

Std_ReturnType Timer2_ReadVal(const timer2_config_t *_timer , uint8 *readVal){
    Std_ReturnType ret = E_NOT_OK;
    if((NULL == _timer) && (NULL == readVal) ){
        ret = E_NOT_OK;
    }
    else{
        *readVal = (uint8)TMR2;
        ret = E_OK;
    }
    
    return ret ;
}

Std_ReturnType Timer2_WriteVal(const timer2_config_t *_timer , uint8 writeVal){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _timer){
        ret = E_NOT_OK;
    }
    else{
        TMR2 = (uint8)writeVal ;
        ret = E_OK;
    }
    
    return ret ;
}