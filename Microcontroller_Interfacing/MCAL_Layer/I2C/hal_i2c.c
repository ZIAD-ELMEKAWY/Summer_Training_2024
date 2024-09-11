/* 
 * File:   hal_i2c.c
 * Author: Ziad Elmekawy
 *
 * Created on 28 August, 2024, 01:54 PM
 */

/*************** Section : includes ****************/
#include <pic18f4620.h>
#include "hal_i2c.h"

/****************************** Section : Helper Function *********************/
static inline void MSSP_I2C_Mode_GPIO_Config(void);
static inline void MSSP_I2C_Mode_Clock_Config( const mssp_i2c_t *i2c_Obj );
static inline void MSSP_I2C_Interrupt_Config( const mssp_i2c_t *i2c_Obj );
static inline void MSSP_I2C_Slave_Mode_Config( const mssp_i2c_t *i2c_Obj ) ;

#if _MSSP_I2C_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
static void (*I2C_Report_Write_Collision) (void) = NULL  ;
static void (*I2C_Default_Interrupt_Handler) (void) = NULL  ;
static void (*I2C_Report_Receive_Overflow) (void) = NULL   ;
#endif

/***************** Section : Function Definitions ****************/
/**
 * @Name  MSSP_I2C_Init
 * @param i2c_Obj
 * @return Status of the function 
 *              (E_OK) : The function done successfully
 *              (E_NOK): The function has issue to perform this action
 */
Std_ReturnType MSSP_I2C_Init        (const mssp_i2c_t *i2c_Obj)
{
    Std_ReturnType ret = E_NOK ;
    if(i2c_Obj == NULL)
    {
        ret = E_NOK ;
    }
    else
    {
        /* Disable MSSP I2C Module */
        MSSP_MODULE_DISABLE_CFG();
        /* MSSP I2C Select Mode */
        if ( i2c_Obj->i2c_config.i2c_mode == MSSP_I2C_MASTER_MODE )
        {/* MSSP I2C Master Mode Configurations */
            /* MSSP I2C Master Mode Clock Configurations */
            MSSP_I2C_Mode_Clock_Config(i2c_Obj);
        }
        else if ( i2c_Obj->i2c_config.i2c_mode == MSSP_I2C_SLAVE_MODE )
        { /* MSSP I2C Slave Mode Configurations */
            /* MSSP I2C Slave Mode General Call Configurations */
            if( i2c_Obj->i2c_config.i2c_general_call == I2C_GENERAL_CALL_ENABLE )
            {
                I2C_GENERAL_CALL_ENABLE_CFG( ) ;
            }
            else if( i2c_Obj->i2c_config.i2c_general_call == I2C_GENERAL_CALL_DISABLE )
            {
                I2C_GENERAL_CALL_DISABLE_CFG( ) ;
            }
            else { /* ^--^ Nothing *--^ */ }
            /* Clear the write collision detect */
            SSPCON1bits.WCOL = 0  ;              /* No collision */
            /* Clear the receive overflow Indicator */
            SSPCON1bits.SSPOV = 0 ;             /* No overflow  */
            /* Release the clock */
            SSPCON1bits.CKP = 1 ;                /* Clock Release -> 1 */
            /* Assign the I2C Slave Address */
            SSPADD = i2c_Obj->i2c_config.i2c_Slave_Add ;
            /* MSSP I2C Slave Mode Configurations */
            MSSP_I2C_Slave_Mode_Config(i2c_Obj); 
        }
        else { /* ^--^ Nothing *--^ */ }
        /* MSSP I2C Mode GPIO Configurations */
        MSSP_I2C_Mode_GPIO_Config();
        /* MSSP I2C Slew Rate Control */
        if( i2c_Obj->i2c_config.i2c_slew_rate == I2C_SLEW_RATE_ENABLE )
         {
                I2C_SLEW_RATE_ENABLE_CFG( ) ;
         }
         else if( i2c_Obj->i2c_config.i2c_general_call == I2C_SLEW_RATE_DISABLE )
         {
                I2C_SLEW_RATE_DISABLE_CFG( ) ;
         }
         else { /* ^--^ Nothing *--^ */ }
        /* MSSP I2C SMBus Control  */
        if( i2c_Obj->i2c_config.i2c_SMBus_control == I2C_SMBus_ENABLE )
         {
                I2C_SMBus_ENABLE_CFG( )  ;
         }
         else if( i2c_Obj->i2c_config.i2c_SMBus_control == I2C_SMBus_DISABLE )
         {
                I2C_SMBus_DISABLE_CFG( ) ;
         }
         else { /* ^--^ Nothing *--^ */ }
        /* Interrupt Configurations */
#if _MSSP_I2C_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE 
        MSSP_I2C_Interrupt_Config(i2c_Obj );
#endif|
        /* Enable MSSP I2C Module */
        MSSP_MODULE_ENABLE_CFG();
        ret = E_OK ;
    }
    return ret ;
}

