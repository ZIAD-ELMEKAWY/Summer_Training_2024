/* 
 * File:   hal_i2c.h
 * Author: Ziad Elmekawy
 *
 * Created on 28 August, 2024, 01:54 PM
 */

#ifndef HAL_I2C_H
#define	HAL_I2C_H

/*************** Section : includes ****************/
#include "../MCAL_std_Types.h"
#include "../Interrupt/mcal_internal_interrupt.h"
#include "pic18f4620.h"
#include "../GPIO/hal_GPIO.h"

/**************** Section : Macro Declarations *****************/
/* Slew Rate Enable */
#define I2C_SLEW_RATE_DISABLE   1
#define I2C_SLEW_RATE_ENABLE    0
/* SMBus Enable */
#define I2C_SMBus_DISABLE                       1
#define I2C_SMBus_ENABLE                        0
/* Stop Bit */
#define I2C_STOP_BIT_DETECTED               1
#define I2C_STOP_BIT_NOT_DETECTED     0
/* Start Bit */
#define I2C_START_BIT_DETECTED               1
#define I2C_START_BIT_NOT_DETECTED     0
/* Slave Mode Data/Address Instruction */
#define I2C_LAST_BYTE_DATA                         1
#define I2C_LAST_BYTE_ADDRESS                  0
/* Slave / Master select */
#define MSSP_I2C_MASTER_MODE                1
#define MSSP_I2C_SLAVE_MODE                    0
/* Master Synchronous Serial Port Mode select */
#define I2C_SLAVE_MODE_7BIT_ADDRESS                                          0x06U
#define I2C_SLAVE_MODE_10BIT_ADDRESS                                        0x07U
#define I2C_SLAVE_MODE_7BIT_ADDRESS_SS_INT_ENABLED       0x0EU
#define I2C_SLAVE_MODE_10BIT_ADDRESS_SS_INT_ENABLED     0x0FU
#define I2C_MASTER_MODE_DEFINED_CLOCK                                    0x08U
#define I2C_MASTER_MODE_FIRMWARE_CONTROLED                    0x0BU
/* General Call Enable */
#define I2C_GENERAL_CALL_ENABLE      1
#define I2C_GENERAL_CALL_DISABLE     0
/* Master Mode Receive Enable */
#define I2C_MASTER_RECEIVE_ENABLE    1
#define I2C_MASTER_RECEIVE_DISABLE   0
/* Acknowledge Status bit (Master Transmit mode only) */
#define I2C_ACK_RECEIVED_FROM_SLAVE                0        
#define I2C_ACK_NOT_RECEIVED_FROM_SLAVE      1
/* Acknowledge Data bit (Master Receive mode only) */
#define I2C_MASTER_SEND_ACK               0        
#define I2C_MASTER_SEND_NACK            1

/***************** Section : Macro Function Declarations *****************/
/* Disable MSSP I2C Module */
#define MSSP_MODULE_ENABLE_CFG()                                ( SSPCON1bits.SSPEN = 1 )
#define MSSP_MODULE_DISABLE_CFG()                               ( SSPCON1bits.SSPEN = 0 )
/* Slew Rate Enable */
#define I2C_SLEW_RATE_DISABLE_CFG( )                            ( SSPSTATbits.SMP = 1 )
#define I2C_SLEW_RATE_ENABLE_CFG( )                              ( SSPSTATbits.SMP = 0 )                                       
/* SMBus Enable */
#define I2C_SMBus_DISABLE_CFG( )                              (SSPSTATbits.CKE = 0  )  
#define I2C_SMBus_ENABLE_CFG( )                                ( SSPSTATbits.CKE = 1 )  
/* General Call Enable */
#define I2C_GENERAL_CALL_ENABLE_CFG( )                              ( SSPCON2bits.GCEN = 1 )  
#define I2C_GENERAL_CALL_DISABLE_CFG( )                             ( SSPCON2bits.GCEN = 0 )  
/* Master Mode Receive Enable */
#define I2C_MASTER_RECEIVE_ENABLE_CFG( )                             ( SSPCON2bits.RCEN = 1 )  
#define I2C_MASTER_RECEIVE_DISABLE_CFG( )                            ( SSPCON2bits.RCEN = 0 
/* Initiates start condition */
#define I2C_INITIATE_START_CONDITION_CFG( )                           ( SSPCON2bits.SEN = 1 )
#define I2C_IDEAL_START_CONDITION_CFG( )                               ( SSPCON2bits.SEN = 0 )
/* Initiates Repeated start condition */
#define I2C_INITIATE_REPEATED_START_CONDITION_CFG( )                           ( SSPCON2bits.RSEN = 1 )
#define I2C_IDEAL_REPEATED_START_CONDITION_CFG( )                               ( SSPCON2bits.RSEN = 0 )
/* Initiates stop condition */
#define I2C_INITIATE_STOP_CONDITION_CFG( )                           ( SSPCON2bits.PEN = 1 )
#define I2C_IDEAL_STOP_CONDITION_CFG( )                               ( SSPCON2bits.PEN = 0 )



/***************** Section : Data Type Declarations *****************/
typedef struct 
{
    uint8 i2c_mode_cfg ;
    uint8 i2c_mode : 1 ;
    uint8 i2c_slew_rate : 1 ;
    uint8 i2c_SMBus_control : 1 ;
    uint8 i2c_general_call : 1 ;
    uint8 i2c_master_rec_mode : 1 ;
    uint8 i2c_Slave_Add  ;
    uint8 i2c_reserved : 3 ;
/* Interrupt Priority configuration */
#if _INTERRUPT_PERIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
        interrupt_periority_cfg     mssp_i2c_priority ;
        interrupt_periority_cfg     mssp_i2c_bus_col_priority ;
#endif    
}i2c_config_t;



typedef struct
{
    uint32 i2c_clock ;                                                           /* for Master Clock Frequency */
    /* Interrupt Configurations */
#if _MSSP_I2C_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    void (*I2C_Report_Write_Collision) (void) ;           /* Write Collision Indicator*/
    void (*I2C_Default_Interrupt_Handler) (void) ;     /*  Default Interrupt Handler */
    void (*I2C_Report_Receive_Overflow) (void) ;      /* Receive Overflow Indicator */
#endif
    i2c_config_t i2c_config ;
}mssp_i2c_t;
/***************** Section : Function Declarations *****************/
Std_ReturnType MSSP_I2C_Init                                                ( const mssp_i2c_t *i2c_Obj);
Std_ReturnType MSSP_I2C_DeInit                                           ( const mssp_i2c_t *i2c_Obj);
Std_ReturnType MSSP_I2C_Master_Send_Start                    ( const mssp_i2c_t *i2c_Obj);
Std_ReturnType MSSP_I2C_Master_Send_Repeated_Start ( const mssp_i2c_t *i2c_Obj);
Std_ReturnType MSSP_I2C_Master_Send_Stop                    ( const mssp_i2c_t *i2c_Obj);
Std_ReturnType MSSP_I2C_Master_Write_Blocking            ( const mssp_i2c_t *i2c_Obj , uint8 data , uint8 *ack);
Std_ReturnType MSSP_I2C_Master_Write_Not_Blocking    ( const mssp_i2c_t *i2c_Obj , uint8 data , uint8 *ack);
Std_ReturnType MSSP_I2C_Master_Read_Blocking            ( const mssp_i2c_t *i2c_Obj , uint8 *data , uint8 ack);
Std_ReturnType MSSP_I2C_Master_Read_Not_Blocking    ( const mssp_i2c_t *i2c_Obj , uint8 *data , uint8 ack);

#endif	/* HAL_I2C_H */

