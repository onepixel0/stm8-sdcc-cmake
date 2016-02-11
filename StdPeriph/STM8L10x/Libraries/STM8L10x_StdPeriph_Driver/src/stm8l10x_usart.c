/**
  ********************************************************************************
  * @file    stm8l10x_usart.c
  * @author  MCD Application Team
  * @version V1.2.1
  * @date    30-September-2014
  * @brief   This file contains all the functions for the USART peripheral.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm8l10x_usart.h"
#include "stm8l10x_clk.h"

/** @addtogroup STM8L10x_StdPeriph_Driver
  * @{
  */

/** @defgroup USART
  * @brief USART driver modules
  * @{
  */
  
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


/**
  * @addtogroup USART_Private_Functions
  * @{
  */

/**
  * @brief  Deinitializes the USART peripheral.
  * @param  None
  * @retval None
  */
void USART_DeInit(void)
{
  /* Clear the Idle Line Detected bit in the status rerister by a read
     to the USART_SR register followed by a Read to the USART_DR register */
  (void)USART->SR;
  (void)USART->DR;

  USART->BRR2 = USART_BRR2_RESET_VALUE;  /* Set USART_BRR2 to reset value 0x00 */
  USART->BRR1 = USART_BRR1_RESET_VALUE;  /* Set USART_BRR1 to reset value 0x00 */

  USART->CR1 = USART_CR1_RESET_VALUE;  /* Set USART_CR1 to reset value 0x00 */
  USART->CR2 = USART_CR2_RESET_VALUE;  /* Set USART_CR2 to reset value 0x00 */
  USART->CR3 = USART_CR3_RESET_VALUE;  /* Set USART_CR3 to reset value 0x00 */
  USART->CR4 = USART_CR4_RESET_VALUE;  /* Set USART_CR4 to reset value 0x00 */
}

/**
  * @brief  Initializes the USART according to the specified parameters.
  * @note   Configure in Push Pull or Open Drain mode the Tx pin by setting the
  *         correct I/O Port register according the product package and line
  *         configuration
  * @param  USART_WordLength: the word length
  *           This parameter can be one of the following values:
  *            @arg USART_WordLength_8D: 8 bits Data
  *            @arg USART_WordLength_9D: 9 bits Data  
  * @param  USART_StopBits: Stop Bit
  *           This parameter can be one of the following values:
  *            @arg USART_StopBits_1: One stop bit is transmitted at the end of frame
  *            @arg USART_StopBits_2: Two stop bits are transmitted at the end of frame
  * @param  USART_Parity: Parity
  *           This parameter can be one of the following values:
  *            @arg USART_Parity_No: No Parity
  *            @arg USART_Parity_Even: Even Parity
  *            @arg USART_Parity_Odd: Odd Parity   
  * @param  BaudRate         The baudrate.
  * @param  USART_Mode: Mode
  *           This parameter can be one of the following values:
  *            @arg USART_Mode_Rx: Receive Enable
  *            @arg USART_Mode_Tx: Transmit Enable 
  * @retval None
  */
