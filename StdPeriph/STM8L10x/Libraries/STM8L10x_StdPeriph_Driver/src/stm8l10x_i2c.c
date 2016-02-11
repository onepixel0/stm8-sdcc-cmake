/**
  ******************************************************************************
  * @file    stm8l10x_i2c.c
  * @author  MCD Application Team
  * @version V1.2.1
  * @date    30-September-2014
  * @brief   This file provides firmware functions to manage the following
  *          functionalities of the Inter-integrated circuit (I2C)
  *           - Initialization and Configuration
  *           - Data transfers
  *           - Interrupts, events and flags management
  *
  *  @verbatim
  *
  *          ===================================================================
  *                                 How to use this driver
  *          ===================================================================
  *          1. Enable peripheral clock using CLK_PeripheralClockConfig(CLK_Peripheral_I2C,
  *             ENABLE) function
  *
  *          2. Program the duty cycle , Own address, Ack, Speed and Acknowledged
  *             Address using the I2C_Init() function.
  *
  *          3. Optionally you can enable/configure the following parameters without
  *             re-initialization (i.e there is no need to call again I2C_Init() function):
  *              - Enable the acknowledge feature using I2C_AcknowledgeConfig() function
  *              - Enable the general call using the I2C_GeneralCallCmd() function
  *              - Enable the clock stretching using I2C_StretchClockCmd() function
  *              - Enable the fast mode duty cycle using the I2C_FastModeDutyCycleConfig()
  *                function
  *
  *          4. Enable the interrupt using the function I2C_ITConfig() if you need
  *             to use interrupt mode.
  *
  *          5. Enable the I2C using the I2C_Cmd() function.
  *
  *         Note: The external Pull-up resistors must be connected on SDA and SCL.
  *
  *  @endverbatim
  *
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
#include "stm8l10x_i2c.h"
#include "stm8l10x_clk.h"

/** @addtogroup STM8L10x_StdPeriph_Driver
  * @{
  */

/** @defgroup I2C
  * @brief I2C driver modules
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/** @defgroup I2C_Private_Define
  * @{
  */

/* I2C register mask */
#define REGISTER_Mask               ((uint16_t)0x3000)
#define REGISTER_SR1_Index          ((uint16_t)0x0100)
#define REGISTER_SR2_Index          ((uint16_t)0x0200)
/* I2C Interrupt Enable mask */
#define ITEN_Mask                   ((uint16_t)0x0700)
/* I2C FLAG mask */
#define FLAG_Mask                   ((uint16_t)0x00FF)
/* I2C ADD0 mask */
#define OAR1_ADD0_Set               ((uint8_t)0x01)
#define OAR1_ADD0_Reset             ((uint8_t)0xFE)

