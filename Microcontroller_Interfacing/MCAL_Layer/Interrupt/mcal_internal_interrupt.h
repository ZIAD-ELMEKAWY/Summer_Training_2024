/* 
 * File:   mcal_internal_interrupt.h
 * Author: Ziad Elmekawy
 *
 * Created on 17 July 2024
 */

#ifndef MCAL_INTERNAL_INTERRUPT_H
#define	MCAL_INTERNAL_INTERRUPT_H

/******************** Section : includes ********************/
#include "mcal_interrupt_config.h"

/******************** Section : Macro Declarations ********************/

/******************** Section : Macro Function Declarations ********************/
/* ============================   ADC   =======================*/
#if _ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/* This routine clears the interrupt enable for the internal interrupt : INT0 */
#define ADC_InterruptDisable()      ( PIE1bits.ADIE = 0 )
/* This routine sets the interrupt enable for the ADC Module */
#define ADC_InterruptEnable()       ( PIE1bits.ADIE = 1 )
/* This routine clears the interrupt flag for the ADC Module */
#define ADC_InterruptFlagClear()    ( PIR1bits.ADIF = 0 )

#if _INTERRUPT_PERIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
/* This routine sets the ADC priority to be high */
#define ADC_HighPrioritySet()       ( IPR1bits.ADIP = 1 )
/* This routine sets the ADC priority to be low */
#define ADC_LowPrioritySet()        ( IPR1bits.ADIP = 0 ) 

#endif
#endif

/* ============================ TIMER 0 =======================*/
#if _TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/* This routine clears the interrupt enable for the internal interrupt : INT0 */
#define TIMER0_InterruptDisable()      ( INTCONbits.TMR0IE = 0 )
/* This routine sets the interrupt enable for the ADC Module */
#define TIMER0_InterruptEnable()       ( INTCONbits.TMR0IE = 1 )
/* This routine clears the interrupt flag for the ADC Module */
#define TIMER0_InterruptFlagClear()    ( INTCONbits.TMR0IF = 0 )

#if _INTERRUPT_PERIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
/* This routine sets the ADC priority to be high */
#define TIMER0_HighPrioritySet()       ( INTCON2bits.TMR0IP = 1 )
/* This routine sets the ADC priority to be low */
#define TIMER0_LowPrioritySet()        ( INTCON2bits.TMR0IP = 0 ) 

#endif
#endif

/* ============================ TIMER 1 =======================*/
#if _TIMER1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/* This routine clears the interrupt enable for the internal interrupt : INT0 */
#define TIMER1_InterruptDisable()      ( PIE1bits.TMR1IE = 0 )
/* This routine sets the interrupt enable for the ADC Module */
#define TIMER1_InterruptEnable()       ( PIE1bits.TMR1IE = 1 )
/* This routine clears the interrupt flag for the ADC Module */
#define TIMER1_InterruptFlagClear()    ( PIR1bits.TMR1IF = 0 )

#if _INTERRUPT_PERIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
/* This routine sets the ADC priority to be high */
#define TIMER1_HighPrioritySet()       ( IPR1bits.TMR1IP = 1 )
/* This routine sets the ADC priority to be low */
#define TIMER1_LowPrioritySet()        ( IPR1bits.TMR1IP = 0 ) 

#endif
#endif

/* ============================ TIMER 2 =======================*/
#if _TIMER2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/* This routine clears the interrupt enable for the internal interrupt : INT0 */
#define TIMER2_InterruptDisable()      ( PIE1bits.TMR2IE = 0 )
/* This routine sets the interrupt enable for the ADC Module */
#define TIMER2_InterruptEnable()       ( PIE1bits.TMR2IE = 1 )
/* This routine clears the interrupt flag for the ADC Module */
#define TIMER2_InterruptFlagClear()    ( PIR1bits.TMR2IF = 0 )

#if _INTERRUPT_PERIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
/* This routine sets the ADC priority to be high */
#define TIMER2_HighPrioritySet()       ( IPR1bits.TMR2IP = 1 )
/* This routine sets the ADC priority to be low */
#define TIMER2_LowPrioritySet()        ( IPR1bits.TMR2IP = 0 ) 

#endif
#endif

/* ============================ TIMER 3 =======================*/
#if _TIMER3_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/* This routine clears the interrupt enable for the internal interrupt : INT0 */
#define TIMER3_InterruptDisable()      ( PIE2bits.TMR3IE = 0 )
/* This routine sets the interrupt enable for the ADC Module */
#define TIMER3_InterruptEnable()       ( PIE2bits.TMR3IE = 1 )
/* This routine clears the interrupt flag for the ADC Module */
#define TIMER3_InterruptFlagClear()    ( PIR2bits.TMR3IF = 0 )

#if _INTERRUPT_PERIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
/* This routine sets the ADC priority to be high */
#define TIMER3_HighPrioritySet()       ( IPR2bits.TMR3IP = 1 )
/* This routine sets the ADC priority to be low */
#define TIMER3_LowPrioritySet()        ( IPR2bits.TMR3IP = 0 ) 

#endif
#endif


/* ============================ CCP1 =======================*/
#if _CCP1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/* This routine clears the interrupt enable for the CCP1 */
#define CCP1_InterruptDisable()      ( PIE1bits.CCP1IE = 0 )
/* This routine sets the interrupt enable for the CCP1 Module */
#define CCP1_InterruptEnable()       ( PIE1bits.CCP1IE = 1 )
/* This routine clears the interrupt flag for the CCP1 Module */
#define CCP1_InterruptFlagClear()    ( PIR1bits.CCP1IF = 0 )

