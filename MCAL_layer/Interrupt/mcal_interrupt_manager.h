/* 
 * File:   mcal_interrupt_manager.h
 * Author: anaal
 *
 * Created on April 13, 2025, 4:14 PM
 */

#ifndef MCAL_INTERRUPT_MANAGER_H
#define	MCAL_INTERRUPT_MANAGER_H



/*Section : Includes */
#include "mcal_interrupt_config.h"

/* Section : Macro Declarations */

/* Section : Macro Functions Declarations */
        

/* Section : Data Type Declarations */

/* Section : Function Declarations */
void INT0_ISR(void);
void INT1_ISR(void);
void INT2_ISR(void);
void RB4_ISR(uint8 RB4_Source);
void RB5_ISR(uint8 RB5_Source);
void RB6_ISR(uint8 RB6_Source);
void RB7_ISR(uint8 RB7_Source);
void ADC_ISR(void);
void TIMER0_ISR(void); 
void TIMER1_ISR(void); 
void TIMER2_ISR(void); 
void TIMER3_ISR(void); 
void CCP1_ISR(void);
void CCP2_ISR(void);
void EUSART_Tx_ISR(void);
void EUSART_Rx_ISR(void);
void SPI_ISR(void);
void MSSP_I2C_ISR(void);
void MSSP_I2C_BC_ISR(void);

#endif	/* MCAL_INTERRUPT_MANAGER_H */

