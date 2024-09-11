/* 
 * File:   hal_usart.h
 * Author: Ziad Elmekawy
 *
 * Created on 16 August, 2024, 08:18 PM
 */
/************************ Section : Includes ***************/
#include <pic18f4620.h>

#include "hal_usart.h"

/************************ Helper Function *****************/
static void EUSART_Baud_Rate_Calculation (const usart_t * eusart);
static void EUSART_ASYNC_Tx_Init(const usart_t *eusart);
static void EUSART_ASYNC_Rx_Init(const usart_t *eusart);

#if _EUSART_Tx_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    static void (* EUSART_Tx_InterruptHandler)(void) = NULL;
#endif
#if _EUSART_Rx_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    static void (* EUSART_Rx_InterruptHandler)(void) = NULL;
    static void (* EUSART_FramingErrorHandler)(void) = NULL;
    static void (* EUSART_OverrunErrorHandler)(void) = NULL;
#endif
/************** Section : Function Definitions *************/
/**
 * @NAME  EUSART_ASYNC_Init
 * @param eusart
 * @return Status of the function 
 *              (E_OK) : The function done successfully
 *              (E_NOK): The function has issue to perform this action
 */
Std_ReturnType EUSART_ASYNC_Init      (const usart_t *eusart )
{
    Std_ReturnType ret = E_NOK ;
    if(NULL == eusart)
    {
        ret = E_NOK ;
    }
    else 
    {
        RCSTAbits.SPEN = EUSART_MODULE_DISABLE ;
        TRISCbits.RC6 = 1 ;
        TRISCbits.RC7 = 1 ;
        EUSART_Baud_Rate_Calculation(eusart);
        EUSART_ASYNC_Tx_Init(eusart);
        EUSART_ASYNC_Rx_Init(eusart);
        RCSTAbits.SPEN = EUSART_MODULE_ENABLE ;
        ret = E_OK ;
    }
    return ret ;
}

/**
 * @NAME  EUSART_ASYNC_DeInit
 * @param eusart
 * @return Status of the function 
 *              (E_OK) : The function done successfully
 *              (E_NOK): The function has issue to perform this action
 */
Std_ReturnType EUSART_ASYNC_DeInit    (const usart_t *eusart )
{
    Std_ReturnType ret = E_NOK ;
    if(NULL == eusart)
    {
        ret = E_NOK ;
    }
    else 
    {
        RCSTAbits.SPEN = EUSART_MODULE_DISABLE;
        ret = E_OK ;
    }
    return ret ;
}

/**
 * @NAME  EUSART_ASYNC_ReadByteBlocking
 * @param eusart
 * @param data
 * @return Status of the function 
 *              (E_OK) : The function done successfully
 *              (E_NOK): The function has issue to perform this action 
 */
Std_ReturnType EUSART_ASYNC_ReadByteBlocking  ( uint8 *data )
{
    Std_ReturnType ret = E_NOK ;
    if(NULL == data)
    {
        ret = E_NOK ;
    }
    else 
    {
        while(!PIR1bits.RCIF);
        *data = RCREG ;
        ret = E_OK ;
    }
    return ret ;
}

/**
 * @NAME EUSART_ASYNC_ReadByteNonBlocking
 * @param data
 * @return Status of the function 
 *              (E_OK) : The function done successfully
 *              (E_NOK): The function has issue to perform this action
 */
Std_ReturnType EUSART_ASYNC_ReadByteNonBlocking  ( uint8 *data )
{
    Std_ReturnType ret = E_NOK ;
    if(NULL == data)
    {
        ret = E_NOK ;
    }
    else 
    {
        if (1 == PIR1bits.RCIF )
        {
            *data = RCREG ;
            ret = E_OK ;
        }
        else 
        {
            ret = E_NOK ;
        }
    }
    return ret ;
}

/**
 * @name  EUSART_ASYNC_Rx_Restart
 * @brief For Framing error 
 * @return Status of the function 
 *              (E_OK) : The function done successfully
 *              (E_NOK): The function has issue to perform this action
 */
Std_ReturnType EUSART_ASYNC_Rx_Restart (void)          
{
    Std_ReturnType ret = E_OK ;
    RCSTAbits.CREN = 0 ;    /* Disable Receiver  */
    RCSTAbits.CREN = 1 ;    /* Enable Receiver  */
    return ret ;
}


/**
 * @NAME  EUSART_ASYNC_WriteByteBlocking
 * @param eusart
 * @param data
 * @return Status of the function 
 *              (E_OK) : The function done successfully
 *              (E_NOK): The function has issue to perform this action
 */
