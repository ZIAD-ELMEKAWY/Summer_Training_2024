/* 
 * File:   eeprom.h
 * Author: Ziad Elmekawy
 *
 * Created on 24 August, 2024, 05:20 PM
 */

#ifndef EEPROM_H
#define	EEPROM_H

/*************** Section : includes ****************/
#include "../MCAL_std_Types.h"
#include "pic18f4620.h"
#include "../GPIO/hal_GPIO.h"
#include "../Interrupt/mcal_internal_interrupt.h"

/**************** Section : Macro Declarations *****************/

/* ----------------- Macro Declarations -----------------*/
/* Flash Program or Data EEPROM Memory Select  */
#define ACCESS_FLASH_PROGRAM_MEMORY       1
#define ACCESS_EEPROM_PROGRAM_MEMORY      0
/* Flash Program/Data EEPROM or Configuration Select */
#define ACCESS_CONFIG_REGISTERS           1
#define ACCESS_FLASH_EEPROM_MEMORY        0
/* Flash Program/Data EEPROM Write Enable */
#define ALLOW_WRITE_CYCLES_FLASH_EEPROM   1
#define INHIBTS_WRITE_CYCLES_FLASH_EEPROM 0
/* Write Control */
#define INITIATE_DATA_EEPROM_WRITE_ERASE  1
#define DATA_EEPROM_WRITE_ERASE_COMPLETED 0
/* Read Control */
#define INITIATE_DATA_EEPROM_READ         1

/* ----------------- Macro Functions Declarations -----------------*/

/* ----------------- Data Type Declarations -----------------*/

/* ----------------- Software Interfaces Declarations -----------------*/
Std_ReturnType Data_EEPROM_WriteByte(uint16 bAdd, uint8 bData);
Std_ReturnType Data_EEPROM_ReadByte(uint16 bAdd, uint8 *bData);

#endif	/* EEPROM_H */

