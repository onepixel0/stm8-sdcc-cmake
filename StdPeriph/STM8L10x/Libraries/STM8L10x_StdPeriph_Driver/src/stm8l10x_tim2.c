/**
  ******************************************************************************
  * @file    stm8l10x_tim2.c
  * @author  MCD Application Team
  * @version V1.2.1
  * @date    30-September-2014
  * @brief   This file contains all the functions for the TIM2 peripheral.
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
#include "stm8l10x_tim2.h"

/** @addtogroup STM8L10x_StdPeriph_Driver
  * @{
  */
/** @defgroup TIM2 
  * @brief TIM2 driver modules
  * @{
  */ 
  
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void TI1_Config(TIM2_ICPolarity_TypeDef TIM2_ICPolarity,
                       TIM2_ICSelection_TypeDef TIM2_ICSelection,
                       uint8_t TIM2_ICFilter);

static void TI2_Config(TIM2_ICPolarity_TypeDef TIM2_ICPolarity,
                       TIM2_ICSelection_TypeDef TIM2_ICSelection,
                       uint8_t TIM2_ICFilter);


/**
  * @addtogroup TIM2_Private_Functions
  * @{
  */

/**
  * @brief  Deinitializes the TIM2 peripheral registers to their default reset values.
  * @param  None
  * @retval None
  */
void TIM2_DeInit(void)
{
  TIM2->CR1 = TIM_CR1_RESET_VALUE;
  TIM2->CR2 = TIM_CR2_RESET_VALUE;
  TIM2->SMCR = TIM_SMCR_RESET_VALUE;
  TIM2->ETR = TIM_ETR_RESET_VALUE;
  TIM2->IER = TIM_IER_RESET_VALUE;
  TIM2->SR2 = TIM_SR2_RESET_VALUE;

  /* Disable channels */
  TIM2->CCER1 = TIM_CCER1_RESET_VALUE;
  /* Configure channels as inputs: it is necessary if lock level is equal to 2 or 3 */
  TIM2->CCMR1 = 0x01;/*TIM2_ICxSource_TIxFPx */
  TIM2->CCMR2 = 0x01;/*TIM2_ICxSource_TIxFPx */

  /* Then reset channel registers: it also works if lock level is equal to 2 or 3 */
  TIM2->CCER1 = TIM_CCER1_RESET_VALUE;
  TIM2->CCMR1 = TIM_CCMR1_RESET_VALUE;
  TIM2->CCMR2 = TIM_CCMR2_RESET_VALUE;

  TIM2->CNTRH = TIM_CNTRH_RESET_VALUE;
  TIM2->CNTRL = TIM_CNTRL_RESET_VALUE;

  TIM2->PSCR = TIM_PSCR_RESET_VALUE;

  TIM2->ARRH = TIM_ARRH_RESET_VALUE;
  TIM2->ARRL = TIM_ARRL_RESET_VALUE;

  TIM2->CCR1H = TIM_CCR1H_RESET_VALUE;
  TIM2->CCR1L = TIM_CCR1L_RESET_VALUE;
  TIM2->CCR2H = TIM_CCR2H_RESET_VALUE;
  TIM2->CCR2L = TIM_CCR2L_RESET_VALUE;

  TIM2->OISR = TIM_OISR_RESET_VALUE;
  TIM2->EGR = 0x01;/*TIM_EGR_UG;*/
  TIM2->BKR = TIM_BKR_RESET_VALUE;
  TIM2->SR1 = TIM_SR1_RESET_VALUE;
}

/**
  * @brief  Initializes the TIM2 Time Base Unit according to the specified  parameters.
  * @param  TIM2_Prescaler: Prescaler 
  *          This parameter can be one of the following values:
  *            @arg TIM2_Prescaler_1: Time base Prescaler = 1 (No effect)
  *            @arg TIM2_Prescaler_2: Time base Prescaler = 2
  *            @arg TIM2_Prescaler_4: Time base Prescaler = 4
  *            @arg TIM2_Prescaler_8: Time base Prescaler = 8
  *            @arg TIM2_Prescaler_16: Time base Prescaler = 16
  *            @arg TIM2_Prescaler_32: Time base Prescaler = 32
  *            @arg TIM2_Prescaler_64: Time base Prescaler = 64
  *            @arg TIM2_Prescaler_128: Time base Prescaler = 128                            
  * @param  TIM2_CounterMode: Counter mode
  *          This parameter can be one of the following values:
  *            @arg TIM2_CounterMode_Up: Counter Up Mode
  *            @arg TIM2_CounterMode_Down: Counter Down Mode
  *            @arg TIM2_CounterMode_CenterAligned1: Counter Central aligned Mode 1
  *            @arg TIM2_CounterMode_CenterAligned2: Counter Central aligned Mode 2
  *            @arg TIM2_CounterMode_CenterAligned3: Counter Central aligned Mode 3        
  * @param  TIM2_Period: This parameter must be a value between 0x0000 and 0xFFFF.
  * @retval None
  */
void TIM2_TimeBaseInit(TIM2_Prescaler_TypeDef TIM2_Prescaler,
                       TIM2_CounterMode_TypeDef TIM2_CounterMode,
                       uint16_t TIM2_Period)
{

  assert_param(IS_TIM2_PRESCALER(TIM2_Prescaler));
  assert_param(IS_TIM2_COUNTER_MODE(TIM2_CounterMode));

  /* Set the Autoreload value */
  TIM2->ARRH = (uint8_t)(TIM2_Period >> 8) ;
  TIM2->ARRL = (uint8_t)(TIM2_Period);

  /* Set the Prescaler value */
  TIM2->PSCR = (uint8_t)(TIM2_Prescaler);

  /* Select the Counter Mode */
  TIM2->CR1 &= (uint8_t)((uint8_t)(~TIM_CR1_CMS)) & ((uint8_t)(~TIM_CR1_DIR));
  TIM2->CR1 |= (uint8_t)(TIM2_CounterMode);
}

/**
  * @brief Initializes the TIM2 Channel1 according to the specified parameters.
  * @param  TIM2_OCMode: Output Compare Mode 
  *          This parameter can be one of the following values:
  *            @arg TIM2_OCMode_Timing: Timing (Frozen) Mode
  *            @arg TIM2_OCMode_Active: Active Mode
  *            @arg TIM2_OCMode_Inactive: Inactive Mode
  *            @arg TIM2_OCMode_Toggle: Toggle Mode
  *            @arg TIM2_OCMode_PWM1: PWM Mode 1
  *            @arg TIM2_OCMode_PWM2: PWM Mode 2          
  * @param  TIM2_OutputState: Output state
  *          This parameter can be one of the following values:
  *            @arg TIM2_OutputState_Disable: Output compare State disabled (channel output disabled)
  *            @arg TIM2_OutputState_Enable: Output compare State enabled (channel output enabled)
  * @param  TIM2_Pulse: This parameter must be a value between 0x0000 and 0xFFFF.
  * @param  TIM2_OCPolarity: Polarity
  *          This parameter can be one of the following values:
  *            @arg TIM2_OCPolarity_High: Output compare polarity  = High
  *            @arg TIM2_OCPolarity_Low: Output compare polarity  = Low 
  * @param  TIM2_OCIdleState: Output Compare Idle State
  *          This parameter can be one of the following values:
  *            @arg TIM2_OCIdleState_Reset: Output Compare Idle state  = Reset
  *            @arg TIM2_OCIdleState_Set: Output Compare Idle state  = Set
  * @retval None
  */
void TIM2_OC1Init(TIM2_OCMode_TypeDef TIM2_OCMode,
                  TIM2_OutputState_TypeDef TIM2_OutputState,
                  uint16_t TIM2_Pulse,
                  TIM2_OCPolarity_TypeDef TIM2_OCPolarity,
                  TIM2_OCIdleState_TypeDef TIM2_OCIdleState)
{
  uint8_t tmpccmr1 = 0;

  /* Check the parameters */
  assert_param(IS_TIM2_OC_MODE(TIM2_OCMode));
  assert_param(IS_TIM2_OUTPUT_STATE(TIM2_OutputState));
  assert_param(IS_TIM2_OC_POLARITY(TIM2_OCPolarity));
  assert_param(IS_TIM2_OCIDLE_STATE(TIM2_OCIdleState));

  tmpccmr1 = TIM2->CCMR1;

  /* Disable the Channel 1: Reset the CCE Bit */
  TIM2->CCER1 &= (uint8_t)(~TIM_CCER1_CC1E);
  /* Reset the Output Compare Bits */
  tmpccmr1 &= (uint8_t)(~TIM_CCMR_OCM);

  /* Set the Ouput Compare Mode */
  tmpccmr1 |= (uint8_t)TIM2_OCMode;

  TIM2->CCMR1 = tmpccmr1;

  /* Set the Output State */
  if (TIM2_OutputState == TIM2_OutputState_Enable)
  {
    TIM2->CCER1 |= TIM_CCER1_CC1E;
  }
  else
  {
    TIM2->CCER1 &= (uint8_t)(~TIM_CCER1_CC1E);
  }

  /* Set the Output Polarity */
  if (TIM2_OCPolarity == TIM2_OCPolarity_Low)
  {
    TIM2->CCER1 |= TIM_CCER1_CC1P;
  }
  else
  {
    TIM2->CCER1 &= (uint8_t)(~TIM_CCER1_CC1P);
  }

  /* Set the Output Idle state */
  if (TIM2_OCIdleState == TIM2_OCIdleState_Set)
  {
    TIM2->OISR |= TIM_OISR_OIS1;
  }
  else
  {
    TIM2->OISR &= (uint8_t)(~TIM_OISR_OIS1);
  }

  /* Set the Pulse value */
  TIM2->CCR1H = (uint8_t)(TIM2_Pulse >> 8);
  TIM2->CCR1L = (uint8_t)(TIM2_Pulse);
}

