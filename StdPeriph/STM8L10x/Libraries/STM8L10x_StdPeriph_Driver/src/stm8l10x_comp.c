/**
  ******************************************************************************
  * @file    stm8l10x_comp.c
  * @author  MCD Application Team
  * @version V1.2.1
  * @date    30-September-2014
  * @brief   This file contains all the functions for the COMP peripheral.
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
#include "stm8l10x_comp.h"

/** @addtogroup STM8L10x_StdPeriph_Driver
  * @{
  */
/** @defgroup COMP 
  * @brief COMP driver modules
  * @{
  */ 
  
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

/**
  * @addtogroup COMP_Private_Functions
  * @{
  */

/**
  * @brief Deinitializes the COMP peripheral registers to their default reset values.
  * @param None
  * @retval None
  */
void COMP_DeInit(void)
{
  COMP->CR   = COMP_CR_RESET_VALUE;
  COMP->CSR  = COMP_CSR_RESET_VALUE;
  COMP->CCS  = COMP_CCS_RESET_VALUE;
}


/**
  * @brief  Initializes the COMP according to the specified parameters
  * @note   The function @ref COMP_Cmd() should be called to set the BIASEN bit 
  *         in the COMP_CR register, first.
  * @param  COMP_Selection The state of the COMP peripheral
  *          This parameter can be any combination of the following values:
  *            @arg COMP_Selection_None:        No comparator selected
  *            @arg COMP_Selection_COMP1:       COMP1 enable
  *            @arg COMP_Selection_COMP2:       COMP2 enable
  *            @arg COMP_Selection_All:         COMP1 & COMP2 enable        
  * @param  COMP_Reference The reference of the comparison
  *          This parameter can be any combination of the following values:
  *            @arg COMP_Reference_Internal:    Comparator reference is internal
  *            @arg COMP_Reference_External:    Comparator reference is external
  * @param  COMP_Polarity  The desired comparator polarity
  *          This parameter can be any combination of the following values:
  *            @arg COMP_Polarity_High:    For a detected event, output comparator is 1
  *            @arg COMP_Polarity_Low:     For a detected event, output comparator is 0
  * @retval None
  */
void COMP_Init(COMP_Selection_TypeDef COMP_Selection,
               COMP_Reference_TypeDef COMP_Reference,
               COMP_Polarity_TypeDef COMP_Polarity)
{
  /* Check the parameters */
  assert_param(IS_COMP_POLARITY(COMP_Polarity));
  assert_param(IS_COMP_REFERENCE(COMP_Reference));
  assert_param(IS_COMP_SELECTION(COMP_Selection));

  COMP->CR &= (uint8_t)(~((uint8_t)COMP_Polarity | (uint8_t)COMP_Reference | (uint8_t)COMP_Selection));
  /* Set the Configuration */
  COMP->CR |= (uint8_t)((uint8_t)COMP_Polarity | (uint8_t)COMP_Reference | (uint8_t)COMP_Selection);

}

/**
  * @brief  Enables or disables the COMP.
  * @note   This function must be used 4µs before the function @ref COMP_SelectionConfig().
  * @param  NewState The New state of the COMP peripheral.
  * @retval None
  */
void COMP_Cmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* set  BIAS_EN  */
    COMP->CR |= COMP_CR_BIASEN;
  }
  else  /* NewState == DISABLE */
  {
    COMP->CR &= (uint8_t)(~COMP_CR_BIASEN);
  }
}

/**
  * @brief  Enables or disables the desired COMP peripheral.
  * @note   BIAS bit should be set 4µs before enabling the comparators.
  * @param  COMP_Selection The state of the COMP peripheral
  *          This parameter can be any combination of the following values:
  *            @arg COMP_Selection_None:        No comparator selected
  *            @arg COMP_Selection_COMP1:       COMP1 enable
  *            @arg COMP_Selection_COMP2:       COMP2 enable
  *            @arg COMP_Selection_All:         COMP1 & COMP2 enable   
  * @param  NewState  The new state of the COMP peripheral.
  * @retval None
  */
void COMP_SelectionConfig(COMP_Selection_TypeDef COMP_Selection,
                          FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  assert_param(IS_COMP_SELECTION(COMP_Selection));

  if (NewState != DISABLE)
  {
    COMP->CR |= (uint8_t)COMP_Selection;
  }
  else  /* NewState == DISABLE */
  {
    COMP->CR &= (uint8_t)(~(uint8_t)COMP_Selection);
  }
}

/**
  * @brief  Enables or disables the specified COMP interrupts.
  * @param  COMP_IT  Specifies the COMP interrupts source.
  *          This parameter can be any combination of the following values:
  *            @arg COMP_IT_ITEN1:        COMP1 interrupt enable
  *            @arg COMP_IT_ITEN2:        COMP2 interrupt enable
  *            @arg COMP_IT_CEF1:         COMP1 pending bit
  *            @arg COMP_IT_CEF2:         COMP2 pending bit     
  * @param  NewState The new state of the COMP peripheral.
  * @retval None
  */
