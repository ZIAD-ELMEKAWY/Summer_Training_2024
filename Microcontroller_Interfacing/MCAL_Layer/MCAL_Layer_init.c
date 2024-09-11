/* 
 * File:   MCAL_Layer_init.c
 * Author: Ziad Elmekawy
 *
 * Created on 28 July, 2024, 07:24 ?
 */

/******************* Section : Includes *****************/
#include "MCAL_Layer_init.h"

/***************************   Global Variables ****************************/

/*************************** Helper Function definitions *******************/



/******************* Section : Objects *****************/
/*==================== ADC Object =====================*/
/*
adc_config_t adc_1 =
{
   .ADC_InterruptHandler = NULL ,
   .acquisition_time = ADC_12_TAD ,
   .adc_channel = ADC_CHANNEL_AN0 ,
   .conversion_clock = ADC_CONVERSION_CLOCK_FOSC_DIV_16 , 
   .result_format = ADC_RESULT_RIGHT ,
   .voltage_reference = ADC_VOLTAGE_REFRENCE_DISABLE
};

adc_config_t adc_2 =
{
   .ADC_InterruptHandler = NULL ,
   .acquisition_time = ADC_12_TAD ,
   .adc_channel = ADC_CHANNEL_AN1 ,
   .conversion_clock = ADC_CONVERSION_CLOCK_FOSC_DIV_16 , 
   .result_format = ADC_RESULT_RIGHT ,
   .voltage_reference = ADC_VOLTAGE_REFRENCE_DISABLE
};

adc_config_t adc_3 =
{
   .ADC_InterruptHandler = NULL ,
   .acquisition_time = ADC_12_TAD ,
   .adc_channel = ADC_CHANNEL_AN0 ,
   .conversion_clock = ADC_CONVERSION_CLOCK_FOSC_DIV_16 , 
   .result_format = ADC_RESULT_RIGHT ,
   .voltage_reference = ADC_VOLTAGE_REFRENCE_DISABLE
};

adc_config_t adc_4 =
{
   .ADC_InterruptHandler = NULL ,
   .acquisition_time = ADC_12_TAD ,
   .adc_channel = ADC_CHANNEL_AN0 ,
   .conversion_clock = ADC_CONVERSION_CLOCK_FOSC_DIV_16 , 
   .result_format = ADC_RESULT_RIGHT ,
   .voltage_reference = ADC_VOLTAGE_REFRENCE_DISABLE
};
*/
/*================== Interrupt Object ================*/
/*
interrupt_INTx_t int0_obj = 
{
    .EXT_InterruptHandler = Int0_App_ISR ,
    .edge = INTERRUPT_RISING_EDGE ,
    .priority = INTERRUPT_HIGH_PRIORITY ,
    .source = INTERRUPT_EXTERNAL_INT0 ,
    .mcu_pin.port = PORTB_INDEX ,
    .mcu_pin.pin = PIN0 ,
    .mcu_pin.direction = GPIO_DIRECTION_INPUT 
};

interrupt_INTx_t int1_obj = 
{
    .EXT_InterruptHandler = Int1_App_ISR ,
    .edge = INTERRUPT_RISING_EDGE ,
    .priority = INTERRUPT_LOW_PRIORITY ,
    .source = INTERRUPT_EXTERNAL_INT1 ,
    .mcu_pin.port = PORTB_INDEX ,
    .mcu_pin.pin = PIN1 ,
    .mcu_pin.direction = GPIO_DIRECTION_INPUT 
};

interrupt_INTx_t int2_obj = 
{
    .EXT_InterruptHandler = Int2_App_ISR ,
    .edge = INTERRUPT_RISING_EDGE ,
    .priority = INTERRUPT_HIGH_PRIORITY ,
    .source = INTERRUPT_EXTERNAL_INT2 ,
    .mcu_pin.port = PORTB_INDEX ,
    .mcu_pin.pin = PIN2 ,
    .mcu_pin.direction = GPIO_DIRECTION_INPUT 
};
*/
/*
interrupt_RBx_t rb4_int_obj = 
{
    .EXT_InterruptHandlerHigh = RB4_HIGH_Int_App_ISR ,
    .EXT_InterruptHandlerLow  = RB4_LOW_Int_App_ISR ,
    .priority = INTERRUPT_HIGH_PRIORITY ,
    .mcu_pin.port = PORTB_INDEX ,
    .mcu_pin.pin = PIN4 ,
    .mcu_pin.direction = GPIO_DIRECTION_INPUT 
}; 
*/
/*================== Timer0 Object ================*/
/*
timer0_t timer0_obj =
{
    .TMR0_InterruptHandler = Timer0_DefaultInterruptHandler,
    .timer0_mode = TIMER0_TIMER_MODE ,
    .timer0_register_size = TIMER0_16BIT_REGISTER_MODE ,
    .prescaler_enable = TIMER0_PRESCALER_ENABLE_CFG ,
    .prescaler_value = TIMER0_PRESCALER_DIV_BY_8 ,
    .timer0_preload_value = 3036 
};
*/
/*================== Timer1 Object ================*/
/*
 uint16 timer0_counter_value = 0 ;
volatile uint16 timer1_on = 0 ;
volatile uint16 timer1_val = 0 ;
void Timer1_DefaultInterruptHandler(void)
{
    Std_ReturnType ret = E_NOK ;
    ret = led_toggle(&led_1); 
    timer1_on++;
}

void timer1_timer_init (void)
{
    Std_ReturnType ret = E_NOK ;
    timer1_t timer1_timer_obj ;
    timer1_timer_obj.TMR1_InterruptHandler = Timer1_DefaultInterruptHandler ;
    timer1_timer_obj.periority = INTERRUPT_LOW_PRIORITY ;
    timer1_timer_obj.timer1_mode = TIMER1_TIMER_MODE ;
    timer1_timer_obj.timer1_prescaler_value = TIMER1_PRESCALER_DIV_BY_4 ;
    timer1_timer_obj.timer1_preload_value = 15536 ;
    timer1_timer_obj.timer1_reg_rw_mode = TIMER1_RW_REG_16BIT__MODE ;
    ret = Timer1_Init(&timer1_timer_obj);
}

void timer1_counter_init (void)
{
    timer1_t timer1_counter_obj ;
    timer1_counter_obj.TMR1_InterruptHandler = NULL ;
    timer1_counter_obj.periority = INTERRUPT_LOW_PRIORITY ;
    timer1_counter_obj.timer1_mode = TIMER1_COUNTER_MODE ;
    timer1_counter_obj.timer1_prescaler_value = TIMER1_PRESCALER_DIV_BY_1 ;
    timer1_counter_obj.timer1_preload_value = 0 ;
    timer1_counter_obj.timer1_reg_rw_mode = TIMER1_RW_REG_16BIT__MODE ;
    timer1_counter_obj.timer1_counter_mode = TIMER1_SYNCH_COUNTER_MODE ;
    Timer1_Init(&timer1_counter_obj);
}

 */

/************************* Section : Function Definitions *************/


void mcal_layer_initialize (void) 
{
    Std_ReturnType ret = E_NOK ;
//    ret = ADC_Init(&adc_1) ;
//    ret = Timer0_Init(&timer0_obj);
//    ret = ADC_Init(&adc_2) ;
//    ret = ADC_Init(&adc_3) ;
//    ret = ADC_Init(&adc_4) ;
    //ret =  Interrupt_INTx_Initialize(&int0_obj);
    //ret =  Interrupt_INTx_Initialize(&int1_obj);
    //ret =  Interrupt_INTx_Initialize(&int2_obj);
    //ret = Interrupt_RBx_Initialize(&rb4_int_obj);
}

