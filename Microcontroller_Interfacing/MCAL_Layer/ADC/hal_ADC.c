/* 
 * File:   hal_ADC.c
 * Author: Ziad Elmekawy
 *
 * Created on 26 July, 2024, 04:34 
 */

/************************ Section : Includes *********************/
#include <pic18f4620.h>
#include "hal_ADC.h"

/********************** Section : Global Variables  *******************/
#if _ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
static void (* ADC_InterruptHandler)(void) = NULL ;

#endif
/************** Section : Helper Function Declarations *******************/
static inline void ADC_input_channel_port_cnfigure (adc_channel_select_t channel );
static inline void ADC_Select_Result_Format (const adc_config_t *adc );
static inline void ADC_Configure_Voltage_Refrence (const adc_config_t *adc );

/************** Section : Function Definitions *******************/
/**
 * 
 * @param adc
 * @return Std_ReturnType
 */
Std_ReturnType ADC_Init     (const adc_config_t *adc)
{
    Std_ReturnType ret = E_NOK ;
    if (NULL == adc)
    {
        ret = E_NOK ;
    }
    else
    {
        /* Disable the ADC */
        ADC_CONVERTER_DISABLE();
        /* Configure the acquisition time */
        ADCON2bits.ACQT = (adc->acquisition_time) ;
        /* configure the conversion clock */
        ADCON2bits.ADCS = (adc->conversion_clock);
        /* Configure the default channel */
        ADCON0bits.CHS = (adc->adc_channel);
        ADC_input_channel_port_cnfigure(adc->adc_channel);
        /* Configure the interrupt */
#if _ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        /* @NOTE    --> We must enable the ( Global & Peripheral ) interrupt before the ADC interrupt to work*/
        ADC_InterruptEnable();
        ADC_InterruptFlagClear();
#ifdef _INTERRUPT_PERIORITY_LEVELS_ENABLE 
        if(INTERRUPT_HIGH_PRIORITY == (adc->priority)){ ADC_HighPrioritySet(); }
        else if(INTERRUPT_LOW_PRIORITY == (adc->priority)) { ADC_LowPrioritySet(); }
        else { /* Nothing */}
#else 
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
#endif
        ADC_InterruptHandler = (adc->ADC_InterruptHandler) ;
#endif
        /* Configure the result format */
        ADC_Select_Result_Format(adc);
        /* Configure the voltage reference */
        ADC_Configure_Voltage_Refrence(adc);
        /* Enable the ADC */
        ADC_CONVERTER_ENABLE();
        ret = E_OK ;
    }
    return ret ;
}

/**
 * 
 * @param adc
 * @return Std_ReturnType
 */
Std_ReturnType ADC_DeInit   (const adc_config_t *adc)
{
    Std_ReturnType ret = E_NOK ;
    if (NULL == adc)
    {
        ret = E_NOK ;
    }
    else
    {
        /* Disable the ADC */
        ADC_CONVERTER_DISABLE();
        /* Disable the interrupt */
        #if _ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        ADC_InterruptDisable();
        #endif
        ret = E_OK ;
    }
    return ret ;
}

/**
 * 
 * @param adc
 * @param channel
 * @return Std_ReturnType
 */
Std_ReturnType ADC_Select_Channel     (const adc_config_t *adc , adc_channel_select_t channel)
{
    Std_ReturnType ret = E_NOK ;
    if (NULL == adc)
    {
        ret = E_NOK ;
    }
    else
    {
        /* Configure the default channel */
        ADCON0bits.CHS = channel;
        ADC_input_channel_port_cnfigure(channel);
        ret = E_OK ;
    }
    return ret ;
}

/**
 * 
 * @param adc
 * @return Std_ReturnType
 */
Std_ReturnType ADC_Start_Conversion   (const adc_config_t *adc)
{
    Std_ReturnType ret = E_NOK ;
    if (NULL == adc)
    {
        ret = E_NOK ;
    }
    else
    {
        ADC_START_CONVERSION(); 
        ret = E_OK ;
    }
    return ret ;
}

/**
 * @description conversion_status : if return True  : ADC conversion is complete
 *                                  if return False : ADC conversion is not complete 
 * @param adc
 * @param conversion_status
 * @return Std_ReturnType
 */
Std_ReturnType ADC_IsConversionDone   (const adc_config_t *adc , uint8 *conversion_status)
{
    Std_ReturnType ret = E_NOK ;
    if ((NULL == adc) || (NULL == conversion_status))
    {
        ret = E_NOK ;
    }
    else
    {
        *conversion_status = (uint8)(!(ADCON0bits.GO_nDONE)) ;
        ret = E_OK ;
    }
    return ret ;
}

/**
 * 
 * @param adc
 * @param conversion_result
 * @return Std_ReturnType
 */
