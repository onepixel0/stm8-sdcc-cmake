/**
  ******************************************************************************
  * @file    stm8l10x_tim4.c
  * @author  MCD Application Team
  * @version V1.2.1
  * @date    30-September-2014
  * @brief   This file contains all the functions for the TIM4 peripheral.
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
#include "stm8l10x_tim4.h"

/** @addtogroup STM8L10x_StdPeriph_Driver
  * @{
  */

/** @defgroup TIM4
  * @brief TIM4 driver modules
  * @{
  */
  
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

/**
  * @addtogroup TIM4_Private_Functions
  * @{
  */

/**
  * @brief  Deinitializes the TIM4 peripheral registers to their default reset values.
  * @param  None
  * @retval None
  */
void TIM4_DeInit(void)
{
  TIM4->CR1  = TIM4_CR1_RESET_VALUE;
  TIM4->CR2  = TIM4_CR2_RESET_VALUE;
  TIM4->SMCR  = TIM4_SMCR_RESET_VALUE;
  TIM4->IER  = TIM4_IER_RESET_VALUE;
  TIM4->CNTR  = TIM4_CNTR_RESET_VALUE;
  TIM4->PSCR = TIM4_PSCR_RESET_VALUE;
  TIM4->ARR  = TIM4_ARR_RESET_VALUE;
  TIM4->SR1  = TIM4_SR1_RESET_VALUE;
}

/**
  * @brief  Initializes the TIM4 Time Base Unit according to the specified parameters.
  * @param  TIM4_Prescaler: Prescaler
  *          This parameter can be one of the following values:
  *            @arg TIM4_Prescaler_1: Time base Prescaler = 1 (No effect)
  *            @arg TIM4_Prescaler_2: Time base Prescaler = 2
  *            @arg TIM4_Prescaler_4: Time base Prescaler = 4
  *            @arg TIM4_Prescaler_8: Time base Prescaler = 8
  *            @arg TIM4_Prescaler_16: Time base Prescaler = 16
  *            @arg TIM4_Prescaler_32: Time base Prescaler = 32
  *            @arg TIM4_Prescaler_64: Time base Prescaler = 64
  *            @arg TIM4_Prescaler_128: Time base Prescaler = 128
  *            @arg TIM4_Prescaler_256: Time base Prescaler = 256
  *            @arg TIM4_Prescaler_512: Time base Prescaler = 512
  *            @arg TIM4_Prescaler_1024: Time base Prescaler = 1024
  *            @arg TIM4_Prescaler_2048: Time base Prescaler = 2048
  *            @arg TIM4_Prescaler_4096: Time base Prescaler = 4096
  *            @arg TIM4_Prescaler_8192: Time base Prescaler = 8192
  *            @arg TIM4_Prescaler_16384: Time base Prescaler = 16384
  *            @arg TIM4_Prescaler_32768: Time base Prescaler = 32768                              
  * @param  TIM4_Period: This parameter must be a value between 0x00 and 0xFF.
  * @retval None
  */
void TIM4_TimeBaseInit(TIM4_Prescaler_TypeDef TIM4_Prescaler,
                       uint8_t TIM4_Period)
{
  /* Check TIM4 prescaler value */
  assert_param(IS_TIM4_PRESCALER(TIM4_Prescaler));
  /* Set the Autoreload value */
  TIM4->ARR = (uint8_t)(TIM4_Period);
  /* Set the Prescaler value */
  TIM4->PSCR = (uint8_t)(TIM4_Prescaler);
}

/**
  * @brief  Enables or disables the TIM4 peripheral.
  * @param  NewState: The new state of the TIM4 peripheral.
  *          This parameter can be ENABLE or DISABLE
  * @retval None
  */
void TIM4_Cmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  /* set or Reset the CEN Bit */
  if (NewState != DISABLE)
  {
    TIM4->CR1 |= TIM4_CR1_CEN ;
  }
  else
  {
    TIM4->CR1 &= (uint8_t)(~TIM4_CR1_CEN) ;
  }
}

/**
  * @brief  Enables or disables the specified TIM4 interrupts.
  * @param  TIM4_IT: Specifies the TIM4 interrupts sources to be enabled or disabled.
  *          This parameter can be one of the following values:
  *            @arg TIM4_IT_Update: Update
  *            @arg TIM4_IT_Trigger: Trigger
  * @param  NewState: The new state of the TIM4 peripheral.
  *          This parameter can be ENABLE or DISABLE
  * @retval None
  */