Std_ReturnType EUSART_ASYNC_WriteByteBlocking (uint8 data )
{
    Std_ReturnType ret = E_OK ;
    while(!TXSTAbits.TRMT);                                                     /* @NOTE While TRMT register is full, still in the loop  */ 
#if _EUSART_Tx_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    EUSART_Tx_InterruptEnable() ;                                               /* @NOTE here, we enable interrupt to stop interrupt high rate [ explanation in notebook ] */ 
#endif
    TXREG = data ; 
    return ret ;
}

/**
 * @NAME  EUSART_ASYNC_WriteStringBlocking
 * @param data
 * @param str_length
 * @return Status of the function 
 *              (E_OK) : The function done successfully
 *              (E_NOK): The function has issue to perform this action
 */
Std_ReturnType EUSART_ASYNC_WriteStringBlocking (uint8 *data , uint16 str_len)
{
    Std_ReturnType ret = E_NOK ;
    uint16 l_counter = 0 ;
    if(NULL == data)
    {
        ret = E_NOK ;
    }
    else 
    {
        for(l_counter =0 ; l_counter< str_len ; l_counter++)
        {
            ret = EUSART_ASYNC_WriteByteBlocking(data[l_counter]) ;
        }
    }
    return ret ;
}

/**
 * @name  EUSART_ASYNC_WriteByteNonBlocking
 * @param data
 * @return Status of the function 
 *              (E_OK) : The function done successfully
 *              (E_NOK): The function has issue to perform this action
 */
Std_ReturnType EUSART_ASYNC_WriteByteNonBlocking   (uint8 data )
{
    Std_ReturnType ret = E_NOK ;
    if(1 == TXSTAbits.TRMT)
    {
#if _EUSART_Tx_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        EUSART_Tx_InterruptEnable() ;                                           /* @NOTE here, we enable interrupt to stop interrupt high rate [ explanation in notebook ] */ 
#endif
        TXREG = data ;
    }
    else { /* Nothing ^-* */ } 
    ret = E_OK ;
    return ret ;
}

/**
 * @name  EUSART_ASYNC_WriteStringNonBlocking
 * @param data
 * @param str_length
 * @return Status of the function 
 *              (E_OK) : The function done successfully
 *              (E_NOK): The function has issue to perform this action
 */
Std_ReturnType EUSART_ASYNC_WriteStringNonBlocking (uint8 *data , uint16 str_len)
{
    Std_ReturnType ret = E_NOK ;
    uint16 l_counter = 0 ;
    if (NULL == data)
    {
        ret = E_NOK ;
    }
    else
    {
        for(l_counter =0 ; l_counter< str_len ; l_counter++)
        {
            ret = EUSART_ASYNC_WriteByteBlocking(data[l_counter]) ;
        }
        ret = E_OK ;
    }
    return ret ;
}

/***************************************** Helper Function ***************************/
/**
 * @NAME  EUSART_Baud_Rate_Calculation
 * @brief For EUSART_Baud_Rate_Calculation and return the value in SPBRG register 
 * @param eusart
 * @RETURN void
 */