void COMP_ITConfig(COMP_IT_TypeDef COMP_IT,
                   FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_COMP_IT(COMP_IT));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the Interrupt sources */
    COMP->CSR |= (uint8_t)COMP_IT;
  }
  else
  {
    /* Disable the Interrupt sources */
    COMP->CSR &= (uint8_t)(~(uint8_t)COMP_IT);
  }
}

/**
  * @brief  Selection between Timer1 input capture1 or Timer1 break for first comparator output.
  * @param  COMP_TIM2Config  TIM configartionfor first comparator output.
  *          This parameter can be any combination of the following values:
  *            @arg COMP_TIM2Config_IC1:      Input capture 1 selection
  *            @arg COMP_TIM2Config_BK:       Break selection  
  * @retval None
  */
void COMP_TIM2Config(COMP_TIM2Config_TypeDef COMP_TIM2Config)
{
  /* Check the parameters */
  assert_param(IS_COMP_TIM2CONFIG(COMP_TIM2Config));

  /* Clear the IC1_BK bit*/
  COMP->CR &= (uint8_t)(~(uint8_t)COMP_CR_IC1BK);

  /* Configure the  IC1_BK bit */
  COMP->CR |= (uint8_t)COMP_TIM2Config;
}

/**
  * @brief  Enables or disables the specified Switch.
  * @param  COMP_Switch Specifies the COMP SWITCH to be enabled or disabled.
  *          This parameter can be any combination of the following values:
  *            @arg COMP_Switch_COMP1Ch1:     Comparator 1 Switch 1 Enable
  *            @arg COMP_Switch_COMP1Ch2:     Comparator 1 Switch 1 Enable
  *            @arg COMP_Switch_COMP1Ch3:     Comparator 1 Switch 1 Enable
  *            @arg COMP_Switch_COMP1Ch4:     Comparator 1 Switch 1 Enable
  *            @arg COMP_Switch_COMP2Ch1:     Comparator 2 Switch 1 Enable
  *            @arg COMP_Switch_COMP2Ch2:     Comparator 2 Switch 2 Enable
  *            @arg COMP_Switch_COMP2Ch3:     Comparator 2 Switch 3 Enable
  *            @arg COMP_Switch_COMP2Ch4:     Comparator 2 Switch 4 Enable              
  * @param  NewState    The new state of the COMP peripheral.
  * @retval None
  */
void COMP_SwitchConfig(COMP_Switch_TypeDef COMP_Switch,
                       FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_COMP_SWITCH(COMP_Switch));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the switch */
    COMP->CCS |= (uint8_t)COMP_Switch;
  }
  else
  {
    /* Disable the Switch */
    COMP->CCS &= (uint8_t)(~(uint8_t)COMP_Switch);
  }
}

/**
  * @brief  Selects the COMP peripheral Output Connection with Timers peripheral inputs.
  * @param  COMP_TIMConnection  TIM connection configuration.
  *          This parameter can be any combination of the following values:
  *            @arg COMP_TimersConnection_None:     No connection
  *            @arg COMP_TimersConnection_COMP1ToTIM2IC1BK:                 COMP1 out to IC1/BK TIM2
  *            @arg COMP_TimersConnection_COMP1ToTIM2IC1BK_COMP2ToTIM2IC2:  COMP1 out to IC1/BK TIM2 & COMP2 out to IC2 TIM2
  *            @arg COMP_TimersConnection_COMP1ToTIM2IC1BK_COMP2ToTIM3IC2:  COMP1 out to IC1/BK TIM2 & COMP2 out to IC1 TIM3        
  * @retval None
  */
void COMP_TIMConnect(COMP_TimersConnection_TypeDef COMP_TIMConnection)
{
  /* Check the parameters */
  assert_param(IS_COMP_TIMCONNECTION(COMP_TIMConnection));

  /* Clear the TIM connection configuration bits */
  COMP->CR &= (uint8_t)(~(uint8_t)COMP_CR_CNFTIM);

  /* Configure the TIM connection */
  COMP->CR |= (uint8_t)COMP_TIMConnection;
}

/**
  * @brief  Selects the polarity of both comparators.
  * @param  COMP_Polarity The desired comparator polarity
  *          This parameter can be any combination of the following values:
  *            @arg COMP_Polarity_High:    For a detected event, output comparator is 1
  *            @arg COMP_Polarity_Low:     For a detected event, output comparator is 0  
  * @retval None
  */
