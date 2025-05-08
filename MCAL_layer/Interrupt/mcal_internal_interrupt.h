/* 
 * File:   mcal_internal_interrupt.h
 * Author: anaal
 *
 * Created on April 13, 2025, 4:13 PM
 */

#ifndef MCAL_INTERNAL_INTERRUPT_H
#define	MCAL_INTERNAL_INTERRUPT_H



/*Section : Includes */
#include "mcal_interrupt_config.h"

/* Section : Macro Declarations */

/* Section : Macro Functions Declarations */
#if ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE     

/*this routine enable and disable the ADC interrupt */
#define ADC_INTERRUPT_ENABLE()                  (PIE1bits.ADIE=1)        
#define ADC_INTERRUPT_DISABLE()                 (PIE1bits.ADIE=0)
    
#define ADC_INTERRUPT_CLEAR_FLAG()              (PIR1bits.ADIF=0)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
/*This routine enable the high and low interrupt level feature if it enable in the microcontroller*/
#define ADC_INTERRUPT_HIGH_PRIORITY_ENABLE()    (IPR1bits.ADIP=1)
#define ADC_INTERRUPT_LOW_PRIORITY_ENABLE()     (IPR1bits.ADIP=0)

#endif
#endif


#if  TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE 
#define TIMER0_INTERRUPT_ENABLE()               (INTCONbits.TMR0IE = 1) 
#define TIMER0_INTERRUPT_DISABLE()              (INTCONbits.TMR0IE = 0) 
#define TIMER0_INTERRUPT_CLEAR_FLAG()           (INTCONbits.TMR0IF = 0)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE

#define TIMER0_INTERRUPT_HIGH_PRIORITY()          (INTCON2bits.TMR0IP = 1)
#define TIMER0_INTERRUPT_LOW_PRIORITY()           (INTCON2bits.TMR0IP = 0)

#endif
#endif

#if INTERRUPT_FEATURE_ENABLE == TIMER1_INTERRUPT_FEATURE_ENABLE 
#define TIMER1_INTERRUPT_ENABLE()                   (PIE1bits.TMR1IE = 1)
#define TIMER1_INTERRUPT_DISABLE()                  (PIE1bits.TMR1IE = 0)
#define TIMER1_INTERRUPT_CLEAR_FLAG()               (PIR1bits.TMR1IF = 0)
#if INTERRUPT_FEATURE_ENABLE == INTERRUPT_PRIORITY_LEVELS_ENABLE
#define TIMER1_INTERRUPT_HIGH_PRIORITY()            (IPR1bits.TMR1IP = 1)              
#define TIMER1_INTERRUPT_LOW_PRIORITY()             (IPR1bits.TMR1IP = 0)
#endif
#endif

#if INTERRUPT_FEATURE_ENABLE == TIMER2_INTERRUPT_FEATURE_ENABLE
#define TIMER2_INTERRUPT_ENABLE()                   (PIE1bits.TMR2IE = 1)
#define TIMER2_INTERRUPT_DISABLE()                  (PIE1bits.TMR2IE = 0)
#define TIMER2_INTERRUPT_CLEAR_FLAG()               (PIR1bits.TMR2IF = 0)
#if INTERRUPT_FEATURE_ENABLE == INTERRUPT_PRIORITY_LEVELS_ENABLE
#define TIMER2_INTERRUPT_HIGH_PRIORITY()            (IPR1bits.TMR2IP = 1)
#define TIMER2_INTERRUPT_LOW_PRIORITY()             (IPR1bits.TMR2IP = 0)
#endif
#endif


#if INTERRUPT_FEATURE_ENABLE == TIMER3_INTERRUPT_FEATURE_ENABLE
#define TIMER3_INTERRUPT_ENABLE()                   (PIE2bits.TMR3IE = 1)
#define TIMER3_INTERRUPT_DISABLE()                  (PIE2bits.TMR3IE = 0)
#define TIMER3_INTERRUPT_CLEAR_FLAG()               (PIR2bits.TMR3IF = 0)
#if INTERRUPT_FEATURE_ENABLE == INTERRUPT_PRIORITY_LEVELS_ENABLE
#define TIMER3_INTERRUPT_HIGH_PRIORITY()            (IPR2bits.TMR3IP = 1)
#define TIMER3_INTERRUPT_LOW_PRIORITY()             (IPR2bits.TMR3IP = 0)
#endif
#endif


/* Section : Data Type Declarations */

/* Section : Function Declarations */

#endif	/* MCAL_INTERNAL_INTERRUPT_H */