/**
 * @name  MSSP_I2C_DeInit
 * @param i2c_Obj
 * @return Status of the function 
 *              (E_OK) : The function done successfully
 *              (E_NOK): The function has issue to perform this action
 */
Std_ReturnType MSSP_I2C_DeInit    (const mssp_i2c_t *i2c_Obj)
{
    Std_ReturnType ret = E_NOK ;
    if(i2c_Obj == NULL)
    {
        ret = E_NOK;
    }
    else
    {
        /* Disable MSSP I2C Module */
        MSSP_MODULE_DISABLE_CFG();
        /* Interrupt Configurations */
#if _MSSP_I2C_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        MSSP_I2C_InterruptDisable()  ;
        MSSP_I2C_Bus_COL_InterruptDisable();
#endif
        ret = E_OK ;
    }
    return ret ;
}

/**
 * @Name  MSSP_I2C_Master_Send_Start
 * @param i2c_Obj
 * @return Status of the function 
 *              (E_OK) : The function done successfully
 *              (E_NOK): The function has issue to perform this action
 */
Std_ReturnType MSSP_I2C_Master_Send_Start    (const mssp_i2c_t *i2c_Obj)
{
    Std_ReturnType ret = E_NOK ;
    if(i2c_Obj == NULL)
    {
        ret = E_NOK;
    }
    else
    {
        /* Initiates start condition on SDA and SCL pins */
        SSPCON2bits.SEN = 1 ;                                     /* Automatically removed by hardware  */
        /* wait for the completion of the start condition */
        while( SSPCON2bits.SEN );
        /* Clear the MSSP Interrupt Flag bit -> SSPIF */
        PIR1bits.SSPIF = 0;
        /* Report the start condition Detection */
        if( I2C_START_BIT_DETECTED == SSPSTATbits.S )
        {
            ret = E_OK ;
        }
        else 
        {
            ret = E_NOK;
        }
    }
    return ret ;
}

/**
 * @Name  MSSP_I2C_Master_Send_Repeated_Start
 * @param i2c_Obj
 * @return Status of the function 
 *              (E_OK) : The function done successfully
 *              (E_NOK): The function has issue to perform this action
 */
Std_ReturnType MSSP_I2C_Master_Send_Repeated_Start    (const mssp_i2c_t *i2c_Obj)
{
    Std_ReturnType ret = E_NOK ;
    if(i2c_Obj == NULL)
    {
        ret = E_NOK;
    }
    else
    {
        /* Initiates Repeated start condition on SDA and SCL pins */
        SSPCON2bits.RSEN = 1 ;               /* Automatically removed by hardware  */
        /* wait for the completion of the start condition */
        while( SSPCON2bits.RSEN );
        /* Clear the MSSP Interrupt Flag bit -> SSPIF */
        PIR1bits.SSPIF = 0;
        ret = E_OK ;
    }
    return ret ;
}

