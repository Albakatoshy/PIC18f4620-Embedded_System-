/* 
 * File:   mcal_external_interrupt.c
 * Author: Abdalrahman
 *
 * Created on April 13, 2025, 4:14 PM
 */


#include "mcal_external_interrupt.h"


static void (*INT0_InterruptHandler)(void) = NULL;
static void (*INT1_InterruptHandler)(void) = NULL;
static void (*INT2_InterruptHandler)(void) = NULL;

static void (*RB4_InterruptHandler_HIGH)(void) = NULL;
static void (*RB4_InterruptHandler_LOW)(void) = NULL;
static void (*RB5_InterruptHandler_HIGH)(void) = NULL;
static void (*RB5_InterruptHandler_LOW)(void) = NULL;
static void (*RB6_InterruptHandler_HIGH)(void) = NULL;
static void (*RB6_InterruptHandler_LOW)(void) = NULL;
static void (*RB7_InterruptHandler_HIGH)(void) = NULL;
static void (*RB7_InterruptHandler_LOW)(void) = NULL;


static Std_ReturnType Interrupt_INTx_Enable(const interrupt_INTx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Disable(const interrupt_INTx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Priority_Init(const interrupt_INTx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Edge_Init(const interrupt_INTx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Pin_Init(const interrupt_INTx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Clear_Flag(const interrupt_INTx_t *int_obj);

static Std_ReturnType INT0_SetInterruptHandler(void (*InterruptHandler)(void));
static Std_ReturnType INT1_SetInterruptHandler(void (*InterruptHandler)(void));
static Std_ReturnType INT2_SetInterruptHandler(void (*InterruptHandler)(void));
static Std_ReturnType Interrupt_INTx_SetInterruptHandler(const interrupt_INTx_t *int_obj);

static Std_ReturnType Interrupt_RBx_Enable(const interrupt_RBx_t *int_obj);
static Std_ReturnType Interrupt_RBx_Disable(const interrupt_RBx_t *int_obj);
static Std_ReturnType Interrupt_RBx_Priority_Init(const interrupt_RBx_t *int_obj);
static Std_ReturnType Interrupt_RBx_Pin_Init(const interrupt_RBx_t *int_obj);



void INT0_ISR(void){
    /*CLEAR THE FLAG*/
    EXTERNAL_INTERRUPT_INT0_ClearInterruptFlag();
    /*code*/
    
    /*call back function gets called every time this function executed */
    
    if(INT0_InterruptHandler){
        INT0_InterruptHandler();
    }
    else{/*NOTHING*/}
}

void INT1_ISR(void){
    /*CLEAR THE FLAG*/
    EXTERNAL_INTERRUPT_INT1_ClearInterruptFlag();
    /*code*/
    
    /*call back function gets called every time this function executed */
    
    if(INT1_InterruptHandler){
        INT1_InterruptHandler();
    }
    else{/*NOTHING*/}
}

void INT2_ISR(void){
    /*CLEAR THE FLAG*/
    EXTERNAL_INTERRUPT_INT2_ClearInterruptFlag();
    /*code*/
    
    /*call back function gets called every time this function executed */
    
    if(INT2_InterruptHandler){
        INT2_InterruptHandler();
    }
    else{/*NOTHING*/}   
}

void RB4_ISR(uint8 RB4_Source){
    EXTERNAL_INTERRUPT_RBx_ClearInterruptFlag();
    
    if(RB4_Source == 0){
        if(RB4_InterruptHandler_HIGH){
        RB4_InterruptHandler_HIGH();
        }
    }
    else if (RB4_Source == 1 ){
        if(RB4_InterruptHandler_LOW){
        RB4_InterruptHandler_LOW();
        }
    }
    else{/*NOTHING*/} 
}
void RB5_ISR(uint8 RB5_Source){
    EXTERNAL_INTERRUPT_RBx_ClearInterruptFlag();
    
    if(RB5_Source == 0){
        if(RB5_InterruptHandler_HIGH){
        RB5_InterruptHandler_HIGH();
        }
    }
    else if (RB5_Source==1 ){
        if(RB5_InterruptHandler_LOW){
        RB5_InterruptHandler_LOW();
        }
    }
    else{/*NOTHING*/} 
}
void RB6_ISR(uint8 RB6_Source){
    EXTERNAL_INTERRUPT_RBx_ClearInterruptFlag();
    if(RB6_Source == 0){
        if(RB6_InterruptHandler_HIGH){
        RB6_InterruptHandler_HIGH();
        }
    }
    else if (RB6_Source==1 ){
        if(RB6_InterruptHandler_LOW){
        RB6_InterruptHandler_LOW();
        }
    }
    else{/*NOTHING*/} 
}
void RB7_ISR(uint8 RB7_Source){
    EXTERNAL_INTERRUPT_RBx_ClearInterruptFlag();
    if(RB7_Source == 0){
        if(RB7_InterruptHandler_HIGH){
        RB7_InterruptHandler_HIGH();
        }
    }
    else if (RB7_Source==1 ){
        if(RB7_InterruptHandler_LOW){
        RB7_InterruptHandler_LOW();
        }
    }
    else{/*NOTHING*/}  
}


Std_ReturnType Interrupt_INTx_Init(const interrupt_INTx_t *int_obj){
    Std_ReturnType ret = E_OK;
    if (NULL == int_obj){
        ret = E_NOT_OK ;
    }
    else{
        /*Disable the External interrupt*/
        ret = Interrupt_INTx_Disable((int_obj));
        
        ret = Interrupt_INTx_Clear_Flag(int_obj);
        ret = Interrupt_INTx_Edge_Init((int_obj));
        #if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
        ret = Interrupt_INTx_Priority_Init(int_obj);
        #endif
        ret = Interrupt_INTx_Pin_Init(int_obj);
        
        /*configure default interrupt call back*/
        ret = Interrupt_INTx_SetInterruptHandler(int_obj);
        /*enable the External interrupt*/
        ret = Interrupt_INTx_Enable(int_obj);
    }
    
    return ret ;
}
Std_ReturnType Interrupt_INTx_DeInit(const interrupt_INTx_t *int_obj){
    Std_ReturnType ret = E_OK;
    if (NULL == int_obj){
        ret = E_NOT_OK ;
    }
    else{
        ret = Interrupt_INTx_Disable((int_obj));
    }
    
    return ret ;
}

Std_ReturnType Interrupt_RBx_Init(const interrupt_RBx_t *int_obj){
    Std_ReturnType ret = E_OK;
    if (NULL == int_obj){
        ret = E_NOT_OK ;
    }
    else{
        EXTERNAL_INTERRUPT_RBx_InterruptDisable();
        EXTERNAL_INTERRUPT_RBx_ClearInterruptFlag();
        #if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE 
        INTERRUPT_InterruptPriorityEnable();
        if (INTERRUPT_LOW_PRIORITY == int_obj->priority){
            INTERRUPT_GlobalInterruptLowEnable();
            EXTERNAL_INTERRUPT_RBx_InterruptLowPriority();
        }
        else if(INTERRUPT_HIGH_PRIORITY == int_obj->priority){
            INTERRUPT_GlobalInterruptHighEnable();
            EXTERNAL_INTERRUPT_RBx_InterruptHighPriority();
        } 
        else{/*NOTHING*/}
        #else
        INTERRUPT_PeripheralInterruptEnable();
        INTERRUPT_GlobalInterruptEnable();
        #endif

        ret = gpio_pin_direction_intialize(&(int_obj->mcu_pin));
        
        switch(int_obj->mcu_pin.pin){
            case GPIO_PIN4 :
                RB4_InterruptHandler_HIGH = int_obj->EXT_InterruprHandler_HIGH;
                RB4_InterruptHandler_LOW  = int_obj->EXT_InterruprHandler_LOW;
                break;
            case GPIO_PIN5 :
                RB5_InterruptHandler_HIGH = int_obj->EXT_InterruprHandler_HIGH;
                RB5_InterruptHandler_LOW  = int_obj->EXT_InterruprHandler_LOW;
                break;
            case GPIO_PIN6 :
                RB6_InterruptHandler_HIGH = int_obj->EXT_InterruprHandler_HIGH;
                RB6_InterruptHandler_LOW  = int_obj->EXT_InterruprHandler_LOW;
                break;    
            case GPIO_PIN7 :
                RB7_InterruptHandler_HIGH = int_obj->EXT_InterruprHandler_HIGH;
                RB7_InterruptHandler_LOW  = int_obj->EXT_InterruprHandler_LOW;
                break;    
        }
        
        
        
        EXTERNAL_INTERRUPT_RBx_InterruptEnable();
    }
    
    return ret ;
}
Std_ReturnType Interrupt_RBx_DeInit(const interrupt_RBx_t *int_obj){
    Std_ReturnType ret = E_OK;
    if (NULL == int_obj){
        ret = E_NOT_OK ;
    }
    else{
        
    }
    
    return ret ;
}


static Std_ReturnType Interrupt_INTx_Enable(const interrupt_INTx_t *int_obj){
    Std_ReturnType ret = E_OK;
    if (NULL == int_obj){
        ret = E_NOT_OK ;
    }
    else{
        switch(int_obj->source){
            case INTERRUPT_EXTERNAL_INT0 :
                #if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
                INTERRUPT_GlobalInterruptHighEnable();
                #else
                INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_PeripheralInterruptEnable();
                #endif
                EXTERNAL_INTERRUPT_INT0_InterruptEnable();
                break;
            case INTERRUPT_EXTERNAL_INT1:
                #if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
                INTERRUPT_InterruptPriorityEnable();     
                if (INTERRUPT_LOW_PRIORITY == (int_obj->priority) ){
                    INTERRUPT_GlobalInterruptLowEnable();
                }
                else if (INTERRUPT_HIGH_PRIORITY == (int_obj->priority)){
                    INTERRUPT_GlobalInterruptHighEnable();
                }
                else{
                    /*NOTHING*/
                }
                #else
                INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_PeripheralInterruptEnable();
                #endif
                EXTERNAL_INTERRUPT_INT1_InterruptEnable();
                break;
            case INTERRUPT_EXTERNAL_INT2:
                #if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
                INTERRUPT_InterruptPriorityEnable();
                if (INTERRUPT_LOW_PRIORITY == (int_obj->priority) ){
                    INTERRUPT_GlobalInterruptLowEnable();
                }
                else if (INTERRUPT_HIGH_PRIORITY == (int_obj->priority)){
                    INTERRUPT_GlobalInterruptHighEnable();
                }
                else{
                    /*NOTHING*/
                }
                #else
                INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_PeripheralInterruptEnable();
                #endif
                EXTERNAL_INTERRUPT_INT2_InterruptEnable();
                break;
            default : ret = E_NOT_OK ;    
                
                
        }
    }
    
    return ret ;
}

static Std_ReturnType Interrupt_INTx_Disable(const interrupt_INTx_t *int_obj){
    Std_ReturnType ret = E_OK;
    if (NULL == int_obj){
        ret = E_NOT_OK ;
    }
    else{
        switch(int_obj->source){
            case INTERRUPT_EXTERNAL_INT0 :
                EXTERNAL_INTERRUPT_INT0_InterruptDisable();
                break;
            case INTERRUPT_EXTERNAL_INT1:
                EXTERNAL_INTERRUPT_INT1_InterruptDisable();
                break;
            case INTERRUPT_EXTERNAL_INT2:
                EXTERNAL_INTERRUPT_INT2_InterruptDisable();
                break;
            default : ret = E_NOT_OK ;
    }
    
   
    }
    return ret ;
}
    


#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE  
static Std_ReturnType Interrupt_INTx_Priority_Init(const interrupt_INTx_t *int_obj){
    Std_ReturnType ret = E_OK;
    if (NULL == int_obj){
        ret = E_NOT_OK ;
    }
    else{
        switch(int_obj->source){
            
            case INTERRUPT_EXTERNAL_INT1:
                if (INTERRUPT_LOW_PRIORITY == (int_obj->priority) ){
                    EXTERNAL_INTERRUPT_INT1_InterruptLowPriority();
                }
                else if (INTERRUPT_HIGH_PRIORITY == (int_obj->priority)){
                    EXTERNAL_INTERRUPT_INT1_InterruptHighPriority();
                }
                else{
                    /*NOTHING*/
                }
                break;
            case INTERRUPT_EXTERNAL_INT2:
                if (INTERRUPT_LOW_PRIORITY == (int_obj->priority) ){
                    EXTERNAL_INTERRUPT_INT2_InterruptLowPriority();
                }
                else if (INTERRUPT_HIGH_PRIORITY == (int_obj->priority)){
                    EXTERNAL_INTERRUPT_INT2_InterruptHighPriority();
                }
                else{
                    /*NOTHING*/
                }
                break;
            default : ret = E_NOT_OK ;
    }
    }
    
    return ret ;
}

#endif

static Std_ReturnType Interrupt_INTx_Edge_Init(const interrupt_INTx_t *int_obj){
    Std_ReturnType ret = E_OK;
    if (NULL == int_obj){
        ret = E_NOT_OK ;
    }
    else{
        switch(int_obj->source){
        
            case INTERRUPT_EXTERNAL_INT0 :
                if(INTERRUPT_FALLING_EDGE == (int_obj->edge)) {
                    EXTERNAL_INTERRUPT_INT0_FallingEdgeSelect();
                }
                else if (INTERRUPT_RISING_EDGE == (int_obj->edge)){
                    EXTERNAL_INTERRUPT_INT0_RisingEdgeSelect();
                }
                else{
                    /*NOTHING*/
                }
                    break;
                case INTERRUPT_EXTERNAL_INT1:
                    if(INTERRUPT_FALLING_EDGE == (int_obj->edge)) {
                    EXTERNAL_INTERRUPT_INT1_FallingEdgeSelect();
                }
                else if (INTERRUPT_RISING_EDGE == (int_obj->edge)){
                    EXTERNAL_INTERRUPT_INT1_RisingEdgeSelect();
                }
                else{
                    /*NOTHING*/
                }    
                    break;
                case INTERRUPT_EXTERNAL_INT2:
                    if(INTERRUPT_FALLING_EDGE == (int_obj->edge)) {
                    EXTERNAL_INTERRUPT_INT2_FallingEdgeSelect();
                }
                else if (INTERRUPT_RISING_EDGE == (int_obj->edge)){
                    EXTERNAL_INTERRUPT_INT2_RisingEdgeSelect();
                }
                else{
                    /*NOTHING*/
                }
                    break;
                default : ret = E_NOT_OK ;
        }
    }
    return ret ;
}
    
    

static Std_ReturnType Interrupt_INTx_Pin_Init(const interrupt_INTx_t *int_obj){
    Std_ReturnType ret = E_OK;
    if (NULL == int_obj){
        ret = E_NOT_OK ;
    }
    else{
        ret = gpio_pin_direction_intialize(&(int_obj->mcu_pin));
    }
    
    return ret ;
}

static Std_ReturnType Interrupt_INTx_Clear_Flag(const interrupt_INTx_t *int_obj){
    Std_ReturnType ret = E_OK;
    if (NULL == int_obj){
        ret = E_NOT_OK ;
    }
    else{
        switch(int_obj->source){
            case INTERRUPT_EXTERNAL_INT0 :
                EXTERNAL_INTERRUPT_INT0_ClearInterruptFlag();
                break;
            case INTERRUPT_EXTERNAL_INT1:
                EXTERNAL_INTERRUPT_INT1_ClearInterruptFlag();
                break;
            case INTERRUPT_EXTERNAL_INT2:
                EXTERNAL_INTERRUPT_INT2_ClearInterruptFlag();
                break;
            default : ret = E_NOT_OK ;
    }
    
   
    }
    return ret ;
}

static Std_ReturnType INT0_SetInterruptHandler(void (*InterruptHandler)(void)){
    Std_ReturnType ret = E_OK ;
    if (NULL == InterruptHandler){
        ret = E_NOT_OK ;
    }
    else{
        INT0_InterruptHandler = InterruptHandler ; 
    }
    
    return ret ;
}
static Std_ReturnType INT1_SetInterruptHandler(void (*InterruptHandler)(void)){
    Std_ReturnType ret = E_OK ;
    if (NULL == InterruptHandler){
        ret = E_NOT_OK ;
    }
    else{
        INT1_InterruptHandler = InterruptHandler ; 
    }
    
    return ret ;
}
static Std_ReturnType INT2_SetInterruptHandler(void (*InterruptHandler)(void)){
    Std_ReturnType ret = E_OK ;
    if (NULL == InterruptHandler){
        ret = E_NOT_OK ;
    }
    else{
        INT2_InterruptHandler = InterruptHandler ; 
    }
    
    return ret ;
}
static Std_ReturnType Interrupt_INTx_SetInterruptHandler(const interrupt_INTx_t *int_obj){
     Std_ReturnType ret = E_OK;
    if (NULL == int_obj){
        ret = E_NOT_OK ;
    }
    else{
        switch(int_obj->source){
            case INTERRUPT_EXTERNAL_INT0 :
                ret = INT0_SetInterruptHandler(int_obj->EXT_InterruprHandler);
                break;
            case INTERRUPT_EXTERNAL_INT1:
                ret = INT1_SetInterruptHandler(int_obj->EXT_InterruprHandler);
                break;
            case INTERRUPT_EXTERNAL_INT2:
                ret = INT2_SetInterruptHandler(int_obj->EXT_InterruprHandler);
                break;
            default : ret = E_NOT_OK ;
    }
    
   
    }
    return ret ;
}