Std_ReturnType ADC_GetConversionResult   (const adc_config_t *adc , uint16 *conversion_result)
{
    Std_ReturnType ret = E_NOK ;
    if ((NULL == adc) || (NULL == conversion_result))
    {
        ret = E_NOK ;
    }
    else
    {
        if ((adc->result_format) == ADC_RESULT_RIGHT )
        {
            *conversion_result = (uint16)((ADRESH<<8) + ADRESL);
        }
        else if ((adc->result_format) == ADC_RESULT_LEFT)
        {
            *conversion_result = (uint16)(((ADRESH<<8) + ADRESL)>>6);
        }
        else
        {
            *conversion_result = (uint16)((ADRESH<<8) + ADRESL);
        }
        ret = E_OK ;
    }
    return ret ;
}

/**
 * 
 * @param adc
 * @param conversion_status
 * @param channel
 * @return Std_ReturnType
 */
Std_ReturnType ADC_GetConversion_Blocking   (const adc_config_t *adc , uint16 *conversion_result , adc_channel_select_t channel)
{
    Std_ReturnType ret = E_NOK ;
    uint8 l_conversion_status = 0 ;
    if ((NULL == adc) || (NULL == conversion_result))
    {
        ret = E_NOK ;
    }
    else
    {
        /* Select A/D Channel */
        ret = ADC_Select_Channel(adc , channel);
        /* Start ADC conversion */
        ret = ADC_Start_Conversion(adc);
        /* check A/D conversion is complete or not */
        while(ADCON0bits.GO_nDONE); /* Block until finish conversion */
        ret = ADC_GetConversionResult(adc , conversion_result);
    }
    return ret ;
}

/**
 * 
 * @param adc
 * @param conversion_result
 * @param channel
 * @return 
 */
Std_ReturnType ADC_StartConversion_Interrupt   (const adc_config_t *adc , adc_channel_select_t channel)
{
    Std_ReturnType ret = E_NOK ;
    uint8 l_conversion_status = 0 ;
    if ((NULL == adc))
    {
        ret = E_NOK ;
    }
    else
    {
        /* Select A/D Channel */
        ret = ADC_Select_Channel(adc , channel);
        /* Start ADC conversion */
        ret = ADC_Start_Conversion(adc);
    }
    return ret ;
}
/************** Section : Helper Function Definitions *******************/
static inline void ADC_input_channel_port_cnfigure ( adc_channel_select_t channel)
{
    switch(channel)
    {
        case ADC_CHANNEL_AN0 : SET_BIT(TRISA , _TRISA_RA0_POSN); break ; /* 0 for Rx0*/
        case ADC_CHANNEL_AN1 : SET_BIT(TRISA , _TRISA_RA1_POSN); break ; /* 1 for Rx1*/
        case ADC_CHANNEL_AN2 : SET_BIT(TRISA , _TRISA_RA2_POSN); break ; /* 2 for Rx2*/
        case ADC_CHANNEL_AN3 : SET_BIT(TRISA , _TRISA_RA3_POSN); break ;
        case ADC_CHANNEL_AN4 : SET_BIT(TRISA , _TRISA_RA5_POSN); break ;
        case ADC_CHANNEL_AN5 : SET_BIT(TRISA , _TRISA_RA0_POSN); break ;
        case ADC_CHANNEL_AN6 : SET_BIT(TRISA , _TRISA_RA1_POSN); break ;
        case ADC_CHANNEL_AN7 : SET_BIT(TRISA , _TRISA_RA2_POSN); break ;
        case ADC_CHANNEL_AN8 : SET_BIT(TRISA , _TRISA_RA2_POSN); break ;
        case ADC_CHANNEL_AN9 : SET_BIT(TRISA , _TRISA_RA3_POSN); break ;
        case ADC_CHANNEL_AN10 : SET_BIT(TRISA , _TRISA_RA1_POSN); break ;
        case ADC_CHANNEL_AN11 : SET_BIT(TRISA , _TRISA_RA4_POSN); break ;
        case ADC_CHANNEL_AN12 : SET_BIT(TRISA , _TRISA_RA0_POSN); break ;
    }
}

static inline void ADC_Select_Result_Format (const adc_config_t *adc )
{
    if ((adc->result_format) == ADC_RESULT_RIGHT )
    {
        ADC_RESULT_RIGHT_FORMAT();
    }
    else if ((adc->result_format) == ADC_RESULT_LEFT)
    {
        ADC_RESULT_LEFT_FORMAT();
    }
    else
    {
        ADC_RESULT_RIGHT_FORMAT();
    }
}

static inline void ADC_Configure_Voltage_Refrence (const adc_config_t *adc )
{
    if ((adc->voltage_reference) == ADC_VOLTAGE_REFRENCE_ENABLE )
    {
        ADC_ENABLE_VOLTAGE_REFRENCE();
    }
    else if ((adc->voltage_reference) == ADC_VOLTAGE_REFRENCE_DISABLE)
    {
        ADC_DISABLE_VOLTAGE_REFRENCE();
    }
    else
    {
        ADC_DISABLE_VOLTAGE_REFRENCE();
    }
}

/***************************** ISR ***************************/
void ADC_ISR (void )
{
    ADC_InterruptFlagClear();
    if(ADC_InterruptHandler)
    {
        ADC_InterruptHandler();
    }
}