/**
 * @Name  MSSP_I2C_Master_Send_Stop
 * @param i2c_Obj
 * @return Status of the function 
 *              (E_OK) : The function done successfully
 *              (E_NOK): The function has issue to perform this action
 */
Std_ReturnType MSSP_I2C_Master_Send_Stop    (const mssp_i2c_t *i2c_Obj)
{
    Std_ReturnType ret = E_NOK ;
    if(i2c_Obj == NULL)
    {
        ret = E_NOK;
    }
    else
    {
        /* Initiates stop condition on SDA and SCL pins */
        SSPCON2bits.PEN = 1 ;                                    /* Automatically removed by hardware  */
        /* wait for the completion of the stop condition */
        while( SSPCON2bits.PEN );
        /* Clear the MSSP Interrupt Flag bit -> SSPIF */
        PIR1bits.SSPIF = 0;
        /* Report the start condition Detection */
        if( I2C_STOP_BIT_DETECTED == SSPSTATbits.P )
        {
            ret = E_OK ;
        }
        else 
        {
            ret = E_NOK;
        }
        ret = E_OK ;
    }
    return ret ;
}

/**
 * @Name  MSSP_I2C_Write_Not_Blocking
 * @param i2c_Obj
 * @param data
 * @return Status of the function 
 *              (E_OK) : The function done successfully
 *              (E_NOK): The function has issue to perform this action
 */
Std_ReturnType MSSP_I2C_Master_Write_Not_Blocking    (const mssp_i2c_t *i2c_Obj , uint8 data , uint8 *ack)
{
    Std_ReturnType ret = E_NOK ;
    if((i2c_Obj == NULL) || (ack == NULL))
    {
        ret = E_NOK;
    }
    else
    {
        /* Write data to the data register */
        SSPBUF =  data ;
        /* Wait the transmission to be completed */
        if ( SSPSTATbits.BF == 1 )
        {
            /* Clear the MSSP Interrupt Flag bit -> SSPIF */
            PIR1bits.SSPIF = 0;
            /* Report the acknowledge received from the slave  */
            if(I2C_ACK_RECEIVED_FROM_SLAVE == SSPCON2bits.ACKSTAT)
            {
                *ack = I2C_ACK_RECEIVED_FROM_SLAVE ;
            }
            else if(I2C_ACK_NOT_RECEIVED_FROM_SLAVE == SSPCON2bits.ACKSTAT)
            {
                *ack = I2C_ACK_NOT_RECEIVED_FROM_SLAVE ;
            }
            else { /* ^--^ Nothing *--^ */ }
        }
        else { /* ^--^ Nothing *--^*/ }
        
        ret = E_OK ;
    }
    return ret ;
}

/**
 * @Name  MSSP_I2C_Write
 * @param i2c_Obj
 * @param data
 * @return Status of the function 
 *              (E_OK) : The function done successfully
 *              (E_NOK): The function has issue to perform this action
 */
Std_ReturnType MSSP_I2C_Master_Write_Blocking    (const mssp_i2c_t *i2c_Obj , uint8 data , uint8 *ack)
{
    Std_ReturnType ret = E_NOK ;
    if((i2c_Obj == NULL) || (ack == NULL))
    {
        ret = E_NOK;
    }
    else
    {
        /* Write data to the data register */
        SSPBUF =  data ;
        /* Wait the transmission to be completed */
        while( SSPSTATbits.BF );
        /* Clear the MSSP Interrupt Flag bit -> SSPIF */
        PIR1bits.SSPIF = 0 ;
        /* Report the acknowledge received from the slave  */
        if(I2C_ACK_RECEIVED_FROM_SLAVE == SSPCON2bits.ACKSTAT)
        {
            *ack = I2C_ACK_RECEIVED_FROM_SLAVE ;
        }
        else if(I2C_ACK_NOT_RECEIVED_FROM_SLAVE == SSPCON2bits.ACKSTAT)
        {
            *ack = I2C_ACK_NOT_RECEIVED_FROM_SLAVE ;
        }
        else { /* ^--^ Nothing *--^ */ }
        ret = E_OK ;
    }
    return ret ;
}

