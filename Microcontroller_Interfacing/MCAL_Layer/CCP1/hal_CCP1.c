/* 
 * File:   hal_CCP1.c
 * Author: Ziad Elmekawy
 *
 * Created on 07 August, 2024
 */

/********************** Section :  Includes *******************/
#include "hal_CCP1.h"

/********************** Section :  Function Definition  *******************/
#if _CCP1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    static void (*CCP1_InterruptHandler)(void) = NULL;
#endif
#if _CCP2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    static void (*CCP2_InterruptHandler)(void) = NULL;
#endif
    
static void CCP_Interrupt_Config(const ccp_t *ccp_obj) ;
static void CCP_Capture_Mode_Timer_Select(const ccp_t *ccp_obj) ;
static Std_ReturnType CCP_Compare_Mode_Config(const ccp_t *ccp_obj);
static Std_ReturnType CCP_Capture_Mode_Config(const ccp_t *ccp_obj);

/**
 * @name  CCP_Initialization
 * @param ccp1_obj
 * @return Std_ReturnType
 */
Std_ReturnType CCP_Init   (const ccp_t *ccp1_obj)
{
    Std_ReturnType ret = E_NOK ;
    if(ccp1_obj == NULL)
    {
        ret = E_NOK;
    }
    else
    {
        /* === CCP Mode Disable === */
        if(CCP1_INST == ccp1_obj->ccp_inst)
        {
            CCP1_SET_MODE(CCP_MODULE_DISABLE);
        }
        else if (CCP2_INST == ccp1_obj->ccp_inst)
        {
            CCP2_SET_MODE(CCP_MODULE_DISABLE);
        }
        else { /* Nothing */ }
        /* CCP1 Module @Capture Mode Initialization */
        if(CCP_CAPTURE_MODE_SELECTED == ccp1_obj->ccp_mode)
        {
            ret = CCP_Capture_Mode_Config(ccp1_obj);
        }
        /* CCP1 Module @Compare Mode Initialization */
        else if(CCP_COMPARE_MODE_SELECTED == ccp1_obj->ccp_mode)
        {
            ret = CCP_Compare_Mode_Config(ccp1_obj);
        }
        /* CCP Module @PWM Mode Initialization */
        else if(CCP_PWM_MODE_SELECTED == ccp1_obj->ccp_mode)
        {
#if ((CCP1_CFG_MODE_SELECTED == CCP_CFG_PWM_MODE_SELECTED) || (CCP2_CFG_MODE_SELECTED == CCP_CFG_PWM_MODE_SELECTED))
            if(CCP1_INST == ccp1_obj->ccp_inst)
            {
                if( CCP_PWM_MODE == ccp1_obj->CCP_mode_variant)
                {
                    CCP1_SET_MODE(CCP_PWM_MODE);
                }
                else { /* Nothing */ }
            }
            else if (CCP2_INST == ccp1_obj->ccp_inst)
            {
                 if( CCP_PWM_MODE == ccp1_obj->CCP_mode_variant)
                {
                    CCP2_SET_MODE(CCP_PWM_MODE);
                }
                else { /* Nothing */ }
            }
            /* Initialize PWM frequency */
            PR2 = (uint8)((_XTAL_FREQ / 
                  (ccp1_obj->PWM_Frequency * 4.0 * ccp1_obj->prescaler_value * ccp1_obj->postscaler_value))-1);
#endif
        }
        else { /* Nothing */ }
        ret = E_OK ;
    }
    /* Pin Configuration */
    ret = gpio_pin_intialize(&(ccp1_obj->CCP_pin));
    /* CCP Interrupt Configuration for CCP1 and CCP2 Module */
    CCP_Interrupt_Config(ccp1_obj);
    return ret ;
}

/**
 * @name  CCP_DeInitialization
 * @param ccp1_obj
 * @return 
 */