static void EUSART_Baud_Rate_Calculation (const usart_t * eusart)
{
    f32 Baud_Rate_Temp = 0 ;
    switch(eusart->baudrate_gen_config)
    {
        case BAUDRATE_ASYN_8BIT_LOW_SPEED :
            TXSTAbits.SYNC = EUSART_ASYNCHRONOUS_MODE ;
            TXSTAbits.BRGH = EUSART_ASYNCHRONOUS_LOW_SPEED ;
            BAUDCONbits.BRG16 = EUSART_8BIT_BAUDRATE_GEN ;
            Baud_Rate_Temp = (((_XTAL_FREQ / (f32)(eusart->baudrate)) / 64)- 1) ;
            break ;
        case BAUDRATE_ASYN_8BIT_HIGH_SPEED :
            TXSTAbits.SYNC = EUSART_ASYNCHRONOUS_MODE ;
            TXSTAbits.BRGH = EUSART_ASYNCHRONOUS_HIGH_SPEED ;
            BAUDCONbits.BRG16 = EUSART_8BIT_BAUDRATE_GEN ;
            Baud_Rate_Temp = (((_XTAL_FREQ / (f32)(eusart->baudrate)) / 16)- 1) ;
            break ;
        case BAUDRATE_ASYN_16BIT_LOW_SPEED :
            TXSTAbits.SYNC = EUSART_ASYNCHRONOUS_MODE ;
            TXSTAbits.BRGH = EUSART_ASYNCHRONOUS_LOW_SPEED ;
            BAUDCONbits.BRG16 = EUSART_16BIT_BAUDRATE_GEN ;
            Baud_Rate_Temp = (((_XTAL_FREQ / (f32)(eusart->baudrate)) / 16)- 1) ;
            break ;
        case BAUDRATE_ASYN_16BIT_HIGH_SPEED :
            TXSTAbits.SYNC = EUSART_ASYNCHRONOUS_MODE ;
            TXSTAbits.BRGH = EUSART_ASYNCHRONOUS_HIGH_SPEED ;
            BAUDCONbits.BRG16 = EUSART_16BIT_BAUDRATE_GEN ;
            Baud_Rate_Temp = (((_XTAL_FREQ / (f32)(eusart->baudrate)) / 4)- 1) ;
            break ;
        case BAUDRATE_SYN_8BIT :
            TXSTAbits.SYNC = EUSART_SYNCHRONOUS_MODE ;
            BAUDCONbits.BRG16 = EUSART_8BIT_BAUDRATE_GEN ;
            Baud_Rate_Temp = (((_XTAL_FREQ / (f32)(eusart->baudrate)) / 4)- 1) ;
            break ;
        case BAUDRATE_SYN_16BIT :
            TXSTAbits.SYNC = EUSART_SYNCHRONOUS_MODE ;
            BAUDCONbits.BRG16 = EUSART_16BIT_BAUDRATE_GEN ;
            Baud_Rate_Temp = (((_XTAL_FREQ / (f32)(eusart->baudrate)) / 4)- 1) ;
            break ;
    }
    SPBRG = (uint8)((uint32)Baud_Rate_Temp) ;
    SPBRGH = (uint8)(((uint32)Baud_Rate_Temp) >> 8 ) ;
}

/**
 * @NAME  EUSART_ASYNC_Tx_Init
 * @param eusart
 * @RETURN void
 */
static void EUSART_ASYNC_Tx_Init(const usart_t *eusart)
{
    /* EUSART @TRANSMIT_ENABLE Configuration */
    if ( EUSART_ASYNCHRONOUS_TX_ENABLE == eusart->usart_tx_cfg.usart_tx_enable)
    {
        TXSTAbits.TXEN = EUSART_ASYNCHRONOUS_TX_ENABLE ;
        EUSART_Tx_InterruptHandler = eusart->EUSART_TxDefaultInterruptHandler ;
        /*========= EUSART Transmit @INTERRUPT Enable Configuration =========*/
        if ( EUSART_ASYNCHRONOUS_INTERRUPT_TX_ENABLE == eusart->usart_tx_cfg.usart_tx_interrupt_enable)
        {
            PIE1bits.TXIE = EUSART_ASYNCHRONOUS_INTERRUPT_TX_ENABLE ;
/* Interrupt Configuration */
#if _EUSART_Tx_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
            EUSART_Tx_InterruptEnable();
/* Interrupt Priority configuration */
#if _INTERRUPT_PERIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
        INTERRUPT_PeriortyLevelEnable();
        if (eusart->usart_tx_cfg.usart_tx_priority == INTERRUPT_HIGH_PRIORITY)
        {
            /* Enable all high-priority interrupts */
            INTERRUPT_GlobalInterruptHighEnable();
            EUSART_Tx_HighPrioritySet();
        }
        else if (eusart->usart_tx_cfg.usart_tx_priority == INTERRUPT_LOW_PRIORITY)
        {
            /* Enable all low-priority interrupts */
            INTERRUPT_GlobalInterruptLowEnable();
            EUSART_Tx_LowPrioritySet();
        }
        else {/* Nothing ^-* */ } 
#else 
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
#endif        
#endif
        }
        else if ( EUSART_ASYNCHRONOUS_INTERRUPT_TX_DISABLE == eusart->usart_tx_cfg.usart_tx_interrupt_enable)
        {
            PIE1bits.TXIE = EUSART_ASYNCHRONOUS_INTERRUPT_TX_DISABLE ;
        }
        else {/* Nothing ^-* */ } 

        /*========= EUSART @_9_Bit Transmit Enable Configuration =========*/
        if ( EUSART_ASYNCHRONOUS_9BIT_TX_ENABLE == eusart->usart_tx_cfg.usart_tx_9bit_enable)
        {
            TXSTAbits.TX9 = EUSART_ASYNCHRONOUS_9BIT_TX_ENABLE ;
        }
        else if ( EUSART_ASYNCHRONOUS_9BIT_TX_DISABLE == eusart->usart_tx_cfg.usart_tx_9bit_enable)
        {
            TXSTAbits.TX9 = EUSART_ASYNCHRONOUS_9BIT_TX_DISABLE ;
        }
        else {/* Nothing ^-* */ } 
    }
    else {/* Nothing ^-* */ }
}