/**
  * @brief Initializes the TIM2 Channel2 according to the specified parameters.
  * @param  TIM2_OCMode: Output Compare Mode 
  *          This parameter can be one of the following values:
  *            @arg TIM2_OCMode_Timing: Timing (Frozen) Mode
  *            @arg TIM2_OCMode_Active: Active Mode
  *            @arg TIM2_OCMode_Inactive: Inactive Mode
  *            @arg TIM2_OCMode_Toggle: Toggle Mode
  *            @arg TIM2_OCMode_PWM1: PWM Mode 1
  *            @arg TIM2_OCMode_PWM2: PWM Mode 2          
  * @param  TIM2_OutputState: Output state
  *          This parameter can be one of the following values:
  *            @arg TIM2_OutputState_Disable: Output compare State disabled (channel output disabled)
  *            @arg TIM2_OutputState_Enable: Output compare State enabled (channel output enabled)
  * @param  TIM2_Pulse: This parameter must be a value between 0x0000 and 0xFFFF.
  * @param  TIM2_OCPolarity: Polarity
  *          This parameter can be one of the following values:
  *            @arg TIM2_OCPolarity_High: Output compare polarity  = High
  *            @arg TIM2_OCPolarity_Low: Output compare polarity  = Low 
  * @param  TIM2_OCIdleState: Output Compare Idle State
  *          This parameter can be one of the following values:
  *            @arg TIM2_OCIdleState_Reset: Output Compare Idle state  = Reset
  *            @arg TIM2_OCIdleState_Set: Output Compare Idle state  = Set
  * @retval None
  */
void TIM2_OC2Init(TIM2_OCMode_TypeDef TIM2_OCMode,
                  TIM2_OutputState_TypeDef TIM2_OutputState,
                  uint16_t TIM2_Pulse,
                  TIM2_OCPolarity_TypeDef TIM2_OCPolarity,
                  TIM2_OCIdleState_TypeDef TIM2_OCIdleState)
{
  uint8_t tmpccmr2 = 0;

  /* Check the parameters */
  assert_param(IS_TIM2_OC_MODE(TIM2_OCMode));
  assert_param(IS_TIM2_OUTPUT_STATE(TIM2_OutputState));
  assert_param(IS_TIM2_OC_POLARITY(TIM2_OCPolarity));
  assert_param(IS_TIM2_OCIDLE_STATE(TIM2_OCIdleState));

  tmpccmr2 = TIM2->CCMR2;

  /* Disable the Channel 2: Reset the CCE Bit */
  TIM2->CCER1 &= (uint8_t)(~TIM_CCER1_CC2E);

  /* Reset the Output Compare Bits */
  tmpccmr2 &= (uint8_t)(~TIM_CCMR_OCM);

  /* Set the Output Compare Mode */
  tmpccmr2 |= (uint8_t)TIM2_OCMode;

  TIM2->CCMR2 = tmpccmr2;

  /* Set the Output State */
  if (TIM2_OutputState == TIM2_OutputState_Enable)
  {
    TIM2->CCER1 |= TIM_CCER1_CC2E;
  }
  else
  {
    TIM2->CCER1 &= (uint8_t)(~TIM_CCER1_CC2E);
  }

  /* Set the Output Polarity */
  if (TIM2_OCPolarity == TIM2_OCPolarity_Low)
  {
    TIM2->CCER1 |= TIM_CCER1_CC2P;
  }
  else
  {
    TIM2->CCER1 &= (uint8_t)(~TIM_CCER1_CC2P);
  }


  /* Set the Output Idle state */
  if (TIM2_OCIdleState == TIM2_OCIdleState_Set)
  {
    TIM2->OISR |= TIM_OISR_OIS2;
  }
  else
  {
    TIM2->OISR &= (uint8_t)(~TIM_OISR_OIS2);
  }

  /* Set the Pulse value */
  TIM2->CCR2H = (uint8_t)(TIM2_Pulse >> 8);
  TIM2->CCR2L = (uint8_t)(TIM2_Pulse);
}

/**
  * @brief Configures the Break feature, dead time, Lock level, the OSSI,
  * @param  TIM2_OSSIState: Off-State Selection for Idle mode states.
  *          This parameter can be one of the following values:
  *            @arg TIM2_OSSIState_Enable: Off-State Selection for Idle mode enabled
  *            @arg TIM2_OSSIState_Disable: Off-State Selection for Idle mode disabled 
  * @param  TIM2_LockLevel: Lock level.
  *          This parameter can be one of the following values:
  *            @arg TIM2_LockLevel_Off: Lock option disabled
  *            @arg TIM2_LockLevel_1: Select Lock Level 1
  *            @arg TIM2_LockLevel_2: Select Lock Level 2
  *            @arg TIM2_LockLevel_3: Select Lock Level 3    
  * @param  TIM2_BreakState: Break Input enable/disable .
  *          This parameter can be one of the following values:
  *            @arg TIM2_BreakState_Disable: Break State disabled (break option disabled)
  *            @arg TIM2_BreakState_Enable: Break State enabled (break option enabled) 
  * @param  TIM2_BreakPolarity: Break Polarity.
  *          This parameter can be one of the following values:
  *            @arg TIM2_BreakPolarity_High: if Break, channel polarity = High
  *            @arg TIM2_BreakPolarity_Low: if Break, channel polarity = Low   
  * @param  TIM2_AutomaticOutput: TIM2 AOE Bit Set/Reset .
  *          This parameter can be one of the following values:
  *            @arg TIM2_AutomaticOutput_Enable: Automatic Output option enabled
  *            @arg TIM2_AutomaticOutput_Disable: Automatic Output option disabled
  * @retval None
  */
void TIM2_BKRConfig(TIM2_OSSIState_TypeDef TIM2_OSSIState,
                    TIM2_LockLevel_TypeDef TIM2_LockLevel,
                    TIM2_BreakState_TypeDef TIM2_BreakState,
                    TIM2_BreakPolarity_TypeDef TIM2_BreakPolarity,
                    TIM2_AutomaticOutput_TypeDef TIM2_AutomaticOutput)

{
  /* Check the parameters */
  assert_param(IS_TIM2_OSSI_STATE(TIM2_OSSIState));
  assert_param(IS_TIM2_LOCK_LEVEL(TIM2_LockLevel));
  assert_param(IS_TIM2_BREAK_STATE(TIM2_BreakState));
  assert_param(IS_TIM2_BREAK_POLARITY(TIM2_BreakPolarity));
  assert_param(IS_TIM2_AUTOMATIC_OUTPUT_STATE(TIM2_AutomaticOutput));

  /* Set the Lock level, the Break enable Bit and the Ploarity, the OSSI State,
  the dead time value and the Automatic Output Enable Bit */

  TIM2->BKR = (uint8_t)((uint8_t)TIM2_OSSIState | (uint8_t)TIM2_LockLevel | \
                        (uint8_t)TIM2_BreakState | (uint8_t)TIM2_BreakPolarity | \
                        (uint8_t)TIM2_AutomaticOutput);
}

/**
  * @brief  Initializes the TIM2 peripheral according to the specified parameters.
  * @param  TIM2_Channel: TIM2 Channel
  *          This parameter can be one of the following values:
  *            @arg TIM2_Channel_1: Channel 1
  *            @arg TIM2_Channel_2: Channel 2     
  * @param  TIM2_ICPolarity: Input Capture Polarity
  *          This parameter can be one of the following values:
  *            @arg TIM2_ICPolarity_Rising: Input Capture on Rising Edge
  *            @arg TIM2_ICPolarity_Falling: Input Capture on Falling Edge  
  * @param  TIM2_ICSelection: Input Capture Selection
  *          This parameter can be one of the following values:
  *            @arg TIM2_ICSelection_DirectTI: Input Capture mapped on the direct input
  *            @arg TIM2_ICSelection_IndirectTI: Input Capture mapped on the indirect input
  *            @arg TIM2_ICSelection_TRGI: Input Capture mapped on the Trigger Input   
  * @param  TIM2_ICPrescaler: Input Capture Prescaler
  *          This parameter can be one of the following values:
  *            @arg TIM2_ICPSC_DIV1: Input Capture Prescaler = 1 (one capture every 1 event)
  *            @arg TIM2_ICPSC_DIV2: Input Capture Prescaler = 2 (one capture every 2 events)
  *            @arg TIM2_ICPSC_DIV4: Input Capture Prescaler = 4 (one capture every 4 events)
  *            @arg TIM2_ICPSC_DIV8: Input Capture Prescaler = 8 (one capture every 8 events)   
  * @param  TIM2_ICFilter: This parameter must be a value between 0x00 and 0x0F.
  * @retval None
  */
void TIM2_ICInit(TIM2_Channel_TypeDef TIM2_Channel,
                 TIM2_ICPolarity_TypeDef TIM2_ICPolarity,
                 TIM2_ICSelection_TypeDef TIM2_ICSelection,
                 TIM2_ICPSC_TypeDef TIM2_ICPrescaler,
                 uint8_t TIM2_ICFilter)
{
  /* Check the parameters */
  assert_param(IS_TIM2_CHANNEL(TIM2_Channel));

  if (TIM2_Channel == TIM2_Channel_1)
  {
    /* TI1 Configuration */
    TI1_Config(TIM2_ICPolarity,
               TIM2_ICSelection,
               TIM2_ICFilter);

    /* Set the Input Capture Prescaler value */
    TIM2_SetIC1Prescaler(TIM2_ICPrescaler);
  }
  else /* if (TIM2_Channel == TIM2_Channel_2) */
  {
    /* TI2 Configuration */
    TI2_Config(TIM2_ICPolarity,
               TIM2_ICSelection,
               TIM2_ICFilter);
    /* Set the Input Capture Prescaler value */
    TIM2_SetIC2Prescaler(TIM2_ICPrescaler);
  }
}