Std_ReturnType CCP_DeInit (const ccp_t *ccp1_obj)
{
    Std_ReturnType ret = E_NOK ;
    if(ccp1_obj == NULL)
    {
        ret = E_NOK;
    }
    else
    {
        /* CCP Mode Disable */
        if(CCP1_INST == ccp1_obj->ccp_inst)
        {
            CCP1_SET_MODE(CCP_MODULE_DISABLE); /* CCP1 Module Disable */
        /* Interrupt Configuration */
        #if _CCP1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
            CCP1_InterruptDisable();
        #endif
        }
        else if (CCP2_INST == ccp1_obj->ccp_inst)
        {
            CCP2_SET_MODE(CCP_MODULE_DISABLE); /* CCP2 Module Disable */
            /* Interrupt Configuration */
        #if _CCP2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
            CCP2_InterruptDisable();
        #endif
        }
        else { /* Nothing */ }


        ret = E_OK ;
    }
    return ret ;
}

/* === Compile time switch === */
#if ((CCP1_CFG_MODE_SELECTED == CCP1_CFG_CAPTURE_MODE_SELECTED) || (CCP2_CFG_MODE_SELECTED == CCP1_CFG_CAPTURE_MODE_SELECTED))
/**
 * 
 * @param Capture_Status
 * @return 
 */
Std_ReturnType CCP_IsCaptureDataReady  (uint8 *Capture_Status)
{
    Std_ReturnType ret = E_NOK ;
    if(Capture_Status == NULL)
    {
        ret = E_NOK;
    }
    else
    {
        if ( CCP_CAPTURE_READY == PIR1bits.CCP1IF)
        {
            *Capture_Status = CCP_CAPTURE_READY ;
            CCP1_InterruptFlagClear();
        }
        else 
        {
            *Capture_Status = CCP_CAPTURE_NOT_READY ;
        }
        ret = E_OK ;
    }
    return ret ;
}

/**
 * 
 * @param Capture_Value
 * @return 
 */
Std_ReturnType CCP_CaptureModeReadValue (uint16 *Capture_Value)
{
    Std_ReturnType ret = E_NOK ;
    CCP1_REG_T capture_temp_value  = { .ccpr_low = 0 , .ccpr_high = 0 };
    if(Capture_Value == NULL)
    {
        ret = E_NOK;
    }
    else
    {
        capture_temp_value.ccpr_low = CCPR1L ;
        capture_temp_value.ccpr_high = CCPR1H ;
        *Capture_Value = capture_temp_value.ccpr_16bit;
        ret = E_OK ;
    }
    return ret ;
}
#endif
#if ((CCP1_CFG_MODE_SELECTED == CCP1_CFG_COMPARE_MODE_SELECTED) || (CCP2_CFG_MODE_SELECTED == CCP1_CFG_COMPARE_MODE_SELECTED))
Std_ReturnType CCP_Is_Compare_Complete     (uint8 *compare_status)
{
    Std_ReturnType ret = E_NOK ;
    if(compare_status == NULL)
    {
        ret = E_NOK;
    }
    else
    {
        if ( CCP_COMPARE_READY == PIR1bits.CCP1IF)
        {
            *compare_status = CCP_COMPARE_READY ;
            CCP1_InterruptFlagClear();
        }
        else 
        {
            *compare_status = CCP_COMPARE_NOT_READY ;
        }
        ret = E_OK ;
    }
    return ret ;
}

/**
 * 
 * @param ccp1_obj
 * @param Compare_value
 * @return 
 */
