/* 
 * File:   hal_timer0.h
 * Author: Ziad
 *
 * Created on 16 july, 2024, 07:16 ?
 */

/************************ Section : Includes ************************/
#include "hal_timer0.h"


/************************ Section : Helper Function Declarations ************************/

static inline void Timer0_Prescaler_config (const timer0_t *timer);
static inline void Timer0_Mode_Select (const timer0_t *timer);
static inline void Timer0_Register_Size_config (const timer0_t *timer);

/************************ Section : Function Definitions ************************/
/**
 * 
 * @param timer
 * @return Status of the function 
 *              (E_OK) : The function done successfully
 *              (E_NOK): The function has issue to perform this action
 */
#if _TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    static void (* TMR0_InterruptHandler)(void) = NULL;
#endif
static uint16 timer0_preload = 0 ;

/**
 * @name  Timer0_Initialization
 * @param timer
 * @return Status of the function 
 *              (E_OK) : The function done successfully
 *              (E_NOK): The function has issue to perform this action
 */
Std_ReturnType Timer0_Init (const timer0_t *timer)
{
    Std_ReturnType ret = E_OK ;
    if(timer == NULL)
    {
        ret = E_NOK ;
    }
    else
    {
        TIMER0_MODULE_DISABLE() ;
        Timer0_Prescaler_config(timer);
        Timer0_Mode_Select(timer);
        Timer0_Register_Size_config(timer);
        TMR0H = (timer->timer0_preload_value) >>8 ;
        TMR0L = (uint8)(timer->timer0_preload_value);
        timer0_preload = timer->timer0_preload_value ;
 /* Interrupt Configuration */
#if _TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        TIMER0_InterruptEnable();
        TIMER0_InterruptFlagClear();
        TMR0_InterruptHandler = timer->TMR0_InterruptHandler;
 /* Interrupt Priority configuration */
#if _INTERRUPT_PERIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
        INTERRUPT_PeriortyLevelEnable();
        if (timer->periority == INTERRUPT_HIGH_PRIORITY)
        {
            /* Enable all high-priority interrupts */
            INTERRUPT_GlobalInterruptHighEnable();
            TIMER0_HighPrioritySet();
        }
        else if (timer->periority == INTERRUPT_LOW_PRIORITY)
        {
            /* Enable all unmasked peripheral interrupts */
            INTERRUPT_GlobalInterruptLowEnable();
            TIMER0_LowPrioritySet();
        }
#else 
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
#endif        
#endif
        TIMER0_MODULE_ENABLE() ;
        ret = E_OK ; 
    }
    return ret ;
}

/**
 * @name  Timer0_DeInitialization
 * @param timer
 * @return Status of the function 
 *              (E_OK) : The function done successfully
 *              (E_NOK): The function has issue to perform this action
 */
Std_ReturnType Timer0_DeInit (const timer0_t *timer)
{
    Std_ReturnType ret = E_OK ;
    if(timer == NULL)
    {
        ret = E_NOK ;
    }
    else
    {
#if _TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        TIMER0_InterruptDisable();
#endif
    }
    return ret ;
}

/**
 * @name  Timer0_Write_Value
 * @param timer
 * @param value
 * @return Status of the function 
 *              (E_OK) : The function done successfully
 *              (E_NOK): The function has issue to perform this action
 */
Std_ReturnType Timer0_Write_Value (const timer0_t *timer , uint16 value)
{
    Std_ReturnType ret = E_OK ;
    if(timer == NULL)
    {
        ret = E_NOK ;
    }
    else
    {
        TMR0H = (value) >>8 ;
        TMR0L = (uint8)(value);
    }
    return ret ;
}

/**
 * @name  Timer0_Read_Value
 * @param timer
 * @param value
 * @return Status of the function 
 *              (E_OK) : The function done successfully
 *              (E_NOK): The function has issue to perform this action 
 */
Std_ReturnType Timer0_Read_Value  (const timer0_t *timer , uint16 *value)
{
    Std_ReturnType ret = E_OK ;
    uint8 l_tmr0_low = 0 , l_tmr0_high = 0;
    if((timer == NULL) || (value == NULL))
    {
        ret = E_NOK ;
    }
    else
    {
        l_tmr0_low  = TMR0L ;
        l_tmr0_high = TMR0H ;
        *value = (uint16)((l_tmr0_high<<8)+l_tmr0_low);
    }
    return ret ;
}


/************************ Section : Helper Function Definitions ************************/
/* ===================== Pre-scaler Function ===================*/
/**
 * @name  Timer0_Pre-scaler_configuration 
 * @param timer
 */
static inline void Timer0_Prescaler_config (const timer0_t *timer)
{
    if(TIMER0_PRESCALER_ENABLE_CFG == timer->prescaler_enable)
    {
        TIMER0_PRESCALER_ENABLE();
        T0CONbits.T0PS = timer->prescaler_value;
    }
    else if (TIMER0_PRESCALER_DISABLE_CFG == timer->prescaler_enable)
    {
        TIMER0_PRESCALER_DISABLE();
    }
    else
    { /* Nothing */ }
}

/* ===================== Timer0_Mode Function ===================*/
/**
 * @name  Timer0_Mode_Select
 * @param timer
 */
static inline void Timer0_Mode_Select (const timer0_t *timer)
{
    if(TIMER0_TIMER_MODE == timer->timer0_mode)
    {
        TIMER0_TIMER_MODE_ENABLE();
    }
    else if (TIMER0_COUNTER_MODE == timer->timer0_mode)
    {
        TIMER0_COUNTER_MODE_ENABLE();
        if(TIMER0_COUNTER_RISING_EDGE_CFG == timer->timer0_counter_edge)
        {
            TIMER0_RISING_EDGE_ENABLE();
        }
        else if(TIMER0_COUNTER_FALLING_EDGE_CFG == timer->timer0_counter_edge)
        {
            TIMER0_FALLING_EDGE_ENABLE();
        }
        else
        { /* Nothing */ }
    }
    else
    { /* Nothing */ }
}

/* ===================== Timer0_Register Size Function ===================*/
/**
 * @name  Timer0_Register_Size_configuration
 * @param timer
 */
static inline void Timer0_Register_Size_config (const timer0_t *timer)
{
    if(TIMER0_8BIT_REGISTER_MODE == timer->timer0_register_size)
    {
        TIMER0_8BIT_REGISTER_MODE_ENABLE();
    }
    else if (TIMER0_8BIT_REGISTER_MODE == timer->timer0_register_size)
    {
        TIMER0_16BIT_REGISTER_MODE_ENABLE();
    }
    else
    { /* Nothing */ }
}

/* ===================== ISR Function ====================== */
/**
 * @name TMR0_ISR
 * @return void 
 * @brief 
 */
void TMR0_ISR (void)
{
    TIMER0_InterruptFlagClear();
    /* to return pre-load values to Timer0 register after overflow */
    TMR0H = (timer0_preload) >>8 ;
    TMR0L = (uint8)(timer0_preload);
    if (TMR0_InterruptHandler)
    {
        TMR0_InterruptHandler();
    }
}