/**
  * @brief  Configures the TIM2 peripheral in PWM Input Mode according to the
  *         specified parameters.
  * @param  TIM2_Channel: TIM2 Channel
  *          This parameter can be one of the following values:
  *            @arg TIM2_Channel_1: Channel 1
  *            @arg TIM2_Channel_2: Channel 2     
  * @param  TIM2_ICPolarity: Input Capture Polarity
  *          This parameter can be one of the following values:
  *            @arg TIM2_ICPolarity_Rising: Input Capture on Rising Edge
  *            @arg TIM2_ICPolarity_Falling: Input Capture on Falling Edge  
  * @param  TIM2_ICSelection: Input Capture Selection
  *          This parameter can be one of the following values:
  *            @arg TIM2_ICSelection_DirectTI: Input Capture mapped on the direct input
  *            @arg TIM2_ICSelection_IndirectTI: Input Capture mapped on the indirect input
  *            @arg TIM2_ICSelection_TRGI: Input Capture mapped on the Trigger Input   
  * @param  TIM2_ICPrescaler: Input Capture Prescaler
  *          This parameter can be one of the following values:
  *            @arg TIM2_ICPSC_DIV1: Input Capture Prescaler = 1 (one capture every 1 event)
  *            @arg TIM2_ICPSC_DIV2: Input Capture Prescaler = 2 (one capture every 2 events)
  *            @arg TIM2_ICPSC_DIV4: Input Capture Prescaler = 4 (one capture every 4 events)
  *            @arg TIM2_ICPSC_DIV8: Input Capture Prescaler = 8 (one capture every 8 events) 
  * @retval None
  */
void TIM2_PWMIConfig(TIM2_Channel_TypeDef TIM2_Channel,
                     TIM2_ICPolarity_TypeDef TIM2_ICPolarity,
                     TIM2_ICSelection_TypeDef TIM2_ICSelection,
                     TIM2_ICPSC_TypeDef TIM2_ICPrescaler,
                     uint8_t TIM2_ICFilter)
{
  uint8_t icpolarity = (uint8_t)TIM2_ICPolarity_Rising;
  uint8_t icselection = (uint8_t)TIM2_ICSelection_DirectTI;

  /* Check the parameters */
  assert_param(IS_TIM2_CHANNEL(TIM2_Channel));

  /* Select the Opposite Input Polarity */
  if (TIM2_ICPolarity == TIM2_ICPolarity_Rising)
  {
    icpolarity = (uint8_t)TIM2_ICPolarity_Falling;
  }
  else
  {
    icpolarity = (uint8_t)TIM2_ICPolarity_Rising;
  }

  /* Select the Opposite Input */
  if (TIM2_ICSelection == TIM2_ICSelection_DirectTI)
  {
    icselection = (uint8_t)TIM2_ICSelection_IndirectTI;
  }
  else
  {
    icselection = (uint8_t)TIM2_ICSelection_DirectTI;
  }

  if (TIM2_Channel == TIM2_Channel_1)
  {
    /* TI1 Configuration */
    TI1_Config(TIM2_ICPolarity, TIM2_ICSelection,
               TIM2_ICFilter);

    /* Set the Input Capture Prescaler value */
    TIM2_SetIC1Prescaler(TIM2_ICPrescaler);

    /* TI2 Configuration */
    TI2_Config((TIM2_ICPolarity_TypeDef)icpolarity, (TIM2_ICSelection_TypeDef)icselection, TIM2_ICFilter);

    /* Set the Input Capture Prescaler value */
    TIM2_SetIC2Prescaler(TIM2_ICPrescaler);
  }
  else
  {
    /* TI2 Configuration */
    TI2_Config(TIM2_ICPolarity, TIM2_ICSelection,
               TIM2_ICFilter);

    /* Set the Input Capture Prescaler value */
    TIM2_SetIC2Prescaler(TIM2_ICPrescaler);

    /* TI1 Configuration */
    TI1_Config((TIM2_ICPolarity_TypeDef)icpolarity, (TIM2_ICSelection_TypeDef)icselection, TIM2_ICFilter);

    /* Set the Input Capture Prescaler value */
    TIM2_SetIC1Prescaler(TIM2_ICPrescaler);
  }
}

/**
  * @brief Enables or disables the TIM2 peripheral.
  * @param NewState The new state of the TIM2 peripheral.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void TIM2_Cmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  /* set or Reset the CEN Bit */
  if (NewState != DISABLE)
  {
    TIM2->CR1 |= TIM_CR1_CEN;
  }
  else
  {
    TIM2->CR1 &= (uint8_t)(~TIM_CR1_CEN);
  }
}

/**
  * @brief  Enables or disables the TIM2 peripheral Main Outputs.
  * @param  NewState: The new state of the TIM2 peripheral.
  *          This parameter can be ENABLE or DISABLE
  * @retval None
  */
void TIM2_CtrlPWMOutputs(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  /* Set or Reset the MOE Bit */

  if (NewState != DISABLE)
  {
    TIM2->BKR |= TIM_BKR_MOE ;
  }
  else
  {
    TIM2->BKR &= (uint8_t)(~TIM_BKR_MOE) ;
  }
}

/**
  * @brief  Enables or disables the specified TIM2 interrupts.
  * @param  TIM2_IT: Specifies the TIM2 interrupts sources to be enabled or disabled.
  *          This parameter can be any combination of the following values:
  *            @arg TIM2_IT_Update: Update
  *            @arg TIM2_IT_CC1: Capture Compare Channel1
  *            @arg TIM2_IT_CC2: Capture Compare Channel2 
  *            @arg TIM2_IT_Trigger: Trigger 
  *            @arg TIM2_IT_Break: Break  
  * @param  NewState: The new state of the TIM2 peripheral.
  *          This parameter can be ENABLE or DISABLE
  * @retval None
  */
void TIM2_ITConfig(TIM2_IT_TypeDef TIM2_IT, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_TIM2_IT(TIM2_IT));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the Interrupt sources */
    TIM2->IER |= (uint8_t)TIM2_IT;
  }
  else
  {
    /* Disable the Interrupt sources */
    TIM2->IER &= (uint8_t)(~(uint8_t)TIM2_IT);
  }
}

/**
  * @brief  Enables the TIM2 internal Clock.
  * @param  None
  * @retval None
  */
void TIM2_InternalClockConfig(void)
{
  /* Disable slave mode to clock the prescaler directly with the internal clock */
  TIM2->SMCR &= (uint8_t)(~TIM_SMCR_SMS);
}

/**
  * @brief  Configures the TIM2 External clock Mode1.
  * @param  TIM2_ExtTRGPrescaler: Specifies the external Trigger Prescaler.
  *          This parameter can be one of the following values:
  *            @arg TIM2_ExtTRGPSC_OFF: No External Trigger prescaler
  *            @arg TIM2_ExtTRGPSC_DIV2: External Trigger prescaler = 2 (ETRP frequency divided by 2)
  *            @arg TIM2_ExtTRGPSC_DIV4: External Trigger prescaler = 4 (ETRP frequency divided by 4) 
  *            @arg TIM2_ExtTRGPSC_DIV8: External Trigger prescaler = 8 (ETRP frequency divided by 8)   
  * @param  TIM2_ExtTRGPolarity: Specifies the external Trigger Polarity.
  *          This parameter can be one of the following values:
  *            @arg TIM2_ExtTRGPolarity_Inverted: External Trigger Polarity = inverted
  *            @arg TIM2_ExtTRGPolarity_NonInverted: External Trigger Polarity = non inverted
  * @param  ExtTRGFilter: Specifies the External Trigger Filter.
  *          This parameter must be a value between 0x00 and 0x0F
  * @retval None
  */
void TIM2_ETRClockMode1Config(TIM2_ExtTRGPSC_TypeDef TIM2_ExtTRGPrescaler,
                              TIM2_ExtTRGPolarity_TypeDef TIM2_ExtTRGPolarity,
                              uint8_t TIM2_ExtTRGFilter)
{
  /* Configure the ETR Clock source */
  TIM2_ETRConfig(TIM2_ExtTRGPrescaler, TIM2_ExtTRGPolarity, TIM2_ExtTRGFilter);

  /* Select the External clock mode1 */
  TIM2->SMCR &= (uint8_t)(~TIM_SMCR_SMS);
  TIM2->SMCR |= (uint8_t)(TIM2_SlaveMode_External1);

  /* Select the Trigger selection : ETRF */
  TIM2->SMCR &= (uint8_t)(~TIM_SMCR_TS);
  TIM2->SMCR |= (uint8_t)((TIM2_TRGSelection_TypeDef)TIM2_TRGSelection_ETRF);
}

/**
  * @brief Configures the TIM2 External clock Mode2.
  * @param TIM2_ExtTRGPrescaler Specifies the external Trigger Prescaler
  * @param TIM2_ExtTRGPolarity  Specifies the external Trigger Polarity
  * @param TIM2_ExtTRGFilter    Specifies the External Trigger Filter (must be a value between 0 and 15)
  * @retval None
  */
void TIM2_ETRClockMode2Config(TIM2_ExtTRGPSC_TypeDef TIM2_ExtTRGPrescaler,
                              TIM2_ExtTRGPolarity_TypeDef TIM2_ExtTRGPolarity,
                              uint8_t TIM2_ExtTRGFilter)
{
  /* Configure the ETR Clock source */
  TIM2_ETRConfig(TIM2_ExtTRGPrescaler, TIM2_ExtTRGPolarity, TIM2_ExtTRGFilter);

  /* Enable the External clock mode2 */
  TIM2->ETR |= TIM_ETR_ECE ;
}