Std_ReturnType CCP_Compare_Mode_Set_Value  (const ccp_t *ccp1_obj , uint16 Compare_value)
{
    Std_ReturnType ret = E_NOK ;
    CCP1_REG_T capture_temp_value  = { .ccpr_low = 0 , .ccpr_high = 0 };
    
    if(NULL == ccp1_obj)
    {
        ret = E_NOK ;
    }
    else 
    {
        capture_temp_value.ccpr_16bit = Compare_value;
        if(CCP1_INST == ccp1_obj->ccp_inst)
        {
            CCPR1L = capture_temp_value.ccpr_low ;
            CCPR1H = capture_temp_value.ccpr_high ;
        }
        else if (CCP2_INST == ccp1_obj->ccp_inst)
        {
            CCPR2L = capture_temp_value.ccpr_low ;
            CCPR2H = capture_temp_value.ccpr_high ;
        }
        else { /* Nothing */ }
        ret = E_OK ;
    }
    return ret ;
}

#endif
#if ((CCP1_CFG_MODE_SELECTED == CCP_CFG_PWM_MODE_SELECTED) || (CCP2_CFG_MODE_SELECTED == CCP_CFG_PWM_MODE_SELECTED))

Std_ReturnType CCP_Start_PWM       (const ccp_t *ccp1_obj)
{
    Std_ReturnType ret = E_NOK ;
    
    if(ccp1_obj == NULL)
    {
        ret = E_NOK;
    }
    else
    {
        if(CCP1_INST == ccp1_obj->ccp_inst)
        {
            CCP1CONbits.CCP1M = CCP_PWM_MODE ;
        }
        else if (CCP2_INST == ccp1_obj->ccp_inst)
        {
            CCP2CONbits.CCP2M = CCP_PWM_MODE ;
        }
        ret = E_OK ;
    }
    return ret ;
}
Std_ReturnType CCP_Stop_PWM       (const ccp_t *ccp1_obj)
{
    Std_ReturnType ret = E_NOK ;
    
    if(ccp1_obj == NULL)
    {
        ret = E_NOK;
    }
    else
    {
        if(CCP1_INST == ccp1_obj->ccp_inst)
        {
            CCP1CONbits.CCP1M = CCP_MODULE_DISABLE;
        }
        else if (CCP2_INST == ccp1_obj->ccp_inst)
        {
            CCP1CONbits.CCP1M = CCP_MODULE_DISABLE;
        }
        ret = E_OK ;
    }
    return ret ;
    
}
Std_ReturnType CCP_Set_Duty_PWM    ( const ccp_t *ccp1_obj , const uint8 duty)
{
    Std_ReturnType ret = E_NOK ;
    uint16 l_duty_temp = 0 ;    
    
    if(ccp1_obj == NULL)
    {
        ret = E_NOK;
    }
    else
    {
        l_duty_temp = (uint16)((PR2 + 1)*(duty / 100.0)*4);
        if(CCP1_INST == ccp1_obj->ccp_inst)
        {
            CCP1CONbits.DC1B = (uint8)(l_duty_temp & 0x003);
            CCPR1L = (uint8)(l_duty_temp >> 2);
        }
        else if (CCP2_INST == ccp1_obj->ccp_inst)
        {
            CCP2CONbits.DC2B = (uint8)(l_duty_temp & 0x003);
            CCPR2L = (uint8)(l_duty_temp >> 2);
        }
        else { /* Nothing */ }
        ret = E_OK ;
    }
    return ret ;
}
#endif

/* ===================== ISR Function ====================== */
/**
 * @name CCP1_ISR
 * @return void 
 * @brief 
 */
void CCP1_ISR (void)
{
    CCP1_InterruptFlagClear();
    /* to return pre-load values to Timer0 register after overflow */
    if (CCP1_InterruptHandler)
    {
        CCP1_InterruptHandler();        /* Call the callback function */
    }
}

/**
 * @name CCP2_ISR
 * @return void 
 * @brief 
 */
void CCP2_ISR (void)
{
    CCP2_InterruptFlagClear();
    /* to return pre-load values to Timer0 register after overflow */
    if (CCP2_InterruptHandler)
    {
        CCP2_InterruptHandler();        /* Call the callback function */
    }
}

/* ===================== Helper Function ====================== */