void USART_Init(uint32_t BaudRate, USART_WordLength_TypeDef USART_WordLength,
                USART_StopBits_TypeDef USART_StopBits, USART_Parity_TypeDef
                USART_Parity, USART_Mode_TypeDef USART_Mode)
{
  uint32_t BaudRate_Mantissa = 0;

  /* Check the parameters */
  assert_param(IS_USART_BAUDRATE(BaudRate));

  assert_param(IS_USART_WordLength(USART_WordLength));

  assert_param(IS_USART_STOPBITS(USART_StopBits));

  assert_param(IS_USART_PARITY(USART_Parity));

  assert_param(IS_USART_MODE(USART_Mode));

  /* Clear the word length and Parity Control bits */
  USART->CR1 &= (uint8_t)(~(USART_CR1_PCEN | USART_CR1_PS | USART_CR1_M));
  /* Set the word length bit according to USART_WordLength value */
  /* Set the Parity Control bit to USART_Parity value */
  USART->CR1 |= (uint8_t)((uint8_t)USART_WordLength | (uint8_t)USART_Parity);

  /* Clear the STOP bits */
  USART->CR3 &= (uint8_t)(~USART_CR3_STOP);
  /* Set the STOP bits number according to USART_StopBits value */
  USART->CR3 |= (uint8_t)USART_StopBits;

  /* Clear the LSB mantissa of USARTDIV */
  USART->BRR1 &= (uint8_t)(~USART_BRR1_DIVM);
  /* Clear the MSB mantissa of USARTDIV */
  USART->BRR2 &= (uint8_t)(~USART_BRR2_DIVM);
  /* Clear the Fraction bits of USARTDIV */
  USART->BRR2 &= (uint8_t)(~USART_BRR2_DIVF);

  BaudRate_Mantissa  = ((uint32_t)CLK_GetClockFreq() / BaudRate);
  /* Set the fraction of USARTDIV */
  USART->BRR2 = (uint8_t)((BaudRate_Mantissa >> (uint8_t)8) & (uint8_t)0xF0);
  /* Set the MSB mantissa of USARTDIV */
  USART->BRR2 |= (uint8_t)(BaudRate_Mantissa & (uint8_t)0x0F);
  /* Set the LSB mantissa of USARTDIV */
  USART->BRR1 = (uint8_t)(BaudRate_Mantissa >> (uint8_t)4);

  /* Disable the Transmitter and Receiver */
  USART->CR2 &= (uint8_t)~(USART_CR2_TEN | USART_CR2_REN);
  /* Set TEN and REN bits according to USART_Mode value */
  USART->CR2 |= (uint8_t)USART_Mode;
}

/**
  * @brief Initializes the USART Clock according to the specified parameters.
  * @param  USART_Clock: Clock
  *           This parameter can be one of the following values:
  *            @arg USART_Clock_Disable: CK pin disabled
  *            @arg USART_Clock_Enable: CK pin enabled  
  * @param  USART_CPOL: Clock Polarity
  *           This parameter can be one of the following values:
  *            @arg USART_CPOL_Low: CK to 0 when idle
  *            @arg USART_CPOL_High: CK to 1 when idle
  * @param  USART_CPHA: Clock Phase
  *           This parameter can be one of the following values:
  *            @arg USART_CPHA_1Edge: The first clock transition is the first data capture edge
  *            @arg USART_CPHA_2Edge: The second clock transition is the first data capture edge
  * @param  USART_LastBit: Last Bit
  *           This parameter can be one of the following values:
  *            @arg USART_LastBit_Disable: The clock pulse of the last data bit is 
  *               not output to the SCLK pin
  *            @arg USART_LastBit_Enable: The clock pulse of the last data bit is 
  *               output to the SCLK pin
  * @retval None
  */
void USART_ClockInit(USART_Clock_TypeDef USART_Clock, USART_CPOL_TypeDef USART_CPOL,
                     USART_CPHA_TypeDef USART_CPHA, USART_LastBit_TypeDef USART_LastBit)
{
  /* Check the parameters */
  assert_param(IS_USART_CLOCK(USART_Clock));
  assert_param(IS_USART_CPOL(USART_CPOL));
  assert_param(IS_USART_CPHA(USART_CPHA));
  assert_param(IS_USART_LASTBIT(USART_LastBit));

  /* Clear the Clock Polarity, lock Phase, Last Bit Clock pulse */
  USART->CR3 &= (uint8_t)~(USART_CR3_CPOL | USART_CR3_CPHA | USART_CR3_LBCL);
  /* Set the Clock Polarity, lock Phase, Last Bit Clock pulse */
  USART->CR3 |= (uint8_t)((uint8_t)USART_CPOL | (uint8_t)USART_CPHA | (uint8_t)USART_LastBit);

  if (USART_Clock != USART_Clock_Disable)
  {
    USART->CR3 |= (uint8_t)(USART_CR3_CLKEN); /* Set the Clock Enable bit */
  }
  else
  {
    USART->CR3 &= (uint8_t)(~USART_CR3_CLKEN); /* Clear the Clock Enable bit */
  }
}

