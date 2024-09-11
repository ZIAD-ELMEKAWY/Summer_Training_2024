/* 
 * File:   hal_ADC.h
 * Author: Ziad Elmekawy
 *
 * Created on 26 July, 2024, 04:34 
 */

#ifndef HAL_ADC_H
#define	HAL_ADC_H

/* Section : includes */
#include "hal_ADC_cfg.h"
#include "../../MCAL_Layer/GPIO/hal_GPIO.h"
#include "../MCAL_std_Types.h"
#include "pic18f4620.h"
#include "../../MCAL_Layer/Interrupt/mcal_internal_interrupt.h"

/*************************** Section : Macro Declarations ***************************/
#define ADC_AN0_ANALOG_FUNCTIONALITY  0X0E
#define ADC_AN1_ANALOG_FUNCTIONALITY  0X0D
#define ADC_AN2_ANALOG_FUNCTIONALITY  0X0C
#define ADC_AN3_ANALOG_FUNCTIONALITY  0X0B
#define ADC_AN4_ANALOG_FUNCTIONALITY  0X0A
#define ADC_AN5_ANALOG_FUNCTIONALITY  0X09
#define ADC_AN6_ANALOG_FUNCTIONALITY  0X08
#define ADC_AN7_ANALOG_FUNCTIONALITY  0X07
#define ADC_AN8_ANALOG_FUNCTIONALITY  0X06
#define ADC_AN9_ANALOG_FUNCTIONALITY  0X05
#define ADC_AN10_ANALOG_FUNCTIONALITY 0X04
#define ADC_AN11_ANALOG_FUNCTIONALITY 0X03
#define ADC_AN12_ANALOG_FUNCTIONALITY 0X02
#define ADC_ALL_ANALOG_FUNCTIONALITY  0X01
#define ADC_ALL_DIGITAL_FUNCTIONALITY 0X0F

#define ADC_RESULT_RIGHT 0x01U
#define ADC_RESULT_LEFT  0x00U

#define ADC_VOLTAGE_REFRENCE_ENABLE  0x01U
#define ADC_VOLTAGE_REFRENCE_DISABLE 0x00U

#define ADC_CONVERSION_COMPLETED    1
#define ADC_CONVERSION_INPROGRESS   0

/*************************** Section : Macro Function Declarations ***************************/
/* A/D Conversion Status : A/D conversion in progress / A/D Idle */
#define ADC_CONVERSION_STATUS()     (ADCON0bits.GO_nDONE)
/*
 * @NOTE    1) ADC_CONVERTER_ENABLE() -> enable the analog-to-digital
 *          2) ADC_CONVERTER_DISABLE() -> disable the analog-to-digital
 */
#define ADC_CONVERTER_ENABLE()          (ADCON0bits.ADON = 1)
#define ADC_CONVERTER_DISABLE()         (ADCON0bits.ADON = 0)
/*
 * @brief Voltage refrence configuration
 * @note  ADC_ENABLE_VOLTAGE_REFRENCE()  : voltage refrence is Vref- & Vref+
 *        ADC_DISABLE_VOLTAGE_REFRENCE() : voltage refrence is VSS   & VDD
 */
#define ADC_ENABLE_VOLTAGE_REFRENCE()   do{ADCON1bits.VCFG1 = 1 ;\
                                           ADCON1bits.VCFG0 = 1 ;\              
                                          }while(0)
#define ADC_DISABLE_VOLTAGE_REFRENCE()  do{ADCON1bits.VCFG1 = 0 ;\
                                           ADCON1bits.VCFG0 = 0 ;\              
                                          }while(0)
/*
 * @BRIEF  ADC_START_CONVERSION()   -> start the analog-to-digital 
 */    
#define ADC_START_CONVERSION()      (ADCON0bits.GODONE = 1)
/*
 *  @BRIEF  Analog-To-Digital port configuration control 
 *  @note   Example : ADC_ANALOG_DIGITAL_PORT_CONFIG(ADC_AN0_ANALOG_FUNCTIONALITY);
 *                    when ADC_AN4_ANALOG_FUNCTIONALITY is configured, this means 
 *                    AN4, AN3, AN2, AN1, AN0 are analog functionality.
 *  @ref    Analog-To-Digital Port Configuration Control 
 */
