#include "hal_usart.h"

static inline Std_ReturnType EUSART_ModeSelection(const usart_t *_usart_obj);
static void EUSART_TX_Init(const usart_t *_usart_obj);
static void EUSART_RX_Init(const usart_t *_usart_obj);

#if INTERRUPT_FEATURE_ENABLE == EUSART_INTERRUPT_TX_FEATURE_ENABLE
static void(*EUSART_TxInterruptHandler)(void) = NULL;
#endif

#if INTERRUPT_FEATURE_ENABLE == EUSART_INTERRUPT_RX_FEATURE_ENABLE
static void(*EUSART_RxInterruptHandler)(void) = NULL;
static void(*EUSART_FramingErrorHandler)(void) = NULL;
static void(*EUSART_OverrunHandler)(void) = NULL;
#endif

uint8 val =ZERO_INIT;

void EUSART_Tx_ISR(void){
    
    EUSART_ASYNCHRONOUS_INTERRUPT_TX_DISABLE();
    
    if(EUSART_TxInterruptHandler){
        EUSART_TxInterruptHandler();
    }
            
}

void EUSART_Rx_ISR(void){
//    val = RCREG;
    
    if(EUSART_RxInterruptHandler){
        EUSART_RxInterruptHandler();
    }
    if(EUSART_FramingErrorHandler){
        EUSART_FramingErrorHandler();
    }
    if(EUSART_OverrunHandler){
        EUSART_OverrunHandler();
    }
}

Std_ReturnType EUSART_Init(const usart_t *_usart_obj){
    Std_ReturnType ret = E_NOT_OK;
    if (NULL == _usart_obj){
        ret = E_NOT_OK;
    }
    else{
        EUSART_SERIAL_PORT_DISABLE();
        TRISCbits.RC7 = 1;
        TRISCbits.RC6 = 1;

        EUSART_ModeSelection(_usart_obj);
        EUSART_TX_Init(_usart_obj);
        EUSART_RX_Init(_usart_obj);
        
        
        EUSART_SERIAL_PORT_ENABLE();
        ret = E_OK;
    }
    
    return ret ;
}
Std_ReturnType EUSART_DeInit(const usart_t *_usart_obj){
    Std_ReturnType ret = E_NOT_OK;
    if (NULL == _usart_obj){
        ret = E_NOT_OK;
    }
    else{
        EUSART_MODULE_DISABLE();
        ret = E_OK;
    }
    
    return ret ;
}
Std_ReturnType EUSART_ReadByteBlocking(const usart_t *_usart_obj , uint8 *_data){
    Std_ReturnType ret = E_NOT_OK;
    if (NULL == _usart_obj && NULL == _data){
        ret = E_NOT_OK;
    }
    else{
        while(!(PIR1bits.RCIF));

        *_data = RCREG ;
        ret = E_OK;
    }
    
    return ret ;
}
Std_ReturnType EUSART_WriteByteBlocking(uint8 _data){
    while(!(TXSTAbits.TRMT));
    EUSART_ASYNCHRONOUS_INTERRUPT_TX_ENABLE();
    TXREG = _data;
}

