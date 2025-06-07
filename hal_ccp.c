#include "MCAL_layer/CCP/hal_ccp.h"
#include "ECU_layer/LCD/ecu_chr_lcd.h"

static void CCP_PWM_MODE_CONFIG(const ccp_config_t *ccp_obj);
static void CCP_INTERRUPT_CONFIG(const ccp_config_t *ccp_obj);
static void CCP_CAPTURE_MODE_TIMER_SELECT(const ccp_config_t *ccp_obj);


#if INTERRUPT_FEATURE_ENABLE == CCP1_INTERRUPT_FEATURE_ENABLE
    static void (*CCP1_IntrerruptHandler)(void) = NULL ;
#endif
    
#if INTERRUPT_FEATURE_ENABLE == CCP2_INTERRUPT_FEATURE_ENABLE
    static void (*CCP2_IntrerruptHandler)(void) = NULL ;
#endif    
    
void CCP1_ISR(void){
    CCP1_INTERRUPT_CLEAR_FLAG();
    
    if(CCP1_IntrerruptHandler){
        CCP1_IntrerruptHandler();
    }
} 

void CCP2_ISR(void){
    CCP2_INTERRUPT_CLEAR_FLAG();
    
    if(CCP2_IntrerruptHandler){
        CCP2_IntrerruptHandler();
    }
} 

Std_ReturnType CCP_Init(const ccp_config_t *ccp_obj){
    Std_ReturnType ret = E_NOT_OK ;
    if (NULL == ccp_obj){
        ret  = E_NOT_OK ;
    }
    else{
        
        if (CCP1_INST == ccp_obj->ccp_inst_select){
            CCP1_SELECT_MODE(CCP_MODULE_DISABLE_CFG);
        }
        else if(CCP2_INST == ccp_obj->ccp_inst_select){
            CCP2_SELECT_MODE(CCP_MODULE_DISABLE_CFG);
        }
        else{/*NOTHING*/}
               
        if(CCP_CAPTURE_MODE_SELECT == ccp_obj->ccp_mode_select){
            
            switch(ccp_obj->ccp_mode_behavior){
                case CCP_CAPTURE_MODE_EVERY_FALLING_EDGE_CFG:
                    CCP1_SELECT_MODE(CCP_CAPTURE_MODE_EVERY_FALLING_EDGE_CFG);
                    break;
                case CCP_CAPTURE_MODE_EVERY_RISING_EDGE_CFG:
                    CCP1_SELECT_MODE(CCP_CAPTURE_MODE_EVERY_RISING_EDGE_CFG);
                    break;
                case CCP_CAPTURE_MODE_EVERY_4th_FALLING_EDGE_CFG:
                    CCP1_SELECT_MODE(CCP_CAPTURE_MODE_EVERY_4th_FALLING_EDGE_CFG);
                    break;
                case CCP_CAPTURE_MODE_EVERY_16th_FALLING_EDGE_CFG:
                    CCP1_SELECT_MODE(CCP_CAPTURE_MODE_EVERY_16th_FALLING_EDGE_CFG);
                    break;
                default:
                    ret = E_NOT_OK ;
                    break;    
            }
                CCP_CAPTURE_MODE_TIMER_SELECT(ccp_obj);
                
                }

                
        else if(CCP_COMPARE_MODE_SELECT == ccp_obj->ccp_mode_select){
            switch(ccp_obj->ccp_mode_behavior){
                case CCP_COMPARE_MODE_TOGGLE_ON_MATCH_CFG:
                    CCP1_SELECT_MODE(CCP_COMPARE_MODE_TOGGLE_ON_MATCH_CFG);
                    break;
                case CCP_COMPARE_MODE_INIT_LOW_SET_HIGH_CFG:
                    CCP1_SELECT_MODE(CCP_COMPARE_MODE_INIT_LOW_SET_HIGH_CFG);
                    break;
                case CCP_COMPARE_MODE_INIT_HIGH_SET_LOW_CFG:
                    CCP1_SELECT_MODE(CCP_COMPARE_MODE_INIT_HIGH_SET_LOW_CFG);
                    break;
                case CCP_COMPARE_MODE_GENERATE_SW_INTERRUPT_CFG:
                    CCP1_SELECT_MODE(CCP_COMPARE_MODE_GENERATE_SW_INTERRUPT_CFG);
                    break;
                case CCP_COMPARE_MODE_TRIGGER_SPECIAL_EVENT_CFG:
                    CCP1_SELECT_MODE(CCP_COMPARE_MODE_TRIGGER_SPECIAL_EVENT_CFG);
                    break;    
                default:
                    ret = E_NOT_OK ;
                    break;    
            }
        }

#if (CCP1_CFG_MODE_SELECT == CCP_CFG_PWM_MODE_SELECTED) || (CCP2_CFG_MODE_SELECT == CCP_CFG_PWM_MODE_SELECTED)                
        else if (CCP_PWM_MODE_SELECT == ccp_obj->ccp_mode_select){
            CCP_PWM_MODE_CONFIG(ccp_obj);
        }
        else{/*NOTHING*/}
#endif
        
        else{/*NOTHING*/}
        ret = gpio_pin_intialize(&(ccp_obj->pin));
        CCP_INTERRUPT_CONFIG(ccp_obj);
        
        ret = E_OK;

            }


            
        
        
        
    
    return ret ;
}

