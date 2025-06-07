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
    
    if((INTERRUPT_ENABLE == (PIE1bits.TMR2IE)) && (INTERRUPT_OCCUR == (PIR1bits.TMR2IF))){
        TIMER2_ISR();
    }
    
    if ((INTERRUPT_ENABLE == (PIE2bits.TMR3IE)) && (INTERRUPT_OCCUR == (PIR2bits.TMR3IF))){
        TIMER3_ISR();
    }
    else{/*NOTHING*/}
}
    
void __interrupt(low_priority) InterruptManagerLow(void){
     if((INTERRUPT_ENABLE == INTCON3bits.INT1IE) && (INTERRUPT_OCCUR == INTCON3bits.INT1IF)){
        INT1_ISR();
    }
     if((INTERRUPT_ENABLE == PIE1bits.TMR1IE) && (INTERRUPT_OCCUR == PIR1bits.TMR1IF)){
        TIMER1_ISR();
    }
    
    if((INTERRUPT_ENABLE == (PIE1bits.TMR2IE)) && (INTERRUPT_OCCUR == (PIR1bits.TMR2IF))){
        TIMER2_ISR();
    }
    
    if ((INTERRUPT_ENABLE == (PIE2bits.TMR3IE)) && (INTERRUPT_OCCUR == (PIR2bits.TMR3IF))){
        TIMER3_ISR();
    }
    else{/*NOTHING*/} 
     


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
    
    if((INTERRUPT_ENABLE == (PIE1bits.ADIE)) && (INTERRUPT_OCCUR == (PIR1bits.ADIF) )){
        ADC_ISR();
    }
    else{/*NOTHING*/}
    
    if((INTERRUPT_ENABLE == (INTCONbits.TMR0IE)) && (INTERRUPT_OCCUR ==(INTCONbits.TMR0IF)) ){
        TIMER0_ISR();
    }
    else{/*NOTHING*/}
    
    if((INTERRUPT_ENABLE == (PIE1bits.TMR1IE)) && (INTERRUPT_OCCUR == (PIR1bits.TMR1IF))){
        TIMER1_ISR();
    }
    else{/*NOTHING*/}
    
    if((INTERRUPT_ENABLE == (PIE1bits.TMR2IE)) && (INTERRUPT_OCCUR == (PIR1bits.TMR2IF))){
        TIMER2_ISR();
    }
    else{/*NOTHING*/}
    
    if ((INTERRUPT_ENABLE == (PIE2bits.TMR3IE)) && (INTERRUPT_OCCUR == (PIR2bits.TMR3IF))){
        TIMER3_ISR();
    }
    else{/*NOTHING*/}
    
    if ((INTERRUPT_ENABLE == (PIE1bits.CCP1IE)) && (INTERRUPT_OCCUR == (PIR1bits.CCP1IF))){
        CCP1_ISR();
    }
    else{/*NOTHING*/}
    
    if ((INTERRUPT_ENABLE == (PIE2bits.CCP2IE)) && (INTERRUPT_OCCUR == (PIR2bits.CCP2IF))){
        CCP2_ISR();
    }
    else{/*NOTHING*/}
    
    if ((INTERRUPT_ENABLE == (PIE1bits.TXIE)) && (INTERRUPT_OCCUR == (PIR1bits.TXIF))){
        EUSART_Tx_ISR();
    }
    else{/*NOTHING*/}
    
    if ((INTERRUPT_ENABLE == (PIE1bits.RCIE)) && (INTERRUPT_OCCUR == (PIR1bits.RCIF))){
        EUSART_Rx_ISR();
    }
    else{/*NOTHING*/}
    
    if ((INTERRUPT_ENABLE == (PIE1bits.SSPIE)) && (INTERRUPT_OCCUR == (PIR1bits.SSPIF))){
        SPI_ISR();
    }
    else{/*NOTHING*/}
    
}
#endif

