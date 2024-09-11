/* 
 * File:   hal_usart.h
 * Author: Ziad Elmekawy
 *
 * Created on 16 August, 2024, 08:18 PM
 */
#ifndef HAL_USART_H
#define	HAL_USART_H
/*************** Section : includes ****************/
#include "pic18f4620.h"
#include "hal_usart_cfg.h"
#include "../MCAL_std_Types.h"
#include "../GPIO/hal_GPIO.h"
#include "../Interrupt/mcal_internal_interrupt.h"

/**************** Section : Macro Declarations *****************/
/*  ^-^  EUSART MODULE  ^-^  */
/* Enable / Disable EUSART Mode */
#define EUSART_MODULE_DISABLE            0
#define EUSART_MODULE_ENABLE             1
/* Selecting EUSART Mode */
#define EUSART_ASYNCHRONOUS_MODE            0
#define EUSART_SYNCHRONOUS_MODE             1
/* Baud Rate Generator Asynchronous speed mode */
#define EUSART_ASYNCHRONOUS_LOW_SPEED       0
#define EUSART_ASYNCHRONOUS_HIGH_SPEED      1
/* Baud Rate Generator Register Size */
#define EUSART_8BIT_BAUDRATE_GEN            0
#define EUSART_16BIT_BAUDRATE_GEN           1

/*  ^-^  TRANSMITER  ^-^  */
/* EUSART Transmit Enable */
#define EUSART_ASYNCHRONOUS_TX_DISABLE      0
#define EUSART_ASYNCHRONOUS_TX_ENABLE       1
/* EUSART Transmit Interrupt Enable */
#define EUSART_ASYNCHRONOUS_INTERRUPT_TX_DISABLE      0
#define EUSART_ASYNCHRONOUS_INTERRUPT_TX_ENABLE       1
/* EUSART 9-Bit Transmit Enable */
#define EUSART_ASYNCHRONOUS_9BIT_TX_DISABLE  0
#define EUSART_ASYNCHRONOUS_9BIT_TX_ENABLE   1

/*  ^-^  RECEIVER  ^-^  */
/* EUSART Receiver Enable */
#define EUSART_ASYNCHRONOUS_RX_DISABLE      0
#define EUSART_ASYNCHRONOUS_RX_ENABLE       1
/* EUSART Receiver Interrupt Enable */
#define EUSART_ASYNCHRONOUS_INTERRUPT_RX_DISABLE      0
#define EUSART_ASYNCHRONOUS_INTERRUPT_RX_ENABLE       1
/* EUSART 9-Bit Receiver Enable */
#define EUSART_ASYNCHRONOUS_9BIT_RX_DISABLE  0
#define EUSART_ASYNCHRONOUS_9BIT_RX_ENABLE   1

/*  ^-^  ERROR ^-^  */
/* EUSART Framing Error */
#define EUSART_FRAMING_ERROR_CLEARED        0
#define EUSART_FRAMING_ERROR_DETECTED       1
/* EUSART Overrun Error */
#define EUSART_OVERRUN_ERROR_CLEARED        0
#define EUSART_OVERRUN_ERROR_DETECTED       1


typedef enum 
{
    BAUDRATE_ASYN_8BIT_LOW_SPEED = 0 ,
    BAUDRATE_ASYN_8BIT_HIGH_SPEED ,
    BAUDRATE_ASYN_16BIT_LOW_SPEED  ,
    BAUDRATE_ASYN_16BIT_HIGH_SPEED ,
    BAUDRATE_SYN_8BIT  ,
    BAUDRATE_SYN_16BIT
}baudrate_gen_t;

typedef struct 
{
    uint8 usart_tx_reserved : 5 ;
    uint8 usart_tx_enable : 1 ;
    uint8 usart_tx_interrupt_enable : 1 ;
    uint8 usart_tx_9bit_enable : 1 ;   
    interrupt_periority_cfg usart_tx_priority ;
}usart_tx_cfg_t;

typedef struct 
{
    uint8 usart_rx_reserved : 5 ;
    uint8 usart_rx_enable : 1 ;
    uint8 usart_rx_interrupt_enable : 1 ;
    uint8 usart_rx_9bit_enable : 1 ;   
    interrupt_periority_cfg usart_rx_priority ;
}usart_rx_cfg_t;

typedef union 
{
    struct 
    {
        uint8 usart_tx_reserved : 6 ;
        uint8 usart_ferr : 1 ;
        uint8 usart_oerr : 1 ;
    };
    uint8 status ;
}usart_error_status_t;

typedef struct 
{
    uint32 baudrate ;
    baudrate_gen_t baudrate_gen_config ;
    usart_tx_cfg_t usart_tx_cfg ;
    usart_rx_cfg_t usart_rx_cfg ;
    usart_error_status_t error_status ;
#if _EUSART_Tx_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    void (*EUSART_TxDefaultInterruptHandler)(void);
    void (*EUSART_RxDefaultInterruptHandler)(void);
    void (*EUSART_FramingErrorHandler)(void);
    void (*EUSART_OverrunErrorHandler)(void);   
#endif
}usart_t;

/***************** Section : Macro Function Declarations *****************/


/***************** Section : Data Type Declarations *****************/


/***************** Section : Function Declarations *****************/
Std_ReturnType EUSART_ASYNC_Init      (const usart_t *eusart );
Std_ReturnType EUSART_ASYNC_DeInit    (const usart_t *eusart );

Std_ReturnType EUSART_ASYNC_ReadByteBlocking        ( uint8 *data );
Std_ReturnType EUSART_ASYNC_ReadByteNonBlocking     ( uint8 *data );
Std_ReturnType EUSART_ASYNC_Rx_Restart              (void);

Std_ReturnType EUSART_ASYNC_WriteByteBlocking   (uint8 data );
Std_ReturnType EUSART_ASYNC_WriteStringBlocking (uint8 *data , uint16 str_len);
Std_ReturnType EUSART_ASYNC_WriteByteNonBlocking   (uint8 data );
Std_ReturnType EUSART_ASYNC_WriteStringNonBlocking (uint8 *data , uint16 str_len);

#endif	/* HAL_USART_H */