Std_ReturnType CCP_DeInit(const ccp_config_t *ccp_obj){
    Std_ReturnType ret = E_NOT_OK ;
    if (NULL == ccp_obj){
        ret  = E_NOT_OK ;
    }
    else{
       
        if (CCP1_INST == ccp_obj->ccp_inst_select){
            CCP1_SELECT_MODE(CCP_MODULE_DISABLE_CFG);
            #if INTERRUPT_FEATURE_ENABLE == CCP1_INTERRUPT_FEATURE_ENABLE
                CCP1_INTERRUPT_DISABLE();
            #endif
        }
        else if(CCP2_INST == ccp_obj->ccp_inst_select){
            CCP2_SELECT_MODE(CCP_MODULE_DISABLE_CFG);
            #if INTERRUPT_FEATURE_ENABLE == CCP2_INTERRUPT_FEATURE_ENABLE
                CCP2_INTERRUPT_DISABLE();
            #endif
        }
        else{/*NOTHING*/}
        
        ret = E_OK;
    }
    
    return ret ;
}


#if (CCP1_CFG_MODE_SELECT == CCP_CFG_CAPTURE_MODE_SELECTED)    
Std_ReturnType CCP1_IsCapturedDataReady(uint8 *_capture_status){
    Std_ReturnType ret = E_NOT_OK ;
    if (NULL == _capture_status){
        ret  = E_NOT_OK ;
    }
    else{
        if(CCP_CAPTURE_READY == PIR1bits.CCP1IF){
            *_capture_status = CCP_CAPTURE_READY;
            CCP1_INTERRUPT_CLEAR_FLAG();
        }
        else{
            *_capture_status = CCP_CAPTURE_NOT_READY;
        }
        ret = E_OK;
    }
    
    return ret ;
}

Std_ReturnType CCP_Capture_Mode_Read_Value(uint16 *_capture_value){
    Std_ReturnType ret = E_NOT_OK ;
    CCP_REG_T capture_temp_value = {.ccpr_low=0 , .ccpr_high = 0};
    if (NULL == _capture_value){
        ret  = E_NOT_OK ;
    }
    else{
        capture_temp_value.ccpr_low = CCPR1L;
        capture_temp_value.ccpr_high= CCPR1H; 
        
        *_capture_value = capture_temp_value.ccpr_16Bit;
        ret = E_OK;
    }
    
    return ret ;
}   

#endif
    
#if (CCP1_CFG_MODE_SELECT == CCP_CFG_COMPARE_MODE_SELECTED)     
Std_ReturnType CCP_IsCompareDone(const ccp_config_t *ccp_obj , uint8 *_compare_status){
    
    Std_ReturnType ret = E_NOT_OK ;
    if (NULL == _compare_status){
        ret  = E_NOT_OK ;
    }
    else{
        
        if(CCP1_INST == ccp_obj->ccp_inst_select){

            if(CCP_COMPARE_READY == PIR1bits.CCP1IF){
                *_compare_status = CCP_COMPARE_READY;
                CCP1_INTERRUPT_CLEAR_FLAG();
            }
            else{
                *_compare_status = CCP_COMPARE_NOT_READY;
             }
        }
        else if(CCP2_INST == ccp_obj->ccp_inst_select){

            if(CCP_COMPARE_READY == PIR2bits.CCP2IF){
                *_compare_status = CCP_COMPARE_READY;
                CCP2_INTERRUPT_CLEAR_FLAG();
            }
            else{
                *_compare_status = CCP_COMPARE_NOT_READY;
             }
        }
        
        ret = E_OK;
    }
    
    return ret ;
}

