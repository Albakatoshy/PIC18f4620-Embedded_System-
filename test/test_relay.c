/* 
 * File:   application.c
 * Author: abdalrahman.ahmed
 *
 * Created on January 27, 2025, 2:15 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include "application.h"
#define _XTAL_FREQ 4000000  // 4 MHz clock





int main() {
    Std_ReturnType ret = E_OK;
    application_initialize();
    while(1){
        
   }
    
     
}


void application_initialize(void){
    Std_ReturnType ret = E_OK;
    ret = relay_initialize(&relay1);
    
    
}
        
        