/**
  * @}
  */

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup I2C_Private_Functions
  * @{
  */

/** @defgroup I2C_Group1 Initialization and Configuration functions
 *  @brief   Initialization and Configuration functions
 *
@verbatim
 ===============================================================================
                   Initialization and Configuration functions
 ===============================================================================

@endverbatim
  * @{
  */

/**
  * @brief Deinitializes the I2C peripheral registers to their default reset values.
  * @param None
  * @retval None
  */
void I2C_DeInit(void)
{
  I2C->CR1 = I2C_CR1_RESET_VALUE;
  I2C->CR2 = I2C_CR2_RESET_VALUE;
  I2C->FREQR = I2C_FREQR_RESET_VALUE;
  I2C->OARL = I2C_OARL_RESET_VALUE;
  I2C->OARH = I2C_OARH_RESET_VALUE;
  I2C->ITR = I2C_ITR_RESET_VALUE;
  I2C->CCRL = I2C_CCRL_RESET_VALUE;
  I2C->CCRH = I2C_CCRH_RESET_VALUE;
  I2C->TRISER = I2C_TRISER_RESET_VALUE;
}

/**
  * @brief Initializes the I2C according to the specified parameters in standard or fast mode.
  * @param  OutputClockFrequency: Specifies the output clock frequency in Hz.
  * @param  OwnAddress: Specifies the own address.
  * @param  I2C_DutyCycle: Specifies the duty cycle to apply in fast mode.
  *          This parameter can be one of the following values:
  *            @arg I2C_DutyCycle_2: I2C fast mode Tlow/Thigh = 2
  *            @arg I2C_DutyCycle_16_9: I2C fast mode Tlow/Thigh = 16/9
  * @note   The I2C_DutyCycle parameter doesn't have impact when the OutputClockFrequency
  *         is lower than 100KHz.
  * @param  I2C_Ack: Specifies the acknowledge mode to apply.
  *          This parameter can be one of the following values:
  *            @arg I2C_Ack_Disable: No acknowledge
  *            @arg I2C_Ack_Enable: Acknowledge Enabled
  * @param  I2C_AcknowledgedAddress: Specifies the acknowledge address to apply.
  *          This parameter can be one of the following values:
  *            @arg I2C_AcknowledgedAddress_7bit: 7-bit slave address
  *            @arg I2C_AcknowledgedAddress_10bit: 10-bit slave address
  * @note   To use the I2C at 400 KHz (in fast mode), the PCLK frequency
  *         (I2C peripheral input clock) must be a multiple of 10 MHz.
  * @retval None
  */
void I2C_Init(uint32_t OutputClockFrequency, uint16_t OwnAddress,
              I2C_DutyCycle_TypeDef I2C_DutyCycle, I2C_Ack_TypeDef I2C_Ack,
              I2C_AcknowledgedAddress_TypeDef I2C_AcknowledgedAddress)
{
  uint32_t result = 0x0004;
  uint16_t tmpval = 0;
  uint8_t tmpccrh = 0;
  uint8_t input_clock = 0;

  /* Check the parameters */
  assert_param(IS_I2C_OUTPUT_CLOCK_FREQ(OutputClockFrequency));
  assert_param(IS_I2C_OWN_ADDRESS(OwnAddress));
  assert_param(IS_I2C_DUTY_CYCLE(I2C_DutyCycle));
  assert_param(IS_I2C_ACK_STATE(I2C_Ack));
  assert_param(IS_I2C_ACKNOWLEDGE_ADDRESS(I2C_AcknowledgedAddress));

  /* Get system clock frequency */
  input_clock = (uint8_t)(CLK_GetClockFreq() / 1000000);

  /*------------------------- I2C FREQ Configuration ------------------------*/
  /* Clear frequency bits */
  I2C->FREQR &= (uint8_t)(~I2C_FREQR_FREQ);
  /* Write new value */
  I2C->FREQR |= input_clock;

  /*--------------------------- I2C CCR Configuration ------------------------*/
  /* Disable I2C to configure TRISER */
  I2C->CR1 &= (uint8_t)(~I2C_CR1_PE);

  /* Clear CCRH & CCRL */
  I2C->CCRH &= (uint8_t)(~(I2C_CCRH_FS | I2C_CCRH_DUTY | I2C_CCRH_CCR));
  I2C->CCRL &= (uint8_t)(~I2C_CCRL_CCR);

  /* Detect Fast or Standard mode depending on the Output clock frequency selected */
  if (OutputClockFrequency > I2C_MAX_STANDARD_FREQ) /* FAST MODE */
  {
    /* Set F/S bit for fast mode */
    tmpccrh = I2C_CCRH_FS;

    if (I2C_DutyCycle == I2C_DutyCycle_2)
    {
      /* Fast mode speed calculate: Tlow/Thigh = 2 */
      result = (uint32_t) ((input_clock * 1000000) / (OutputClockFrequency * 3));
    }
    else /* I2C_DutyCycle_16_9 */
    {
      /* Fast mode speed calculate: Tlow/Thigh = 16/9 */
      result = (uint32_t) ((input_clock * 1000000) / (OutputClockFrequency * 25));
      /* Set DUTY bit */
      tmpccrh |= I2C_CCRH_DUTY;
    }

    /* Verify and correct CCR value if below minimum value */
    if (result < (uint16_t)0x0001)
    {
      /* Set the minimum allowed value */
      result = (uint16_t)0x0001;
    }

    /* Set Maximum Rise Time: 300ns max in Fast Mode
       = [300ns/(1/input_clock.10e6)]+1
       = [(input_clock * 3)/10]+1 */
    tmpval = ((input_clock * 3) / 10) + 1;
    I2C->TRISER = (uint8_t)tmpval;

  }
  else /* STANDARD MODE */
  {
    /* Calculate standard mode speed */
    result = (uint16_t)((input_clock * 1000000) / (OutputClockFrequency << (uint8_t)1));

    /* Verify and correct CCR value if below minimum value */
    if (result < (uint16_t)0x0004)
    {
      /* Set the minimum allowed value */
      result = (uint16_t)0x0004;
    }

    /* Set Maximum Rise Time: 1000ns max in Standard Mode
     = [1000ns/(1/input_clock.10e6)]+1
     = input_clock+1 */
     I2C->TRISER = (uint8_t)((uint8_t)input_clock + (uint8_t)1);
  }

  /* Write CCR with new calculated value */
  I2C->CCRL = (uint8_t)result;
  I2C->CCRH = (uint8_t)((uint8_t)((uint8_t)((uint8_t)result >> 8) & I2C_CCRH_CCR) | tmpccrh);

  /* Enable I2C */
    I2C->CR1 |= I2C_CR1_PE;

  /* Clear the I2C Ack bit */
  I2C->CR2 &= (uint8_t)(~I2C_CR2_ACK);
  
  /* Configure I2C acknowledgement */
  I2C->CR2 |= (uint8_t)I2C_Ack;

    /*--------------------------- I2C OAR Configuration ------------------------*/
    I2C->OARL = (uint8_t)(OwnAddress);
    I2C->OARH = (uint8_t)((uint8_t)(I2C_AcknowledgedAddress | I2C_OARH_ADDCONF) |
                         (uint8_t)((uint16_t)( (uint16_t)OwnAddress &  (uint16_t)0x0300) >> 7));
}

/**
  * @brief Enables or disables the I2C peripheral.
  * @param  NewState: Indicate the new I2C peripheral state.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void I2C_Cmd(FunctionalState NewState)
{
  /* Check function parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable I2C peripheral */
    I2C->CR1 |= I2C_CR1_PE;
  }
  else
  {
    /* Disable I2C peripheral */
    I2C->CR1 &= (uint8_t)(~I2C_CR1_PE);
  }
}

