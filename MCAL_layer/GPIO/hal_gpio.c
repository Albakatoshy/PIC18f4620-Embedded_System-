#include "hal_gpio.h"

volatile uint8 *tris_register[]={&TRISA ,&TRISB,&TRISC ,&TRISD ,&TRISE};
volatile uint8 *lat_register[]={&LATA ,&LATB,&LATC ,&LATD ,&LATE};
volatile uint8 *port_register[]={&PORTA ,&PORTB,&PORTC ,&PORTD ,&PORTE};


    



/** 
 * 
 * @param _pin_config
 * @return 
 */
#if GPIO_PORT_PIN_CONFIGURATION==CONFIG_ENABLE
Std_ReturnType gpio_pin_direction_intialize (const pin_config_t *_pin_config){
    Std_ReturnType ret= E_OK;
    
    if (_pin_config==NULL  || _pin_config->pin > PORT_PIN_MAX_NUMBER-1){
        ret=E_NOT_OK;
    }
    else{
        switch (_pin_config->direction){
                case GPIO_DIRECTION_OUTPUT:
                    CLEAR_BIT(*tris_register[_pin_config->port],_pin_config->pin);
                    break;
                case GPIO_DIRECTION_INPUT:
                    SET_BIT(*tris_register[_pin_config->port],_pin_config->pin);
                    break;        
                default:
                    ret= E_NOT_OK;
        }
    }
    return    ret ;     
    }
#endif
    
/**
 * 
 * @param _pin_config
 * @param dir_status
 * @return 
 */
#if GPIO_PORT_PIN_CONFIGURATION==CONFIG_ENABLE
Std_ReturnType gpio_pin_get_direction_status (const pin_config_t *_pin_config ,direction_t *dir_status ){
    Std_ReturnType ret = E_OK;
    
    if (NULL == _pin_config || NULL == dir_status || _pin_config->pin > PORT_PIN_MAX_NUMBER-1)
    {
         ret = E_NOT_OK;
    }
    else
    {
        *dir_status = READ_BIT(*tris_register[_pin_config->port],_pin_config->pin);
        
    }
    
    return    ret ;
    
}
#endif
/**
 * 
 * @param _pin_config
 * @param logic
 * @return 
 */
#if GPIO_PORT_PIN_CONFIGURATION==CONFIG_ENABLE
Std_ReturnType gpio_pin_write_logic (const pin_config_t *_pin_config,logic_t logic){
    Std_ReturnType ret = E_OK;
    
    if (NULL == _pin_config || _pin_config->pin > PORT_PIN_MAX_NUMBER-1 )
    {
         ret = E_NOT_OK;
    }
    else
    {
        switch(logic){
            case GPIO_HIGH:
                SET_BIT(*lat_register[_pin_config->port],_pin_config->pin);
                break;
            case GPIO_LOW:
                CLEAR_BIT(*lat_register[_pin_config->port],_pin_config->pin);
                break;
            default: ret =E_NOT_OK;
        }
    }
    
    return    ret ;
}
#endif
/**
 * 
 * @param _pin_config
 * @param logic
 * @return 
 */
#if GPIO_PORT_PIN_CONFIGURATION==CONFIG_ENABLE
Std_ReturnType gpio_pin_read_logic (const pin_config_t *_pin_config,logic_t *logic){
    Std_ReturnType ret = E_OK;
    
    if (NULL == _pin_config || NULL == logic || _pin_config->pin > PORT_PIN_MAX_NUMBER-1)
    {
         ret = E_NOT_OK;
    }
    else
    {
        *logic = READ_BIT(*port_register[_pin_config->port],_pin_config->pin);
    }
    
    return    ret ;
}
#endif
/**
 * 
 * @param _pin_config
 * @return 
 */
#if GPIO_PORT_PIN_CONFIGURATION==CONFIG_ENABLE
Std_ReturnType gpio_pin_toggle_logic (const pin_config_t *_pin_config){
    Std_ReturnType ret = E_OK;
    
    if (NULL == _pin_config  || _pin_config->pin > PORT_PIN_MAX_NUMBER-1  )
    {
         ret = E_NOT_OK;
    }
    else
    {
        TOGGLE_BIT(*lat_register[_pin_config->port],_pin_config->pin);
    }
    
    return    ret ;
}
#endif
#if GPIO_PORT_PIN_CONFIGURATION==CONFIG_ENABLE
Std_ReturnType gpio_pin_intialize (const pin_config_t *_pin_config){
    Std_ReturnType ret = E_OK;
    
    if (NULL == _pin_config  || _pin_config->pin > PORT_PIN_MAX_NUMBER-1  )
    {
         ret = E_NOT_OK;
    }
    else
    {
        ret =gpio_pin_direction_intialize(_pin_config);
        ret =gpio_pin_write_logic(_pin_config,_pin_config->logic);
    }
    
    return    ret ;
}
#endif


#if GPIO_PORT_CONFIGURATION==CONFIG_ENABLE
Std_ReturnType gpio_port_direction_intialize (port_index_t port , uint8 direction ){
    Std_ReturnType ret = E_OK;
    if (port>PORT_MAX_NUMBER-1){
        ret = E_NOT_OK;
        
    }
    else{
        *tris_register[port]=direction;
    }
    
    
    return    ret ;
}

#endif
/**
 * 
 * @param port
 * @param dir_status
 * @return 
 */
#if GPIO_PORT_CONFIGURATION==CONFIG_ENABLE
Std_ReturnType gpio_port_get_direction_status (port_index_t port,uint8 *dir_status  ){
    Std_ReturnType ret = E_OK;
    
    if ((NULL == dir_status) && (port>PORT_MAX_NUMBER-1) )
    {
         ret = E_NOT_OK;
    }
    else
    {
    *dir_status=*tris_register[port]; 
    }
    
    
    return    ret ;
}
#endif

/**
 * 
 * @param port
 * @param logic
 * @return 
 */
#if GPIO_PORT_CONFIGURATION==CONFIG_ENABLE
Std_ReturnType gpio_port_write_logic (port_index_t port, uint8 logic){
    Std_ReturnType ret = E_OK;
    if ((port > PORT_MAX_NUMBER-1))
    {
         ret = E_NOT_OK;
    }
    else
    {
        *lat_register[port] = logic ; 
    }
    
    
    return    ret ;
}
#endif
/**
 * 
 * @param port
 * @param logic
 * @return 
 */

#if GPIO_PORT_CONFIGURATION==CONFIG_ENABLE
Std_ReturnType gpio_port_read_logic (port_index_t port, uint8 *logic){
    Std_ReturnType ret = E_OK;
    
    if ((NULL == logic )&& (port > PORT_MAX_NUMBER-1))
    {
         ret = E_NOT_OK;
    }
    else
    {
        *logic=*lat_register[port];
        
    }
    
    
    return    ret ;
}
#endif

/**
 * 
 * @param port
 * @return 
 */
#if GPIO_PORT_CONFIGURATION==CONFIG_ENABLE
Std_ReturnType gpio_port_toggle_logic (port_index_t port){
    Std_ReturnType ret = E_OK;
    if ( (port > PORT_MAX_NUMBER-1))
    {
         ret = E_NOT_OK;
    }
    else
    {
        *lat_register[port]^= PORT_MASK ;
        
    }
    
    
    return    ret ;
}
#endif