/**
  * @brief  Configures the TIM2 External clock Mode2.
  * @param  TIM2_ExtTRGPrescaler: Specifies the external Trigger Prescaler.
  *          This parameter can be one of the following values:
  *            @arg TIM2_ExtTRGPSC_OFF: No External Trigger prescaler
  *            @arg TIM2_ExtTRGPSC_DIV2: External Trigger prescaler = 2 (ETRP frequency divided by 2)
  *            @arg TIM2_ExtTRGPSC_DIV4: External Trigger prescaler = 4 (ETRP frequency divided by 4) 
  *            @arg TIM2_ExtTRGPSC_DIV8: External Trigger prescaler = 8 (ETRP frequency divided by 8) 
  * @param  TIM2_ExtTRGPolarity: Specifies the external Trigger Polarity.
  *          This parameter can be one of the following values:
  *            @arg TIM2_ExtTRGPolarity_Inverted: External Trigger Polarity = inverted
  *            @arg TIM2_ExtTRGPolarity_NonInverted: External Trigger Polarity = non inverted
  * @param  ExtTRGFilter: Specifies the External Trigger Filter.
  *          This parameter must be a value between 0x00 and 0x0F
  */
void TIM2_ETRConfig(TIM2_ExtTRGPSC_TypeDef TIM2_ExtTRGPrescaler,
                    TIM2_ExtTRGPolarity_TypeDef TIM2_ExtTRGPolarity,
                    uint8_t TIM2_ExtTRGFilter)
{
  /* Check the parameters */
  assert_param(IS_TIM2_EXT_PRESCALER(TIM2_ExtTRGPrescaler));
  assert_param(IS_TIM2_EXT_POLARITY(TIM2_ExtTRGPolarity));
  assert_param(IS_TIM2_EXT_FILTER(TIM2_ExtTRGFilter));
  /* Set the Prescaler, the Filter value and the Polarity */
  TIM2->ETR |= (uint8_t)((uint8_t)TIM2_ExtTRGPrescaler | (uint8_t)TIM2_ExtTRGPolarity | (uint8_t)TIM2_ExtTRGFilter);
}

/**
  * @brief  Configures the TIM2 Trigger as External Clock.
  * @param  TIM2_TIxExternalCLKSource: Specifies Trigger source.
  *          This parameter can be one of the following values:
  *            @arg TIM2_TIxExternalCLK1Source_TI1ED: External Clock mode 1 source = TI1ED
  *            @arg TIM2_TIxExternalCLK1Source_TI1: External Clock mode 1 source = TI1 
  *            @arg TIM2_TIxExternalCLK1Source_TI2: External Clock mode 1 source = TI2  
  * @param  TIM2_ICPolarity: Specifies the TIx Polarity.
  *          This parameter can be one of the following values:
  *            @arg TIM2_ICPolarity_Rising: Input Capture on Rising Edge
  *            @arg TIM2_ICPolarity_Falling: Input Capture on Falling Edge  
  * @param  ICFilter: Specifies the filter value.
  *          This parameter must be a value between 0x00 and 0x0F
  * @retval None
  */
void TIM2_TIxExternalClockConfig(TIM2_TIxExternalCLK1Source_TypeDef TIM2_TIxExternalCLKSource,
                                 TIM2_ICPolarity_TypeDef TIM2_ICPolarity,
                                 uint8_t TIM2_ICFilter)
{
  /* Check the parameters */
  assert_param(IS_TIM2_TIXCLK_SOURCE(TIM2_TIxExternalCLKSource));
  assert_param(IS_TIM2_IC_POLARITY(TIM2_ICPolarity));
  assert_param(IS_TIM2_IC_FILTER(TIM2_ICFilter));

  /* Configure the TIM2 Input Clock Source */
  if (TIM2_TIxExternalCLKSource == TIM2_TIxExternalCLK1Source_TI2)
  {
    TI2_Config(TIM2_ICPolarity, TIM2_ICSelection_DirectTI, TIM2_ICFilter);
  }
  else
  {
    TI1_Config(TIM2_ICPolarity, TIM2_ICSelection_DirectTI, TIM2_ICFilter);
  }

  /* Select the Trigger source */
  TIM2_SelectInputTrigger((TIM2_TRGSelection_TypeDef)TIM2_TIxExternalCLKSource);

  /* Select the External clock mode1 */
  TIM2->SMCR |= (uint8_t)(TIM2_SlaveMode_External1);
}

/**
  * @brief  Selects the TIM2 Input Trigger source.
  * @param  TIM2_InputTriggerSource: Specifies Input Trigger source.
  *          This parameter can be one of the following values:
  *            @arg TIM2_TRGSelection_TIM4: TRIG Input source =  TIM TRIG Output
  *            @arg TIM2_TRGSelection_TIM1: TRIG Input source =  TIM TRIG Output
  *            @arg TIM2_TRGSelection_TIM2: TRIG Input source =  TIM TRIG Output
  *            @arg TIM2_TRGSelection_TIM2: TRIG Input source =  TIM TRIG Output
  *            @arg TIM2_TRGSelection_TI1F_ED: TRIG Input source = TI1F_ED (TI1 Edge Detector)
  *            @arg TIM2_TRGSelection_TI1FP1: TRIG Input source = TI1FP1 (Filtered Timer Input 1)
  *            @arg TIM2_TRGSelection_TI2FP2: TRIG Input source = TI2FP2 (Filtered Timer Input 2)
  *            @arg TIM2_TRGSelection_ETRF: TRIG Input source =  ETRF (External Trigger Input ) 
  * @retval None
  */
void TIM2_SelectInputTrigger(TIM2_TRGSelection_TypeDef TIM2_InputTriggerSource)
{
  uint8_t tmpsmcr = 0;

  /* Check the parameters */
  assert_param(IS_TIM2_TRIGGER_SELECTION(TIM2_InputTriggerSource));

  tmpsmcr = TIM2->SMCR;

  /* Select the Trigger Source */
  tmpsmcr &= (uint8_t)(~TIM_SMCR_TS);
  tmpsmcr |= (uint8_t)TIM2_InputTriggerSource;

  TIM2->SMCR = (uint8_t)tmpsmcr;
}

/**
  * @brief  Enables or Disables the TIM2 Update event.
  * @param  NewState: The new state of the TIM2 peripheral Preload register.
  *          This parameter can be ENABLE or DISABLE
  * @retval None
  */
void TIM2_UpdateDisableConfig(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  /* Set or Reset the UDIS Bit */
  if (NewState != DISABLE)
  {
    TIM2->CR1 |= TIM_CR1_UDIS;
  }
  else
  {
    TIM2->CR1 &= (uint8_t)(~TIM_CR1_UDIS);
  }
}

/**
  * @brief  Selects the TIM2 Update Request Interrupt source.
  * @param  TIM2_UpdateSource: Specifies the Update source.
  *          This parameter can be one of the following values:
  *            @arg TIM2_UpdateSource_Global: Global Update request source
  *            @arg TIM2_UpdateSource_Regular: Regular Update request source 
  * @retval None
  */
void TIM2_UpdateRequestConfig(TIM2_UpdateSource_TypeDef TIM2_UpdateSource)
{
  /* Check the parameters */
  assert_param(IS_TIM2_UPDATE_SOURCE(TIM2_UpdateSource));

  /* Set or Reset the URS Bit */
  if (TIM2_UpdateSource == TIM2_UpdateSource_Regular)
  {
    TIM2->CR1 |= TIM_CR1_URS ;
  }
  else
  {
    TIM2->CR1 &= (uint8_t)(~TIM_CR1_URS);
  }
}

/**
  * @brief  Enables or Disables the TIM’s Hall sensor interface.
  * @param  NewState: The new state of the TIM2 Hall sensor interface.
  *          This parameter can be ENABLE or DISABLE
  * @retval None
  */
void TIM2_SelectHallSensor(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  /* Set or Reset the TI1S Bit */
  if (NewState != DISABLE)
  {
    TIM2->CR2 |= TIM_CR2_TI1S;
  }
  else
  {
    TIM2->CR2 &= (uint8_t)(~TIM_CR2_TI1S);
  }
}

/**
  * @brief  Selects the TIM’s One Pulse Mode.
  * @param  TIM2_OPMode: Specifies the OPM Mode to be used.
  *          This parameter can be one of the following values:
  *            @arg TIM2_OPMode_Single: Single one Pulse mode (OPM Active)
  *            @arg TIM2_OPMode_Repetitive: Single one Pulse mode (OPM Active)  
  * @retval None
  */
void TIM2_SelectOnePulseMode(TIM2_OPMode_TypeDef TIM2_OPMode)
{
  /* Check the parameters */
  assert_param(IS_TIM2_OPM_MODE(TIM2_OPMode));

  /* Set or Reset the OPM Bit */
  if (TIM2_OPMode == TIM2_OPMode_Single)
  {
    TIM2->CR1 |= TIM_CR1_OPM ;
  }
  else
  {
    TIM2->CR1 &= (uint8_t)(~TIM_CR1_OPM);
  }
}

/**
  * @brief  Selects the TIM2 Trigger Output Mode.
  * @param  TIM2_TRGOSource: Specifies the Trigger Output source.
  *          This parameter can be one of the following values:
  *            @arg TIM2_TRGOSource_Reset: Trigger Output source = Reset 
  *            @arg TIM2_TRGOSource_Enable: Trigger Output source = TIM2 is enabled 
  *            @arg TIM2_TRGOSource_Update: Trigger Output source = Update event
  *            @arg TIM2_TRGOSource_OC1: Trigger Output source = output compare channel1
  *            @arg TIM2_TRGOSource_OC1REF: Trigger Output source = output compare channel 1 reference
  *            @arg TIM2_TRGOSource_OC2REF: Trigger Output source = output compare channel 2 reference   
  * @retval None
  */
void TIM2_SelectOutputTrigger(TIM2_TRGOSource_TypeDef TIM2_TRGOSource)
{
  uint8_t tmpcr2 = 0;

  /* Check the parameters */
  assert_param(IS_TIM2_TRGO_SOURCE(TIM2_TRGOSource));

  tmpcr2 = TIM2->CR2;

  /* Reset the MMS Bits */
  tmpcr2 &= (uint8_t)(~TIM_CR2_MMS);

  /* Select the TRGO source */
  tmpcr2 |= (uint8_t)TIM2_TRGOSource;

  TIM2->CR2 = tmpcr2;
}