/**
  * @brief Enables or disables the I2C General Call feature.
  * @param  NewState: State of the General Call feature.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void I2C_GeneralCallCmd(FunctionalState NewState)
{
  /* Check function parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable General Call */
    I2C->CR1 |= I2C_CR1_ENGC;
  }
  else
  {
    /* Disable General Call */
    I2C->CR1 &= (uint8_t)(~I2C_CR1_ENGC);
  }
}

/**
  * @brief Generates I2C communication START condition.
  * @note   CCR must be programmed, i.e. I2C_Init function must have been called
  *         with a valid I2C_ClockSpeed
  * @param  NewState: Enable or disable the start condition.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void I2C_GenerateSTART(FunctionalState NewState)
{
  /* Check function parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Generate a START condition */
    I2C->CR2 |= I2C_CR2_START;
  }
  else
  {
    /* Disable the START condition generation */
    I2C->CR2 &= (uint8_t)(~I2C_CR2_START);
  }
}

/**
  * @brief Generates I2C communication STOP condition.
  * @param  NewState: Enable or disable the stop condition.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void I2C_GenerateSTOP(FunctionalState NewState)
{
  /* Check function parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Generate a STOP condition */
    I2C->CR2 |= I2C_CR2_STOP;
  }
  else /* NewState == DISABLE */
  {
    /* Disable the STOP condition generation */
    I2C->CR2 &= (uint8_t)(~I2C_CR2_STOP);
  }
}

/**
  * @brief  Enables or disables I2C software reset.
  * @note   Before calling this function with the ENABLE parameter, make sure that
  *         the I2C lines are released and the bus is free.
  * @param  NewState: Specifies the new state of the I2C software reset.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void I2C_SoftwareResetCmd(FunctionalState NewState)
{
  /* Check function parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Peripheral under reset */
    I2C->CR2 |= I2C_CR2_SWRST;
  }
  else
  {
    /* Peripheral not under reset */
    I2C->CR2 &= (uint8_t)(~I2C_CR2_SWRST);
  }
}

/**
  * @brief  Enables or disables the I2C clock stretching.
  * @param  NewState: Specifies the new state of the I2C Clock stretching.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void I2C_StretchClockCmd(FunctionalState NewState)
{
  /* Check function parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Clock Stretching Enable */
    I2C->CR1 &= (uint8_t)(~I2C_CR1_NOSTRETCH);
  }
  else /* NewState == DISABLE */
  {
    /* Clock Stretching Disable (Slave mode) */
    I2C->CR1 |= I2C_CR1_NOSTRETCH;
  }
}

/**
  * @brief  Enable or Disable the I2C acknowledge feature.
  * @param  NewState: Specifies the new state of the I2C acknowledge.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void I2C_AcknowledgeConfig(FunctionalState NewState)
{
  /* Check function parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the acknowledgement */
    I2C->CR2 |= I2C_CR2_ACK;
  }
  else
  {
    /* Disable the acknowledgement */
    I2C->CR2 &= (uint8_t)(~I2C_CR2_ACK);
  }
}

