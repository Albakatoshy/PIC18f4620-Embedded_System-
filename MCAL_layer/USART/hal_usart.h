/* 
 * File:   hal_usart.h
 * Author: anaal
 *
 * Created on May 24, 2025, 10:20 AM
 */

#ifndef HAL_USART_H
#define	HAL_USART_H



/*Section : Includes */

#include <pic18f4620.h>
#include "../GPIO/hal_gpio.h"
#include "../GPIO/mcal_std_types.h"
#include "../Interrupt/mcal_internal_interrupt.h"
#include "hal_usart_cfg.h"

/* Section : Macro Declarations */

#define EUSART_SYNCHRONOUS_MODE_CFG                     1
#define EUSART_ASYNCHRONOUS_MODE_CFG                    0

#define EUSART_ASYNCHRONOUS_TX_ENABLE_CFG                   1
#define EUSART_ASYNCHRONOUS_TX_DISABLE_CFG                  0

#define EUSART_ASYNCHRONOUS_TX_INTERRUPT_ENABLE_CFG         1
#define EUSART_ASYNCHRONOUS_TX_INTERRUPT_DISABLE_CFG        0

#define EUSART_ASYNCHRONOUS_9BIT_TX_ENABLE_CFG              1
#define EUSART_ASYNCHRONOUS_8BIT_TX_ENABLE_CFG              0

#define EUSART_HIGH_SPEED_BUAD_RATE_CFG                     1
#define EUSART_LOW_SPEED_BAUD_RATE_CFG                      0

#define EUSART_SERIAL_PORT_ENABLE_CFG                       1
#define EUSART_SERIAL_PORT_DISABLE_CFG                      0

#define EUSART_ASYNCHRONOUS_RX_ENABLE_CFG                   1
#define EUSART_ASYNCHRONOUS_RX_DISABLE_CFG                  0

#define EUSART_ASYNCHRONOUS_9BIT_RX_ENABLE_CFG              1
#define EUSART_ASYNCHRONOUS_8BIT_RX_ENABLE_CFG              0

#define EUSART_ASYNCHRONOUS_RX_INTERRUPT_ENABLE_CFG         1
#define EUSART_ASYNCHRONOUS_RX_INTERRUPT_DISABLE_CFG        0

#define EUSART_16BIT_BAUD_RATE_GENERATOR_CFG                1
#define EUSART_8BIT_BAUD_RATE_GENERATOR_CFG                 0       

/*FARMING ERROR*/
#define EUSART_FRAMING_ERROR_DETECTED                   1
#define EUSART_FRAMING_ERROR_CLEARED                    0


/* Section : Macro Functions Declarations */
#define EUSART_MODULE_DISABLE()                         (RCSTAbits.SPEN = 0)    
#define EUSART_SYNCHRONOUS_MODE_ENABLE()                (TXSTAbits.SYNC = 1)
#define EUSART_ASYNCHRONOUS_MODE_ENABLE()               (TXSTAbits.SYNC = 0)
#define EUSART_HIGH_SPEED_BUAD_RATE_ENABLE()            (TXSTAbits.BRGH = 1)  
#define EUSART_LOW_SPEED_BUAD_RATE_ENABLE()             (TXSTAbits.BRGH = 0)  
#define EUSART_16BIT_BAUD_RATE_GENERATOR_ENABLE()       (BAUDCONbits.BRG16 = 1) 
#define EUSART_8BIT_BAUD_RATE_GENERATOR_ENABLE()        (BAUDCONbits.BRG16 = 0) 
#define EUSART_SERIAL_PORT_ENABLE()                     (RCSTAbits.SPEN = 1)    
#define EUSART_SERIAL_PORT_DISABLE()                    (RCSTAbits.SPEN = 0)
#define EUSART_ASYNCHRONOUS_TX_ENABLE()                 (TXSTAbits.TXEN = 1)       
#define EUSART_ASYNCHRONOUS_TX_DISABLE()                (TXSTAbits.TXEN = 0)
#define EUSART_ASYNCHRONOUS_RX_ENABLE()                 (RCSTAbits.CREN = 1)       
#define EUSART_ASYNCHRONOUS_RX_DISABLE()                (RCSTAbits.CREN = 0)
#define EUSART_ASYNCHRONOUS_9BIT_TX_ENABLE()            (TXSTAbits.TX9  = 1)     
#define EUSART_ASYNCHRONOUS_8BIT_TX_ENABLE()            (TXSTAbits.TX9  = 0)
#define EUSART_ASYNCHRONOUS_9BIT_RX_ENABLE()            (RCSTAbits.RX9  = 1)     
#define EUSART_ASYNCHRONOUS_8BIT_RX_ENABLE()            (RCSTAbits.RX9  = 0)
#define EUSART_ASYNCHRONOUS_TX_INTERRUPT_ENABLE()       (PIE1bits.TXIE = 1)  
#define EUSART_ASYNCHRONOUS_TX_INTERRUPT_DISABLE()      (PIE1bits.TXIE = 0)  
#define EUSART_ASYNCHRONOUS_RX_INTERRUPT_ENABLE()       (PIE1bits.RCIE = 1)  
#define EUSART_ASYNCHRONOUS_RX_INTERRUPT_DISABLE()      (PIE1bits.RCIE = 0) 
/* Section : Data Type Declarations */