/**
  * @brief  Selects the TIM2 Slave Mode.
  * @param  TIM2_SlaveMode: Specifies the TIM2 Slave Mode.
  *          This parameter can be one of the following values:
  *            @arg TIM2_SlaveMode_Reset: Slave Mode Selection  = Reset
  *            @arg TIM2_SlaveMode_Gated: Slave Mode Selection  = Gated
  *            @arg TIM2_SlaveMode_Trigger: Slave Mode Selection  = Trigger
  *            @arg TIM2_SlaveMode_External1: Slave Mode Selection  = External 1 
  * @retval None
  */
void TIM2_SelectSlaveMode(TIM2_SlaveMode_TypeDef TIM2_SlaveMode)
{
  uint8_t tmpsmcr = 0;

  /* Check the parameters */
  assert_param(IS_TIM2_SLAVE_MODE(TIM2_SlaveMode));

  tmpsmcr = TIM2->SMCR;

  /* Reset the SMS Bits */
  tmpsmcr &= (uint8_t)(~TIM_SMCR_SMS);

  /* Select the Slave Mode */
  tmpsmcr |= (uint8_t)TIM2_SlaveMode;

  TIM2->SMCR = tmpsmcr;
}

/**
  * @brief  Sets or Resets the TIM2 Master/Slave Mode.
  * @param  NewState: The new state of the synchronization between TIM2 and its slaves (through TRGO).
  *          This parameter can be ENABLE or DISABLE
  * @retval None
  */
void TIM2_SelectMasterSlaveMode(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  /* Set or Reset the MSM Bit */
  if (NewState != DISABLE)
  {
    TIM2->SMCR |= TIM_SMCR_MSM;
  }
  else
  {
    TIM2->SMCR &= (uint8_t)(~TIM_SMCR_MSM);
  }
}

/**
  * @brief  Configures the TIM2 Encoder Interface.
  * @param  TIM2_EncoderMode: Specifies the TIM2 Encoder Mode.
  *          This parameter can be one of the following values:
  *            @arg TIM2_EncoderMode_TI1: Encoder mode 1
  *            @arg TIM2_EncoderMode_TI2: Encoder mode 2
  *            @arg TIM2_EncoderMode_TI12: Encoder mode 3   
  * @param  TIM2_IC1Polarity: Specifies the IC1 Polarity.
  *          This parameter can be one of the following values:
  *            @arg TIM2_ICPolarity_Rising: Input Capture on Rising Edge
  *            @arg TIM2_ICPolarity_Falling: Input Capture on Falling Edge  
  * @param  TIM2_IC2Polarity: Specifies the IC2 Polarity.
  *          This parameter can be one of the following values:
  *            @arg TIM2_ICPolarity_Rising: Input Capture on Rising Edge
  *            @arg TIM2_ICPolarity_Falling: Input Capture on Falling Edge 
  * @retval None
  */
void TIM2_EncoderInterfaceConfig(TIM2_EncoderMode_TypeDef TIM2_EncoderMode,
                                 TIM2_ICPolarity_TypeDef TIM2_IC1Polarity,
                                 TIM2_ICPolarity_TypeDef TIM2_IC2Polarity)
{
  uint8_t tmpsmcr = 0;
  uint8_t tmpccmr1 = 0;
  uint8_t tmpccmr2 = 0;

  /* Check the parameters */
  assert_param(IS_TIM2_ENCODER_MODE(TIM2_EncoderMode));
  assert_param(IS_TIM2_IC_POLARITY(TIM2_IC1Polarity));
  assert_param(IS_TIM2_IC_POLARITY(TIM2_IC2Polarity));

  tmpsmcr = TIM2->SMCR;
  tmpccmr1 = TIM2->CCMR1;
  tmpccmr2 = TIM2->CCMR2;

  /* Set the encoder Mode */
  tmpsmcr &= (uint8_t)(TIM_SMCR_MSM | TIM_SMCR_TS)  ;
  tmpsmcr |= (uint8_t)TIM2_EncoderMode;

  /* Select the Capture Compare 1 and the Capture Compare 2 as input */
  tmpccmr1 &= (uint8_t)(~TIM_CCMR_CCxS);
  tmpccmr2 &= (uint8_t)(~TIM_CCMR_CCxS);
  tmpccmr1 |= TIM_CCMR_TIxDirect_Set;
  tmpccmr2 |= TIM_CCMR_TIxDirect_Set;

  /* Set the TI1 and the TI2 Polarities */
  if (TIM2_IC1Polarity == TIM2_ICPolarity_Falling)
  {
    TIM2->CCER1 |= TIM_CCER1_CC1P ;
  }
  else
  {
    TIM2->CCER1 &= (uint8_t)(~TIM_CCER1_CC1P) ;
  }

  if (TIM2_IC2Polarity == TIM2_ICPolarity_Falling)
  {
    TIM2->CCER1 |= TIM_CCER1_CC2P ;
  }
  else
  {
    TIM2->CCER1 &= (uint8_t)(~TIM_CCER1_CC2P) ;
  }

  TIM2->SMCR = tmpsmcr;
  TIM2->CCMR1 = tmpccmr1;
  TIM2->CCMR2 = tmpccmr2;
}

/**
  * @brief  Configures the TIM2 Prescaler.
  * @param  Prescaler: Specifies the Prescaler Register value
  *          This parameter can be one of the following values:
  *            @arg TIM2_Prescaler_1: Time base Prescaler = 1 (No effect)
  *            @arg TIM2_Prescaler_2: Time base Prescaler = 2
  *            @arg TIM2_Prescaler_4: Time base Prescaler = 4
  *            @arg TIM2_Prescaler_8: Time base Prescaler = 8
  *            @arg TIM2_Prescaler_16: Time base Prescaler = 16
  *            @arg TIM2_Prescaler_32: Time base Prescaler = 32
  *            @arg TIM2_Prescaler_64: Time base Prescaler = 64
  *            @arg TIM2_Prescaler_128: Time base Prescaler = 128  
  * @param  TIM2_PSCReloadMode: Specifies the TIM2 Prescaler Reload mode.
  *          This parameter can be one of the following values:
  *            @arg TIM2_PSCReloadMode_Update: Prescaler value is reloaded at every update
  *            @arg TIM2_PSCReloadMode_Immediate: Prescaler value is reloaded at every update  
  * @retval None
  */
void TIM2_PrescalerConfig(TIM2_Prescaler_TypeDef TIM2_Prescaler,
                          TIM2_PSCReloadMode_TypeDef TIM2_PSCReloadMode)
{
  /* Check the parameters */
  assert_param(IS_TIM2_PRESCALER(TIM2_Prescaler));
  assert_param(IS_TIM2_PRESCALER_RELOAD(TIM2_PSCReloadMode));

  /* Set the Prescaler value */
  TIM2->PSCR = (uint8_t)(TIM2_Prescaler);

  /* Set or reset the UG Bit */
  if (TIM2_PSCReloadMode == TIM2_PSCReloadMode_Immediate)
  {
    TIM2->EGR |= TIM_EGR_UG ;
  }
  else
  {
    TIM2->EGR &= (uint8_t)(~TIM_EGR_UG) ;
  }
}

/**
  * @brief  Specifies the TIM2 Counter Mode to be used.
  * @param  TIM2_CounterMode: Specifies the Counter Mode to be used
  *          This parameter can be one of the following values:
  *            @arg TIM2_CounterMode_Up: Counter Up Mode
  *            @arg TIM2_CounterMode_Down: Counter Down Mode
  *            @arg TIM2_CounterMode_CenterAligned1: Counter Central aligned Mode 1
  *            @arg TIM2_CounterMode_CenterAligned2: Counter Central aligned Mode 2
  *            @arg TIM2_CounterMode_CenterAligned3: Counter Central aligned Mode 3   
  * @retval None
  */
void TIM2_CounterModeConfig(TIM2_CounterMode_TypeDef TIM2_CounterMode)
{
  uint8_t tmpcr1 = 0;

  /* Check the parameters */
  assert_param(IS_TIM2_COUNTER_MODE(TIM2_CounterMode));

  tmpcr1 = TIM2->CR1;

  /* Reset the CMS and DIR Bits */
  tmpcr1 &= (uint8_t)((uint8_t)(~TIM_CR1_CMS) & (uint8_t)(~TIM_CR1_DIR));

  /* Set the Counter Mode */
  tmpcr1 |= (uint8_t)TIM2_CounterMode;

  TIM2->CR1 = tmpcr1;
}

/**
  * @brief  Forces the TIM2 Channel1 output waveform to active or inactive level.
  * @param  TIM2_ForcedAction: Specifies the forced Action to be set to the output waveform.
  *          This parameter can be one of the following values:
  *            @arg TIM2_ForcedAction_Active: Output Reference is forced low 
  *            @arg TIM2_ForcedAction_Inactive: Output Reference is forced high 
  * @retval None
  */
void TIM2_ForcedOC1Config(TIM2_ForcedAction_TypeDef TIM2_ForcedAction)
{
  uint8_t tmpccmr1 = 0;

  /* Check the parameters */
  assert_param(IS_TIM2_FORCED_ACTION(TIM2_ForcedAction));

  tmpccmr1 = TIM2->CCMR1;

  /* Reset the OCM Bits */
  tmpccmr1 &= (uint8_t)(~TIM_CCMR_OCM);

  /* Configure The Forced output Mode */
  tmpccmr1 |= (uint8_t)TIM2_ForcedAction;

  TIM2->CCMR1 = tmpccmr1;
}