static void CCP_Interrupt_Config(const ccp_t *ccp_obj)
{
         /* Interrupt Configuration */
/* === CCP1 Interrupt === */
#if _CCP1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    CCP1_InterruptEnable();
    CCP1_InterruptFlagClear();
    CCP1_InterruptHandler = ccp_obj->CCP1_InterruptHandler;
 /* Interrupt Priority configuration */
#if _INTERRUPT_PERIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
    INTERRUPT_PeriortyLevelEnable();
    if (ccp_obj->ccp1_priority == INTERRUPT_HIGH_PRIORITY)
    {
            /* Enable all high-priority interrupts */
            INTERRUPT_GlobalInterruptHighEnable();
            CCP1_HighPrioritySet();
        }
        else if (ccp_obj->ccp1_priority == INTERRUPT_LOW_PRIORITY)
        {
            /* Enable all unmasked peripheral interrupts */
            INTERRUPT_GlobalInterruptLowEnable();
            CCP1_LowPrioritySet();
        }
#else 
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
#endif
#endif
/* === CCP2 Interrupt === */
#if _CCP2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        CCP2_InterruptEnable();
        CCP2_InterruptFlagClear();
        CCP2_InterruptHandler = ccp_obj->CCP2_InterruptHandler;
 /* Interrupt Priority configuration */
#if _INTERRUPT_PERIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
        INTERRUPT_PeriortyLevelEnable();
        if (ccp_obj->ccp2_priority == INTERRUPT_HIGH_PRIORITY)
        {
            /* Enable all high-priority interrupts */
            INTERRUPT_GlobalInterruptHighEnable();
            CCP2_HighPrioritySet();
        }
        else if (ccp_obj->ccp2_priority == INTERRUPT_LOW_PRIORITY)
        {
            /* Enable all unmasked peripheral interrupts */
            INTERRUPT_GlobalInterruptLowEnable();
            CCP2_LowPrioritySet();
        }
#else 
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
#endif
#endif
}

static void CCP_Capture_Mode_Timer_Select(const ccp_t *ccp_obj)
{
    if(CCP1_CCP2_TIMER3 == ccp_obj->ccp_capture_timer) /* Timer3 is the capture/compare clock source for the CCP modules */
    {
        T3CONbits.T3CCP1 = 0 ;
        T3CONbits.T3CCP2 = 1 ;
    }
    else if(CCP1_TIMER1_CCP2_TIMER3 == ccp_obj->ccp_capture_timer) /* Timer3 is the capture/compare clock source for CCP2;
                                                                      Timer1 is the capture/compare clock source for CCP1 */
    {
        T3CONbits.T3CCP1 = 1 ;
        T3CONbits.T3CCP2 = 0 ;
    }
    else if(CCP1_CCP2_TIMER1 == ccp_obj->ccp_capture_timer) /* Timer1 is the capture/compare clock source for the CCP modules */
    {
        T3CONbits.T3CCP1 = 0 ;
        T3CONbits.T3CCP2 = 0 ;
    }
    else { /* Nothing */ }
}