/**
  * @brief  Selects the specified I2C Ack position.
  * @note   This function must be called before data reception starts.
  * @param  I2C_AckPosition: specifies the Ack position.
  *          This parameter can be one of the following values:
  *            @arg I2C_AckPosition_Current: Acknowledge on the current byte
  *            @arg I2C_AckPosition_Next: Acknowledge on the next byte
  * @retval None
  */
void I2C_AckPositionConfig(I2C_AckPosition_TypeDef I2C_AckPosition)
{
  /* Check function parameters */
  assert_param(IS_I2C_ACK_POSITION(I2C_AckPosition));

  /* Clear the I2C Ack position */
  I2C->CR2 &= (uint8_t)(~I2C_CR2_POS);

  /* Configure the specified I2C Ack position*/
  I2C->CR2 |= (uint8_t)I2C_AckPosition;
}

/**
  * @brief  Selects I2C fast mode duty cycle.
  * @param  I2C_DutyCycle: specifies the fast mode duty cycle.
  *          This parameter can be one of the following values:
  *            @arg I2C_DutyCycle_2: I2C fast mode Tlow/Thigh = 2
  *            @arg I2C_DutyCycle_16_9: I2C fast mode Tlow/Thigh = 16/9
  * @retval None
  */
void I2C_FastModeDutyCycleConfig(I2C_DutyCycle_TypeDef I2C_DutyCycle)
{
  /* Check function parameters */
  assert_param(IS_I2C_DUTY_CYCLE(I2C_DutyCycle));

  if (I2C_DutyCycle == I2C_DutyCycle_16_9)
  {
    /* I2C fast mode Tlow/Thigh = 16/9 */
    I2C->CCRH |= I2C_CCRH_DUTY;
  }
  else /* I2C_DUTYCYCLE_2 */
  {
    /* I2C fast mode Tlow/Thigh = 2 */
    I2C->CCRH &= (uint8_t)(~I2C_CCRH_DUTY);
  }
}

/**
  * @brief  Transmits the 7-bit address (to select the) slave device.
  * @param  Address: Specifies the slave address which will be transmitted.
  * @param  I2C_Direction: specifies whether the I2C device will be a Transmitter
  *         or a Receiver.
  *          This parameter can be one of the following values
  *            @arg I2C_Direction_Transmitter: Transmitter mode
  *            @arg I2C_Direction_Receiver: Receiver mode
  * @retval None
  */
void I2C_Send7bitAddress(uint8_t Address, I2C_Direction_TypeDef I2C_Direction)
{
  /* Check function parameters */
  assert_param(IS_I2C_ADDRESS(Address));
  assert_param(IS_I2C_DIRECTION(I2C_Direction));

  /* Test on the direction to set/reset the read/write bit */
  if (I2C_Direction != I2C_Direction_Transmitter)
  {
    /* Set the address bit0 for read */
    Address |= OAR1_ADD0_Set;
  }
  else
  {
    /* Reset the address bit0 for write */
    Address &= OAR1_ADD0_Reset;
  }
  /* Send the address */
  I2C->DR = Address;
}

/**
  * @}
  */

/** @defgroup I2C_Group2 Data transfers functions
 *  @brief   Data transfers functions
 *
@verbatim
 ===============================================================================
                        Data transfers functions
 ===============================================================================

@endverbatim
  * @{
  */

/**
  * @brief  Send a byte by writing in the DR register.
  * @param  Data: Byte to be sent.
  * @retval None
  */
void I2C_SendData(uint8_t Data)
{
  /* Write in the DR register the data to be sent */
  I2C->DR = Data;
}

/**
  * @brief  Returns the most recent received data.
  * @param  None
  * @retval The value of the received byte data.
  */
uint8_t I2C_ReceiveData(void)
{
  /* Return the data present in the DR register */
  return ((uint8_t)I2C->DR);
}

/**
  * @}
  */