void TIM4_ITConfig(TIM4_IT_TypeDef TIM4_IT, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_TIM4_IT(TIM4_IT));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the Interrupt sources */
    TIM4->IER |= (uint8_t)TIM4_IT;
  }
  else
  {
    /* Disable the Interrupt sources */
    TIM4->IER &= (uint8_t)(~(uint8_t)TIM4_IT);
  }
}

/**
  * @brief  Enables the TIM4 internal Clock.
  * @param  None
  * @retval None
  */
void TIM4_InternalClockConfig(void)
{
  /* Disable slave mode to clock the prescaler directly with the internal clock */
  TIM4->SMCR &= (uint8_t)(~TIM4_SMCR_SMS);
}

/**
  * @brief  Selects the TIM4 Input Trigger source.
  * @param  TIM4_InputTriggerSource: Specifies Input Trigger source.
  *          This parameter can be one of the following values:
  *            @arg TIM4_TRGSelection_TIM3: TRIG Input source =  TIM3 TRIG Output
  *            @arg TIM4_TRGSelection_TIM2: TRIG Input source =  TIM2 TRIG Output
  * @retval None
  */
void TIM4_SelectInputTrigger(TIM4_TRGSelection_TypeDef TIM4_InputTriggerSource)
{
  uint8_t tmpsmcr = 0;

  /* Check the parameters */
  assert_param(IS_TIM4_TRIGGER_SELECTION(TIM4_InputTriggerSource));

  tmpsmcr = TIM4->SMCR;

  /* Select the Trigger Source */
  tmpsmcr &= (uint8_t)(~TIM4_SMCR_TS);
  tmpsmcr |= (uint8_t)TIM4_InputTriggerSource;

  TIM4->SMCR = (uint8_t)tmpsmcr;
}

/**
  * @brief  Enables or Disables the TIM4 Update event.
  * @param  NewState: The new state of the TIM4 peripheral Preload register.
  *          This parameter can be ENABLE or DISABLE
  * @retval None
  */
void TIM4_UpdateDisableConfig(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  /* Set or Reset the UDIS Bit */
  if (NewState != DISABLE)
  {
    TIM4->CR1 |= TIM4_CR1_UDIS ;
  }
  else
  {
    TIM4->CR1 &= (uint8_t)(~TIM4_CR1_UDIS) ;
  }
}

/**
  * @brief  Selects the TIM4 Update Request Interrupt source.
  * @param  TIM4_UpdateSource: Specifies the Update source.
  *          This parameter can be one of the following values:
  *            @arg TIM4_UpdateSource_Global: Global Update request source
  *            @arg TIM4_UpdateSource_Regular: Regular Update request source
  * @retval None
  */
void TIM4_UpdateRequestConfig(TIM4_UpdateSource_TypeDef TIM4_UpdateSource)
{
  /* Check the parameters */
  assert_param(IS_TIM4_UPDATE_SOURCE(TIM4_UpdateSource));

  /* Set or Reset the URS Bit */
  if (TIM4_UpdateSource == TIM4_UpdateSource_Regular)
  {
    TIM4->CR1 |= TIM4_CR1_URS ;
  }
  else
  {
    TIM4->CR1 &= (uint8_t)(~TIM4_CR1_URS) ;
  }
}

/**
  * @brief  Selects the TIM4’s One Pulse Mode.
  * @param  TIM4_OPMode: Specifies the OPM Mode to be used.
  *          This parameter can be one of the following values:
  *            @arg TIM4_OPMode_Single: Single one Pulse mode (OPM Active)
  *            @arg TIM4_OPMode_Repetitive: Repetitive Pulse mode (OPM inactive)
  * @retval None
  */
void TIM4_SelectOnePulseMode(TIM4_OPMode_TypeDef TIM4_OPMode)
{
  /* Check the parameters */
  assert_param(IS_TIM4_OPM_MODE(TIM4_OPMode));

  /* Set or Reset the OPM Bit */
  if (TIM4_OPMode == TIM4_OPMode_Single)
  {
    TIM4->CR1 |= TIM4_CR1_OPM ;
  }
  else
  {
    TIM4->CR1 &= (uint8_t)(~TIM4_CR1_OPM) ;
  }

}

