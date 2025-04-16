#include <stdio.h>
#include <stdlib.h>
#include "application1.h"
#define _XTAL_FREQ 4000000

led_t led1 = {
    .port_name = PORTC_INDEX,
    .pin = GPIO_PIN0,
    .led_status = GPIO_LOW,
};

button_t btn1 = {
    .button_pin.port = PORTC_INDEX,
    .button_pin.pin = GPIO_PIN2,
    .button_pin.direction = GPIO_DIRECTION_INPUT,
    .button_pin.logic = GPIO_LOW,
    .button_connection = BUTTON_ACTIVE_HIGH,
    .button_state = BUTTON_RELEASED,
};

button_state_t button1_status = BUTTON_RELEASED;
uint8 button1_status_flag = 0;
uint32 btn_high_valid = 0;
button_state_t button1_valid_status = BUTTON_RELEASED;
button_state_t button1_last_valid_status = BUTTON_RELEASED;
led_status_t led1_status = LED_OFF;
Std_ReturnType ret = E_OK;

int main() {
    application_initialize();
    while (1) {
        ret = button_read_state(&btn1, &button1_status);
        if (button1_status == BUTTON_PRESSED) {
            btn_high_valid++;
            if (btn_high_valid > 500) {
                button1_valid_status = BUTTON_PRESSED;
            }
        } else {
            btn_high_valid = 0;
            button1_valid_status = BUTTON_RELEASED;
        }

        if (button1_valid_status != button1_last_valid_status) {
            button1_last_valid_status = button1_valid_status;
            if (button1_valid_status == BUTTON_PRESSED) {
                if (LED_OFF == led1_status) {
                    led_turn_on(&led1);
                    led1_status = LED_ON;
                } else {
                    led_turn_off(&led1);
                    led1_status = LED_OFF;
                }
            }
        }
    }
    return (EXIT_SUCCESS);
}

void application_initialize(void) {
    ret = button_initialze(&btn1);
    ret = led_initialize(&led1);
}