/**
  * @brief  Forces the TIM2 Channel2 output waveform to active or inactive level.
  * @param  TIM2_ForcedAction: Specifies the forced Action to be set to the output waveform.
  *          This parameter can be one of the following values:
  *            @arg TIM2_ForcedAction_Active: Output Reference is forced low 
  *            @arg TIM2_ForcedAction_Inactive: Output Reference is forced high 
  * @retval None
  */
void TIM2_ForcedOC2Config(TIM2_ForcedAction_TypeDef TIM2_ForcedAction)
{
  uint8_t tmpccmr2 = 0;

  /* Check the parameters */
  assert_param(IS_TIM2_FORCED_ACTION(TIM2_ForcedAction));

  tmpccmr2 = TIM2->CCMR2;

  /* Reset the OCM Bits */
  tmpccmr2 &= (uint8_t)(~TIM_CCMR_OCM);

  /* Configure The Forced output Mode */
  tmpccmr2 |= (uint8_t)TIM2_ForcedAction;

  TIM2->CCMR2 = tmpccmr2;
}

/**
  * @brief  Enables or disables TIM2 peripheral Preload register on ARR.
  * @param  NewState: The new state of the TIM2 peripheral Preload register.
  *          This parameter can be ENABLE or DISABLE
  * @retval None
  */
void TIM2_ARRPreloadConfig(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  /* Set or Reset the ARPE Bit */
  if (NewState != DISABLE)
  {
    TIM2->CR1 |= TIM_CR1_ARPE;
  }
  else
  {
    TIM2->CR1 &= (uint8_t)(~TIM_CR1_ARPE);
  }
}

/**
  * @brief  Enables or disables the TIM2 peripheral Preload Register on CCR1.
  * @param  NewState: The new state of the Capture Compare Preload register.
  *          This parameter can be ENABLE or DISABLE
  * @retval None
  */
void TIM2_OC1PreloadConfig(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  /* Set or Reset the OC1PE Bit */
  if (NewState != DISABLE)
  {
    TIM2->CCMR1 |= TIM_CCMR_OCxPE ;
  }
  else
  {
    TIM2->CCMR1 &= (uint8_t)(~TIM_CCMR_OCxPE) ;
  }
}

/**
  * @brief  Enables or disables the TIM2 peripheral Preload Register on CCR2.
  * @param  NewState: The new state of the Capture Compare Preload register.
  *          This parameter can be ENABLE or DISABLE
  * @retval None
  */
void TIM2_OC2PreloadConfig(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  /* Set or Reset the OC2PE Bit */
  if (NewState != DISABLE)
  {
    TIM2->CCMR2 |= TIM_CCMR_OCxPE ;
  }
  else
  {
    TIM2->CCMR2 &= (uint8_t)(~TIM_CCMR_OCxPE) ;
  }
}

/**
  * @brief Configures the TIM2 Capture Compare 1 Fast feature.
  * @param NewState The new state of the Output Compare Fast Enable bit.
  * @retval None
  */
void TIM2_OC1FastCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  /* Set or Reset the OC1FE Bit */
  if (NewState != DISABLE)
  {
    TIM2->CCMR1 |= TIM_CCMR_OCxFE ;
  }
  else
  {
    TIM2->CCMR1 &= (uint8_t)(~TIM_CCMR_OCxFE) ;
  }
}

/**
  * @brief Configures the TIM2 Capture Compare 2 Fast feature.
  * @param NewState The new state of the Output Compare Fast Enable bit.
  * @retval None
  */
void TIM2_OC2FastCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  /* Set or Reset the OC2FE Bit */
  if (NewState != DISABLE)
  {
    TIM2->CCMR2 |= TIM_CCMR_OCxFE ;
  }
  else
  {
    TIM2->CCMR2 &= (uint8_t)(~TIM_CCMR_OCxFE) ;
  }
}

/**
  * @brief  Configures the TIM2 event to be generated by software.
  * @param  TIM2_EventSource: Specifies the event source.
  *          This parameter can be any combination of the following values:
  *            @arg TIM2_EventSource_Update: Update
  *            @arg TIM2_EventSource_CC1: Capture Compare Channel1
  *            @arg TIM2_EventSource_CC2: Capture Compare Channel2 
  *            @arg TIM2_EventSource_Trigger: Trigger 
  *            @arg TIM2_EventSource_Break: Break  
  * @retval None
  */
void TIM2_GenerateEvent(TIM2_EventSource_TypeDef TIM2_EventSource)
{
  /* Check the parameters */
  assert_param(IS_TIM2_EVENT_SOURCE((uint8_t)TIM2_EventSource));

  /* Set the event sources */
  TIM2->EGR |= (uint8_t)TIM2_EventSource;
}

/**
  * @brief  Configures the TIM2 Channel 1 polarity.
  * @param  TIM2_OCPolarity: Specifies the OC1 Polarity.
  *          This parameter can be one of the following values:
  *            @arg TIM2_OCPolarity_High: Output compare polarity  = High
  *            @arg TIM2_OCPolarity_Low: Output compare polarity  = Low 
  * @retval None
  */
void TIM2_OC1PolarityConfig(TIM2_OCPolarity_TypeDef TIM2_OCPolarity)
{
  /* Check the parameters */
  assert_param(IS_TIM2_OC_POLARITY(TIM2_OCPolarity));

  /* Set or Reset the CC1P Bit */
  if (TIM2_OCPolarity == TIM2_OCPolarity_Low)
  {
    TIM2->CCER1 |= TIM_CCER1_CC1P ;
  }
  else
  {
    TIM2->CCER1 &= (uint8_t)(~TIM_CCER1_CC1P) ;
  }
}

/**
  * @brief  Configures the TIM2 Channel 2 polarity.
  * @param  TIM2_OCPolarity: Specifies the OC2 Polarity.
  *          This parameter can be one of the following values:
  *            @arg TIM2_OCPolarity_High: Output compare polarity  = High
  *            @arg TIM2_OCPolarity_Low: Output compare polarity  = Low 
  * @retval None
  */
void TIM2_OC2PolarityConfig(TIM2_OCPolarity_TypeDef TIM2_OCPolarity)
{
  /* Check the parameters */
  assert_param(IS_TIM2_OC_POLARITY(TIM2_OCPolarity));

  /* Set or Reset the CC2P Bit */
  if (TIM2_OCPolarity == TIM2_OCPolarity_Low)
  {
    TIM2->CCER1 |= TIM_CCER1_CC2P ;
  }
  else
  {
    TIM2->CCER1 &= (uint8_t)(~TIM_CCER1_CC2P) ;
  }
}

/**
  * @brief  Enables or disables the TIM2 Capture Compare Channel x.
  * @param  TIM2_Channel: Specifies the TIM2 Channel.
  *          This parameter can be one of the following values:
  *            @arg TIM2_Channel_1: Channel 1
  *            @arg TIM2_Channel_2: Channel 2  
  * @param  NewState: Specifies the TIM2 Channel CCxE bit new state.
  *          This parameter can be ENABLE or DISABLE
  * @retval None
  */
void TIM2_CCxCmd(TIM2_Channel_TypeDef TIM2_Channel,
                 FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_TIM2_CHANNEL(TIM2_Channel));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (TIM2_Channel == TIM2_Channel_1)
  {
    /* Set or Reset the CC1E Bit */
    if (NewState != DISABLE)
    {
      TIM2->CCER1 |= TIM_CCER1_CC1E ;
    }
    else
    {
      TIM2->CCER1 &= (uint8_t)(~TIM_CCER1_CC1E) ;
    }

  }
  else /* if (TIM2_Channel == TIM2_Channel_2) */
  {
    /* Set or Reset the CC2E Bit */
    if (NewState != DISABLE)
    {
      TIM2->CCER1 |= TIM_CCER1_CC2E;
    }
    else
    {
      TIM2->CCER1 &= (uint8_t)(~TIM_CCER1_CC2E) ;
    }
  }

}

/**
  * @brief  Selects the TIM2 Output Compare Mode. This function disables the
  *         selected channel before changing the Output Compare Mode. User has to
  *         enable this channel using TIM2_CCxCmd and TIM2_CCxNCmd functions.
  * @param  TIM2_Channel: Specifies the TIM2 Channel.
  *          This parameter can be one of the following values:
  *            @arg TIM2_Channel_1: Channel 1
  *            @arg TIM2_Channel_2: Channel 2  
  * @param  TIM2_OCMode: Specifies the TIM2 Output Compare Mode.
  *          This parameter can be one of the following values:
  *            @arg TIM2_OCMode_Timing: Timing (Frozen) Mode
  *            @arg TIM2_OCMode_Active: Active Mode
  *            @arg TIM2_OCMode_Inactive: Inactive Mode
  *            @arg TIM2_OCMode_Toggle: Toggle Mode
  *            @arg TIM2_OCMode_PWM1: PWM Mode 1
  *            @arg TIM2_OCMode_PWM2: PWM Mode 2  
  * @retval None
  */
void TIM2_SelectOCxM(TIM2_Channel_TypeDef TIM2_Channel,
                     TIM2_OCMode_TypeDef TIM2_OCMode)
{
  /* Check the parameters */
  assert_param(IS_TIM2_CHANNEL(TIM2_Channel));
  assert_param(IS_TIM2_OCM(TIM2_OCMode));

  if (TIM2_Channel == TIM2_Channel_1)
  {
    /* Disable the Channel 1: Reset the CCE Bit */
    TIM2->CCER1 &= (uint8_t)(~TIM_CCER1_CC1E);

    /* Reset the Output Compare Bits */
    TIM2->CCMR1 &= (uint8_t)(~TIM_CCMR_OCM);

    /* Set the Ouput Compare Mode */
    TIM2->CCMR1 |= (uint8_t)TIM2_OCMode;
  }
  else /* if (TIM2_Channel == TIM2_Channel_2) */
  {
    /* Disable the Channel 2: Reset the CCE Bit */
    TIM2->CCER1 &= (uint8_t)(~TIM_CCER1_CC2E);

    /* Reset the Output Compare Bits */
    TIM2->CCMR2 &= (uint8_t)(~TIM_CCMR_OCM);

    /* Set the Ouput Compare Mode */
    TIM2->CCMR2 |= (uint8_t)TIM2_OCMode;
  }
}