/** @defgroup I2C_Group3 Interrupts events and flags management functions
 *  @brief   Interrupts, events and flags management functions
 *
@verbatim
 ===============================================================================
                Interrupts, events and flags management functions
 ===============================================================================
  This section provides functions allowing to configure the I2C Interrupts
  sources and check or clear the flags or pending bits status.
  The user should identify which mode will be used in his application to manage
  the communication: Polling mode or Interrupt mode.

 ===============================================================================
                          I2C State Monitoring Functions
 ===============================================================================
 This I2C driver provides three different ways for I2C state monitoring
  depending on the application requirements and constraints:


     1. Basic state monitoring (Using I2C_CheckEvent() function)
     -----------------------------------------------------------
    It compares the status registers (SR1, SR2 and SR3) content to a given event
    (can be the combination of one or more flags).
    It returns SUCCESS if the current status includes the given flags
    and returns ERROR if one or more flags are missing in the current status.
    - When to use:
      - This function is suitable for most applications as well as for startup
      activity since the events are fully described in the product reference manual
      (RM0013).
      - It is also suitable for users who need to define their own events.
    - Limitations:
      - If an error occurs (ie. error flags are set besides to the monitored flags),
        the I2C_CheckEvent() function may return SUCCESS despite the communication
        hold or corrupted real state.
        In this case, it is advised to use error interrupts to monitor the error
        events and handle them in the interrupt IRQ handler.

        @note
        For error management, it is advised to use the following functions:
          - I2C_ITConfig() to configure and enable the error interrupts (I2C_IT_ERR).
          - I2C_IRQHandler() which is called when the I2C interrupts occur.
          - I2C_GetFlagStatus() or I2C_GetITStatus() to be called into the
            I2C_IRQHandler() function in order to determine which error occurred.
          - I2C_ClearFlag() or I2C_ClearITPendingBit() and/or I2C_SoftwareResetCmd()
            and/or I2C_GenerateStop() in order to clear the error flag and
            source and return to correct communication status.


     2. Advanced state monitoring (Using the function I2C_GetLastEvent())
     --------------------------------------------------------------------
     Using the function I2C_GetLastEvent() which returns the image of both SR1
     & SR3 status registers in a single word (uint16_t) (Status Register 3 value
     is shifted left by 8 bits and concatenated to Status Register 1).
     - When to use:
       - This function is suitable for the same applications above but it allows to
         overcome the limitations of I2C_GetFlagStatus() function (see below).
         The returned value could be compared to events already defined in the
         library (stm8l10x_i2c.h) or to custom values defined by user.
       - This function is suitable when multiple flags are monitored at the same time.
       - At the opposite of I2C_CheckEvent() function, this function allows user to
         choose when an event is accepted (when all events flags are set and no
         other flags are set or just when the needed flags are set like
         I2C_CheckEvent() function).
     - Limitations:
       - User may need to define his own events.
       - Same remark concerning the error management is applicable for this
         function if user decides to check only regular communication flags (and
         ignores error flags).


     3. Flag-based state monitoring (Using the function I2C_GetFlagStatus())
     -----------------------------------------------------------------------
     Using the function I2C_GetFlagStatus() which simply returns the status of
     one single flag (ie. I2C_FLAG_RXNE ...).
     - When to use:
        - This function could be used for specific applications or in debug phase.
        - It is suitable when only one flag checking is needed (most I2C events
          are monitored through multiple flags).
     - Limitations:
        - When calling this function, the Status register is accessed. Some flags are
          cleared when the status register is accessed. So checking the status
          of one Flag, may clear other ones.
        - Function may need to be called twice or more in order to monitor one
          single event.

  For detailed description of Events, please refer to section I2C_Events in
  stm8l10x_i2c.h file.


@endverbatim
  * @{
  */

/**
  * @brief  Enables or disables the specified I2C interrupt.
  * @param  I2C_IT: specifies the I2C interrupts sources to be enabled or disabled.
  *          This parameter can be any combination of the following values:
  *            @arg I2C_IT_BUF: Buffer interrupt mask
  *            @arg I2C_IT_EVT: Event interrupt mask
  *            @arg I2C_IT_ERR: Error interrupt mask
  * @param  NewState: State of the interrupt.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void I2C_ITConfig(I2C_IT_TypeDef I2C_IT, FunctionalState NewState)
{
  /* Check functions parameters */
  assert_param(IS_I2C_CONFIG_IT(I2C_IT));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the selected I2C interrupts */
    I2C->ITR |= (uint8_t)I2C_IT;
  }
  else /* NewState == DISABLE */
  {
    /* Disable the selected I2C interrupts */
    I2C->ITR &= (uint8_t)(~(uint8_t)I2C_IT);
  }
}
/**
 ===============================================================================
                          1. Basic state monitoring
 ===============================================================================
 */

