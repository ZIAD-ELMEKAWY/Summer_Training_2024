/* 
 * File:   ecu_buzzer.c
 * Author: Ziad Elmekawy
 *
 * Created on 16 August 2024, 11:58 
 */

/*Section: Includes */
#include "ecu_buzzer.h"

/*********************** Section:  function Definition ************************/
/**
 * @name  buz_intialize
 * @brief Initialized the assigned pin to be output and turn the buzzer off
 * @param buz
 * @return status of the function 
 *          (E_OK) : the function done successfully
 *          (E_NOK): the function has issue while performing this action
 */
#if GPIO_PORT_PIN_CONFIGURATIONS==CONFIG_ENABLE 
Std_ReturnType buz_intialize(const buz_t *buz)
{
    Std_ReturnType ret = E_OK;
    
    if(NULL == buz)
    {
        ret = E_NOK;
    }
    else
    {
        pin_config_t pin_obj = 
        {
        .port = buz->port_name , 
        .pin = buz->pin , 
        .direction= GPIO_DIRECTION_OUTPUT , 
        .logic = buz->buz_status 
        };
        ret = gpio_pin_intialize(&pin_obj);
    }
    return ret ;
}
#endif

/**
 * @name  buz_turn_on
 * @brief Turn the buzzer on
 * @param buz
 * @return status of the function 
 *          (E_OK) : the function done successfully
 *          (E_NOK): the function has issue while performing this action
 */
#if GPIO_PORT_PIN_CONFIGURATIONS==CONFIG_ENABLE
Std_ReturnType buz_turn_on  (const buz_t *buz)
{
    Std_ReturnType ret = E_OK;
    if(NULL == buz)
    {
        ret = E_NOK;
    }
    else
    {
        pin_config_t pin_obj = 
        {
        .port = buz->port_name , 
        .pin = buz->pin , 
        .direction= GPIO_DIRECTION_OUTPUT , 
        .logic = buz->buz_status 
        };
        gpio_pin_write_logic(&pin_obj , GPIO_HIGH);
    }
    return ret ;
}
#endif

/**
 * @name  buz_turn_off
 * @brief Turn the buzzer off
 * @param buz
 * @return status of the function 
 *          (E_OK) : the function done successfully
 *          (E_NOK): the function has issue while performing this action
 */
#if GPIO_PORT_PIN_CONFIGURATIONS==CONFIG_ENABLE
Std_ReturnType buz_turn_off (const buz_t *buz)
{
    Std_ReturnType ret = E_OK;
    if(NULL == buz)
    {
        ret = E_NOK;
    }
    else
    {
        pin_config_t pin_obj = 
        {
        .port = buz->port_name , 
        .pin = buz->pin , 
        .direction= GPIO_DIRECTION_OUTPUT , 
        .logic = buz->buz_status 
        };
        ret = gpio_pin_write_logic(&pin_obj , GPIO_LOW);
    }
    return ret ;
}
#endif

/**
 * @name  buz_toggle
 * @brief Toggle the buzzer
 * @param buz
 * @return status of the function 
 *          (E_OK) : the function done successfully
 *          (E_NOK): the function has issue while performing this action
 */
#if GPIO_PORT_PIN_CONFIGURATIONS==CONFIG_ENABLE
Std_ReturnType buz_toggle   (const buz_t *buz)
{
    Std_ReturnType ret = E_OK;
    if(NULL == buz)
    {
        ret = E_NOK;
    }
    else
    {
        pin_config_t pin_obj = 
        {
        .port = buz->port_name , 
        .pin = buz->pin , 
        .direction= GPIO_DIRECTION_OUTPUT , 
        .logic = buz->buz_status 
        };
        ret = gpio_pin_toggle_logic(&pin_obj);
    }
    return ret ;
}
#endif


