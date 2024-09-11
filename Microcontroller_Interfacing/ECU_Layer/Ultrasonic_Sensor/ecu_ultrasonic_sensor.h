/* 
 * File:   ecu_ultrasonic_sensor.h
 * Author: Ziad_Elmekawy
 *
 * Created on 22 August, 2024, 06:39 PM
 */

#ifndef HCSR04_H
#define	HCSR04_H

#include "pic18f4620.h"
#include "../../MCAL_Layer/Device_config.h"
#include "../../MCAL_Layer/MCAL_std_Types.h"


#define TRIG_PIN LATDbits.LATB0  // Trigger pin
#define ECHO_PIN PORTDbits.RB1   // Echo pin

void init_ultrasonic(void);
uint16 measure_distance(void);

#endif	/* HCSR04_H */