/**
  * @brief  Selects the TIM4 Trigger Output Mode.
  * @param  TIM4_TRGOSource: Specifies the Trigger Output source.
  *          This parameter can be one of the following values:
  *            @arg TIM4_TRGOSource_Reset: Trigger Output source = Reset
  *            @arg TIM4_TRGOSource_Enable: Trigger Output source = TIM4 is enabled
  *            @arg TIM4_TRGOSource_Update: Trigger Output source = Update event
  * @retval None
  */
void TIM4_SelectOutputTrigger(TIM4_TRGOSource_TypeDef TIM4_TRGOSource)
{
  uint8_t tmpcr2 = 0;

  /* Check the parameters */
  assert_param(IS_TIM4_TRGO_SOURCE(TIM4_TRGOSource));

  tmpcr2 = TIM4->CR2;

  /* Reset the MMS Bits */
  tmpcr2 &= (uint8_t)(~TIM4_CR2_MMS);

  /* Select the TRGO source */
  tmpcr2 |= (uint8_t)TIM4_TRGOSource;

  TIM4->CR2 = tmpcr2;
}

/**
  * @brief  Selects the TIM4 Slave Mode.
  * @param  TIM4_SlaveMode: Specifies the TIM4 Slave Mode.
  *          This parameter can be one of the following values:
  *            @arg TIM4_SlaveMode_Disable: Disable slave mode to clock the prescaler
                                            directly with the internal clock
  *            @arg TIM4_SlaveMode_Reset: Slave Mode Selection  = Reset
  *            @arg TIM4_SlaveMode_Gated: Slave Mode Selection  = Gated
  *            @arg TIM4_SlaveMode_Trigger: Slave Mode Selection  = Trigger
  *            @arg TIM4_SlaveMode_External1: Slave Mode Selection  = External 1  
  * @retval None
  */
void TIM4_SelectSlaveMode(TIM4_SlaveMode_TypeDef TIM4_SlaveMode)
{
  uint8_t tmpsmcr = 0;

  /* Check the parameters */
  assert_param(IS_TIM4_SLAVE_MODE(TIM4_SlaveMode));

  tmpsmcr = TIM4->SMCR;

  /* Reset the SMS Bits */
  tmpsmcr &= (uint8_t)(~TIM4_SMCR_SMS);

  /* Select the Slave Mode */
  tmpsmcr |= (uint8_t)TIM4_SlaveMode;

  TIM4->SMCR = tmpsmcr;
}

/**
  * @brief  Sets or Resets the TIM4 Master/Slave Mode.
  * @param NewState: The new state of the synchronization between TIM4 and its slaves (through TRGO).
  *          This parameter can be ENABLE or DISABLE
  * @retval None
  */
void TIM4_SelectMasterSlaveMode(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  /* Set or Reset the MSM Bit */
  if (NewState != DISABLE)
  {
    TIM4->SMCR |= TIM4_SMCR_MSM;
  }
  else
  {
    TIM4->SMCR &= (uint8_t)(~TIM4_SMCR_MSM);
  }
}

/**
  * @brief  Configures the TIM4 Prescaler.
  * @param  Prescaler: Specifies the Prescaler Register value
  *          This parameter can be one of the following values:
  *            @arg TIM4_Prescaler_1: Time base Prescaler = 1 (No effect)
  *            @arg TIM4_Prescaler_2: Time base Prescaler = 2
  *            @arg TIM4_Prescaler_4: Time base Prescaler = 4
  *            @arg TIM4_Prescaler_8: Time base Prescaler = 8
  *            @arg TIM4_Prescaler_16: Time base Prescaler = 16
  *            @arg TIM4_Prescaler_32: Time base Prescaler = 32
  *            @arg TIM4_Prescaler_64: Time base Prescaler = 64
  *            @arg TIM4_Prescaler_128: Time base Prescaler = 128
  *            @arg TIM4_Prescaler_256: Time base Prescaler = 256
  *            @arg TIM4_Prescaler_512: Time base Prescaler = 512
  *            @arg TIM4_Prescaler_1024: Time base Prescaler = 1024
  *            @arg TIM4_Prescaler_2048: Time base Prescaler = 2048
  *            @arg TIM4_Prescaler_4096: Time base Prescaler = 4096
  *            @arg TIM4_Prescaler_8192: Time base Prescaler = 8192
  *            @arg TIM4_Prescaler_16384: Time base Prescaler = 16384
  *            @arg TIM4_Prescaler_32768: Time base Prescaler = 32768 
  * @param  TIM4_PSCReloadMode: Specifies the TIM4 Prescaler Reload mode.
  *          This parameter can be one of the following values:
  *            @arg TIM4_PSCReloadMode_Update: Prescaler value is reloaded at every update
  *            @arg TIM4_PSCReloadMode_Immediate: Prescaler value is reloaded immediately
  * @retval None
  */