Std_ReturnType CCP_Compare_Mode_Set_Value(const ccp_config_t *ccp_obj , uint16 compare_value){
    Std_ReturnType ret = E_NOT_OK ;
    CCP_REG_T capture_temp_value = {.ccpr_low=0 , .ccpr_high = 0};
    
    if (NULL == ccp_obj){
        ret = E_NOT_OK ;
    }
    else{
        capture_temp_value.ccpr_16Bit = compare_value;
    
        if(CCP1_INST == ccp_obj->ccp_inst_select){

                CCPR1L = capture_temp_value.ccpr_low ;
                CCPR1H = capture_temp_value.ccpr_high;
            }
        else if(CCP2_INST == ccp_obj->ccp_inst_select){

                CCPR2L = capture_temp_value.ccpr_low ;
                CCPR2H = capture_temp_value.ccpr_high;
        }
    }
   
    ret = E_OK;
    return ret ;
}

#endif

#if (CCP1_CFG_MODE_SELECT == CCP_CFG_PWM_MODE_SELECTED)    
Std_ReturnType CCP_PWM_Set_Duty(const ccp_config_t *ccp_obj , const uint8 _duty){
    Std_ReturnType ret = E_NOT_OK ;
    uint16 l_duty_temp = 0;
     if (NULL == ccp_obj){
        ret = E_NOT_OK;
    }
    else{
        l_duty_temp = (uint16)((PR2+1)*(_duty/100.0)* 4) ;
        if(CCP1_INST == (ccp_obj->ccp_inst_select)){
            CCP1CONbits.DC1B = (uint8)(l_duty_temp & 0x0003); 
            CCPR1L = (uint8)(l_duty_temp>>2);
        }
        else if(CCP2_INST == (ccp_obj->ccp_inst_select)){
            CCP2CONbits.DC2B = (uint8)(l_duty_temp & 0x0003); 
            CCPR2L = (uint8)(l_duty_temp>>2);
        }
        else{/*NOTHING*/}
    }
    
    ret = E_OK;
    return ret ;
}

Std_ReturnType CCP_PWM_Start(const ccp_config_t *ccp_obj){
    Std_ReturnType ret = E_NOT_OK ;
    if (NULL == ccp_obj){
        ret = E_NOT_OK;
    }
    else{
        if(CCP1_INST == (ccp_obj->ccp_inst_select)){
            CCP1_SELECT_MODE(CCP_PWM_MODE_CFG);
        }
        else if(CCP2_INST == (ccp_obj->ccp_inst_select)){
            CCP2_SELECT_MODE(CCP_PWM_MODE_CFG); 
        }
        else{/*NOTHING*/}
    }
    
    
    
    ret = E_OK;
    return ret ;
}

Std_ReturnType CCP_PWM_Stop(const ccp_config_t *ccp_obj){
    Std_ReturnType ret = E_NOT_OK ;
    if (NULL == ccp_obj){
        ret = E_NOT_OK;
    }
    else{
        if(CCP1_INST == (ccp_obj->ccp_inst_select)){
            CCP1_SELECT_MODE(CCP_MODULE_DISABLE_CFG);
        }
        else if(CCP2_INST == (ccp_obj->ccp_inst_select)){
            CCP2_SELECT_MODE(CCP_MODULE_DISABLE_CFG); 
        }
        else{/*NOTHING*/}
    }
    ret = E_OK;
    return ret ;
}

#endif