/**
 * @Name  MSSP_I2C_Read
 * @param i2c_Obj
 * @param data
 * @return Status of the function 
 *              (E_OK) : The function done successfully
 *              (E_NOK): The function has issue to perform this action
 */
Std_ReturnType MSSP_I2C_Master_Read_Blocking    (const mssp_i2c_t *i2c_Obj , uint8 *data , uint8 ack)
{
    Std_ReturnType ret = E_NOK ;
    if((i2c_Obj == NULL) || (NULL == data))
    {
        ret = E_NOK;
    }
    else
    {
        /* Master Mode Receive Enable */
        I2C_MASTER_RECEIVE_ENABLE_CFG( );
        /* Wait for buffer full flag : Acoplete byte received */
        while(!SSPSTATbits.BF);
        /* copy the data registers to buffer variable */
        *data  = SSPBUF ;
        /* Send ACK or NACK after read */
        if (ack == I2C_MASTER_SEND_ACK)
        {
            SSPCON2bits.ACKDT = I2C_MASTER_SEND_ACK;         /* Acknowledge */
            SSPCON2bits.ACKEN = 1 ;                                                 /* Initiates Acknowledge sequence on SDA and SCL pins and transmit ACKDT data bit */
        }
        else if (ack == I2C_MASTER_SEND_NACK)
        {
            SSPCON2bits.ACKDT = I2C_MASTER_SEND_NACK;      /* Not-Acknowledge */
            SSPCON2bits.ACKEN = 1 ;                                                 /* Initiates Acknowledge sequence on SDA and SCL pins and transmit ACKDT data bit */
        }
        else { /* ^--^ Nothing *--^ */ }
        ret = E_OK ;
    }
    return ret ;
}

/**
 * @Name  MSSP_I2C_Master_Read_Not_Blocking
 * @param i2c_Obj
 * @param data
 * @return Status of the function 
 *              (E_OK) : The function done successfully
 *              (E_NOK): The function has issue to perform this action
 */
Std_ReturnType MSSP_I2C_Master_Read_Not_Blocking    (const mssp_i2c_t *i2c_Obj , uint8 *data , uint8 ack)
{
    Std_ReturnType ret = E_NOK ;
    if((i2c_Obj == NULL) || (NULL == data))
    {
        ret = E_NOK;
    }
    else
    {
        /* Master Mode Receive Enable */
        I2C_MASTER_RECEIVE_ENABLE_CFG( );
        /* Wait for buffer full flag : Acoplete byte received */
        if(SSPSTATbits.BF == 1)
        {
             /* copy the data registers to buffer variable */
            *data  = SSPBUF ;
            /* Send ACK or NACK after read */
            if (ack == I2C_MASTER_SEND_ACK)
            {
                SSPCON2bits.ACKDT = I2C_MASTER_SEND_ACK;         /* Acknowledge */
                SSPCON2bits.ACKEN = 1 ;                                                 /* Initiates Acknowledge sequence on SDA and SCL pins and transmit ACKDT data bit */
            }
            else if (ack == I2C_MASTER_SEND_NACK)
            {
                SSPCON2bits.ACKDT = I2C_MASTER_SEND_NACK;      /* Not-Acknowledge */
                SSPCON2bits.ACKEN = 1 ;                                                 /* Initiates Acknowledge sequence on SDA and SCL pins and transmit ACKDT data bit */
            }
            else { /* ^--^ Nothing *--^ */ }
        }
        else { /* ^--^ Nothing *--^ */ }
        ret = E_OK ;
    }
    return ret ;
}

#if _MSSP_I2C_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE 
/* ===================== ISR Function ====================== */
/**
 * @name MSSP_I2C_ISR
 * @return void 
 * @brief 
 */
