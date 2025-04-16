/* 
 * File:   mcal_interrupt_manager.c
 * Author: anaal
 *
 * Created on April 13, 2025, 4:14 PM
 */


#include "mcal_interrupt_manager.h"

static volatile uint8 RB4_FLAG = 1 ;
static volatile uint8 RB5_FLAG = 1 ;
static volatile uint8 RB6_FLAG = 1 ;
static volatile uint8 RB7_FLAG = 1 ;


#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE 
void __interrupt() InterruptManagerHigh(void){
    if((INTERRUPT_ENABLE == INTCONbits.INT0IE) && (INTERRUPT_OCCUR == INTCONbits.INT0IF)){
        INT0_ISR();
    }
    
    if((INTERRUPT_ENABLE == INTCON3bits.INT2IE) && (INTERRUPT_OCCUR == INTCON3bits.INT2IF)){
        INT2_ISR();
    }
}
    
void __interrupt(low_priority) InterruptManagerLow(void){
     if((INTERRUPT_ENABLE == INTCON3bits.INT1IE) && (INTERRUPT_OCCUR == INTCON3bits.INT1IF)){
        INT1_ISR();
    }
}
#else
void __interrupt() InterruptManager(void){
    if((INTERRUPT_ENABLE == INTCONbits.INT0IE) && (INTERRUPT_OCCUR == INTCONbits.INT0IF)){
        INT0_ISR();
    }
    else{/*NOTHING*/}
    
    if((INTERRUPT_ENABLE == INTCON3bits.INT1IE) && (INTERRUPT_OCCUR == INTCON3bits.INT1IF)){
        INT1_ISR();
    }
    else{/*NOTHING*/}
    
    if((INTERRUPT_ENABLE == INTCON3bits.INT2IE) && (INTERRUPT_OCCUR == INTCON3bits.INT2IF)){
        INT2_ISR();
    }
    else{/*NOTHING*/}
    
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && (PORTBbits.RB4 == GPIO_HIGH)&& (RB4_FLAG == 1)){
        RB4_FLAG = 0;
        RB4_ISR(0);
    }
    else{/*NOTHING*/}
    
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && (PORTBbits.RB4 == GPIO_LOW) && (RB4_FLAG == 0)){
        RB4_FLAG = 1;
        RB4_ISR(1);
    }  
    else{/*NOTHING*/}
    
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && (PORTBbits.RB5 == GPIO_HIGH) && (RB5_FLAG == 1)){
        RB5_FLAG=0;
        RB5_ISR(0);
    }
    else{/*NOTHING*/}
    
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && (PORTBbits.RB5 == GPIO_LOW) && (RB5_FLAG == 0)){
        RB5_FLAG=1;
        RB5_ISR(1);
    }  
    else{/*NOTHING*/}
    
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && (PORTBbits.RB6 == GPIO_HIGH)&& (RB6_FLAG == 1)){
        RB6_FLAG=0;
        RB6_ISR(0);
    }
    else{/*NOTHING*/}
    
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && (PORTBbits.RB6 == GPIO_LOW)&& (RB6_FLAG == 0)){
        RB6_FLAG=1;
        RB6_ISR(1);
    }  
    else{/*NOTHING*/}
    
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && (PORTBbits.RB7 == GPIO_HIGH)&& (RB7_FLAG == 1)){
        RB7_FLAG=0;
        RB7_ISR(0);
    }
    else{/*NOTHING*/}
    
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && (PORTBbits.RB7 == GPIO_LOW)&& (RB7_FLAG == 0)){
        RB7_FLAG=1;
        RB7_ISR(1);
    }  
    else{/*NOTHING*/}
}
#endif