/**
  * @brief  Checks whether the last I2C Event is equal to the one passed
  *   as parameter.
  * @param  I2C_EVENT: specifies the event to be checked.
  *          This parameter can be one of the following values:
  *            @arg I2C_EVENT_SLAVE_TRANSMITTER_ADDRESS_MATCHED: EV1
  *            @arg I2C_EVENT_SLAVE_RECEIVER_ADDRESS_MATCHED: EV1
  *            @arg I2C_EVENT_SLAVE_GENERALCALLADDRESS_MATCHED: EV1
  *            @arg I2C_EVENT_SLAVE_BYTE_RECEIVED: EV2
  *            @arg (I2C_EVENT_SLAVE_BYTE_RECEIVED | I2C_FLAG_GENCALL): EV2
  *            @arg I2C_EVENT_SLAVE_BYTE_TRANSMITTED: EV3
  *            @arg (I2C_EVENT_SLAVE_BYTE_TRANSMITTED | I2C_FLAG_GENCALL): EV3
  *            @arg I2C_EVENT_SLAVE_ACK_FAILURE: EV3_2
  *            @arg I2C_EVENT_SLAVE_STOP_DETECTED: EV4
  *            @arg I2C_EVENT_MASTER_MODE_SELECT: EV5
  *            @arg I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED: EV6
  *            @arg I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED: EV6
  *            @arg I2C_EVENT_MASTER_BYTE_RECEIVED: EV7
  *            @arg I2C_EVENT_MASTER_BYTE_TRANSMITTING: EV8
  *            @arg I2C_EVENT_MASTER_BYTE_TRANSMITTED: EV8_2
  *            @arg I2C_EVENT_MASTER_MODE_ADDRESS10: EV9
  *
  * @note: For detailed description of Events, please refer to section
  *    I2C_Events in stm8l10x_i2c.h file.
  *
  * @retval An ErrorStatus enumeration value:
  *         - SUCCESS: Last event is equal to the I2C_EVENT
  *         - ERROR: Last event is different from the I2C_EVENT
  */
ErrorStatus I2C_CheckEvent(I2C_Event_TypeDef I2C_Event)
{
  uint16_t lastevent = 0;
  uint8_t flag1= 0;
  uint8_t flag2= 0;
  ErrorStatus status = ERROR;

  /* Check the parameters */
  assert_param(IS_I2C_EVENT(I2C_Event));

  if (I2C_Event == I2C_EVENT_SLAVE_ACK_FAILURE)
  {
    /* This flag is reset only by writing 0 in the AF bit or by disabling the I2C peripheral */
      lastevent = (uint16_t)(I2C->SR2& I2C_SR2_AF);
  }
  else
  {
    /* Read flags */
    flag1 = I2C->SR1;
    flag2 = I2C->SR3;
    lastevent = ((uint16_t)((uint16_t)flag2 << (uint16_t)8) | (uint16_t)flag1);
  }

  /* Check whether the last event is equal to I2C_EVENT */
  if (((uint16_t)lastevent & (uint16_t)I2C_Event) == (uint16_t)I2C_Event)
  {
    /* SUCCESS: last event is equal to I2C_EVENT */
    status = SUCCESS;
  }
  else
  {
    /* ERROR: last event is different from I2C_EVENT */
    status = ERROR;
  }

  /* Return status */
  return status;
}

/**
 ===============================================================================
                          2. Advanced state monitoring
 ===============================================================================
 */

/**
  * @brief  Returns the last I2C Event.
  * @param  None
  *
  * @note: For detailed description of Events, please refer to section
  *    I2C_Events in stm8l10x_i2c.h file.
  *
  * @retval The last event
  */
I2C_Event_TypeDef I2C_GetLastEvent(void)
{
  __IO uint16_t lastevent = 0;
  uint16_t flag1 = 0;
  uint16_t flag2 = 0;

  if ((I2C->SR2 & I2C_SR2_AF) != 0x00)
  {
    lastevent = I2C_EVENT_SLAVE_ACK_FAILURE;
  }
  else
  {
    /* Read the I2C status register */
    flag1 = I2C->SR1;
    flag2 = I2C->SR3;

    /* Get the last event value from I2C status register */
    lastevent = ((uint16_t)((uint16_t)flag2 << 8) | (uint16_t)flag1);
  }
  /* Return status */
  return (I2C_Event_TypeDef)lastevent;
}

/**
 ===============================================================================
                          3. Flag-based state monitoring
 ===============================================================================
 */