/**
  * @brief  Sets the TIM2 Counter Register value.
  * @param  Counter: Specifies the Counter register new value.
  *          This parameter is between 0x0000 and 0xFFFF.
  * @retval None
  */
void TIM2_SetCounter(uint16_t TIM2_Counter)
{

  /* Set the Counter Register value */
  TIM2->CNTRH = (uint8_t)(TIM2_Counter >> 8);
  TIM2->CNTRL = (uint8_t)(TIM2_Counter);
}

/**
  * @brief  Sets the TIM2 Autoreload Register value.
  * @param  Autoreload: Specifies the Autoreload register new value.
  *          This parameter is between 0x0000 and 0xFFFF.
  * @retval None
  */
void TIM2_SetAutoreload(uint16_t TIM2_Autoreload)
{
  /* Set the Autoreload Register value */
  TIM2->ARRH = (uint8_t)(TIM2_Autoreload >> 8);
  TIM2->ARRL = (uint8_t)(TIM2_Autoreload);
}

/**
  * @brief  Sets the TIM2 Capture Compare1 Register value.
  * @param  Compare: Specifies the Capture Compare1 register new value.
  *         This parameter is between 0x0000 and 0xFFFF.
  * @retval None
  */
void TIM2_SetCompare1(uint16_t TIM2_Compare)
{
  /* Set the Capture Compare1 Register value */
  TIM2->CCR1H = (uint8_t)(TIM2_Compare >> 8);
  TIM2->CCR1L = (uint8_t)(TIM2_Compare);
}

/**
  * @brief  Sets the TIM2 Capture Compare2 Register value.
  * @param  Compare: Specifies the Capture Compare2 register new value.
  *         This parameter is between 0x0000 and 0xFFFF.
  * @retval None
  */
void TIM2_SetCompare2(uint16_t TIM2_Compare)
{
  /* Set the Capture Compare2 Register value */
  TIM2->CCR2H = (uint8_t)(TIM2_Compare >> 8);
  TIM2->CCR2L = (uint8_t)(TIM2_Compare);
}

/**
  * @brief  Sets the TIM2 Input Capture 1 prescaler.
  * @param  TIM2_IC1Prescaler: Specifies the Input Capture prescaler new value
  *          This parameter can be one of the following values:
  *            @arg TIM2_ICPSC_DIV1: Input Capture Prescaler = 1 (one capture every 1 event)
  *            @arg TIM2_ICPSC_DIV2: Input Capture Prescaler = 2 (one capture every 2 events)
  *            @arg TIM2_ICPSC_DIV4: Input Capture Prescaler = 4 (one capture every 4 events)
  *            @arg TIM2_ICPSC_DIV8: Input Capture Prescaler = 8 (one capture every 8 events) 
  * @retval None
  */
void TIM2_SetIC1Prescaler(TIM2_ICPSC_TypeDef TIM2_IC1Prescaler)
{
  uint8_t tmpccmr1 = 0;

  /* Check the parameters */
  assert_param(IS_TIM2_IC_PRESCALER(TIM2_IC1Prescaler));

  tmpccmr1 = TIM2->CCMR1;

  /* Reset the IC1PSC Bits */
  tmpccmr1 &= (uint8_t)(~TIM_CCMR_ICxPSC);

  /* Set the IC1PSC value */
  tmpccmr1 |= (uint8_t)TIM2_IC1Prescaler;

  TIM2->CCMR1 = tmpccmr1;
}

/**
  * @brief  Sets the TIM2 Input Capture 2 prescaler.
  * @param  TIM2_IC2Prescaler: Specifies the Input Capture prescaler new value
  *          This parameter can be one of the following values:
  *            @arg TIM2_ICPSC_DIV1: Input Capture Prescaler = 1 (one capture every 1 event)
  *            @arg TIM2_ICPSC_DIV2: Input Capture Prescaler = 2 (one capture every 2 events)
  *            @arg TIM2_ICPSC_DIV4: Input Capture Prescaler = 4 (one capture every 4 events)
  *            @arg TIM2_ICPSC_DIV8: Input Capture Prescaler = 8 (one capture every 8 events) 
  * @retval None
  */
void TIM2_SetIC2Prescaler(TIM2_ICPSC_TypeDef TIM2_IC2Prescaler)
{
  uint8_t tmpccmr2 = 0;

  /* Check the parameters */
  assert_param(IS_TIM2_IC_PRESCALER(TIM2_IC2Prescaler));

  tmpccmr2 = TIM2->CCMR2;

  /* Reset the IC2PSC Bits */
  tmpccmr2 &= (uint8_t)(~TIM_CCMR_ICxPSC);

  /* Set the IC2PSC value */
  tmpccmr2 |= (uint8_t)TIM2_IC2Prescaler;

  TIM2->CCMR2 = tmpccmr2;
}

/**
  * @brief  Gets the TIM2 Input Capture 1 value.
  * @param  None
  * @retval Capture Compare 1 Register value.
  */
uint16_t TIM2_GetCapture1(void)
{
  uint16_t tmpccr1 = 0;
  uint8_t tmpccr1l, tmpccr1h;

  tmpccr1h = TIM2->CCR1H;
  tmpccr1l = TIM2->CCR1L;

  tmpccr1 = (uint16_t)(tmpccr1l);
  tmpccr1 |= (uint16_t)((uint16_t)tmpccr1h << 8);
  /* Get the Capture 1 Register value */
  return ((uint16_t)tmpccr1);
}

/**
  * @brief  Gets the TIM2 Input Capture 2 value.
  * @param  None
  * @retval Capture Compare 2 Register value.
  */
uint16_t TIM2_GetCapture2(void)
{
  uint16_t tmpccr2 = 0;
  uint8_t tmpccr2l, tmpccr2h;

  tmpccr2h = TIM2->CCR2H;
  tmpccr2l = TIM2->CCR2L;

  tmpccr2 = (uint16_t)(tmpccr2l);
  tmpccr2 |= (uint16_t)((uint16_t)tmpccr2h << 8);
  /* Get the Capture 2 Register value */
  return ((uint16_t)tmpccr2);
}

/**
  * @brief  Gets the TIM2 Counter value.
  * @param  None
  * @retval Counter Register value.
  */
uint16_t TIM2_GetCounter(void)
{
  uint16_t tmpcnt = 0;
  uint8_t tmpcntrl, tmpcntrh;

  tmpcntrh = TIM2->CNTRH;
  tmpcntrl = TIM2->CNTRL;

  tmpcnt = (uint16_t)(tmpcntrl);
  tmpcnt |= (uint16_t)((uint16_t)tmpcntrh << 8);
  /* Get the Counter Register value */
  return ((uint16_t)tmpcnt);
}

/**
  * @brief  Gets the TIM2 Prescaler value.
  * @param  None
  * @retval Prescaler Register value.
  */
TIM2_Prescaler_TypeDef TIM2_GetPrescaler(void)
{
  /* Get the Prescaler Register value */
  return ((TIM2_Prescaler_TypeDef)TIM2->PSCR);
}

/**
  * @brief  Checks whether the specified TIM2 flag is set or not.
  * @param  TIM2_FLAG: Specifies the flag to check.
  *          This parameter can be any combination of the following values:
  *            @arg TIM2_FLAG_Update: Update
  *            @arg TIM2_FLAG_CC1: Capture Compare Channel1
  *            @arg TIM2_FLAG_CC2: Capture Compare Channel2 
  *            @arg TIM2_FLAG_Trigger: Trigger 
  *            @arg TIM2_FLAG_Break: Break  
  *            @arg TIM2_FLAG_CC1OF: Capture compare 1 over capture
  *            @arg TIM2_FLAG_CC2OF: Capture compare 2 over capture  
  * @retval FlagStatus The new state of TIM2_FLAG.
  */
