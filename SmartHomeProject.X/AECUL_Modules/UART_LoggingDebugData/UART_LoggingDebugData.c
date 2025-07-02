#include "UART_LoggingDebugData.h"


void UART_LoggingDebugData_Send_String(uint8_t *_str , uint16_t _str_length){
    uint16_t l__str_length = 0;
    for (l__str_length = 0 ; l__str_length < _str_length ;++l__str_length){
        EUSART_Write(_str[l__str_length]);
    }
    
    
    //    while(_str != '\0'){
//        EUSART_Write(*_str++);
//    }
}