#define ADC_ANALOG_DIGITAL_PORT_CONFIG(_CONFIG) (ADCON1bits.PCFG = _CONFIG)
/*
 *  @ref    A/D Result Format Select 
 */
#define ADC_RESULT_RIGHT_FORMAT()       (ADCON2bits.ADFM = 1)                                                   
#define ADC_RESULT_LEFT_FORMAT()       (ADCON2bits.ADFM = 0)

                                              
/******************** Section : Data Type Declarations ********************/
/*
 * @BRIEF Analog Channel Select
 */
typedef enum 
{
    ADC_CHANNEL_AN0 = 0 ,
    ADC_CHANNEL_AN1 ,
    ADC_CHANNEL_AN2 ,
    ADC_CHANNEL_AN3 ,
    ADC_CHANNEL_AN4 ,
    ADC_CHANNEL_AN5 ,
    ADC_CHANNEL_AN6 ,
    ADC_CHANNEL_AN7 ,
    ADC_CHANNEL_AN8 ,
    ADC_CHANNEL_AN9 ,
    ADC_CHANNEL_AN10 ,
    ADC_CHANNEL_AN11 ,
    ADC_CHANNEL_AN12       
}adc_channel_select_t;

/*
 * @BRIEF ADC acquisition time_t
 */
typedef enum 
{
    ADC_0_TAD = 0 ,
    ADC_2_TAD ,
    ADC_4_TAD ,
    ADC_6_TAD ,
    ADC_8_TAD ,
    ADC_12_TAD ,
    ADC_16_TAD ,
    ADC_20_TAD 
}adc_acquisition_time_t;

/*
 * @BRIEF ADC conversion clock t
 */
typedef enum 
{
    ADC_CONVERSION_CLOCK_FOSC_DIV_2 = 0 ,
    ADC_CONVERSION_CLOCK_FOSC_DIV_8 ,
    ADC_CONVERSION_CLOCK_FOSC_DIV_32 ,
    ADC_CONVERSION_CLOCK_FOSC_DIV_FRC ,
    ADC_CONVERSION_CLOCK_FOSC_DIV_4 ,
    ADC_CONVERSION_CLOCK_FOSC_DIV_16 ,
    ADC_CONVERSION_CLOCK_FOSC_DIV_64 
}adc_conversion_clock_t;

typedef struct
{
#if _ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    void (* ADC_InterruptHandler)(void);
    interrupt_periority_cfg priority ;
#endif
    
    adc_acquisition_time_t  acquisition_time ; /* @ref adc_acquisition_time_t */
    adc_conversion_clock_t  conversion_clock ; /* @ref adc_conversion_clock_t */
    adc_channel_select_t     adc_channel     ; /* @ref adc_channel_select_t */   
    uint8 voltage_reference : 1 ;              /* Voltage Reference configuration */
    uint8 result_format    : 1 ;               /* A/D Result format select */ 
    uint8 ADC_Reserved     : 6 ;
}adc_config_t;
/*************************** Section : Function Declarations ***************************/
Std_ReturnType ADC_Init     (const adc_config_t *adc);
Std_ReturnType ADC_DeInit   (const adc_config_t *adc);
Std_ReturnType ADC_Select_Channel     (const adc_config_t *adc , adc_channel_select_t channel);
Std_ReturnType ADC_Start_Conversion   (const adc_config_t *adc);
Std_ReturnType ADC_IsConversionDone   (const adc_config_t *adc , uint8 *conversion_status);
Std_ReturnType ADC_GetConversionResult       (const adc_config_t *adc , uint16 *conversion_result);
Std_ReturnType ADC_GetConversion_Blocking    (const adc_config_t *adc , uint16 *conversion_result , adc_channel_select_t channel);
Std_ReturnType ADC_StartConversion_Interrupt (const adc_config_t *adc , adc_channel_select_t channel);


#endif	/* HAL_ADC_H */

