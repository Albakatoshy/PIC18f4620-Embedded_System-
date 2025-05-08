/* 
 * File:   hal_adc.h
 * Author: Abdalrahman
 *
 * Created on April 22, 2025, 12:51 PM
 */

#ifndef HAL_ADC_H
#define	HAL_ADC_H



/*Section : Includes */
#include <xc.h>
#include "hal_adc_cfg.h"
#include <pic18f4620.h>
#include "../GPIO/mcal_std_types.h"
#include "../Interrupt/mcal_internal_interrupt.h"
#include "../GPIO/hal_gpio.h"
/* Section : Macro Declarations */

#define ADC_AN0_ANALOG_FUNCTIONALITY        0x0E
#define ADC_AN1_ANALOG_FUNCTIONALITY        0x0D
#define ADC_AN2_ANALOG_FUNCTIONALITY        0x0C
#define ADC_AN3_ANALOG_FUNCTIONALITY        0x0B
#define ADC_AN4_ANALOG_FUNCTIONALITY        0x0A
#define ADC_AN5_ANALOG_FUNCTIONALITY        0x09
#define ADC_AN6_ANALOG_FUNCTIONALITY        0x08
#define ADC_AN7_ANALOG_FUNCTIONALITY        0x07
#define ADC_AN8_ANALOG_FUNCTIONALITY        0x06
#define ADC_AN9_ANALOG_FUNCTIONALITY        0x05
#define ADC_AN10_ANALOG_FUNCTIONALITY       0x04
#define ADC_AN11_ANALOG_FUNCTIONALITY       0x03
#define ADC_AN12_ANALOG_FUNCTIONALITY       0x02
#define ADC_ALL_ANALOG_FUNCTIONALITY        0x00
#define ADC_ALL_DIGITAL_FUNCTIONALITY       0x0F


#define ADC_RESULT_FORMAT_RIGHT             0x01U
#define ADC_RESULT_FORMAT_LEFT              0x00U

#define ADC_VOLTAGE_REFERENCE_ENABLE        0x01U
#define ADC_VOLTAGE_REFERENCE_DISABLE       0x00U

#define ADC_CONVERSION_COMPLETED            0x01U
#define ADC_CONVERSION_IN_PROGRESS          0x00U

/* Section : Macro Functions Declarations */

/*  GO/DONE
 : A/D Conversion Status bit( 1 = A/D conversion in progress )(0 = A/D Idle) */
#define ADC_CONVERSION_STATUS()     (ADCON0bits.GO_nDONE)

#define ADC_START_CONVERSION()      (ADCON0bits.GO_nDONE=1)

/*ADON: A/D On bit
 1 = A/D Converter module is enabled 
 0 = A/D Converter module is disabled */
#define ADC_CONVERTER_ENABLE()     (ADCON0bits.ADON=1) 
#define ADC_CONVERTER_DISABLE()    (ADCON0bits.ADON=0)


/*
 ADC_ENABLE_VOLTAGE_REFERENCE()     Voltage ref is VREF+ VREF-
 ADC_DISABLE_VOLTAGE_REFERENCE()    Voltage ref is VSS VDD    
 */
#define ADC_ENABLE_VOLTAGE_REFERENCE() do{ADCON1bits.VCFG0 = 1;\
                                          ADCON1bits.VCFG1 = 1;\
                                          }while(0)
#define ADC_DISABLE_VOLTAGE_REFERENCE() do{ADCON1bits.VCFG0 = 0;\
                                           ADCON1bits.VCFG1 = 0;\
                                          }while(0)

#define ADC_ANALOG_DIGITAL_PORT_CONFIG(_CONFIG) (ADCON1bits.PCFG=_CONFIG) 

#define ADC_RESULT_FORMAT_RIGHT_JUSTIFIED()       (ADCON2bits.ADFM=1)
#define ADC_RESULT_FORMAT_LEFT_JUSTIFIED()        (ADCON2bits.ADFM=0)


/* Section : Data Type Declarations */

typedef void (*InterruptHandler)(void);

typedef enum {
    ADC_CHANNEL_AN0 = 0 ,
    ADC_CHANNEL_AN1,
    ADC_CHANNEL_AN2,
    ADC_CHANNEL_AN3,        
    ADC_CHANNEL_AN4,        
    ADC_CHANNEL_AN5,        
    ADC_CHANNEL_AN6,        
    ADC_CHANNEL_AN7,        
    ADC_CHANNEL_AN8,        
    ADC_CHANNEL_AN9,        
    ADC_CHANNEL_AN10,        
    ADC_CHANNEL_AN11,
    ADC_CHANNEL_AN12       
}adc_channel_select_t;

typedef enum{
    ADC_0_TAD = 0 ,
    ADC_2_TAD  ,        
    ADC_4_TAD  ,        
    ADC_6_TAD  ,        
    ADC_8_TAD  ,        
    ADC_12_TAD ,        
    ADC_16_TAD ,        
    ADC_20_TAD ,       
}adc_acquisition_time_select_t;

typedef enum{
    ADC_CONVERSION_CLOCK_FOSC_DIV_2 = 0 ,
    ADC_CONVERSION_CLOCK_FOSC_DIV_8     ,
    ADC_CONVERSION_CLOCK_FOSC_DIV_32    ,
    ADC_CONVERSION_CLOCK_RC_OSCILLATOR  , 
    ADC_CONVERSION_CLOCK_FOSC_DIV_4     ,    
    ADC_CONVERSION_CLOCK_FOSC_DIV_16    ,
    ADC_CONVERSION_CLOCK_FOSC_DIV_64    ,
            
}adc_conversion_clock_select_t;



typedef struct{
#if ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE     
    void(* ADC_InterruptHandler)(void)                  ;
    #if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE    
        interrupt_priority_cfg          adc_priority        ;
    #endif
#endif    
    adc_channel_select_t            adc_channel         ;
    adc_acquisition_time_select_t   acquisition_time    ;
    adc_conversion_clock_select_t   conversion_clock    ;
    uint8                           voltage_reference   : 1;
    uint8                           result_format       : 1;
    uint8                           ADC_Reserved        : 6;
}adc_configuration_t;

typedef uint16 adc_result_t;
/* Section : Function Declarations */

Std_ReturnType ADC_Init(const adc_configuration_t *_adc);
Std_ReturnType ADC_DeInit(const adc_configuration_t *_adc);
Std_ReturnType ADC_SelectChannel(const adc_configuration_t *_adc , adc_channel_select_t channel );
Std_ReturnType ADC_StartConversion(const adc_configuration_t *_adc);
Std_ReturnType ADC_IsConversionDone(const adc_configuration_t *_adc , uint8 *conversion_status);
Std_ReturnType ADC_GetConversionResult(const adc_configuration_t *_adc , adc_result_t *conversion_result);
Std_ReturnType ADC_GetConversion_Blocking(const adc_configuration_t *_adc , adc_channel_select_t channel  
                                                                 , adc_result_t *conversion_result);
Std_ReturnType ADC_StartConversion_Interrupt(const adc_configuration_t *_adc , adc_channel_select_t channel);

#endif	/* HAL_ADC_H */

