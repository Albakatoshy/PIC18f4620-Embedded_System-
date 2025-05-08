/* 
 * File:   hal_adc.c
 * Author: Abdalrahman
 *
 * Created on April 22, 2025, 12:51 PM
 */


#include "hal_adc.h"


#if ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
static InterruptHandler ADC_InterruptHandler = NULL;
#endif

static inline void adc_input_channel_port_configure( adc_channel_select_t channel);
static inline void adc_select_result_format(const adc_configuration_t *_adc);
static inline void adc_select_voltage_reference(const adc_configuration_t *_adc);


void ADC_ISR(void){
    ADC_INTERRUPT_CLEAR_FLAG();
    
    if (ADC_InterruptHandler){
        ADC_InterruptHandler();
    }
}

Std_ReturnType ADC_Init(const adc_configuration_t *_adc){
    Std_ReturnType ret = E_NOT_OK;
    if(_adc==NULL){
        ret= E_NOT_OK;
    }
    else{
        /*Disable ADC*/
        ADC_CONVERTER_DISABLE();
        
        /*Configure the acquisition_time*/
        ADCON2bits.ACQT = _adc->acquisition_time;
        
        /*Configure the conversion_clock*/
        ADCON2bits.ADCS = _adc->conversion_clock;
        
        /*Configure the default channel*/
        ADCON0bits.CHS = _adc->adc_channel;
        adc_input_channel_port_configure(_adc->adc_channel);
        /*Configure the interrupt*/
#if ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE     
        ADC_INTERRUPT_ENABLE();
        
        ADC_INTERRUPT_CLEAR_FLAG();
    #if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
            if(INTERRUPT_HIGH_PRIORITY == (_adc->adc_priority)){
                INTERRUPT_GlobalInterruptHighEnable();
                ADC_INTERRUPT_HIGH_PRIORITY_ENABLE();
            }
            else if(INTERRUPT_LOW_PRIORITY == (_adc->adc_priority)){
                INTERRUPT_GlobalInterruptLowEnable();
                ADC_INTERRUPT_LOW_PRIORITY_ENABLE();
            }
            else{/*NOTHING*/}
    #else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();

    #endif        
        ADC_InterruptHandler = _adc->ADC_InterruptHandler;
  
#endif 
        
        
        /*adc_select_result_format*/
        adc_select_result_format(_adc);
        
        /*adc_select_voltage_reference*/
        adc_select_voltage_reference(_adc);
        
        ADC_CONVERTER_ENABLE();
        
        ret = E_OK;
        
    }
    return      ret;
}


Std_ReturnType ADC_DeInit(const adc_configuration_t *_adc){
    Std_ReturnType ret = E_NOT_OK;
    if(_adc==NULL){
        ret= E_NOT_OK;
    }
    else{
        #if ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE     
        ADC_INTERRUPT_DISABLE();    
        #endif
        
        ADC_CONVERTER_DISABLE();
        
    }
    return      ret;
}


Std_ReturnType ADC_SelectChannel(const adc_configuration_t *_adc , adc_channel_select_t channel ){
    Std_ReturnType ret = E_NOT_OK;
    if(_adc==NULL){
        ret= E_NOT_OK;
    }
    else{
        
         /*Configure the default channel*/
        ADCON0bits.CHS =channel;   
        adc_input_channel_port_configure(channel);
        
        ret = E_OK;
    }
    return      ret;
}


Std_ReturnType ADC_StartConversion(const adc_configuration_t *_adc){
    Std_ReturnType ret = E_NOT_OK;
    if(_adc==NULL){
        ret= E_NOT_OK;
    }
    else{
       
        ADC_START_CONVERSION();
        ret = E_OK;
    }
    return      ret;
}

/**
 * 
 * @param _adc
 * @param conversion_status
 * true if conversion is done
 * false if it is not completed
 * @return 
 */
Std_ReturnType ADC_IsConversionDone(const adc_configuration_t *_adc , uint8 *conversion_status){
    Std_ReturnType ret = E_NOT_OK;
    if(_adc==NULL || NULL == conversion_status ){
        ret= E_NOT_OK;
    }
    else{
        
        *conversion_status = (uint8)(!(ADCON0bits.GODONE));
        
        ret = E_OK;
    }
    return      ret;
}