void TIM4_PrescalerConfig(TIM4_Prescaler_TypeDef TIM4_Prescaler,
                          TIM4_PSCReloadMode_TypeDef TIM4_PSCReloadMode)
{
  /* Check the parameters */
  assert_param(IS_TIM4_PRESCALER_RELOAD(TIM4_PSCReloadMode));
  assert_param(IS_TIM4_PRESCALER(TIM4_Prescaler));

  /* Set the Prescaler value */
  TIM4->PSCR = (uint8_t)TIM4_Prescaler;

  /* Set or reset the UG Bit */
  if (TIM4_PSCReloadMode == TIM4_PSCReloadMode_Immediate)
  {
    TIM4->EGR |= TIM4_EGR_UG ;
  }
  else
  {
    TIM4->EGR &= (uint8_t)(~TIM4_EGR_UG) ;
  }
}

/**
  * @brief  Enables or disables TIM4 peripheral Preload register on ARR.
  * @param  NewState: The new state of the TIM4 peripheral Preload register.
  *          This parameter can be ENABLE or DISABLE
  * @retval None
  */
void TIM4_ARRPreloadConfig(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  /* Set or Reset the ARPE Bit */
  if (NewState != DISABLE)
  {
    TIM4->CR1 |= TIM4_CR1_ARPE ;
  }
  else
  {
    TIM4->CR1 &= (uint8_t)(~TIM4_CR1_ARPE) ;
  }
}

/**
  * @brief  Configures the TIM4 event to be generated by software.
  * @param  TIM4_EventSource: Specifies the event source.
  *          This parameter can be one of the following values:
  *            @arg TIM4_EventSource_Update: Update
  *            @arg TIM4_EventSource_Trigger: Trigger
  * @retval None
  */
void TIM4_GenerateEvent(TIM4_EventSource_TypeDef TIM4_EventSource)
{
  /* Check the parameters */
  assert_param(IS_TIM4_EVENT_SOURCE((uint8_t)TIM4_EventSource));

  /* Set the event sources */
  TIM4->EGR |= (uint8_t)TIM4_EventSource;
}

/**
  * @brief  Sets the TIM4 Counter Register value.
  * @param  Counter: Specifies the Counter register new value.
  *          This parameter is between 0x00 and 0xFF.
  * @retval None
  */
void TIM4_SetCounter(uint8_t TIM4_Counter)
{
  /* Set the Counter Register value */
  TIM4->CNTR = (uint8_t)(TIM4_Counter);
}

/**
  * @brief  Sets the TIM4 Autoreload Register value.
  * @param  Autoreload: Specifies the Autoreload register new value.
  *          This parameter is between 0x00 and 0xFF.
  * @retval None
  */
void TIM4_SetAutoreload(uint8_t TIM4_Autoreload)
{

  /* Set the Autoreload Register value */
  TIM4->ARR = (uint8_t)(TIM4_Autoreload);
}

/**
  * @brief  Gets the TIM4 Counter value.
  * @param  None
  * @retval Counter Register value.
  */
uint8_t TIM4_GetCounter(void)
{
  uint8_t tmpcntr = 0;
  tmpcntr = TIM4->CNTR;
  /* Get the Counter Register value */
  return ((uint8_t)tmpcntr);
}

/**
  * @brief  Gets the TIM4 Prescaler value.
  * @param  None
  * @retval TIM4 Prescaler can be one of the following values:
  *            - TIM4_Prescaler_1: Time base Prescaler = 1 (No effect)
  *            - TIM4_Prescaler_2: Time base Prescaler = 2
  *            - TIM4_Prescaler_4: Time base Prescaler = 4
  *            - TIM4_Prescaler_8: Time base Prescaler = 8
  *            - TIM4_Prescaler_16: Time base Prescaler = 16
  *            - TIM4_Prescaler_32: Time base Prescaler = 32
  *            - TIM4_Prescaler_64: Time base Prescaler = 64
  *            - TIM4_Prescaler_128: Time base Prescaler = 128
  *            - TIM4_Prescaler_256: Time base Prescaler = 256
  *            - TIM4_Prescaler_512: Time base Prescaler = 512
  *            - TIM4_Prescaler_1024: Time base Prescaler = 1024
  *            - TIM4_Prescaler_2048: Time base Prescaler = 2048
  *            - TIM4_Prescaler_4096: Time base Prescaler = 4096
  *            - TIM4_Prescaler_8192: Time base Prescaler = 8192
  *            - TIM4_Prescaler_16384: Time base Prescaler = 16384
  *            - TIM4_Prescaler_32768: Time base Prescaler = 32768  
  */
