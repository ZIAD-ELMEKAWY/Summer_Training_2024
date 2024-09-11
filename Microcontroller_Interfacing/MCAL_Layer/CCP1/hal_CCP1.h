/* 
 * File:   hal_CCP1.h
 * Author: Ziad Elmekawy
 *
 * Created on 07 August, 2024
 */

#ifndef HAL_CCP1_H
#define	HAL_CCP1_H

/********************** Section :  Includes *******************/
#include "../MCAL_std_Types.h"
#include "../GPIO/hal_GPIO.h"
#include "../Interrupt/mcal_internal_interrupt.h"
#include "pic18f4620.h"
#include "CCP1_cfg.h"

/***************** Section : Macro Declarations  " @IS_USED_FOR_ENHANCING_READABILITY " *****************/
/* === CCP1 Mode Select === */
#define CCP_MODULE_DISABLE                    ((uint8)0x00)
#define CCP_CAPTURE_MODE_1_FALLING_EDGE       ((uint8)0x04)
#define CCP_CAPTURE_MODE_1_RISING_EDGE        ((uint8)0x05)
#define CCP_CAPTURE_MODE_4_RISING_EDGE        ((uint8)0x06)
#define CCP_CAPTURE_MODE_16_RISING_EDGE       ((uint8)0x07)
#define CCP_COMPARE_MODE_SET_PIN_HIGH         ((uint8)0x08)
#define CCP_COMPARE_MODE_SET_PIN_LOW          ((uint8)0x09)
#define CCP_COMPARE_MODE_TOGGLE_ON_MATCH      ((uint8)0x02)
#define CCP_COMPARE_MODE_GEN_SW_INTERRUPT     ((uint8)0x0A)
#define CCP_COMPARE_MODE_GEN_EVENT            ((uint8)0x0B)
#define CCP_PWM_MODE                          ((uint8)0x0C)

/* === CCP1 Capture Mode state === */
#define CCP_CAPTURE_NOT_READY  0x00
#define CCP_CAPTURE_READY      0x01

/* === CCP1 Compare Mode state === */
#define CCP_COMPARE_NOT_READY  0x00
#define CCP_COMPARE_READY      0x01

/***************** Section : Macro Function Declarations *****************/
#define CCP1_SET_MODE(_CONFIG)       (CCP1CONbits.CCP1M = _CONFIG) /* @REF CCP1 Mode Select */
#define CCP2_SET_MODE(_CONFIG)       (CCP2CONbits.CCP2M = _CONFIG) /* @REF CCP1 Mode Select */



/***************** Section : Data Type Declarations *****************/
typedef enum {
    CCP_TIMER2_PRESCALER_DIV_BY_1= 1 ,
    CCP_TIMER2_PRESCALER_DIV_BY_4 ,
    CCP_TIMER2_PRESCALER_DIV_BY_16
}CCP1_timer2_prescaler_select_t;

typedef enum {
    CCP_TIMER2_POSTSCALER_DIV_BY_1= 1 ,
    CCP_TIMER2_POSTSCALER_DIV_BY_2 ,
    CCP_TIMER2_POSTSCALER_DIV_BY_3 ,
    CCP_TIMER2_POSTSCALER_DIV_BY_4 ,
    CCP_TIMER2_POSTSCALER_DIV_BY_5 ,
    CCP_TIMER2_POSTSCALER_DIV_BY_6 ,
    CCP_TIMER2_POSTSCALER_DIV_BY_7 ,
    CCP_TIMER2_POSTSCALER_DIV_BY_8 ,
    CCP_TIMER2_POSTSCALER_DIV_BY_9 ,
    CCP_TIMER2_POSTSCALER_DIV_BY_10 ,
    CCP_TIMER2_POSTSCALER_DIV_BY_11 ,
    CCP_TIMER2_POSTSCALER_DIV_BY_12 ,
    CCP_TIMER2_POSTSCALER_DIV_BY_13 ,
    CCP_TIMER2_POSTSCALER_DIV_BY_14 ,
    CCP_TIMER2_POSTSCALER_DIV_BY_15 ,
    CCP_TIMER2_POSTSCALER_DIV_BY_16
}CCP1_timer2_postscaler_select_t;

