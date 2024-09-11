/* 
 * File:   mcal_interrupt_manager.c
 * Author: Ziad
 *
 * Created on 17 July 2024, 10:06 
 */

#ifndef MCAL_INTERRUPT_MANAGER_H
#define	MCAL_INTERRUPT_MANAGER_H

/******************** Section : includes ********************/
#include "mcal_interrupt_config.h"

/******************** Section : Macro Declarations ********************/

/******************** Section : Macro Function Declarations ********************/

/******************** Section : Data Type Declarations ********************/

/******************** Section : Function Declarations ********************/

/* for INTx */
void INT0_ISR (void);
void INT1_ISR (void);
void INT2_ISR (void);

/* for RBx */
void RB4_ISR  (uint8 RB4_Source);
void RB5_ISR  (uint8 RB5_Source);
void RB6_ISR  (uint8 RB6_Source);
void RB7_ISR  (uint8 RB7_Source);

/* For ADC */
void ADC_ISR    (void);

/* For Timer*/
void TMR0_ISR   (void);
void TMR1_ISR   (void);
void TMR2_ISR   (void);
void TMR3_ISR   (void);

/* For CCP */
void CCP1_ISR   (void);
void CCP2_ISR   (void);

/* For EUSART */
void EUSART_Tx_ISR (void);
void EUSART_Rx_ISR (void);

/* For EEPROM */
void EEPROM_ISR (void);

/* For MSSP I2C */
void MSSP_I2C_ISR (void);
void MSSP_I2C_Bus_COL_ISR (void);

#endif	/* MCAL_INTERRUPT_MANAGER_H */