TIM4_Prescaler_TypeDef TIM4_GetPrescaler(void)
{
  /* Get the Prescaler Register value */
  return ((TIM4_Prescaler_TypeDef)TIM4->PSCR);
}

/**
  * @brief  Checks whether the TIM4 device is enabled or not.
  * @param  None
  * @retval FunctionalState The new state of the TIM4 device.
  */
FunctionalState TIM4_GetStatus(void)
{
  return ((FunctionalState)(TIM4->CR1 & TIM4_CR1_CEN));
}

/**
  * @brief  Checks whether the specified TIM4 flag is set or not.
  * @param  TIM4_FLAG: Specifies the flag to check.
  *          This parameter can be one of the following values:
  *            @arg TIM4_FLAG_Update: Update
  *            @arg TIM4_FLAG_Trigger: Trigger
  * @retval FlagStatus: The new state of TIM4_FLAG.
  *          This parameter can be SET or RESET.
  */
FlagStatus TIM4_GetFlagStatus(TIM4_FLAG_TypeDef TIM4_FLAG)
{
  __IO FlagStatus bitstatus = RESET;

  /* Check the parameters */
  assert_param(IS_TIM4_GET_FLAG(TIM4_FLAG));

  if ((TIM4->SR1 & (uint8_t)TIM4_FLAG)  != 0)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  return ((FlagStatus)bitstatus);
}

/**
  * @brief  Clears the TIM’s pending flags.
  * @param  TIM4_FLAG: Specifies the flag to clear.
  *          This parameter can be one of the following values:
  *            @arg TIM4_FLAG_Update: Update
  *            @arg TIM4_FLAG_Trigger: Trigger
  * @retval None
  */
void TIM4_ClearFlag(TIM4_FLAG_TypeDef TIM4_FLAG)
{
  /* Check the parameters */
  assert_param(IS_TIM4_CLEAR_FLAG((uint8_t)TIM4_FLAG));
  /* Clear the flags (rc_w0) clear this bit by writing 0. Writing ‘1’ has no effect*/
  TIM4->SR1 = (uint8_t)(~((uint8_t)TIM4_FLAG));
}

/**
  * @brief  Checks whether the TIM4 interrupt has occurred or not.
  * @param  TIM4_IT: Specifies the TIM4 interrupt source to check.
  *          This parameter can be one of the following values:
  *            @arg TIM4_IT_Update: Update
  *            @arg TIM4_IT_Trigger: Trigger
  * @retval ITStatus: The new state of the TIM4_IT.
  *          This parameter can be SET or RESET
  */
ITStatus TIM4_GetITStatus(TIM4_IT_TypeDef TIM4_IT)
{
  __IO ITStatus bitstatus = RESET;

  __IO uint8_t itStatus = 0x0, itEnable = 0x0;

  /* Check the parameters */
  assert_param(IS_TIM4_GET_IT(TIM4_IT));

  itStatus = (uint8_t)(TIM4->SR1 & (uint8_t)TIM4_IT);

  itEnable = (uint8_t)(TIM4->IER & (uint8_t)TIM4_IT);

  if ((itStatus != (uint8_t)RESET) && (itEnable != (uint8_t)RESET))
  {
    bitstatus = (ITStatus)SET;
  }
  else
  {
    bitstatus = (ITStatus)RESET;
  }
  return ((ITStatus)bitstatus);
}

/**
  * @brief  Clears the TIM4's interrupt pending bits.
  * @param  TIM4_IT: Specifies the pending bit to clear.
  *          This parameter can be one of the following values:
  *            @arg TIM4_IT_Update: Update
  *            @arg TIM4_IT_Trigger: Trigger
  * @retval None
  */
void TIM4_ClearITPendingBit(TIM4_IT_TypeDef TIM4_IT)
{
  /* Check the parameters */
  assert_param(IS_TIM4_IT(TIM4_IT));

  /* Clear the IT pending Bit */
  TIM4->SR1 = (uint8_t)(~(uint8_t)TIM4_IT);
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