/**
  * @brief  Enable the USART peripheral.
  * @param  NewState: The new state of the USART Communication.
    *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void USART_Cmd(FunctionalState NewState)
{
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    USART->CR1 &= (uint8_t)(~USART_CR1_USARTD); /**< USART Enable */
  }
  else
  {
    USART->CR1 |= USART_CR1_USARTD;  /**< USART Disable */
  }
}

/**
  * @brief Enables or disables the specified USART interrupts.
  * @param  USART_IT specifies the USART interrupt sources to be enabled or disabled.
  *         This parameter can be one of the following values:
  *            @arg USART_IT_TXE: Transmit Data Register empty interrupt
  *            @arg USART_IT_TC: Transmission complete interrupt
  *            @arg USART_IT_RXNE: Receive Data register not empty interrupt
  *            @arg USART_IT_OR: Overrun error interrupt
  *            @arg USART_IT_IDLE: Idle line detection interrupt
  *            @arg USART_IT_ERR: Error interrupt
  * @param  NewState new state of the specified USART interrupts.
    *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void USART_ITConfig(USART_IT_TypeDef USART_IT, FunctionalState NewState)
{
  uint8_t uartreg, itpos = 0x00;
  assert_param(IS_USART_CONFIG_IT(USART_IT));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  /* Get the USART register index */
  uartreg = (uint8_t)((uint16_t)USART_IT >> (uint8_t)0x08);
  /* Get the USART IT index */
  itpos = (uint8_t)((uint8_t)1 << (uint8_t)((uint8_t)USART_IT & (uint8_t)0x0F));

  if (NewState != DISABLE)
  {
    /**< Enable the Interrupt bits according to USART_IT mask */
    if (uartreg == 0x01)
    {
      USART->CR1 |= itpos;
    }
    /*uartreg =0x02*/
    else
    {
      USART->CR2 |= itpos;
    }
  }
  else
  {
    /**< Disable the interrupt bits according to USART_IT mask */
    if (uartreg == 0x01)
    {
      USART->CR1 &= (uint8_t)(~itpos);
    }
    /*uartreg =0x02*/
    else
    {
      USART->CR2 &= (uint8_t)(~itpos);
    }
  }

}

/**
  * @brief Returns the most recent received data by the USART peripheral.
  * @note The function USART_Cmd(ENABLE) must be called first.
  * @param None
  * @retval The received data.
  */
uint8_t USART_ReceiveData8(void)
{
  return USART->DR;
}


/**
  * @brief  Returns the most recent received data by the USART peripheral.
  * @note   The function USART_Cmd(ENABLE) must be called first.
  * @param  None
  * @retval The received data.
  */
uint16_t USART_ReceiveData9(void)
{
  uint16_t temp = 0;
  
  temp = ((uint16_t)(((uint16_t)((uint16_t)USART->CR1 & (uint16_t)USART_CR1_R8)) << 1));
  return (uint16_t)( ((uint16_t)((uint16_t)USART->DR) | temp) & ((uint16_t)0x01FF));
}

/**
  * @brief  Determines if the USART is in mute mode or not.
  * @param  NewState: The new state of the USART mode.
    *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void USART_ReceiverWakeUpCmd(FunctionalState NewState)
{
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the mute mode USART by setting the RWU bit in the CR2 register */
    USART->CR2 |= USART_CR2_RWU;
  }
  else
  {
    /* Disable the mute mode USART by clearing the RWU bit in the CR1 register */
    USART->CR2 &= ((uint8_t)~USART_CR2_RWU);
  }
}

/**
  * @brief  Transmits break characters.
  * @param  None
  * @retval None
  */
void USART_SendBreak(void)
{
  USART->CR2 |= USART_CR2_SBK;
}

/**
  * @brief  Transmits 8 bit data through the USART peripheral.
  * @param  Data The data to transmit.
  * @retval None
  */
void USART_SendData8(uint8_t Data)
{
  /* Transmit Data */
  USART->DR = Data;
}

/**
  * @brief  Transmits 9 bit data through the USART peripheral.
  * @note   The parameter (Data) must be lower than 0x1FF.
  * @param  Data The data to transmit.
  * @retval None
  */