typedef enum 
{
    CCP_CAPTURE_MODE_SELECTED = 0 ,
    CCP_COMPARE_MODE_SELECTED ,
    CCP_PWM_MODE_SELECTED
}ccp1_mode_t ;

/*
 * @sumary          Defines the values to convert from 16bit to two 8 bit and vice versa
 * @description     Used to get two 8 bit values from 16 bit also two 8 bit value are combine to get 16 bit
 */
typedef union 
{
    struct 
    {
        uint8 ccpr_low ;
        uint8 ccpr_high;
    };
    struct 
    {
        uint16 ccpr_16bit ;
    };
}CCP1_REG_T;

typedef enum 
{
    CCP1_INST ,
    CCP2_INST
}CCP_inst_t;

typedef enum
{
    CCP1_CCP2_TIMER3 = 0 ,
    CCP1_TIMER1_CCP2_TIMER3 ,
    CCP1_CCP2_TIMER1
}ccp_capture_timer_t;

typedef struct 
{
    CCP_inst_t ccp_inst ;
    ccp1_mode_t ccp_mode ;       /* CCP main mode*/                                  /* @REF ccp1_mode_t */
    uint8 CCP_mode_variant ;     /* CCP selected mode variant */
    pin_config_t CCP_pin ;            /* CCP pin */
    ccp_capture_timer_t ccp_capture_timer ; 
#if _CCP1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    void (* CCP1_InterruptHandler)(void);
    interrupt_periority_cfg ccp1_priority ;
#endif
#if _CCP2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    void (* CCP2_InterruptHandler)(void);
    interrupt_periority_cfg ccp2_priority ;
#endif
#if ((CCP1_CFG_MODE_SELECTED == CCP_CFG_PWM_MODE_SELECTED) || (CCP2_CFG_MODE_SELECTED == CCP_CFG_PWM_MODE_SELECTED))
    uint32 PWM_Frequency ;
    CCP1_timer2_prescaler_select_t prescaler_value   ;
    CCP1_timer2_postscaler_select_t postscaler_value ;
#endif
}ccp_t;


/***************** Section : Function Declarations *****************/

Std_ReturnType CCP_Init   (const ccp_t *ccp1_obj);
Std_ReturnType CCP_DeInit (const ccp_t *ccp1_obj);

/* === Compile time switch === */
#if ((CCP1_CFG_MODE_SELECTED == CCP1_CFG_CAPTURE_MODE_SELECTED) || (CCP2_CFG_MODE_SELECTED == CCP1_CFG_CAPTURE_MODE_SELECTED))
Std_ReturnType CCP_IsCaptureDataReady  (uint8 *Capture_Status);
Std_ReturnType CCP_CaptureModeReadValue (uint16 *Capture_Value);
#endif
#if ((CCP1_CFG_MODE_SELECTED == CCP1_CFG_COMPARE_MODE_SELECTED) || (CCP2_CFG_MODE_SELECTED == CCP1_CFG_COMPARE_MODE_SELECTED))
Std_ReturnType CCP_Is_Compare_Complete     (uint8 *compare_status);
Std_ReturnType CCP_Compare_Mode_Set_Value  (const ccp_t *ccp1_obj , uint16 Compare_value);
#endif
#if ((CCP1_CFG_MODE_SELECTED == CCP_CFG_PWM_MODE_SELECTED) || (CCP2_CFG_MODE_SELECTED == CCP_CFG_PWM_MODE_SELECTED))
Std_ReturnType CCP_Start_PWM      (const ccp_t *ccp1_obj);
Std_ReturnType CCP_Stop_PWM       (const ccp_t *ccp1_obj);
Std_ReturnType CCP_Set_Duty_PWM   ( const ccp_t *ccp1_obj , const uint8 duty);
#endif

#endif	/* HAL_CCP1_H */

