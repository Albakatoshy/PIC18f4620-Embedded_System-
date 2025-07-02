#include "RealTimeClockDS1307.h"


static RealTimeClockDS1307_T RealTimeClockDS1307;
static uint8_t RealTimeClock_Pack[32]; // Enough space for the full formatted date

// Helper: Convert BCD to Decimal
static uint8_t BCD_To_Dec(uint8_t bcd_value) {
    return ((bcd_value >> 4) * 10) + (bcd_value & 0x0F);
}

// Helper: Convert a number (0?99) to ASCII and insert into buffer
static void Convert_To_ASCII(uint8_t value, uint8_t *buffer, uint8_t *index) {
    buffer[(*index)++] = '0' + (value / 10);
    buffer[(*index)++] = '0' + (value % 10);
}

RealTimeClockDS1307_T RealTimeClock_Get_Time_Date(void) {
    RealTimeClockDS1307._Second = BCD_To_Dec(I2C1_Read1ByteRegister(0x68, 0x00));
    RealTimeClockDS1307._Minutes = BCD_To_Dec(I2C1_Read1ByteRegister(0x68, 0x01));
    RealTimeClockDS1307._Hour   = BCD_To_Dec(I2C1_Read1ByteRegister(0x68, 0x02));
    RealTimeClockDS1307._Day    = BCD_To_Dec(I2C1_Read1ByteRegister(0x68, 0x04));
    RealTimeClockDS1307._Month  = BCD_To_Dec(I2C1_Read1ByteRegister(0x68, 0x05));
    RealTimeClockDS1307._Year   = BCD_To_Dec(I2C1_Read1ByteRegister(0x68, 0x06));
    return RealTimeClockDS1307;
}

void Print_RealTimeClock_Pack_Date(void) {
    uint8_t index = 0;

    // Refresh clock values
    RealTimeClock_Get_Time_Date();

    Convert_To_ASCII(RealTimeClockDS1307._Year, RealTimeClock_Pack, &index);
    RealTimeClock_Pack[index++] = ':';

    Convert_To_ASCII(RealTimeClockDS1307._Month, RealTimeClock_Pack, &index);
    RealTimeClock_Pack[index++] = ':';

    Convert_To_ASCII(RealTimeClockDS1307._Day, RealTimeClock_Pack, &index);
    RealTimeClock_Pack[index++] = ':';

    Convert_To_ASCII(RealTimeClockDS1307._Hour, RealTimeClock_Pack, &index);
    RealTimeClock_Pack[index++] = ':';

    Convert_To_ASCII(RealTimeClockDS1307._Minutes, RealTimeClock_Pack, &index);
    RealTimeClock_Pack[index++] = ':';

    Convert_To_ASCII(RealTimeClockDS1307._Second, RealTimeClock_Pack, &index);

    RealTimeClock_Pack[index++] = '\r';
    RealTimeClock_Pack[index++] = '\n';
    RealTimeClock_Pack[index] = '\0'; // Null-terminate

    UART_LoggingDebugData_Send_String("Date:\r\n", 7);
    UART_LoggingDebugData_Send_String(RealTimeClock_Pack, index);
}