Std_ReturnType ADC_GetConversionResult(const adc_configuration_t *_adc , adc_result_t *conversion_result){
    Std_ReturnType ret = E_NOT_OK;
    if((_adc==NULL )|| (NULL == conversion_result)){
        ret= E_NOT_OK;
    }
    else{
        
        if (_adc->result_format == ADC_RESULT_FORMAT_RIGHT){
            *conversion_result = (adc_result_t)((ADRESH<<8) + ADRESL);
        }

        else if(_adc->result_format == ADC_RESULT_FORMAT_LEFT){
            *conversion_result = (adc_result_t)(((ADRESH<<8) + ADRESL)>>6);
        }
        else{
            *conversion_result = (adc_result_t)((ADRESH<<8) + ADRESL);
        }
        
        ret = E_OK;
    }
    return      ret;
    
}

Std_ReturnType ADC_GetConversion_Blocking(const adc_configuration_t *_adc , adc_channel_select_t channel 
                                                                 , adc_result_t *conversion_result){
    Std_ReturnType ret = E_NOT_OK;
    
    if((_adc==NULL ) || (NULL == conversion_result) ){
        ret= E_NOT_OK;
    }
    else{
        /*select the  ADC channel */
        ret = ADC_SelectChannel(_adc,channel);
        
        /*start the conversion*/
        ret = ADC_StartConversion(_adc);
        
        /*Check the end of conversion*/        
        while(ADCON0bits.GO_nDONE);
        ret = ADC_GetConversionResult(_adc , conversion_result);
        
        
        ret = E_OK;
    }
    return      ret;
}

static inline void adc_input_channel_port_configure( adc_channel_select_t channel){
        switch(channel){
            case ADC_CHANNEL_AN0  : SET_BIT(TRISA , _TRISA_RA0_POSITION ); break ;
            case ADC_CHANNEL_AN1  : SET_BIT(TRISA , _TRISA_RA1_POSITION ); break ;
            case ADC_CHANNEL_AN2  : SET_BIT(TRISA , _TRISA_RA2_POSITION ); break ;
            case ADC_CHANNEL_AN3  : SET_BIT(TRISA , _TRISA_RA3_POSITION ); break ;
            case ADC_CHANNEL_AN4  : SET_BIT(TRISA , _TRISA_RA5_POSITION ); break ;
            case ADC_CHANNEL_AN5  : SET_BIT(TRISE , _TRISE_RE0_POSITION ); break ;
            case ADC_CHANNEL_AN6  : SET_BIT(TRISE , _TRISE_RE1_POSITION ); break ;
            case ADC_CHANNEL_AN7  : SET_BIT(TRISE , _TRISE_RE2_POSITION ); break ;
            case ADC_CHANNEL_AN8  : SET_BIT(TRISB , _TRISB_RB2_POSITION ); break ;
            case ADC_CHANNEL_AN9  : SET_BIT(TRISB , _TRISB_RB3_POSITION ); break ;
            case ADC_CHANNEL_AN10 : SET_BIT(TRISB , _TRISB_RB1_POSITION ); break ;
            case ADC_CHANNEL_AN11 : SET_BIT(TRISB , _TRISB_RB4_POSITION ); break ;
            case ADC_CHANNEL_AN12 : SET_BIT(TRISB , _TRISB_RB0_POSITION ); break ;

        }
        
}

static inline void adc_select_result_format(const adc_configuration_t *_adc){
    if (_adc->result_format == ADC_RESULT_FORMAT_RIGHT){
        ADC_RESULT_FORMAT_RIGHT_JUSTIFIED();
    }
    
    else if(_adc->result_format == ADC_RESULT_FORMAT_LEFT){
        ADC_RESULT_FORMAT_LEFT_JUSTIFIED();
    }
    else{
        ADC_RESULT_FORMAT_RIGHT_JUSTIFIED();
    }
}

static inline void adc_select_voltage_reference(const adc_configuration_t *_adc){
    if (_adc->voltage_reference == ADC_VOLTAGE_REFERENCE_ENABLE){
        ADC_ENABLE_VOLTAGE_REFERENCE();
    }
    else if(_adc->voltage_reference == ADC_VOLTAGE_REFERENCE_DISABLE){
        ADC_DISABLE_VOLTAGE_REFERENCE();
    }
    else{
        ADC_DISABLE_VOLTAGE_REFERENCE();
    }
    
}

Std_ReturnType ADC_StartConversion_Interrupt(const adc_configuration_t *_adc , adc_channel_select_t channel){
    
    Std_ReturnType ret = E_NOT_OK;
    
    if((_adc==NULL )){
        ret= E_NOT_OK;
    }
    else{
        /*select the  ADC channel */
        ret = ADC_SelectChannel(_adc,channel);
        
        /*start the conversion*/
        ret = ADC_StartConversion(_adc); 
        
        ret = E_OK;
    }
    return      ret;
    
}