static inline Std_ReturnType EUSART_ModeSelection(const usart_t *_usart_obj){
    Std_ReturnType ret = E_NOT_OK;
    
    float baud_rate_temp = 0;    

    if (NULL == _usart_obj){
        ret = E_NOT_OK;
    }
    else{
        if(EUSART_SYNCHRONOUS_MODE_CFG == _usart_obj->usart_mode_selection){
            EUSART_SYNCHRONOUS_MODE_ENABLE();
            switch (_usart_obj->baudrate_gen_cfg){
                case BAUDRATE_SYNC_8BIT:
                    EUSART_8BIT_BAUD_RATE_GENERATOR_ENABLE();
                    baud_rate_temp = ((_XTAL_FREQ / (float)(_usart_obj->baudrate) ) / 4) - 1;
                    break;
                
                case BAUDRATE_SYNC_16BIT:
                    EUSART_16BIT_BAUD_RATE_GENERATOR_ENABLE();
                    baud_rate_temp = ((_XTAL_FREQ / (float)(_usart_obj->baudrate) ) / 4) - 1;
                    break;
                    
                default:
                    ret = E_NOT_OK;
                    break;
            }
        }
        else if(EUSART_ASYNCHRONOUS_MODE_CFG == _usart_obj->usart_mode_selection){
            EUSART_ASYNCHRONOUS_MODE_ENABLE();
            switch (_usart_obj->baudrate_gen_cfg){
                case BAUDRATE_ASYNC_8BIT_LOW_SPEED :
                    EUSART_8BIT_BAUD_RATE_GENERATOR_ENABLE();
                    EUSART_LOW_SPEED_BUAD_RATE_ENABLE();
                    baud_rate_temp = ((_XTAL_FREQ / (float)(_usart_obj->baudrate) ) / 64) - 1;
                    break;

                case BAUDRATE_ASYNC_8BIT_HIGH_SPEED:
                    EUSART_8BIT_BAUD_RATE_GENERATOR_ENABLE();
                    EUSART_HIGH_SPEED_BUAD_RATE_ENABLE();
                    baud_rate_temp = ((_XTAL_FREQ / (float)(_usart_obj->baudrate) ) / 16) - 1;
                    break;

                case BAUDRATE_ASYNC_16BIT_LOW_SPEED:
                    EUSART_16BIT_BAUD_RATE_GENERATOR_ENABLE();
                    EUSART_LOW_SPEED_BUAD_RATE_ENABLE();
                    baud_rate_temp = ((_XTAL_FREQ / (float)(_usart_obj->baudrate) ) / 16) - 1;
                    break;

                case BAUDRATE_ASYNC_16BIT_HIGH_SPEED:
                    EUSART_16BIT_BAUD_RATE_GENERATOR_ENABLE();
                    EUSART_HIGH_SPEED_BUAD_RATE_ENABLE();
                    baud_rate_temp = ((_XTAL_FREQ / (float)(_usart_obj->baudrate) ) / 4) - 1;
                    break;
                    
                default:
                    ret = E_NOT_OK ;
                    break;
            }
            SPBRG  = (uint8)((uint32)(baud_rate_temp));
            SPBRGH = (uint8)(((uint32)(baud_rate_temp))>>8)  ;
        }
        else{
           ret = E_NOT_OK; 
        }
        
        ret = E_OK;
    }
    
    return ret ;
}

static void EUSART_TX_Init(const usart_t *_usart_obj){
    if (EUSART_ASYNCHRONOUS_TX_ENABLE_CFG == _usart_obj->usart_tx_cfg.usart_tx_enable ){
        EUSART_ASYNCHRONOUS_TX_ENABLE();
        if (_usart_obj->usart_tx_cfg.usart_tx_interrupt_enable == EUSART_ASYNCHRONOUS_TX_INTERRUPT_ENABLE_CFG){
            EUSART_ASYNCHRONOUS_TX_INTERRUPT_ENABLE();
            #if INTERRUPT_FEATURE_ENABLE == EUSART_INTERRUPT_TX_FEATURE_ENABLE
                    EUSART_ASYNCHRONOUS_INTERRUPT_TX_ENABLE();
                    EUSART_TxInterruptHandler = (_usart_obj->EUSART_TxInterruptHandler);
                    
            #if INTERRUPT_FEATURE_ENABLE == INTERRUPT_PRIORITY_LEVELS_ENABLE
                    INTERRUPT_InterruptPriorityEnable();
                    if(INTERRUPT_HIGH_PRIORITY == _usart_obj->usart_tx_cfg.usart_tx_priority){
                        INTERRUPT_GlobalInterruptHighEnable();
                        EUSART_ASYNCHRONOUS_INTERRUPT_TX_HIGH_PRIORITY();
                    }
                    else if(INTERRUPT_LOW_PRIORITY == _usart_obj->usart_tx_cfg.usart_tx_priority){
                        INTERRUPT_GlobalInterruptLowEnable();
                        EUSART_ASYNCHRONOUS_INTERRUPT_TX_LOW_PRIORITY();
                    }
                    else{/*NOTHING*/}
            #else 
                    INTERRUPT_GlobalInterruptEnable();
                    INTERRUPT_PeripheralInterruptEnable(); 

            #endif
            #endif
        }
        else if(_usart_obj->usart_tx_cfg.usart_tx_interrupt_enable == EUSART_ASYNCHRONOUS_TX_INTERRUPT_DISABLE_CFG){
            EUSART_ASYNCHRONOUS_TX_INTERRUPT_DISABLE();
        }
        else{/*NOTHING*/}

        if(_usart_obj->usart_tx_cfg.usart_tx_9bit_enable == EUSART_ASYNCHRONOUS_9BIT_TX_ENABLE_CFG ){
            EUSART_ASYNCHRONOUS_9BIT_TX_ENABLE();
        }
        else if (_usart_obj->usart_tx_cfg.usart_tx_9bit_enable == EUSART_ASYNCHRONOUS_8BIT_TX_ENABLE_CFG ){
            EUSART_ASYNCHRONOUS_8BIT_TX_ENABLE();
        }
        else{/*NOTHING*/}


        
    }
    else if(EUSART_ASYNCHRONOUS_TX_DISABLE_CFG == _usart_obj->usart_tx_cfg.usart_tx_enable){
        EUSART_ASYNCHRONOUS_TX_DISABLE();
    }
}


