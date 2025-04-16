/* 
 * File:   ecu_seven_segment.h
 * Author: anaal
 *
 * Created on March 4, 2025, 11:20 AM
 */

#ifndef ECU_SEVEN_SEGMENT_H
#define	ECU_SEVEN_SEGMENT_H

/*Section : Includes */
#include "../../MCAL_layer/GPIO/hal_gpio.h"
#include "ecu_seven_segment_cfg.h"

/* Section : Macro Declarations */
#define SEVEN_SEG_PIN0 0 
#define SEVEN_SEG_PIN1 1
#define SEVEN_SEG_PIN2 2 
#define SEVEN_SEG_PIN3 3


/* Section : Macro Functions Declarations */

/* Section : Data Type Declarations */
typedef enum {
    SEVEN_SEG_COMMON_ANODE ,
    SEVEN_SEG_COMMON_CATHODE ,
}seven_seg_type_t;


typedef struct{
    
    pin_config_t sev_segment_pins[4];
    seven_seg_type_t sev_segment_type ;
}sev_segment_t;


/* Section : Function Declarations */

Std_ReturnType seven_seg_initialize(const sev_segment_t *sev_seg);
Std_ReturnType seven_seg_write_number(const sev_segment_t *sev_seg , uint8 number);


#endif	/* ECU_SEVEN_SEGMENT_H */

