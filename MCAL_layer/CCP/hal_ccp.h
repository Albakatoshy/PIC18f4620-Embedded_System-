/* 
 * File:   hal_ccp1.h
 * Author: anaal
 *
 * Created on May 13, 2025, 8:16 AM
 */

#ifndef HAL_CCP1_H
#define	HAL_CCP1_H

/*Section : Includes */

#include "pic18f4620.h"
#include "../GPIO/hal_gpio.h"
#include "../GPIO/mcal_std_types.h"
#include "../Interrupt/mcal_internal_interrupt.h"
#include "hal_ccp_cfg.h"


/* Section : Macro Declarations */

#define CCP_MODULE_DISABLE_CFG                         ((uint8)0x00) 
#define CCP_CAPTURE_MODE_EVERY_FALLING_EDGE_CFG        ((uint8)0x04)
#define CCP_CAPTURE_MODE_EVERY_RISING_EDGE_CFG         ((uint8)0x05)
#define CCP_CAPTURE_MODE_EVERY_4th_FALLING_EDGE_CFG    ((uint8)0x06)
#define CCP_CAPTURE_MODE_EVERY_16th_FALLING_EDGE_CFG   ((uint8)0x07)
#define CCP_COMPARE_MODE_TOGGLE_ON_MATCH_CFG           ((uint8)0x02)    
#define CCP_COMPARE_MODE_INIT_LOW_SET_HIGH_CFG         ((uint8)0x08)          
#define CCP_COMPARE_MODE_INIT_HIGH_SET_LOW_CFG         ((uint8)0x09)         
#define CCP_COMPARE_MODE_GENERATE_SW_INTERRUPT_CFG     ((uint8)0x0A)
#define CCP_COMPARE_MODE_TRIGGER_SPECIAL_EVENT_CFG     ((uint8)0x0B)
#define CCP_PWM_MODE_CFG                               ((uint8)0x0C)

#define CCP_CAPTURE_NOT_READY                      0x00
#define CCP_CAPTURE_READY                          0x01

#define CCP_COMPARE_NOT_READY                      0x00
#define CCP_COMPARE_READY                          0x01

#define CCP_TIMER2_PRESCALER_DIV_1_CFG          1
#define CCP_TIMER2_PRESCALER_DIV_4_CFG          4
#define CCP_TIMER2_PRESCALER_DIV_16_CFG         16


#define CCP_TIMER2_POSTSCALER_DIV_1_CFG          1
#define CCP_TIMER2_POSTSCALER_DIV_2_CFG          2
#define CCP_TIMER2_POSTSCALER_DIV_3_CFG          3
#define CCP_TIMER2_POSTSCALER_DIV_4_CFG          4
#define CCP_TIMER2_POSTSCALER_DIV_5_CFG          5
#define CCP_TIMER2_POSTSCALER_DIV_6_CFG          6
#define CCP_TIMER2_POSTSCALER_DIV_7_CFG          7
#define CCP_TIMER2_POSTSCALER_DIV_8_CFG          8
#define CCP_TIMER2_POSTSCALER_DIV_9_CFG          9
#define CCP_TIMER2_POSTSCALER_DIV_10_CFG         10
#define CCP_TIMER2_POSTSCALER_DIV_11_CFG         11
#define CCP_TIMER2_POSTSCALER_DIV_12_CFG         12
#define CCP_TIMER2_POSTSCALER_DIV_13_CFG         13
#define CCP_TIMER2_POSTSCALER_DIV_14_CFG         14
#define CCP_TIMER2_POSTSCALER_DIV_15_CFG         15
#define CCP_TIMER2_POSTSCALER_DIV_16_CFG         16

/* Section : Macro Functions Declarations */


#define CCP1_SELECT_MODE(_CONFIG)           (CCP1CONbits.CCP1M = _CONFIG)
#define CCP2_SELECT_MODE(_CONFIG)           (CCP2CONbits.CCP2M = _CONFIG)

/* Section : Data Type Declarations */

typedef enum{
    CCP1_INST,
    CCP2_INST        
}ccp_inst_t;

typedef enum{
    CCP_CAPTURE_MODE_SELECT = 0,
    CCP_COMPARE_MODE_SELECT    ,   
    CCP_PWM_MODE_SELECT        ,
        
}ccp_mode_t;

typedef union{
    struct{
        uint8 ccpr_low;
        uint8 ccpr_high;
    };
    struct{
        uint16 ccpr_16Bit;
    };
}CCP_REG_T;

typedef enum{
    CCP1_CCP2_TIMER1 = 0    ,
    CCP1_TIMER1_CCP2_TIMER3 ,
    CCP1_CCP2_TIMER3        ,       
}ccp_capture_timer_select_t;

typedef struct{
#if INTERRUPT_FEATURE_ENABLE == CCP1_INTERRUPT_FEATURE_ENABLE
    void (*CCP1_IntrerruptHandler)(void);
#if INTERRUPT_FEATURE_ENABLE == INTERRUPT_PRIORITY_LEVELS_ENABLE
    interrupt_priority_cfg      ccp1_priority; 
#endif    
#endif
#if INTERRUPT_FEATURE_ENABLE == CCP2_INTERRUPT_FEATURE_ENABLE
    void (*CCP2_IntrerruptHandler)(void);
#if INTERRUPT_FEATURE_ENABLE == INTERRUPT_PRIORITY_LEVELS_ENABLE
    interrupt_priority_cfg      ccp2_priority; 
#endif    
#endif    
    ccp_inst_t                 ccp_inst_select;
    ccp_mode_t                 ccp_mode_select;
    uint8                      ccp_mode_behavior;
    pin_config_t               pin;
    ccp_capture_timer_select_t ccp_capture_timer_select;
#if (CCP1_CFG_MODE_SELECT == CCP_CFG_PWM_MODE_SELECTED) || (CCP2_CFG_MODE_SELECT == CCP_CFG_PWM_MODE_SELECTED)    
    uint32              PWM_frequency;
    uint8 Timer2_Postscale_Select       :4;
    uint8 Timer2_Prescaler_Select       :2; 
#endif

    
    
}ccp_config_t;

/* Section : Function Declarations */

Std_ReturnType CCP_Init(const ccp_config_t *ccp_obj);
Std_ReturnType CCP_DeInit(const ccp_config_t *ccp_obj);

#if (CCP_CFG_MODE_SELECT == CCP_CFG_CAPTURE_MODE_SELECTED)    
Std_ReturnType CCP_IsCapturedDataReady(uint8 *_capture_status);
Std_ReturnType CCP_Capture_Mode_Read_Value(uint16 *_capture_value);    
#endif
    
#if (CCP1_CFG_MODE_SELECT == CCP_CFG_COMPARE_MODE_SELECTED)    
Std_ReturnType CCP_IsCompareDone(const ccp_config_t *ccp_obj ,uint8 *_compare_status);
Std_ReturnType CCP_Compare_Mode_Set_Value(const ccp_config_t *ccp_obj , uint16 compare_value);
#endif

#if (CCP1_CFG_MODE_SELECT == CCP_CFG_PWM_MODE_SELECTED)    
Std_ReturnType CCP_PWM_Set_Duty(const ccp_config_t *ccp_obj , const uint8 _duty);
Std_ReturnType CCP_PWM_Start(const ccp_config_t *ccp_obj);
Std_ReturnType CCP_PWM_Stop(const ccp_config_t *ccp_obj);
#endif    



#endif	/* HAL_CCP1_H */

