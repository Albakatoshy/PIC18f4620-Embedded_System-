/* 
 * File:   hal_spi.h
 * Author: anaal
 *
 * Created on June 6, 2025, 2:35 PM
 */

#ifndef HAL_SPI_H
#define	HAL_SPI_H



/*Section : Includes */
#include "pic18f4620.h"
#include "../GPIO/hal_gpio.h"
#include "../GPIO/mcal_std_types.h"
#include "../Interrupt/mcal_internal_interrupt.h"

/* Section : Macro Declarations */

#define SPI_ENABLE_CFG                          1
#define SPI_DISABLE_CFG                         0   
#define SPI_CLOCK_POLARITY_HIGH_LEVEL_CFG       1
#define SPI_CLOCK_POLARITY_LOW_LEVEL_CFG        0
#define SPI_DATA_SAMPLED_AT_END_OF_DATA_CFG     1
#define SPI_DATA_SAMPLED_AT_MID_OF_DATA_CFG     0
#define SPI_CLOCK_SELECT_ACTIVE_TO_IDLE_CFG     1
#define SPI_CLOCK_SELECT_IDLE_TO_ACTIVE_CFG     0


/* Section : Macro Functions Declarations */
#define SPI_ENABLE()                                  (SSPCON1bits.SSPEN = 1  )
#define SPI_DISABLE()                                 (SSPCON1bits.SSPEN = 0  )
#define SPI_CLOCK_POLARITY_HIGH_LEVEL_ENABLE()        (SSPCON1bits.CKP   = 1  )
#define SPI_CLOCK_POLARITY_LOW_LEVEL_ENABLE()         (SSPCON1bits.CKP   = 0  )
#define SPI_DATA_SAMPLED_AT_END_OF_DATA_ENABLE()      (SSPSTATbits.SMP   = 1  )
#define SPI_DATA_SAMPLED_AT_MID_OF_DATA_ENABLE()      (SSPSTATbits.SMP   = 0  )
#define SPI_CLOCK_SELECT_ACTIVE_TO_IDLE_ENABLE()      (SSPSTATbits.CKE   = 1  ) 
#define SPI_CLOCK_SELECT_IDLE_TO_ACTIVE_ENABLE()      (SSPSTATbits.CKE   = 0  ) 

/* Section : Data Type Declarations */
typedef enum {
    SPI_MASTER_MODE_FOSC_DIV_4 = 0  ,
    SPI_MASTER_MODE_FOSC_DIV_16     ,
    SPI_MASTER_MODE_FOSC_DIV_64     ,
    SPI_MASTER_MODE_FOSC_TMR2_DIV_2 ,
    SPI_SLAVE_MODE_FOSC_SS_ENABLED  ,
    SPI_SLAVE_MODE_FOSC_SS_DISABLED ,        
            
}spi_mode_select_t;


typedef struct{
    uint8 ClockPolarity : 2; /* Clock Polarity Select */
    uint8 SampleSelect : 2;  /* SPI Sample Select */
    uint8 ClockSelect : 2;   /* SPI Clock Select */
    uint8 Reserved : 2;
}SPI_Control_Config;

typedef struct{
#if MSSP_SPI_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    void (* MSSP_SPI_InterruptHandler)(void);
    interrupt_priority_cfg priority;
#endif
    spi_mode_select_t spi_mode;
    SPI_Control_Config spi_config;
}SPI_Config;


/* Section : Function Declarations */
Std_ReturnType SPI_Init(const SPI_Config *spi_obj );
Std_ReturnType SPI_DeInit(const SPI_Config *spi_obj );
Std_ReturnType SPI_Read_VAL(const SPI_Config *spi_obj ,uint8 *readVal );
Std_ReturnType SPI_Write_VAL(const SPI_Config *spi_obj ,uint8 WriteVal );



#endif	/* HAL_SPI_H */

