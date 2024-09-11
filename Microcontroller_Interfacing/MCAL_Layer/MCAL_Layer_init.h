/* 
 * File:   MCAL_Layer_init.h
 * Author: Ziad Elmekawy
 *
 * Created on 28 July, 2024, 07:24 ?
 */

#ifndef MCAL_LAYER_INIT_H
#define	MCAL_LAYER_INIT_H

/*************** Section : includes ***************/
#include "GPIO/hal_GPIO.h"
#include "Interrupt/mcal_external_interrupt.h"
#include "ADC/hal_ADC.h"
#include "Timer/hal_timer0.h"
#include "Timer1/hal_timer1.h"
#include "Timer2/hal_timer2.h"
#include "Timer3/hal_timer3.h"

/*************** Section : Macro Declarations ***************/

/*************** Section : Macro Function Declarations ***************/

/*************** Section : Data Type Declarations ***************/

/*************** Section : Function Declarations  ***************/

void mcal_layer_initialize (void) ;
//void ADC_DefaultInterruptHandler(void);
void Int0_App_ISR (void);
void Int1_App_ISR (void);
void Int2_App_ISR (void);
void RB4_HIGH_Int_App_ISR (void);
void RB4_LOW_Int_App_ISR  (void) ;

/* ^-^ Timer0 ^-^ */



#endif	/* MCAL_LAYER_INIT_H */