/**
  * @brief  Checks whether the specified I2C flag is set or not.
  * @param  I2C_FLAG: specifies the flag to check.
  *          This parameter can be one of the following values:
  *            @arg I2C_FLAG_GENCALL: General call header flag (Slave mode)
  *            @arg I2C_FLAG_TRA: Transmitter/Receiver flag
  *            @arg I2C_FLAG_BUSY: Bus busy flag
  *            @arg I2C_FLAG_MSL: Master/Slave flag
  *            @arg I2C_FLAG_OVR: Overrun/Underrun flag (Slave mode)
  *            @arg I2C_FLAG_AF: Acknowledge failure flag
  *            @arg I2C_FLAG_ARLO: Arbitration lost flag (Master mode)
  *            @arg I2C_FLAG_BERR: Bus error flag
  *            @arg I2C_FLAG_TXE: Data register empty flag (Transmitter)
  *            @arg I2C_FLAG_RXNE: Data register not empty (Receiver) flag
  *            @arg I2C_FLAG_STOPF: Stop detection flag (Slave mode)
  *            @arg I2C_FLAG_ADD10: 10-bit header sent flag (Master mode)
  *            @arg I2C_FLAG_BTF: Byte transfer finished flag
  *            @arg I2C_FLAG_ADDR: Address sent flag (Master mode) “ADSL”
  *   Address matched flag (Slave mode)”ENDAD”
  *            @arg I2C_FLAG_SB: Start bit flag (Master mode)
  * @retval The new state of I2C_FLAG (SET or RESET).
  */
FlagStatus I2C_GetFlagStatus(I2C_FLAG_TypeDef I2C_FLAG)
{
  uint8_t tempreg = 0;
  uint8_t regindex = 0;
  FlagStatus bitstatus = RESET;

  /* Check the parameters */
  assert_param(IS_I2C_GET_FLAG(I2C_FLAG));

  /* Read flag register index (see I2C_FLAG_TypeDef definition) */
  regindex = (uint8_t)((uint16_t)I2C_FLAG >> 8);

  /* Check SRx index */
  switch (regindex)
  {
      /* Returns whether the status register to check is SR1 */
    case 0x01:
      tempreg = (uint8_t)I2C->SR1;
      break;
    
      /* Returns whether the status register to check is SR2 */
    case 0x02:
      tempreg = (uint8_t)I2C->SR2;
      break;
      
      /* Returns whether the status register to check is SR3 */
    case 0x03:
      tempreg = (uint8_t)I2C->SR3;
      break;
    default:
      break;
  }

  /* Check the status of the specified I2C flag */
  if ((tempreg & (uint8_t)I2C_FLAG) != 0)
  {
    /* Flag is set */
    bitstatus = SET;
  }
  else
  {
    /* Flag is reset */
    bitstatus = RESET;
  }
  /* Return the flag status */
  return bitstatus;
}

/**
  * @brief  Clear flags
  * @param  I2C_Flag: Specifies the flag to clear
  *          This parameter can be any combination of the following values:
  *            @arg I2C_FLAG_WUFH: Wakeup from Halt
  *            @arg I2C_FLAG_OVR: Overrun/Underrun flag (Slave mode)
  *            @arg I2C_FLAG_AF: Acknowledge failure flag
  *            @arg I2C_FLAG_ARLO: Arbitration lost flag (Master mode)
  *            @arg I2C_FLAG_BERR: Bus error flag.
  * @note   STOPF (STOP detection) is cleared by software sequence: a read operation
  *          to I2C_SR1 register (I2C_GetFlagStatus()) followed by a write operation
  *          to I2C_CR2 register.
  * @note   ADD10 (10-bit header sent) is cleared by software sequence: a read
  *          operation to I2C_SR1 (I2C_GetFlagStatus()) followed by writing the
  *          second byte of the address in DR register.
  * @note   BTF (Byte Transfer Finished) is cleared by software sequence: a read
  *         operation to I2C_SR1 register (I2C_GetFlagStatus()) followed by a
  *         read/write to I2C_DR register (I2C_SendData()).
  * @note   ADDR (Address sent) is cleared by software sequence: a read operation
  *         to I2C_SR1 register(I2C_GetFlagStatus()) followed by a read operation
  *         to I2C_SR3 register ((void)(I2C->SR3)).
  * @note   SB (Start Bit) is cleared software sequence: a read operation to
  *         I2C_SR1 register (I2C_GetFlagStatus()) followed by a write operation
  *         to I2C_DR register (I2C_SendData()).
  * @retval None
  */
void I2C_ClearFlag(I2C_FLAG_TypeDef I2C_FLAG)
{
  uint16_t flagpos = 0;
  /* Check the parameters */
  assert_param(IS_I2C_CLEAR_FLAG(I2C_FLAG));

  /* Get the I2C flag position */
  flagpos = (uint16_t)I2C_FLAG & FLAG_Mask;
  /* Clear the selected I2C flag */
  I2C->SR2 = (uint8_t)((uint16_t)(~flagpos));
}

