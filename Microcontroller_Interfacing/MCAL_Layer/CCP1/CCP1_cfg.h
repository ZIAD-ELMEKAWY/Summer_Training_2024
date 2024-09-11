/* 
 * File:   CCP1_cfg.h
 * Author: Ziad Elmekawy
 *
 * Created on 07 August, 2024
 */

#ifndef CCP1_CFG_H
#define	CCP1_CFG_H
/****************** Section : Includes *****************/

/***************** Section : Macro Declarations *****************/
#define CCP1_CFG_CAPTURE_MODE_SELECTED      0x00
#define CCP1_CFG_COMPARE_MODE_SELECTED      0x01
#define CCP_CFG_PWM_MODE_SELECTED           0x02

#define CCP1_CFG_MODE_SELECTED  CCP_CFG_PWM_MODE_SELECTED                  /* This macro for selecting mode */
#define CCP2_CFG_MODE_SELECTED  CCP1_CFG_COMPARE_MODE_SELECTED                  /* This macro for selecting mode */


/***************** Section : Macro Function Declarations *****************/

/***************** Section : Data Type Declarations *****************/

/***************** Section : Function Declarations *****************/

#endif	/* CCP1_CFG_H */