void USART_SendData9(uint16_t Data)
{
  assert_param(IS_USART_DATA_9BITS(Data));

  USART->CR1 &= ((uint8_t)~USART_CR1_T8);                    /* Clear the transmit data bit 8     */
  USART->CR1 |= (uint8_t)(((uint8_t)(Data >> 2)) & USART_CR1_T8); /* Write the transmit data bit [8]   */
  USART->DR   = (uint8_t)(Data);                             /* Write the transmit data bit [0:7] */

}

/**
  * @brief  Sets the address of the USART node.
  * @note   The parameter (Address) must be lower than 16
  * @param  Address Indicates the address of the USART node.
  * @retval None
  */
void USART_SetAddress(uint8_t Address)
{
  /* assert_param for USART_Address */
  assert_param(IS_USART_ADDRESS(Address));

  /* Clear the USART address */
  USART->CR4 &= ((uint8_t)~USART_CR4_ADD);
  /* Set the USART address node */
  USART->CR4 |= Address;
}

/**
  * @brief  Selects the USART WakeUp method.
  * @param  USART_WakeUp: Specifies the USART wakeup method.
  *           This parameter can be one of the following values:
  *            @arg USART_WakeUp_IdleLine: 0x01 Idle Line wake up
  *            @arg USART_WakeUp_AddressMark: 0x02 Address Mark wake up   
  * @retval None
  */
void USART_WakeUpConfig(USART_WakeUp_TypeDef USART_WakeUp)
{
  assert_param(IS_USART_WAKEUP(USART_WakeUp));

  USART->CR1 &= ((uint8_t)~USART_CR1_WAKE);
  USART->CR1 |= (uint8_t)USART_WakeUp;
}

/**
  * @brief Checks whether the specified USART flag is set or not.
  * @param  USART_FLAG specifies the flag to check.
  *         This parameter can be one of the following values:
  *            @arg USART_FLAG_TXE: Transmit Data Register empty
  *            @arg USART_FLAG_TC: Transmission Complete 
  *            @arg USART_FLAG_RXNE: Read Data Register Not Empty
  *            @arg USART_FLAG_IDLE: Idle line detected
  *            @arg USART_FLAG_OR: OverRun error
  *            @arg USART_FLAG_PE: Parity Error
  *            @arg USART_FLAG_SBK: Send Break characters   
  * @retval FlagStatus Status of the flag
  */
FlagStatus USART_GetFlagStatus(USART_FLAG_TypeDef USART_FLAG)
{
  FlagStatus status = RESET;

  /* Check parameters */
  assert_param(IS_USART_FLAG(USART_FLAG));

  if (USART_FLAG == USART_FLAG_SBK)
  {
    if ((USART->CR2 & (uint8_t)USART_FLAG) != (uint8_t)0x00)
    {
      /* USART_FLAG is set*/
      status = SET;
    }
    else
    {
      /* USART_FLAG is reset*/
      status = RESET;
    }
  }
  else
  {
    if ((USART->SR & (uint8_t)USART_FLAG) != (uint8_t)0x00)
    {
      /* USART_FLAG is set*/
      status = SET;
    }
    else
    {
      /* USART_FLAG is reset*/
      status = RESET;
    }
  }
  /* Return the USART_FLAG status*/
  return status;
}

/**
  * @brief Clears the USART RXNE (read data register not empty) flag.
  * @param None
  * @note  PE (Parity error), FE (Framing error), NE (Noise error), OR (OverRun error)
  *        and IDLE (Idle line detected) flags are cleared by software sequence: a read
  *        operation to USART_SR register (USART_GetFlagStatus())followed by a read operation
  *        to USART_DR register(USART_ReceiveData8() or USART_ReceiveData9()).
  * @note  RXNE flag can be also cleared by a read to the USART_DR register
  *        (USART_ReceiveData8()or USART_ReceiveData9()).
  * @note  TC flag can be also cleared by software sequence: a read operation to USART_SR
  *        register (USART_GetFlagStatus()) followed by a write operation to USART_DR register
  *        (USART_SendData8() or USART_SendData9()).
  * @note  TXE flag is cleared only by a write to the USART_DR register (USART_SendData8() or
  *        USART_SendData9()).
  * @note  SBK flag is cleared during the stop bit of break.
  * @retval None
  */