/**
  * @brief  Checks whether the specified I2C interrupt has occurred or not.
  * @param  I2C_IT: specifies the interrupt source to check.
  *            This parameter can be one of the following values:
  *            @arg I2C_IT_WUFH: Wakeup from Halt
  *            @arg I2C_IT_OVR: Overrun/Underrun flag (Slave mode)
  *            @arg I2C_IT_AF: Acknowledge failure flag
  *            @arg I2C_IT_ARLO: Arbitration lost flag (Master mode)
  *            @arg I2C_IT_BERR: Bus error flag
  *            @arg I2C_IT_TXE: Data register empty flag (Transmitter)
  *            @arg I2C_IT_RXNE: Data register not empty (Receiver) flag
  *            @arg I2C_IT_STOPF: Stop detection flag (Slave mode)
  *            @arg I2C_IT_ADD10: 10-bit header sent flag (Master mode)
  *            @arg I2C_IT_BTF: Byte transfer finished flag
  *            @arg I2C_IT_ADDR: Address sent flag (Master mode) “ADSL”
  *                              Address matched flag (Slave mode)“ENDAD”
  *            @arg I2C_IT_SB: Start bit flag (Master mode)
  * @retval The new state of I2C_IT
  */
ITStatus I2C_GetITStatus(I2C_IT_TypeDef I2C_IT)
{
  ITStatus bitstatus = RESET;
  __IO uint8_t enablestatus = 0;
  uint16_t tempregister = 0;

  /* Check the parameters */
  assert_param(IS_I2C_GET_IT(I2C_IT));

  tempregister = (uint8_t)( ((uint16_t)((uint16_t)I2C_IT & ITEN_Mask)) >> 8);

  /* Check if the interrupt source is enabled or not */
  enablestatus = (uint8_t)(I2C->ITR & ( uint8_t)tempregister);

  if ((uint16_t)((uint16_t)I2C_IT & REGISTER_Mask) == REGISTER_SR1_Index)
  {
    /* Check the status of the specified I2C flag */
    if (((I2C->SR1 & (uint8_t)I2C_IT) != RESET) && enablestatus)
    {
      /* I2C_IT is set */
      bitstatus = SET;
    }
    else
    {
      /* I2C_IT is reset */
      bitstatus = RESET;
    }
  }
  else
  {
    /* Check the status of the specified I2C flag */
    if (((I2C->SR2 & (uint8_t)I2C_IT) != RESET) && enablestatus)
    {
      /* I2C_IT is set */
      bitstatus = SET;
    }
    else
    {
      /* I2C_IT is reset */
      bitstatus = RESET;
    }
  }
  /* Return the I2C_IT status */
  return  bitstatus;
}

/**
  * @brief  Clear IT pending bit
  * @param  I2C_IT: specifies the interrupt pending bit to clear.
  *            @arg I2C_IT_WUFH: Wakeup from Halt
  *            @arg I2C_IT_OVR: Overrun/Underrun interrupt (Slave mode)
  *            @arg I2C_IT_AF: Acknowledge failure interrupt
  *            @arg I2C_IT_ARLO: Arbitration lost interrupt (Master mode)
  *            @arg I2C_IT_BERR: Bus error interrupt
  *
  * @note   STOPF (STOP detection) is cleared by software sequence: a read operation
  *         to I2C_SR1 register (I2C_GetITStatus()) followed by a write operation to
  *         I2C_CR2 register (I2C_AcknowledgeConfig() to configure the I2C peripheral Acknowledge).
  * @note   ADD10 (10-bit header sent) is cleared by software sequence: a read
  *         operation to I2C_SR1 (I2C_GetITStatus()) followed by writing the second
  *         byte of the address in I2C_DR register.
  * @note   BTF (Byte Transfer Finished) is cleared by software sequence: a read
  *         operation to I2C_SR1 register (I2C_GetITStatus()) followed by a read/write to
  *         I2C_DR register (I2C_SendData()).
  * @note   ADDR (Address sent) is cleared by software sequence: a read operation
  *         to I2C_SR1 register (I2C_GetITStatus()) followed by a read operation
  *         to I2C_SR3 register ((void)(I2C->SR3)).
  * @note   SB (Start Bit) is cleared by software sequence: a read operation to
  *         I2C_SR1 register (I2C_GetITStatus()) followed by a write operation to
  *         I2C_DR register (I2C_SendData()).
  * @retval None
  */
void I2C_ClearITPendingBit(I2C_IT_TypeDef I2C_IT)
{
  uint16_t flagpos = 0;

  /* Check the parameters */
  assert_param(IS_I2C_CLEAR_IT(I2C_IT));

  /* Get the I2C flag position */
  flagpos = (uint16_t)I2C_IT & FLAG_Mask;

  /* Clear the selected I2C flag */
  I2C->SR2 = (uint8_t)((uint16_t)~flagpos);
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

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