typedef enum {
    BAUDRATE_ASYNC_8BIT_LOW_SPEED   ,
    BAUDRATE_ASYNC_8BIT_HIGH_SPEED  ,
    BAUDRATE_ASYNC_16BIT_LOW_SPEED  ,
    BAUDRATE_ASYNC_16BIT_HIGH_SPEED ,
    BAUDRATE_SYNC_8BIT              ,
    BAUDRATE_SYNC_16BIT             ,            
}baudrate_gen_t;

typedef struct {
    uint8 usart_tx_reserved         :4;
    uint8 usart_tx_enable           :1;
    uint8 usart_tx_interrupt_enable :1;
    uint8 usart_tx_9bit_enable      :1;
#if INTERRUPT_FEATURE_ENABLE == INTERRUPT_PRIORITY_LEVELS_ENABLE
    interrupt_priority_cfg          usart_tx_priority;
#endif    
}usart_tx_cfg_t;

typedef struct {
    uint8 usart_rx_reserved         :4;
    uint8 usart_rx_enable           :1;
    uint8 usart_rx_interrupt_enable :1;
    uint8 usart_rx_9bit_enable      :1;
#if INTERRUPT_FEATURE_ENABLE == INTERRUPT_PRIORITY_LEVELS_ENABLE    
    interrupt_priority_cfg          usart_rx_priority;
#endif     
}usart_rx_cfg_t;

typedef union{
   struct{
       uint8 usart_ferr             :1;
       uint8 usart_oerr             :1;
       uint8 usart_tx_reserved      :6;
 
   }; 
   uint8 status;
}usart_error_status_t;

typedef struct {
    uint8               usart_mode_selection;               
    uint32              baudrate;
    baudrate_gen_t      baudrate_gen_cfg;
    usart_tx_cfg_t      usart_tx_cfg;
    usart_rx_cfg_t      usart_rx_cfg;
    
    void(*EUSART_TxInterruptHandler)(void);
    void(*EUSART_RxInterruptHandler)(void);    
    void(*EUSART_FramingErrorHandler)(void);
    void(*EUSART_OverrunHandler)(void);    
    
}usart_t;

/* Section : Function Declarations */

Std_ReturnType EUSART_Init(const usart_t *_usart_obj);
Std_ReturnType EUSART_DeInit(const usart_t *_usart_obj);
Std_ReturnType EUSART_ReadByteBlocking(const usart_t *_usart_obj , uint8 *_data);
Std_ReturnType EUSART_ReadByteNoBlocking(uint8 *_data);
Std_ReturnType EUSART_RX_Restart(void);
Std_ReturnType EUSART_WriteByteBlocking(uint8 _data);
Std_ReturnType EUSART_WriteSrtingBlocking(uint8 *_data , uint8 str_len);
Std_ReturnType EUSART_WriteByteNoBlocking(uint8 _data);
Std_ReturnType EUSART_WriteSrtingNoBlocking(uint8 *_data , uint8 str_len);

#endif	/* HAL_USART_H */

