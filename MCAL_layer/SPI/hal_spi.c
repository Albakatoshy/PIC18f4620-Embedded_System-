#include "hal_spi.h"

static Std_ReturnType SPI_MASTER_PIN_CONFIG(const SPI_Config *spi_obj);
static Std_ReturnType SPI_SLAVE_PIN_CONFIG(const SPI_Config *spi_obj);
static Std_ReturnType SPI_INTERRUPT_INIT(const SPI_Config *spi_obj);

#if INTERRUPT_FEATURE_ENABLE == MSSP_SPI_INTERRUPT_FEATURE_ENABLE
static void(*SPI_InterruptHandler)(void)= NULL ; 
#endif

void SPI_ISR(void){
    SPI_INTERRUPT_CLEAR_FLAG();
    
    if(SPI_InterruptHandler){
        SPI_InterruptHandler();
    }
}

Std_ReturnType SPI_Init(const SPI_Config *spi_obj ){
    Std_ReturnType ret = E_NOT_OK ;
    if(NULL == spi_obj ){
        ret = E_NOT_OK ;
    }
    else{
        SPI_DISABLE();
        SSPCON1bits.SSPM = spi_obj->spi_mode;
        
        #if INTERRUPT_FEATURE_ENABLE == MSSP_SPI_INTERRUPT_FEATURE_ENABLE
        SPI_INTERRUPT_INIT(spi_obj); 
        #endif
        
        if((SPI_MASTER_MODE_FOSC_DIV_4 == spi_obj->spi_mode) ||(SPI_MASTER_MODE_FOSC_DIV_16 == spi_obj->spi_mode) ||
           (SPI_MASTER_MODE_FOSC_DIV_64 == spi_obj->spi_mode)||(SPI_MASTER_MODE_FOSC_TMR2_DIV_2 == spi_obj->spi_mode)){
            SPI_MASTER_PIN_CONFIG(spi_obj);
        }
        else if((SPI_SLAVE_MODE_FOSC_SS_DISABLED == spi_obj->spi_mode)||(SPI_SLAVE_MODE_FOSC_SS_ENABLED == spi_obj->spi_mode)){
            SPI_SLAVE_PIN_CONFIG(spi_obj);
        }
        
        SSPCON1bits.CKP = spi_obj->spi_config.ClockPolarity;
        SSPSTATbits.SMP = spi_obj->spi_config.SampleSelect;
        SSPSTATbits.CKE = spi_obj->spi_config.ClockSelect;
        
        
                
        
        SPI_ENABLE();
       
        ret = E_OK;
    }
    return ret ;
    
}

Std_ReturnType SPI_DeInit(const SPI_Config *spi_obj ){
    Std_ReturnType ret = E_NOT_OK ;
    if(NULL == spi_obj ){
        ret = E_NOT_OK ;
    }
    else{
        
        ret = E_OK;
    }
    return ret ;
    
}

Std_ReturnType SPI_Read_VAL(const SPI_Config *spi_obj ,uint8 *readVal ){
    while(SSPSTATbits.BF == 0);
    *readVal = SSPBUF;
}
Std_ReturnType SPI_Write_VAL(const SPI_Config *spi_obj ,uint8 WriteVal ){
    SSPBUF = WriteVal;
    while(!(PIR1bits.SSPIF)); /* Waiting to transmit */
    PIR1bits.SSPIF = 0;
}

static Std_ReturnType SPI_MASTER_PIN_CONFIG(const SPI_Config *spi_obj){
    Std_ReturnType ret = E_OK ;
    pin_config_t SPI_SDO = {.direction = GPIO_DIRECTION_OUTPUT , .logic = GPIO_LOW , .port = PORTC_INDEX , .pin = GPIO_PIN5 };
    pin_config_t SPI_SDI = {.direction = GPIO_DIRECTION_INPUT , .logic = GPIO_LOW , .port = PORTC_INDEX , .pin = GPIO_PIN4 };
    pin_config_t SPI_SCK = {.direction = GPIO_DIRECTION_OUTPUT , .logic = GPIO_LOW , .port = PORTC_INDEX , .pin = GPIO_PIN3 };
    
    ret = gpio_pin_direction_intialize(&SPI_SDO);
    ret = gpio_pin_direction_intialize(&SPI_SDI);
    ret = gpio_pin_direction_intialize(&SPI_SCK); 
}
static Std_ReturnType SPI_SLAVE_PIN_CONFIG(const SPI_Config *spi_obj){
    Std_ReturnType ret = E_OK ;
    pin_config_t SPI_SDO = {.direction = GPIO_DIRECTION_OUTPUT , .logic = GPIO_LOW , .port = PORTC_INDEX , .pin = GPIO_PIN5 };
    pin_config_t SPI_SDI = {.direction = GPIO_DIRECTION_INPUT , .logic = GPIO_LOW , .port = PORTC_INDEX , .pin = GPIO_PIN4 };
    pin_config_t SPI_SCK = {.direction = GPIO_DIRECTION_INPUT , .logic = GPIO_LOW , .port = PORTC_INDEX , .pin = GPIO_PIN3 };
    pin_config_t SPI_SS = {.direction = GPIO_DIRECTION_INPUT , .logic = GPIO_LOW , .port = PORTA_INDEX , .pin = GPIO_PIN5 };
    
    ret = gpio_pin_direction_intialize(&SPI_SDO);
    ret = gpio_pin_direction_intialize(&SPI_SDI);
    ret = gpio_pin_direction_intialize(&SPI_SCK);
    if (SPI_SLAVE_MODE_FOSC_SS_ENABLED == spi_obj->spi_mode){
        ret = gpio_pin_direction_intialize(&SPI_SS);
    }
    
    
}

static Std_ReturnType SPI_INTERRUPT_INIT(const SPI_Config *spi_obj){
    Std_ReturnType ret = E_OK ;
    
    #if INTERRUPT_FEATURE_ENABLE == TIMER1_INTERRUPT_FEATURE_ENABLE
        SPI_INTERRUPT_ENABLE();
        SPI_INTERRUPT_CLEAR_FLAG();
        SPI_InterruptHandler = spi_obj->MSSP_SPI_InterruptHandler;
    #if INTERRUPT_FEATURE_ENABLE == INTERRUPT_PRIORITY_LEVELS_ENABLE
            INTERRUPT_InterruptPriorityEnable();
            if (INTERRUPT_HIGH_PRIORITY == spi_obj->priority){
                SPI_INTERRUPT_HIGH_PRIORITY(); 
                INTERRUPT_GlobalInterruptHighEnable();
            }
            else if(INTERRUPT_LOW_PRIORITY == spi_obj->priority){
                SPI_INTERRUPT_LOW_PRIORITY();
                INTERRUPT_GlobalInterruptLowEnable();
            }
            else{/*NOTHING*/}
    #else
            INTERRUPT_GlobalInterruptEnable();
            INTERRUPT_PeripheralInterruptEnable();

    #endif
    #endif
    
    
}