void MSSP_I2C_ISR (void)
{
    MSSP_I2C_InterruptFlagClear();
    if(  I2C_Default_Interrupt_Handler )
    {
        I2C_Default_Interrupt_Handler();
    }
    else { /* ^--^ Nothing *--^ */ }
}

/**
 * @name MSSP_I2C_Bus_COL_ISR
 * @return void 
 * @brief 
 */
void MSSP_I2C_Bus_COL_ISR (void)
{
    MSSP_I2C_Bus_COL_InterruptFlagClear() ;
    if(  I2C_Report_Write_Collision )
    {
        I2C_Report_Write_Collision();
    }
    else { /* ^--^ Nothing *--^ */ }
}
#endif

/****************************** Section : Helper Function ***************************/
static inline void MSSP_I2C_Mode_GPIO_Config(void)
{
    TRISCbits.TRISC3 = 1 ;        /* Serial Clock ( SCL ) is input  */
    TRISCbits.TRISC4 = 1 ;        /* Serial Data  ( SDA ) is input  */
}

static inline void MSSP_I2C_Mode_Clock_Config( const mssp_i2c_t *i2c_Obj )
{
    SSPCON1bits.SSPM = i2c_Obj->i2c_config.i2c_mode_cfg  ;
    SSPADD = (uint8)(((_XTAL_FREQ / 4.0) / i2c_Obj->i2c_clock) - 1);
}

static inline void MSSP_I2C_Slave_Mode_Config( const mssp_i2c_t *i2c_Obj )
{
    SSPCON1bits.SSPM = i2c_Obj->i2c_config.i2c_mode_cfg ;
}

static inline void MSSP_I2C_Interrupt_Config( const mssp_i2c_t *i2c_Obj )
{
#if _MSSP_I2C_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE 
    MSSP_I2C_InterruptEnable();
        MSSP_I2C_Bus_COL_InterruptEnable();
        MSSP_I2C_InterruptFlagClear();
        MSSP_I2C_Bus_COL_InterruptFlagClear();
        I2C_Report_Write_Collision = i2c_Obj->I2C_Report_Write_Collision ;
        I2C_Default_Interrupt_Handler = i2c_Obj->I2C_Default_Interrupt_Handler ;
        I2C_Report_Receive_Overflow = i2c_Obj->I2C_Report_Receive_Overflow ;
         /* Interrupt Priority configuration */
#if _INTERRUPT_PERIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
         INTERRUPT_PeriortyLevelEnable();
         /* For I2C priority */
        if (i2c_Obj->i2c_config.mssp_i2c_priority == INTERRUPT_HIGH_PRIORITY) 
        {
            /* Enable all high-priority interrupts */
            INTERRUPT_GlobalInterruptHighEnable();
            MSSP_I2C_HighPrioritySet() ;
        }
        else if (i2c_Obj->i2c_config.mssp_i2c_priority == INTERRUPT_LOW_PRIORITY) 
        {
            /* Enable all unmasked peripheral interrupts */
            INTERRUPT_GlobalInterruptLowEnable();
            MSSP_I2C_LowPrioritySet() ;
        }
          /* For I2C bus collision priority  */
         if  (i2c_Obj->i2c_config.mssp_i2c_bus_col_priority == INTERRUPT_HIGH_PRIORITY)
        {
            /* Enable all high-priority interrupts */
            INTERRUPT_GlobalInterruptHighEnable();
            MSSP_I2C_Bus_COL_HighPrioritySet();
        }
        else if  (i2c_Obj->i2c_config.mssp_i2c_bus_col_priority == INTERRUPT_LOW_PRIORITY)
        {
            /* Enable all unmasked peripheral interrupts */
            INTERRUPT_GlobalInterruptLowEnable();
            MSSP_I2C_Bus_COL_LowPrioritySet() ;
        }
         else { /* ^--^ Nothing *--^ */ }
#else 
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
#endif  
#endif
}