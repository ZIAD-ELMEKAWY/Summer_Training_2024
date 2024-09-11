/* 
 * File:   mcal_interrupt_manager.h
 * Author: Ziad Elmekawy
 *
 * Created on 17 July 2024, 10:06 
 */

/******************** Section : Includes *************************/
#include "mcal_interrupt_manager.h"

/******************** Section : Functions definitions *************************/
static volatile uint8 RB4_Flag = 1 ,RB5_Flag = 1 ,RB6_Flag = 1 , RB7_Flag = 1   ;

#ifdef _INTERRUPT_PERIORITY_LEVELS_ENABLE
/**
 * @name INTERRUPT_ManagerHigh
 * @return  void
 * @param   void
 * @note    1)  [__interrupt] is used to detect that this function is interrupt ISR not a normal function
 *          2)  [__interrupt] is called an interrupt qualifier
 */
void __interrupt() INTERRUPT_ManagerHigh (void) 
{
    if ((INTCONbits.INT0IE == INTERRUPT_ENABLE) && (INTERRUPT_OCCUR == INTCONbits.INT0IF))
    {
        INT0_ISR();
    }
    else 
    {
        /* Nothing */
    }
    if ((INTCON3bits.INT2IE == INTERRUPT_ENABLE) && (INTERRUPT_OCCUR == INTCON3bits.INT2IF))
    {
        INT2_ISR();
    }
    else 
    {
        /* Nothing */
    }
}

/**
 * @name INTERRUPT_ManagerLow
 * @return  void
 * @param   void
 * @note    1) [__interrupt(low_priority)] is used to detect that this function is interrupt ISR not a normal function
 *          2) [__interrupt(low_priority)] is called an interrupt qualifier
 */
void __interrupt(low_priority) INTERRUPT_ManagerLow(void)
{
    if ((INTCON3bits.INT1IE == INTERRUPT_ENABLE) && (INTERRUPT_OCCUR == INTCON3bits.INT1IF))
    {
        INT1_ISR();
    }
    else 
    {
        /* Nothing */
    }
}