#if (CCP1_CFG_MODE_SELECT == CCP_CFG_PWM_MODE_SELECTED) || (CCP2_CFG_MODE_SELECT == CCP_CFG_PWM_MODE_SELECTED) 
static void CCP_PWM_MODE_CONFIG(const ccp_config_t *ccp_obj){
    if (CCP1_INST == ccp_obj->ccp_inst_select){
            if(ccp_obj->ccp_mode_behavior == CCP_PWM_MODE_CFG){
            CCP1_SELECT_MODE(CCP_PWM_MODE_CFG);
            }
            else{/*NOTHING*/}
            }
            else if (CCP2_INST == ccp_obj->ccp_inst_select){
                if(ccp_obj->ccp_mode_behavior == CCP_PWM_MODE_CFG){
                CCP2_SELECT_MODE(CCP_PWM_MODE_CFG);
                }
                else{/*NOTHING*/}
            }
            else{/*NOTHING*/}
            
            PR2 = (uint8)((_XTAL_FREQ /
                    (ccp_obj->PWM_frequency * 4.0 * ccp_obj->Timer2_Prescaler_Select * ccp_obj->Timer2_Postscale_Select ))-1);
        
}
#endif

static void CCP_INTERRUPT_CONFIG(const ccp_config_t *ccp_obj){
    if(CCP1_INST == ccp_obj->ccp_inst_select){
        #if INTERRUPT_FEATURE_ENABLE == CCP1_INTERRUPT_FEATURE_ENABLE
        CCP1_INTERRUPT_CLEAR_FLAG();
        CCP1_INTERRUPT_ENABLE();
        CCP1_IntrerruptHandler = ccp_obj->CCP1_IntrerruptHandler;
        #if INTERRUPT_FEATURE_ENABLE == INTERRUPT_PRIORITY_LEVELS_ENABLE
                INTERRUPT_InterruptPriorityEnable();
                if(INTERRUPT_HIGH_PRIORITY == ccp_obj->ccp1_priority){
                    INTERRUPT_GlobalInterruptHighEnable();
                    CCP1_INTERRUPT_HIGH_PRIORITY();
                }
                else if(INTERRUPT_LOW_PRIORITY == ccp_obj->ccp1_priority){
                    INTERRUPT_GlobalInterruptLowEnable();
                    CCP1_INTERRUPT_LOW_PRIORITY();
                }
                else{/*NOTHING*/}
        #else
                INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_PeripheralInterruptEnable();        
        #endif        
        #endif 
        }
    else if (CCP2_INST == ccp_obj->ccp_inst_select){
        #if INTERRUPT_FEATURE_ENABLE == CCP2_INTERRUPT_FEATURE_ENABLE
        CCP2_INTERRUPT_CLEAR_FLAG();
        CCP2_INTERRUPT_ENABLE();
        CCP2_IntrerruptHandler = ccp_obj->CCP2_IntrerruptHandler;
        #if INTERRUPT_FEATURE_ENABLE == INTERRUPT_PRIORITY_LEVELS_ENABLE
                INTERRUPT_InterruptPriorityEnable();
                if(INTERRUPT_HIGH_PRIORITY == ccp_obj->ccp2_priority){
                    INTERRUPT_GlobalInterruptHighEnable();
                    CCP2_INTERRUPT_HIGH_PRIORITY();
                }
                else if(INTERRUPT_LOW_PRIORITY == ccp_obj->ccp2_priority){
                    INTERRUPT_GlobalInterruptLowEnable();
                    CCP2_INTERRUPT_LOW_PRIORITY();
                }
                else{/*NOTHING*/}
        #else
                INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_PeripheralInterruptEnable();        
        #endif        
        #endif 
    }
}

static void CCP_CAPTURE_MODE_TIMER_SELECT(const ccp_config_t *ccp_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == ccp_obj){
        ret = E_NOT_OK;
    }
    else{
        if(CCP1_CCP2_TIMER1 == ccp_obj->ccp_capture_timer_select){
            T3CONbits.T3CCP1 = 0;
            T3CONbits.T3CCP2 = 0;
        }
        else if (CCP1_TIMER1_CCP2_TIMER3 == ccp_obj->ccp_capture_timer_select){
            T3CONbits.T3CCP1 = 1;
            T3CONbits.T3CCP2 = 0;
        }
        else if (CCP1_CCP2_TIMER3 == ccp_obj->ccp_capture_timer_select){
            T3CONbits.T3CCP1 = 1;
            T3CONbits.T3CCP2 = 1;
        }
        else{/*NOTHING*/}
    }
}
