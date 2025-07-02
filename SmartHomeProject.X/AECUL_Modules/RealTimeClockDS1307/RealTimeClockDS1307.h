/* 
 * File:   RealTimeClockDS1307.h
 * Author: anaal
 *
 * Created on July 1, 2025, 1:28 PM
 */

#ifndef REALTIMECLOCKDS1307_H
#define	REALTIMECLOCKDS1307_H

#include <stdint.h>
#include <stdbool.h>
#include "../../mcc_generated_files/system/system.h"
#include "../UART_LoggingDebugData/UART_LoggingDebugData.h"


typedef struct{
    uint8_t _Hour ;
    uint8_t _Minutes;
    uint8_t _Second;
    uint8_t _Year;
    uint8_t _Month;
    uint8_t _Day;
}RealTimeClockDS1307_T;

RealTimeClockDS1307_T RealTimeClock_Get_Time_Date(void);
void Print_RealTimeClock_Pack_Date(void);
#endif	/* REALTIMECLOCKDS1307_H */