void COMP_SelectPolarity(COMP_Polarity_TypeDef COMP_Polarity)
{
  /* Check the parameters */
  assert_param(IS_COMP_POLARITY(COMP_Polarity));

  /* Clear Polarity bit */
  COMP->CR &= (uint8_t)(~(uint8_t)COMP_CR_POL);

  /* Write the polarity */
  COMP->CR |= (uint8_t)COMP_Polarity;
}

/**
  * @brief  Selects the internal or external reference of both comparators.
  * @param  COMP_Reference The reference of the comparison
  *          This parameter can be any combination of the following values:
  *            @arg COMP_Reference_Internal:    Comparator reference is internal
  *            @arg COMP_Reference_External:    Comparator reference is external
  * @retval None
  */
void COMP_SetReference(COMP_Reference_TypeDef COMP_Reference)
{
  /* Check the parameters */
  assert_param(IS_COMP_REFERENCE(COMP_Reference));

  /* Clear Polarity bit */
  COMP->CR &= (uint8_t)(~(uint8_t)COMP_CR_COMPREF);

  /* Write the polarity */
  COMP->CR |= (uint8_t)COMP_Reference;
}

/**
  * @brief  Checks whether the specified COMP output is set or not.
  * @param  COMP_Output Specifies the output to check.
  *          This parameter can be any combination of the following values:
  *            @arg COMP_Output_COMP1:    COMP1 output
  *            @arg COMP_Output_COMP2:    COMP2 output  
  * @retval The new state of Output.
  */
FlagStatus COMP_GetOutputStatus(COMP_Output_TypeDef COMP_Output)
{
  FlagStatus status = RESET;

  /* Check the parameters */
  assert_param(IS_COMP_OUTPUT(COMP_Output));

  if ((COMP->CSR & (uint8_t)COMP_Output) != 0)
  {
    status = SET;
  }
  else
  {
    status = RESET;
  }
  return status;
}

/**
  * @brief  Checks whether the specified COMP flag is set or not.
  * @param  COMP_Flag Specifies the flag to check.
  *          This parameter can be any combination of the following values:
  *            @arg COMP_FLAG_COMP1:    COMP1 event flag
  *            @arg COMP_FLAG_COMP2:    COMP2 event flag  
  * @retval The new state of Flag.
  */
FlagStatus COMP_GetFlagStatus(COMP_FLAG_TypeDef COMP_Flag)
{
  FlagStatus status = RESET;

  /* Check the parameters */
  assert_param(IS_COMP_FLAG(COMP_Flag));

  if ((COMP->CSR & (uint8_t)COMP_Flag) != 0)
  {
    status = SET;
  }
  else
  {
    status = RESET;
  }
  return status;
}

/**
  * @brief  Clears the specified COMP flag.
  * @param  COMP_Flag Specifies the flag to clear.
  *          This parameter can be any combination of the following values:
  *            @arg COMP_FLAG_COMP1:    COMP1 event flag
  *            @arg COMP_FLAG_COMP2:    COMP2 event flag    
  * @retval None
  */
void COMP_ClearFlag(COMP_FLAG_TypeDef COMP_Flag)
{
  /* Check the parameters */
  assert_param(IS_COMP_FLAG(COMP_Flag));

  /* Clear the flags (rc_w0) clear this bit by writing 1. Writing ‘0’ has no effect*/
  COMP->CSR |= (uint8_t)COMP_Flag;
}

/**
  * @brief Checks whether the COMP interrupt has occurred or not.
  * @param COMP_ITPendingBit Specifies the COMP interrupt source to check.
  *          This parameter can be any combination of the following values:
  *            @arg COMP_IT_CEF1:    COMP1 pending bit
  *            @arg COMP_IT_CEF2:    COMP2 pending bit   
  * @retval ITStatus The new state of the COMP_IT.
  */
ITStatus COMP_GetITStatus(COMP_IT_TypeDef COMP_ITPendingBit)
{
  ITStatus status = RESET;

  /* Check the parameters */
  assert_param(IS_COMP_ITPENDINGBIT(COMP_ITPendingBit));

  if (COMP->CSR & (uint8_t)COMP_ITPendingBit)
  {
    status = SET;
  }
  else
  {
    status = RESET;
  }
  return status;
}

/**
  * @brief  Clears the COMP pending bits.
  * @param  ITPendingBit Specifies the pending bit to clear.
  *          This parameter can be any combination of the following values:
  *            @arg COMP_IT_CEF1:    COMP1 pending bit
  *            @arg COMP_IT_CEF2:    COMP2 pending bit   
  * @retval None
  */
void COMP_ClearITPendingBit(COMP_IT_TypeDef COMP_ITPendingBit)
{
  /* Check the parameters */
  assert_param(IS_COMP_ITPENDINGBIT(COMP_ITPendingBit));

  /* Clear the flags (rc_w0) clear this bit by writing 1. Writing ‘0’ has no effect*/
  COMP->CSR |= (uint8_t)COMP_ITPendingBit;
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
