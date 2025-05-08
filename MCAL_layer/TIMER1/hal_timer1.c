#include "hal_timer1.h"


static inline void Timer1_mode_select(const timer1_config_t *_timer );

static inline void Timer1_oscillator_cfg_select(const timer1_config_t *_timer );

#if INTERRUPT_FEATURE_ENABLE == TIMER1_INTERRUPT_FEATURE_ENABLE
static void(*TIMER1_InterruptHandler)(void)= NULL ; 
#endif
static uint16 timer1_preload = ZERO_INIT;

void TIMER1_ISR(void){
    TIMER1_INTERRUPT_CLEAR_FLAG();
    TMR1H = timer1_preload>>8;
    TMR1L = (uint8)timer1_preload;
    
    if (TIMER1_InterruptHandler){
        TIMER1_InterruptHandler();
    }
}

Std_ReturnType Timer1_Init(const timer1_config_t *_timer){
    Std_ReturnType ret = E_NOT_OK;
    if (NULL == _timer){
        ret = E_NOT_OK;
    }
    else{
        TIMER1_DISABLE();
        T1CONbits.TMR1ON = 0;
        Timer1_mode_select(_timer);
        TIMER1_PRESCALER_SELECT(_timer->timer1_Prescaler_val);
     
        TMR1H = (_timer->timer1_preloaded_value)>>8;
        TMR1L = (uint8)(_timer->timer1_preloaded_value);
        timer1_preload = _timer->timer1_preloaded_value;
        
#if INTERRUPT_FEATURE_ENABLE == TIMER1_INTERRUPT_FEATURE_ENABLE
        TIMER1_INTERRUPT_ENABLE();
        TIMER1_INTERRUPT_CLEAR_FLAG();
        TIMER1_InterruptHandler = _timer->TIMER1_InterruptHandler;
#if INTERRUPT_FEATURE_ENABLE == INTERRUPT_PRIORITY_LEVELS_ENABLE
        INTERRUPT_InterruptPriorityEnable();
        if (INTERRUPT_HIGH_PRIORITY == _timer->timer1_priority){
            TIMER1_INTERRUPT_HIGH_PRIORITY();
            INTERRUPT_GlobalInterruptHighEnable();
        }
        else if(INTERRUPT_LOW_PRIORITY == _timer->timer1_priority){
            TIMER1_INTERRUPT_LOW_PRIORITY();
            INTERRUPT_GlobalInterruptLowEnable();
        }
        else{/*NOTHING*/}
#else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
        
#endif
#endif

        TIMER1_ENABLE();
        ret = E_OK;
    }
    
    return ret ;
}
Std_ReturnType Timer1_DeInit(const timer1_config_t *_timer){
    Std_ReturnType ret = E_NOT_OK;
    if (NULL == _timer){
        ret = E_NOT_OK;
    }
    else{
        
        TIMER1_DISABLE();
#if INTERRUPT_FEATURE_ENABLE == TIMER1_INTERRUPT_FEATURE_ENABLE        
        TIMER1_INTERRUPT_DISABLE();
#endif        
        ret = E_OK;
    }
    
    return ret ;
}
Std_ReturnType Timer1_ReadVal(const timer1_config_t *_timer , uint16 *readVal){
    Std_ReturnType ret = E_NOT_OK;
    uint8 l_TMR1L = 0 ,l_TMR1H = 0; 
    if (NULL == _timer){
        ret = E_NOT_OK;
    }
    else{
        
        l_TMR1L = TMR1L;
        l_TMR1H = TMR1H;
        *readVal = (uint16)((l_TMR1H<<8)+l_TMR1L);
        
        ret = E_OK;
    }
    
    return ret ;
}
Std_ReturnType Timer1_WriteVal(const timer1_config_t *_timer , uint16 writeVal){
    Std_ReturnType ret = E_NOT_OK;
    if (NULL == _timer){
        ret = E_NOT_OK;
    }
    else{
       
        TMR1H = writeVal>>8;
        TMR1L = (uint8)writeVal;
        
        ret = E_OK;
    }
    
    return ret ;
}

static inline void Timer1_mode_select(const timer1_config_t *_timer ){
    if(TIMER1_COUNTER_MODE_CONFIG == _timer->timer1_mode){
        TIMER1_COUNTER_MODE_ENABLE();
        if(TIMER1_ASYNCHRONOUS_COUNTER_CFG ==_timer->timer1_counter_Synchronization_select){
            TIMER1_ASYNCHRONOUS_COUNTER_ENABLE();
        }
        else if(TIMER1_SYNCHRONOUS_COUNTER_CFG == _timer->timer1_counter_Synchronization_select){
            TIMER1_SYNCHRONOUS_COUNTER_ENABLE();
        }
        else{/*NOTHING*/}   
    }
    else if (TIMER1_TIMER_MODE_CONFIG == _timer->timer1_mode){
        TIMER1_TIMER_MODE_ENABLE();
    }
    else{/*NOTHING*/} 
}



static inline void Timer1_oscillator_cfg_select(const timer1_config_t *_timer ){
    if(TIMER1_OSCILLATOR_ENABLE_CFG  == _timer->timer1_oscillator_cfg){
        TIMER1_OSCILLATOR_ENABLE();
    }
    else if (TIMER1_OSCILLATOR_DISABLE_CFG == _timer->timer1_oscillator_cfg){
        TIMER1_OSCILLATOR_DISABLE();
    }
    else{/*NOTHING*/}
}