#if _INTERRUPT_PERIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
/* This routine sets the CCP1 priority to be high */
#define CCP1_HighPrioritySet()       ( IPR1bits.CCP1IP = 1 )
/* This routine sets the CCP1 priority to be low */
#define CCP1_LowPrioritySet()        ( IPR1bits.CCP1IP = 0 ) 

#endif
#endif

/* ============================ CCP2 =======================*/
#if _CCP2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/* This routine clears the interrupt enable for the CCP2 */
#define CCP2_InterruptDisable()      ( PIE2bits.CCP2IE = 0 )
/* This routine sets the interrupt enable for the CCP2 */
#define CCP2_InterruptEnable()       ( PIE2bits.CCP2IE = 1 )
/* This routine clears the interrupt flag for the CCP2 */
#define CCP2_InterruptFlagClear()    ( PIR2bits.CCP2IF = 0 )

#if _INTERRUPT_PERIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
/* This routine sets the CCP2 priority to be high */
#define CCP2_HighPrioritySet()       ( IPR2bits.CCP2IP = 1 )
/* This routine sets the CCP2 priority to be low */
#define CCP2_LowPrioritySet()        ( IPR2bits.CCP2IP = 0 ) 

#endif
#endif

/* ============================ EUSART Tx =======================*/
#if _EUSART_Tx_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/* This routine clears the interrupt enable for the EUSART TX */
#define EUSART_Tx_InterruptDisable()      ( PIE1bits.TXIE = 0 )
/* This routine sets the interrupt enable for the EUSART TX */
#define EUSART_Tx_InterruptEnable()       ( PIE1bits.TXIE = 1 )
/* This routine clears the interrupt flag for the EUSART TX */
#define EUSART_Tx_InterruptFlagClear()    ( PIR1bits.TXIF = 0 )                 /* (cleared when TXREG is written) */

#if _INTERRUPT_PERIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
/* This routine sets the EUSART TX priority to be high */
#define EUSART_Tx_HighPrioritySet()       ( IPR1bits.TXIP = 1 )
/* This routine sets the EUSART TX priority to be low */
#define EUSART_Tx_LowPrioritySet()        ( IPR1bits.TXIP = 0 )                 

#endif
#endif

/* ============================ EUSART Rx =======================*/
#if _EUSART_Rx_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/* This routine clears the interrupt enable for the EUSART RX */
#define EUSART_Rx_InterruptDisable()      ( PIE1bits.RCIE = 0 )
/* This routine sets the interrupt enable for the EUSART RX */
#define EUSART_Rx_InterruptEnable()       ( PIE1bits.RCIE = 1 )
/* This routine clears the interrupt flag for the EUSART RX */
#define EUSART_Rx_InterruptFlagClear()    ( PIR1bits.RCIF = 0 )                 /* (cleared when TXREG is written) */

#if _INTERRUPT_PERIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
/* This routine sets the EUSART RX priority to be high */
#define EUSART_Rx_HighPrioritySet()       ( IPR1bits.RCIP = 1 )
/* This routine sets the EUSART RX priority to be low RX */
#define EUSART_Rx_LowPrioritySet()        ( IPR1bits.RCIP = 0 ) 

#endif
#endif

/* ============================ MSSP (  I2C ) =======================*/
#if _MSSP_I2C_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/* This routine clears the interrupt enable for the I2C MSSP */
#define MSSP_I2C_InterruptDisable()                           ( PIE1bits.SSPIE = 0 )
#define MSSP_I2C_Bus_COL_InterruptDisable()         ( PIE2bits.BCLIE = 0 )
/* This routine sets the interrupt enable for the I2C MSSP */
#define MSSP_I2C_InterruptEnable()                           ( PIE1bits.SSPIE = 1 )     
#define MSSP_I2C_Bus_COL_InterruptEnable()         ( PIE2bits.BCLIE = 1 )
/* This routine clears the interrupt flag for the I2C MSSP */
#define MSSP_I2C_InterruptFlagClear()                      ( PIR1bits.SSPIF = 0 )                     /* (must be cleared in software) */
#define MSSP_I2C_Bus_COL_InterruptFlagClear()    ( PIR2bits.BCLIF = 0 )                     /* (must be cleared in software) */

#if _INTERRUPT_PERIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
/* This routine sets the I2C MSSP priority to be high */
#define MSSP_I2C_HighPrioritySet()                         ( IPR1bits.SSPIP = 1 )
#define MSSP_I2C_Bus_COL_HighPrioritySet()       ( IPR2bits.BCLIP = 1 )
/* This routine sets the I2C MSSP priority to be low */
#define MSSP_I2C_LowPrioritySet()                         ( IPR1bits.SSPIP = 0 ) 
#define MSSP_I2C_Bus_COL_LowPrioritySet()       ( IPR2bits.BCLIP = 0 )

#endif
#endif


/* ============================   EEPROM   =======================*/
#if _EEPROM_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/* This routine clears the interrupt enable for the EEPROM interrupt */
#define EEPROM_InterruptDisable()      ( PIE2bits.EEIE = 0 )
/* This routine sets the interrupt enable for the EEPROM Module */
#define EEPROM_InterruptEnable()       ( PIE2bits.EEIE = 1 )
/* This routine clears the interrupt flag for the EEPROM Module */
#define EEPROM_InterruptFlagClear()    ( PIR2bits.EEIF = 0 )

#if _INTERRUPT_PERIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
/* This routine sets the EEPROM priority to be high */
#define EEPROM_HighPrioritySet()       ( IPR2bits.EEIP = 1 )
/* This routine sets the EEPROM priority to be low */
#define EEPROM_LowPrioritySet()        ( IPR2bits.EEIP = 0 ) 

#endif
#endif

/******************** Section : Data Type Declarations ********************/

/******************** Section : Function Declarations ********************/

#endif	/* MCAL_INTERNAL_INTERRUPT_H */