static Std_ReturnType CCP_Compare_Mode_Config(const ccp_t *ccp_obj)
{
    Std_ReturnType ret = E_OK;
    
    if(CCP1_INST == ccp_obj->ccp_inst){
        /* CCP1 Module Compare variants Mode Initialization */
        switch(ccp_obj->CCP_mode_variant){
            case CCP_COMPARE_MODE_SET_PIN_LOW      : CCP1_SET_MODE(CCP_COMPARE_MODE_SET_PIN_LOW);      break;
            case CCP_COMPARE_MODE_SET_PIN_HIGH     : CCP1_SET_MODE(CCP_COMPARE_MODE_SET_PIN_HIGH);     break;
            case CCP_COMPARE_MODE_TOGGLE_ON_MATCH  : CCP1_SET_MODE(CCP_COMPARE_MODE_TOGGLE_ON_MATCH);  break;
            case CCP_COMPARE_MODE_GEN_SW_INTERRUPT : CCP1_SET_MODE(CCP_COMPARE_MODE_GEN_SW_INTERRUPT); break;
            case CCP_COMPARE_MODE_GEN_EVENT        : CCP1_SET_MODE(CCP_COMPARE_MODE_GEN_EVENT);        break;
            default : ret = E_NOK; /* Not supported variant */
        }
    }
    else if(CCP2_INST == ccp_obj->ccp_inst){
        /* CCP1 Module Compare variants Mode Initialization */
        switch(ccp_obj->CCP_mode_variant){
            case CCP_COMPARE_MODE_SET_PIN_LOW      : CCP2_SET_MODE(CCP_COMPARE_MODE_SET_PIN_LOW);      break;
            case CCP_COMPARE_MODE_SET_PIN_HIGH     : CCP2_SET_MODE(CCP_COMPARE_MODE_SET_PIN_HIGH);     break;
            case CCP_COMPARE_MODE_TOGGLE_ON_MATCH  : CCP2_SET_MODE(CCP_COMPARE_MODE_TOGGLE_ON_MATCH);  break;
            case CCP_COMPARE_MODE_GEN_SW_INTERRUPT : CCP2_SET_MODE(CCP_COMPARE_MODE_GEN_SW_INTERRUPT); break;
            case CCP_COMPARE_MODE_GEN_EVENT        : CCP2_SET_MODE(CCP_COMPARE_MODE_GEN_EVENT);        break;
            default : ret = E_NOK; /* Not supported variant */
        }
    }
    else{ /* Nothing */ }
    
    CCP_Capture_Mode_Timer_Select(ccp_obj);
    
    return ret;
}

static Std_ReturnType CCP_Capture_Mode_Config(const ccp_t *ccp_obj)
{
    Std_ReturnType ret = E_OK;
    
    if(CCP1_INST == ccp_obj->ccp_inst){
        /* CCP1 Module Capture variants Mode Initialization */
        switch(ccp_obj->CCP_mode_variant){
            case CCP_CAPTURE_MODE_1_FALLING_EDGE : CCP1_SET_MODE(CCP_CAPTURE_MODE_1_FALLING_EDGE); break;
            case CCP_CAPTURE_MODE_1_RISING_EDGE  : CCP1_SET_MODE(CCP_CAPTURE_MODE_1_RISING_EDGE);  break;
            case CCP_CAPTURE_MODE_4_RISING_EDGE  : CCP1_SET_MODE(CCP_CAPTURE_MODE_4_RISING_EDGE);  break;
            case CCP_CAPTURE_MODE_16_RISING_EDGE : CCP1_SET_MODE(CCP_CAPTURE_MODE_16_RISING_EDGE); break;
            default : ret = E_NOK; /* Not supported variant */
        }
    }
    else if(CCP2_INST == ccp_obj->ccp_inst){
        /* CCP2 Module Capture variants Mode Initialization */
        switch(ccp_obj->CCP_mode_variant){
            case CCP_CAPTURE_MODE_1_FALLING_EDGE : CCP2_SET_MODE(CCP_CAPTURE_MODE_1_FALLING_EDGE); break;
            case CCP_CAPTURE_MODE_1_RISING_EDGE  : CCP2_SET_MODE(CCP_CAPTURE_MODE_1_RISING_EDGE);  break;
            case CCP_CAPTURE_MODE_4_RISING_EDGE  : CCP2_SET_MODE(CCP_CAPTURE_MODE_4_RISING_EDGE);  break;
            case CCP_CAPTURE_MODE_16_RISING_EDGE : CCP2_SET_MODE(CCP_CAPTURE_MODE_16_RISING_EDGE); break;
            default : ret = E_NOK; /* Not supported variant */
        }
    }
    else{ /* Nothing */ }
    
    CCP_Capture_Mode_Timer_Select(ccp_obj);
    
    return ret;
}