FlagStatus TIM2_GetFlagStatus(TIM2_FLAG_TypeDef TIM2_FLAG)
{
  FlagStatus bitstatus = RESET;
  uint8_t tim2_flag_l, tim2_flag_h;

  /* Check the parameters */
  assert_param(IS_TIM2_GET_FLAG(TIM2_FLAG));

  tim2_flag_l = (uint8_t)(TIM2->SR1 & (uint8_t)(TIM2_FLAG));
  tim2_flag_h = (uint8_t)(TIM2->SR2 & (uint8_t)((uint16_t)TIM2_FLAG >> 8));

  if ((uint8_t)(tim2_flag_l | tim2_flag_h) != 0)
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
  * @param  TIM2_FLAG: Specifies the flag to clear.
  *          This parameter can be any combination of the following values:
  *            @arg TIM2_FLAG_Update: Update
  *            @arg TIM2_FLAG_CC1: Capture Compare Channel1
  *            @arg TIM2_FLAG_CC2: Capture Compare Channel2 
  *            @arg TIM2_FLAG_Trigger: Trigger 
  *            @arg TIM2_FLAG_Break: Break  
  * @retval None
  */
void TIM2_ClearFlag(TIM2_FLAG_TypeDef TIM2_FLAG)
{
  /* Check the parameters */
  assert_param(IS_TIM2_CLEAR_FLAG((uint16_t)TIM2_FLAG));
  /* Clear the flags (rc_w0) clear this bit by writing 0. Writing ‘1’ has no effect*/
  TIM2->SR1 = (uint8_t)(~(uint8_t)(TIM2_FLAG));
  TIM2->SR2 = (uint8_t)(~(uint8_t)((uint16_t)TIM2_FLAG >> 8));
}

/**
  * @brief  Checks whether the TIM2 interrupt has occurred or not.
  * @param  TIM2_IT: Specifies the TIM2 interrupt source to check.
  *          This parameter can be any combination of the following values:
  *            @arg TIM2_IT_Update: Update
  *            @arg TIM2_IT_CC1: Capture Compare Channel1
  *            @arg TIM2_IT_CC2: Capture Compare Channel2 
  *            @arg TIM2_IT_Trigger: Trigger 
  *            @arg TIM2_IT_Break: Break  
  * @retval ITStatus: The new state of the TIM2_IT (SET or RESET)
  */
ITStatus TIM2_GetITStatus(TIM2_IT_TypeDef TIM2_IT)
{
  __IO ITStatus bitstatus = RESET;

  __IO uint8_t TIM2_itStatus = 0x0, TIM2_itEnable = 0x0;

  /* Check the parameters */
  assert_param(IS_TIM2_GET_IT(TIM2_IT));

  TIM2_itStatus = (uint8_t)(TIM2->SR1 & (uint8_t)TIM2_IT);

  TIM2_itEnable = (uint8_t)(TIM2->IER & (uint8_t)TIM2_IT);

  if ((TIM2_itStatus != (uint8_t)RESET) && (TIM2_itEnable != (uint8_t)RESET))
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
  * @brief  Clears the TIM's interrupt pending bits.
  * @param  TIM2_IT: Specifies the pending bit to clear.
  *          This parameter can be any combination of the following values:
  *            @arg TIM2_IT_Update: Update
  *            @arg TIM2_IT_CC1: Capture Compare Channel1
  *            @arg TIM2_IT_CC2: Capture Compare Channel2 
  *            @arg TIM2_IT_Trigger: Trigger 
  *            @arg TIM2_IT_Break: Break  
  * @retval None
  */
void TIM2_ClearITPendingBit(TIM2_IT_TypeDef TIM2_IT)
{
  /* Check the parameters */
  assert_param(IS_TIM2_IT(TIM2_IT));

  /* Clear the IT pending Bit */
  TIM2->SR1 = (uint8_t)(~(uint8_t)TIM2_IT);
}

/**
  * @brief  Configure the TI1 as Input.
  * @param  TIM2_ICPolarity: Input Capture Polarity
  *          This parameter can be one of the following values:
  *            @arg TIM2_ICPolarity_Rising: Input Capture on Rising Edge
  *            @arg TIM2_ICPolarity_Falling: Input Capture on Falling Edge  
  * @param  TIM2_ICSelection: Specifies the input to be used.
  *          This parameter can be one of the following values:
  *            @arg TIM2_ICSelection_DirectTI: Input Capture mapped on the direct input
  *            @arg TIM2_ICSelection_IndirectTI: Input Capture mapped on the indirect input
  *            @arg TIM2_ICSelection_TRGI: Input Capture mapped on the Trigger Input   
  * @param  TIM2_ICFilter: Specifies the Input Capture Filter.
  *          This parameter must be a value between 0x00 and 0x0F.
  * @retval None
  */
static void TI1_Config(TIM2_ICPolarity_TypeDef TIM2_ICPolarity, \
                       TIM2_ICSelection_TypeDef TIM2_ICSelection, \
                       uint8_t TIM2_ICFilter)
{
  uint8_t tmpccmr1 = 0;
  uint8_t tmpicpolarity = (uint8_t)TIM2_ICPolarity;
  tmpccmr1 = TIM2->CCMR1;

  /* Check the parameters */
  assert_param(IS_TIM2_IC_POLARITY(TIM2_ICPolarity));
  assert_param(IS_TIM2_IC_SELECTION(TIM2_ICSelection));
  assert_param(IS_TIM2_IC_FILTER(TIM2_ICFilter));

  /* Disable the Channel 1: Reset the CCE Bit */
  TIM2->CCER1 &= (uint8_t)(~TIM_CCER1_CC1E);

  /* Select the Input and set the filter */
  tmpccmr1 &= (uint8_t)(~TIM_CCMR_CCxS) & (uint8_t)(~TIM_CCMR_ICxF);
  tmpccmr1 |= (uint8_t)(((uint8_t)(TIM2_ICSelection)) | ((uint8_t)(TIM2_ICFilter << 4)));

  TIM2->CCMR1 = tmpccmr1;

  /* Select the Polarity */
  if (tmpicpolarity == (uint8_t)(TIM2_ICPolarity_Falling))
  {
    TIM2->CCER1 |= TIM_CCER1_CC1P;
  }
  else
  {
    TIM2->CCER1 &= (uint8_t)(~TIM_CCER1_CC1P);
  }

  /* Set the CCE Bit */
  TIM2->CCER1 |=  TIM_CCER1_CC1E;
}

/**
  * @brief  Configure the TI2 as Input.
  * @param  TIM2_ICPolarity: Input Capture Polarity
  *          This parameter can be one of the following values:
  *            @arg TIM2_ICPolarity_Rising: Input Capture on Rising Edge
  *            @arg TIM2_ICPolarity_Falling: Input Capture on Falling Edge  
  * @param  TIM2_ICSelection: Specifies the input to be used.
  *          This parameter can be one of the following values:
  *            @arg TIM2_ICSelection_DirectTI: Input Capture mapped on the direct input
  *            @arg TIM2_ICSelection_IndirectTI: Input Capture mapped on the indirect input
  *            @arg TIM2_ICSelection_TRGI: Input Capture mapped on the Trigger Input   
  * @param  TIM2_ICFilter: Specifies the Input Capture Filter.
  *          This parameter must be a value between 0x00 and 0x0F.
  * @retval None
  */
static void TI2_Config(TIM2_ICPolarity_TypeDef TIM2_ICPolarity,
                       TIM2_ICSelection_TypeDef TIM2_ICSelection,
                       uint8_t TIM2_ICFilter)
{
  uint8_t tmpccmr2 = 0;
  uint8_t tmpicpolarity = (uint8_t)TIM2_ICPolarity;

  /* Check the parameters */
  assert_param(IS_TIM2_IC_POLARITY(TIM2_ICPolarity));
  assert_param(IS_TIM2_IC_SELECTION(TIM2_ICSelection));
  assert_param(IS_TIM2_IC_FILTER(TIM2_ICFilter));

  tmpccmr2 = TIM2->CCMR2;

  /* Disable the Channel 2: Reset the CCE Bit */
  TIM2->CCER1 &= (uint8_t)(~TIM_CCER1_CC2E);

  /* Select the Input and set the filter */
  tmpccmr2 &= (uint8_t)(~TIM_CCMR_CCxS) & (uint8_t)(~TIM_CCMR_ICxF);
  tmpccmr2 |= (uint8_t)(((uint8_t)(TIM2_ICSelection)) | ((uint8_t)(TIM2_ICFilter << 4)));

  TIM2->CCMR2 = tmpccmr2;

  /* Select the Polarity */
  if (tmpicpolarity == (uint8_t)TIM2_ICPolarity_Falling)
  {
    TIM2->CCER1 |= TIM_CCER1_CC2P ;
  }
  else
  {
    TIM2->CCER1 &= (uint8_t)(~TIM_CCER1_CC2P) ;
  }

  /* Set the CCE Bit */
  TIM2->CCER1 |=  TIM_CCER1_CC2E;
}

/**
  * @brief  Compute the frequency of the LSI clock expressed in Hertz.
  * @note   The timer clock must be a high speed clock: HSI or HSE
  * @note   It is recommended to use the maximum clock frequency, that is 10 MHz,
  *         to obtain a more precise result.
  * @param  TIM2_TimerClockFreq The TIM2 clock frequency expressed in Hertz.
  * @retval LSI Clock Frequency value.
  */
uint32_t TIM2_ComputeLsiClockFreq(uint32_t TIM2_TimerClockFreq)
{
  uint32_t LSIClockFreq;
  uint16_t ICValue1, ICValue2;

  /* Capture only every 8 events!!! */
  TIM2_ICInit(TIM2_Channel_1, TIM2_ICPolarity_Rising, TIM2_ICSelection_DirectTI, TIM2_ICPSC_Div8, 0x0);

  /* Enable CC1 interrupt */
  TIM2_ITConfig(TIM2_IT_CC1, ENABLE);

  /* Enable TIM2 */
  TIM2_Cmd(ENABLE);

  TIM2->SR1 = 0x00;
  TIM2->SR2 = 0x00;

  /* Clear CC1 Flag*/
  TIM2_ClearFlag(TIM2_FLAG_CC1);

  /* wait a capture on cc1 */
  while ((TIM2->SR1 & (uint8_t)TIM2_FLAG_CC1) != (uint8_t)TIM2_FLAG_CC1)
  {}
  /* Get CCR1 value*/
  ICValue1 = TIM2_GetCapture1();
  TIM2_ClearFlag(TIM2_FLAG_CC1);

  /* wait a capture on cc1 */
  while ((TIM2->SR1 & (uint8_t)TIM2_FLAG_CC1) != (uint8_t)TIM2_FLAG_CC1)
  {}
  /* Get CCR1 value*/
  ICValue2 = TIM2_GetCapture1();
  TIM2_ClearFlag(TIM2_FLAG_CC1);

  /* Disable IC1 input capture */
  TIM2->CCER1 &= (uint8_t)(~TIM_CCER1_CC1E);
  /* Reset CCMR1 register */
  TIM2->CCMR1 = 0x00;
  /* Disable TIM2 */
  TIM2_Cmd(DISABLE);

  /* Compute LSI clock frequency */
  LSIClockFreq = (8 * TIM2_TimerClockFreq) / (ICValue2 - ICValue1);
  return LSIClockFreq;
}

/**
  * @brief Checks whether the TIM2 device is enabled or not.
  * @param None
  * @retval FunctionalState The new state of the TIM2 device.
  */
FunctionalState TIM2_GetStatus(void)
{
  return ((FunctionalState)(TIM2->CR1 & TIM_CR1_CEN));
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