void USART_ClearFlag(void)
{
  /*< Clear the Receive Register Not Empty flag */
  USART->SR = (uint8_t)~(USART_SR_RXNE);
}

/**
  * @brief Checks whether the specified USART interrupt has occurred or not.
  * @param  USART_IT: Specifies the USART interrupt pending bit to check.
  *         This parameter can be one of the following values:
  *            @arg USART_IT_TXE: Transmit Data Register empty interrupt
  *            @arg USART_IT_TC: Transmission complete interrupt
  *            @arg USART_IT_RXNE: Receive Data register not empty interrupt
  *            @arg USART_IT_IDLE: Idle line detection interrupt
  *            @arg USART_IT_OR: OverRun Error interrupt
  *            @arg USART_IT_PE: Parity Error interrupt
  * @retval ITStatus The interruption status
  */
ITStatus USART_GetITStatus(USART_IT_TypeDef USART_IT)
{
  ITStatus pendingbitstatus = RESET;
  uint8_t itpos = 0;
  uint8_t itmask1 = 0;
  uint8_t itmask2 = 0;
  uint8_t enablestatus = 0;

  /* Check parameters */
  assert_param(IS_USART_GET_IT(USART_IT));

  /* Get the USART IT index */
  itpos = (uint8_t)((uint8_t)1 << (uint8_t)((uint8_t)USART_IT & (uint8_t)0x0F));
  /* Get the USART IT index */
  itmask1 = (uint8_t)((uint8_t)USART_IT >> (uint8_t)4);
  /* Set the IT mask*/
  itmask2 = (uint8_t)((uint8_t)1 << itmask1);


  /* Check the status of the specified USART pending bit*/
  if (USART_IT == USART_IT_PE)
  {
    /* Get the USART_IT enable bit status*/
    enablestatus = (uint8_t)((uint8_t)USART->CR1 & itmask2);
    /* Check the status of the specified USART interrupt*/

    if (((USART->SR & itpos) != (uint8_t)0x00) && enablestatus)
    {
      /* Interrupt occurred*/
      pendingbitstatus = SET;
    }
    else
    {
      /* Interrupt not occurred*/
      pendingbitstatus = RESET;
    }
  }
  else
  {
    /* Get the USART_IT enable bit status*/
    enablestatus = (uint8_t)((uint8_t)USART->CR2 & itmask2);
    /* Check the status of the specified USART interrupt*/
    if (((USART->SR & itpos) != (uint8_t)0x00) && enablestatus)
    {
      /* Interrupt occurred*/
      pendingbitstatus = SET;
    }
    else
    {
      /* Interrupt not occurred*/
      pendingbitstatus = RESET;
    }
  }

  /* Return the USART_IT status*/
  return  pendingbitstatus;
}

/**
  * @brief Clears the USART RXNE (read data register not empty) pending bit.
  * @param None
  * @note  PE (Parity error), FE (Framing error), NE (Noise error), OR (OverRun error)
  *        and IDLE (Idle line detected) flags are cleared by software sequence: a read
  *        operation to USART_SR register (USART_GetFlagStatus())followed by a read operation
  *        to USART_DR register(USART_ReceiveData8() or USART_ReceiveData9()).
  * @note  RXNE flag can be also cleared by a read to the USART_DR register
  *        (USART_ReceiveData8()or USART_ReceiveData9()).
  * @note  TC flag can be also cleared by software sequence: a read operation to USART_SR
  *        register (USART_GetFlagStatus()) followed by a write operation to USART_DR register
  *        (USART_SendData8() or USART_SendData9()).
  * @note  TXE flag is cleared only by a write to the USART_DR register (USART_SendData8() or
  *        USART_SendData9()).  
  * @retval None
  */
void USART_ClearITPendingBit(void)
{
  /*< Clear the Receive Register Not Empty pending bit */
  USART->SR = (uint8_t)~(USART_SR_RXNE);
}

/**
  * @}
  */

/**
  * @}
  */
  
/**
  * @}
  */  
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