/**
 * @NAME  EUSART_ASYNC_Rx_Init
 * @param eusart
 * @RETURN void
 */
static void EUSART_ASYNC_Rx_Init(const usart_t *eusart)
{
    /* EUSART @RECEIVER_ENABLE Configuration */
    if(EUSART_ASYNCHRONOUS_RX_ENABLE == eusart->usart_rx_cfg.usart_rx_enable)
    {
        RCSTAbits.CREN = EUSART_ASYNCHRONOUS_RX_ENABLE ;
        EUSART_Rx_InterruptHandler = eusart->EUSART_RxDefaultInterruptHandler ;
        EUSART_FramingErrorHandler = eusart->EUSART_FramingErrorHandler ;
        EUSART_OverrunErrorHandler = eusart->EUSART_OverrunErrorHandler ;
        /*========= EUSART Receiver @INTERRUPT Enable Configuration =========*/
        if (EUSART_ASYNCHRONOUS_INTERRUPT_RX_ENABLE == eusart->usart_rx_cfg.usart_rx_interrupt_enable )
        {
            PIE1bits.RCIE = EUSART_ASYNCHRONOUS_INTERRUPT_RX_ENABLE ;
/* Interrupt Configuration */
#if _EUSART_Rx_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
            EUSART_Rx_InterruptEnable();
/* Interrupt Priority configuration */
#if _INTERRUPT_PERIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
        INTERRUPT_PeriortyLevelEnable();
        if (eusart->usart_rx_cfg.usart_rx_priority == INTERRUPT_HIGH_PRIORITY)
        {
            /* Enable all high-priority interrupts */
            INTERRUPT_GlobalInterruptHighEnable();
            EUSART_Rx_HighPrioritySet();
        }
        else if (eusart->usart_rx_cfg.usart_rx_priority == INTERRUPT_LOW_PRIORITY)
        {
            /* Enable all low-priority interrupts */
            INTERRUPT_GlobalInterruptLowEnable();
            EUSART_Rx_LowPrioritySet();
        }
        else {/* Nothing ^-* */ } 
#else 
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
#endif        
#endif
        }
        else if (EUSART_ASYNCHRONOUS_INTERRUPT_RX_DISABLE == eusart->usart_rx_cfg.usart_rx_interrupt_enable )
        {
            PIE1bits.RCIE = EUSART_ASYNCHRONOUS_INTERRUPT_RX_DISABLE ;
        }
        else 
        { /* Nothing ^-* */ }
        /*========= EUSART @_9_Bit Receiver Enable Configuration =========*/
        if (EUSART_ASYNCHRONOUS_9BIT_RX_ENABLE == eusart->usart_rx_cfg.usart_rx_9bit_enable )
        {
            RCSTAbits.RX9 = EUSART_ASYNCHRONOUS_9BIT_RX_ENABLE ;
        }
        else if (EUSART_ASYNCHRONOUS_9BIT_RX_DISABLE == eusart->usart_rx_cfg.usart_rx_9bit_enable )
        {
            RCSTAbits.RX9 = EUSART_ASYNCHRONOUS_9BIT_RX_DISABLE ;
        }
        else 
        { /* Nothing ^-* */ }
    }
    else 
    { /* Nothing ^-* */ }
}

/***************************************** ISR Functions **************************/
/* For EUSART ISR */
void EUSART_Tx_ISR (void)
{
    EUSART_Tx_InterruptDisable() ;                                              /* @NOTE here, we disable interrupt to stop interrupt high rate [ explanation in notebook ] */ 
    if (EUSART_Tx_InterruptHandler)
    {
        EUSART_Tx_InterruptHandler();
    }
    else { /* Nothing ^-* */ }
}
void EUSART_Rx_ISR (void)
{
    if (EUSART_Rx_InterruptHandler)
    {
        EUSART_Rx_InterruptHandler();
    }
    else { /* Nothing ^-* */ }
    if (EUSART_FramingErrorHandler)
    {
        EUSART_FramingErrorHandler();
    }
    else { /* Nothing ^-* */ }
    if (EUSART_OverrunErrorHandler)
    {
        EUSART_OverrunErrorHandler();
    }
    else { /* Nothing ^-* */ }
}
