/* 
 * File:   ecu_buzzer.h
 * Author: Ziad Elmekawy
 *
 * Created on 16 August 2024, 11:58 
 */

#ifndef ECU_BUZZER_H
#define	ECU_BUZZER_H

/* Section : includes */
#include "../../MCAL_Layer/GPIO/hal_GPIO.h"

/* Section : Macro Declarations */

/* Section : Macro Function Declarations */

/* Section : Data Type Declarations */
typedef enum 
{
    BUZ_OFF,
    BUZ_ON
}buz_status_t;

typedef struct
{
    uint8 port_name  : 4;
    uint8 pin        : 3;
    uint8 buz_status : 1;
}buz_t;

/* Section : Function Declarations */
Std_ReturnType buz_intialize(const buz_t *buz);
Std_ReturnType buz_turn_on  (const buz_t *buz);
Std_ReturnType buz_turn_off (const buz_t *buz);
Std_ReturnType buz_toggle   (const buz_t *buz);

#endif	/* ECU_BUZZER_H */