#else
void __interrupt() INTERRUPT_Manager (void) 
{
    /******************************* for INTx ********************************/
    if ((INTCONbits.INT0IE == INTERRUPT_ENABLE) && (INTERRUPT_OCCUR == INTCONbits.INT0IF))
    {
        INT0_ISR();
    }
    else 
    {
        /* Nothing */
    }
    if ((INTCON3bits.INT1IE == INTERRUPT_ENABLE) && (INTERRUPT_OCCUR == INTCON3bits.INT1IF))
    {
        INT1_ISR();
    }
    else 
    {
        /* Nothing */
    }
    if ((INTCON3bits.INT2IE == INTERRUPT_ENABLE) && (INTERRUPT_OCCUR == INTCON3bits.INT2IF))
    {
        INT2_ISR();
    }
    else 
    {
        /* Nothing */
    }
    
    /******************************* for RBx On Change external interrupt *******************************/
    /* @note     1) make interrupt when the voltage change form 0 to 5 
     *           2) we add [ RB4_Flag == 1 ] -> to prevent the compiler to get into the low condition 
     */
    
    /*========================== RB4 ==========================*/
    if ((INTCONbits.RBIE == INTERRUPT_ENABLE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && (PORTBbits.RB4 == GPIO_HIGH) && (RB4_Flag == 1))
    {
        RB4_Flag = 0 ;
        RB4_ISR(0); // 0 if high
    }
    else 
    {
        /* Nothing */
    }
    /* @note     1) make interrupt when the voltage change form 5 to 0 */
    if ((INTCONbits.RBIE == INTERRUPT_ENABLE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && (PORTBbits.RB4 == GPIO_LOW) && (RB4_Flag == 0))
    {
        RB4_Flag = 1 ;
        RB4_ISR(1);  // 1 if low
    }
    else 
    {
        /* Nothing */
    }
   /*========================== RB5 ==========================*/
    if ((INTCONbits.RBIE == INTERRUPT_ENABLE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && (PORTBbits.RB5 == GPIO_HIGH) && (RB5_Flag == 1))
    {
        RB5_Flag = 0 ;
        RB5_ISR(0); // 0 if high
    }
    else 
    {
        /* Nothing */
    }
    if ((INTCONbits.RBIE == INTERRUPT_ENABLE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && (PORTBbits.RB5 == GPIO_LOW) && (RB5_Flag == 0))
    {
        RB5_Flag = 1 ;
        RB5_ISR(1);  // 1 if low
    }
    else 
    {
        /* Nothing */
    }
    /*========================== RB6 ==========================*/
    if ((INTCONbits.RBIE == INTERRUPT_ENABLE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && (PORTBbits.RB6 == GPIO_HIGH) && (RB6_Flag == 1))
    {
        RB6_Flag = 0 ;
        RB6_ISR(0); // 0 if high
    }
    else 
    {
        /* Nothing */
    }
    if ((INTCONbits.RBIE == INTERRUPT_ENABLE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && (PORTBbits.RB6 == GPIO_LOW) && (RB6_Flag == 0))
    {
        RB6_Flag = 1 ;
        RB6_ISR(1);  // 1 if low
    }
    else 
    {
        /* Nothing */
    }
    /*========================== RB7 ==========================*/
    if ((INTCONbits.RBIE == INTERRUPT_ENABLE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && (PORTBbits.RB7 == GPIO_HIGH) && (RB7_Flag == 1))
    {
        RB7_Flag = 0 ;
        RB7_ISR(0); // 0 if high
    }
    else 
    { /* Nothing */ }
    
    if ((INTCONbits.RBIE == INTERRUPT_ENABLE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && (PORTBbits.RB7 == GPIO_LOW) && (RB7_Flag == 0))
    {
        RB7_Flag = 1 ;
        RB7_ISR(1);  // 1 if low
    }
    else 
    { /* Nothing */ }
    
    /******************************* for ADC Interrupt ********************************/
    if ((PIE1bits.ADIE == INTERRUPT_ENABLE) && (INTERRUPT_OCCUR == PIR1bits.ADIF))
    {
        ADC_ISR();
    }
    else 
    { /* Nothing */ }
    
    /******************************* for Timer Interrupt ********************************/
    /*========================== Timer0 ==========================*/
    if ((INTCONbits.TMR0IE == INTERRUPT_ENABLE) && (INTERRUPT_OCCUR == INTCONbits.TMR0IF))
    {
        TMR0_ISR();
    }
    else 
    { /* Nothing */ }
    
    /*========================== Timer1 ==========================*/
    if ((PIE1bits.TMR1IE == INTERRUPT_ENABLE) && (INTERRUPT_OCCUR == PIR1bits.TMR1IF))
    {
        TMR1_ISR();
    }
    else 
    { /* Nothing */ }
    
    /*========================== Timer2 ==========================*/
    if ((PIE1bits.TMR2IE == INTERRUPT_ENABLE) && (INTERRUPT_OCCUR == PIR1bits.TMR2IF))
    {
        TMR2_ISR();
    }
    else 
    { /* Nothing */ }
    
    /*========================== Timer3 ==========================*/
    if ((PIE2bits.TMR3IE == INTERRUPT_ENABLE) && (INTERRUPT_OCCUR == PIR2bits.TMR3IF))
    {
        TMR3_ISR();
    }
    else 
    { /* Nothing */ }
    
    /******************************* for CCP Interrupt ********************************/
    /*========================== CCP1 ==========================*/
    if ((PIE1bits.CCP1IE == INTERRUPT_ENABLE) && (INTERRUPT_OCCUR == PIR1bits.CCP1IF))
    {
        CCP1_ISR();
    }
    else 
    { /* Nothing */ }
    
    /*========================== CCP2 ==========================*/
    if ((PIE2bits.CCP2IE == INTERRUPT_ENABLE) && (INTERRUPT_OCCUR == PIR2bits.CCP2IF))
    {
        CCP2_ISR();
    }
    else 
    { /* Nothing */ }
    
    /******************************* for EUSART  Interrupt ********************************/
    /*========================== Tx ==========================*/
    if ((PIE1bits.TXIE == INTERRUPT_ENABLE) && (INTERRUPT_OCCUR == PIR1bits.TXIF))
    {
        EUSART_Tx_ISR();
    }
    else 
    { /* Nothing */ }
    /*========================== Rx ==========================*/
    if ((PIE1bits.RCIE == INTERRUPT_ENABLE) && (INTERRUPT_OCCUR == PIR1bits.RCIF))
    {
        EUSART_Rx_ISR();
    }
    else 
    { /* Nothing */ }
    
    /******************************* for EEPROM Interrupt ********************************/
    if ((PIE2bits.EEIE == INTERRUPT_ENABLE) && (INTERRUPT_OCCUR == PIR2bits.EEIF))
    {
        EEPROM_ISR();
    }
    else 
    { /* Nothing */ }
    
    /******************************* for MSSP I2C Interrupt ********************************/
    #if _MSSP_I2C_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE 
    /*========================== I2C ==========================*/
    if ((PIE1bits.SSPIE == INTERRUPT_ENABLE) && (INTERRUPT_OCCUR == PIR1bits.SSPIF))
    {
        MSSP_I2C_ISR();
    }
    else 
    { /* Nothing */ }
    /*========================== Bus collision ==========================*/
    if ((PIE2bits.BCLIE == INTERRUPT_ENABLE) && (INTERRUPT_OCCUR == PIR2bits.BCLIF))
    {
        MSSP_I2C_Bus_COL_ISR();
    }
    else 
    { /* Nothing */ }
#endif
}
#endif
