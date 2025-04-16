/* 
 * File:   application.c
 * Author: abdalrahman.ahmed
 *
 * Created on January 27, 2025, 2:15 AM
 */

#include <stdio.h>
#include <stdlib.h>
    
#include "application.h"

#define ABOOD_HWREG(_x) (*((volatile uint8_t *)(_x)))
#define ABOOD_LATC (ABOOD_HWREG(0xF8B))
#define ABOOD_TRISC (ABOOD_HWREG(0xF94))

#include <xc.h>   // Include the PIC's header
#define _XTAL_FREQ 8000000 


typedef union{
    struct{
        unsigned SELF_LATC0 :1 ;
        unsigned SELF_LATC1 :1 ;
        unsigned SELF_LATC2 :1 ;
        unsigned SELF_LATC3 :1 ;
        unsigned SELF_LATC4 :1 ;
        unsigned SELF_LATC5 :1 ;
        unsigned SELF_LATC6 :1 ;
        unsigned SELF_LATC7 :1 ;
    };
    uint8_t LATC_REGEISTER;
    
}SELF_LATC;


#define LATC_REG ((volatile SELF_LATC *)(0xF8B))
#define LATC_REG (*((volatile SELF_LATC *)(0xF8B)))

int main(int argc, char** argv) {
      ABOOD_TRISC=0x00;
//    while(1){
//        LATC_REG->SELF_LATC0=1;
//    }
      LATC_REG.LATC_REGEISTER=0x55; 
      __delay_ms(2000);
      LATC_REG.SELF_LATC5=1;
      __delay_ms(2000);
      
    

    return (EXIT_SUCCESS);
}