static void EUSART_RX_Init(const usart_t *_usart_obj){
    if (EUSART_ASYNCHRONOUS_RX_ENABLE_CFG == _usart_obj->usart_rx_cfg.usart_rx_enable ){
        EUSART_ASYNCHRONOUS_RX_ENABLE();
        if (_usart_obj->usart_rx_cfg.usart_rx_interrupt_enable == EUSART_ASYNCHRONOUS_RX_INTERRUPT_ENABLE_CFG){
            EUSART_ASYNCHRONOUS_RX_INTERRUPT_ENABLE();
            #if INTERRUPT_FEATURE_ENABLE == EUSART_INTERRUPT_RX_FEATURE_ENABLE
                    EUSART_ASYNCHRONOUS_INTERRUPT_RX_ENABLE();
                    EUSART_RxInterruptHandler = (_usart_obj->EUSART_RxInterruptHandler);
                    EUSART_FramingErrorHandler = _usart_obj->EUSART_FramingErrorHandler;
                    EUSART_OverrunHandler = _usart_obj->EUSART_OverrunHandler;
            #if INTERRUPT_FEATURE_ENABLE == INTERRUPT_PRIORITY_LEVELS_ENABLE
                    INTERRUPT_InterruptPriorityEnable();
                    if(INTERRUPT_HIGH_PRIORITY == _usart_obj->usart_rx_cfg.usart_rx_priority){
                        INTERRUPT_GlobalInterruptHighEnable();
                        EUSART_ASYNCHRONOUS_INTERRUPT_RX_HIGH_PRIORITY();
                    }
                    else if(INTERRUPT_LOW_PRIORITY == _usart_obj->usart_rx_cfg.usart_rx_priority){
                        INTERRUPT_GlobalInterruptLowEnable();
                        EUSART_ASYNCHRONOUS_INTERRUPT_RX_LOW_PRIORITY();
                    }
                    else{/*NOTHING*/}
            #else 
                    INTERRUPT_GlobalInterruptEnable();
                    INTERRUPT_PeripheralInterruptEnable(); 

            #endif
            #endif
        }
        else if(_usart_obj->usart_rx_cfg.usart_rx_interrupt_enable == EUSART_ASYNCHRONOUS_RX_INTERRUPT_DISABLE_CFG){
            EUSART_ASYNCHRONOUS_RX_INTERRUPT_DISABLE();
        }
        else{/*NOTHING*/}

        if(_usart_obj->usart_rx_cfg.usart_rx_9bit_enable == EUSART_ASYNCHRONOUS_9BIT_RX_ENABLE_CFG ){
            EUSART_ASYNCHRONOUS_9BIT_RX_ENABLE();
        }
        else if (_usart_obj->usart_rx_cfg.usart_rx_9bit_enable == EUSART_ASYNCHRONOUS_8BIT_RX_ENABLE_CFG ){
            EUSART_ASYNCHRONOUS_8BIT_RX_ENABLE();
        }
        else{/*NOTHING*/}
        
    }
    else if(EUSART_ASYNCHRONOUS_RX_DISABLE_CFG == _usart_obj->usart_rx_cfg.usart_rx_enable){
        EUSART_ASYNCHRONOUS_RX_DISABLE();
    }
}

Std_ReturnType EUSART_WriteSrtingBlocking(uint8 *_data , uint8 str_len){
    Std_ReturnType ret = E_NOT_OK;
    if (NULL == _data){
        ret = E_NOT_OK;
    }
    else{   
        uint8 l_counter = ZERO_INIT ;
        for(l_counter=ZERO_INIT ; l_counter < str_len ; l_counter++){
            EUSART_WriteByteBlocking(_data[l_counter]);
        }
        
        
        ret = E_OK;
    }
    
    return ret ;
}

Std_ReturnType EUSART_ReadByteNoBlocking(uint8 *_data){
    Std_ReturnType ret = E_NOT_OK;
    
    if(1 == (PIR1bits.RCIF)){
        *_data = RCREG ;
        ret = E_OK;
    }
    else{
        ret = E_NOT_OK;
    }
    
    return ret ;
}

Std_ReturnType EUSART_RX_Restart(void){
    Std_ReturnType ret = E_OK;
    
    RCSTAbits.CREN = 0;
    RCSTAbits.CREN = 1;
    
    return ret ;
}


Std_ReturnType EUSART_WriteByteNoBlocking(uint8 _data){
    Std_ReturnType ret = E_OK;
    if(TXSTAbits.TRMT){
        TXREG = _data;
        ret = E_OK;
    }
    else{
        ret = E_NOT_OK;
    }
    return ret;
}

Std_ReturnType EUSART_WriteSrtingNoBlocking(uint8 *_data , uint8 str_len){
    
}