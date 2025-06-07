/* 
 * File:   application.c
 * Author: abdalrahman.ahmed
 *
 * Created on January 27, 2025, 2:15 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include "application.h"

#define _XTAL_FREQ 4000000  // 4 MHz clock

//void CCP1_IntrerruptHandler_test(void){
//    
//}
//
//timer2_config_t timer2_obj = {
//    .TIMER2_InterruptHandler = NULL,
//    .Timer2_Prescaler_Select = TIMER2_PRESCALER_DIV_1_CFG , 
//    .Timer2_Postscale_Select = TIMER2_POSTSCALER_DIV_1_CFG ,
//    .Timer2_preloaded_value  = 0 , 
//};
//
//ccp_config_t ccp1_test = {
//  .CCP1_IntrerruptHandler   = NULL,
//  .ccp_inst_select          =CCP1_INST,
//  .ccp_mode_select          = CCP_PWM_MODE_SELECT,
////  .PWM_frequency            = 20000,
//  .pin.port                 = PORTC_INDEX,
//  .pin.pin                  = GPIO_PIN2,
//  .pin.direction            = GPIO_DIRECTION_OUTPUT,
//  .ccp_mode_behavior        = CCP_PWM_MODE_CFG,
// // .Timer2_Prescaler_Select  = CCP_TIMER2_PRESCALER_DIV_1_CFG,
// // .Timer2_Postscale_Select  = CCP_TIMER2_POSTSCALER_DIV_1_CFG,
//};
//
//ccp_config_t ccp2_test = {
//  .CCP1_IntrerruptHandler   = NULL,
//  .ccp_inst_select          =CCP2_INST,
//  .ccp_mode_select          = CCP_PWM_MODE_SELECT,
//  //.PWM_frequency            = 20000,
//  .pin.port                 = PORTC_INDEX,
//  .pin.pin                  = GPIO_PIN1,
//  .pin.direction            = GPIO_DIRECTION_OUTPUT,
//  .ccp_mode_behavior        = CCP_PWM_MODE_CFG,
//  //.Timer2_Prescaler_Select  = CCP_TIMER2_PRESCALER_DIV_1_CFG,
// // .Timer2_Postscale_Select  = CCP_TIMER2_POSTSCALER_DIV_1_CFG,
//};
volatile uint32 timer3_OverFlow = 0 ;
volatile uint16 cap_value=0;
volatile uint8 CCP1_second_capture = 0;
uint32 Total_period_MicroSecond = 0;
uint32 freq = 0;

void CCP1_IntrerruptHandler_test(void);
void Timer3_IntrerruptHandler_test(void);



ccp_config_t compare_obj ={
  .CCP1_IntrerruptHandler       = CCP1_IntrerruptHandler_test ,
  .ccp_inst_select              = CCP1_INST,
  .ccp_mode_select              = CCP_COMPARE_MODE_SELECT,
  .ccp_mode_behavior            = CCP_COMPARE_MODE_TOGGLE_ON_MATCH_CFG,
  .ccp_capture_timer_select     = CCP1_CCP2_TIMER3,
  .pin.port                   = PORTC_INDEX,
  .pin.pin                    = GPIO_PIN2,
  .pin.direction              = GPIO_DIRECTION_OUTPUT 
};

//ccp_config_t capture_obj = {
//    .CCP1_IntrerruptHandler = CCP1_IntrerruptHandler_test,
//    .ccp_capture_timer_select = CCP1_CCP2_TIMER3,
//    .ccp_inst_select          = CCP1_INST,
//    .ccp_mode_select          = CCP_CAPTURE_MODE_SELECT,
//    .ccp_mode_behavior        = CCP_CAPTURE_MODE_EVERY_RISING_EDGE_CFG,
//    .pin.port                 = PORTC_INDEX,
//    .pin.pin                  = GPIO_PIN2,
//    .pin.direction            = GPIO_DIRECTION_INPUT  
//};

timer3_config_t timer_obj  = {
    .TIMER3_InterruptHandler = NULL,
    .timer3_mode             = TIMER3_TIMER_MODE_CONFIG,
    .timer3_Prescaler_val    = TIMER3_PRESCALER_DIV_1_CFG,
    .timer3_preloaded_value  = 0,
    .timer3_read_write_mode  = TIMER3_READ_WRITE_16_BIT_MODE_CFG,
    
};





Std_ReturnType ret = E_NOT_OK;
int main() {
    
    application_initialize();
//    ret = Timer2_Init(&timer2_obj);
//    ret = CCP_Init(&ccp1_test);
//    ret = CCP_Init(&ccp2_test);
//    ret = CCP_PWM_Set_Duty(&ccp1_test ,50);
//    ret = CCP_PWM_Start(&ccp1_test);
//
//    
//    ret = CCP_PWM_Set_Duty(&ccp2_test ,70);
//    ret = CCP_PWM_Start(&ccp2_test);

//ret = CCP_Init(&capture_obj);
    

ret = Timer3_Init(&timer_obj);    
    
ret = CCP_Compare_Mode_Set_Value(&compare_obj , 50000);

ret = CCP_Init(&compare_obj);



    while(1){
       
//        if (CCP1_second_capture == 1){
//            
//           Total_period_MicroSecond = (timer3_OverFlow * 65536UL) + cap_value;
//           freq = (uint32)(1/(Total_period_MicroSecond / 1000000.0)); 
//           CCP1_second_capture = 0;
        //}
       
   }
    
    return (EXIT_SUCCESS);
    
     
}



void application_initialize(void){
    Std_ReturnType ret = E_OK;
    
    
}

//void CCP1_IntrerruptHandler_test(void){
//    static uint8 ccp1_flag = 0;
//    ccp1_flag++;
//    if (ccp1_flag == 1){
//        (void)Timer3_WriteVal(&timer_obj, 0);
//    }
//    else if (ccp1_flag == 2){
//        ccp1_flag = 0;
//        timer3_OverFlow = 0;
//            (void)CCP_Capture_Mode_Read_Value(&cap_value);
//        CCP1_second_capture = 1;
//    }
//}
//
//void Timer3_IntrerruptHandler_test(void){
//    timer3_OverFlow++;
//}

void CCP1_IntrerruptHandler_test(void){
    ret = Timer3_WriteVal(&timer_obj ,0 );
}

void Timer3_IntrerruptHandler_test(void){
    
}

       


