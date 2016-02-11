/**
  ******************************************************************************
  * @file    stm8l10x_exti.c
  * @author  MCD Application Team
  * @version V1.2.1
  * @date    30-September-2014
  * @brief   This file contains all the functions for the EXTI peripheral.
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
#include "stm8l10x_exti.h"

/** @addtogroup STM8L10x_StdPeriph_Driver
  * @{
  */
/** @defgroup EXTI 
  * @brief EXTI driver modules
  * @{
  */ 
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @addtogroup EXTI_Private_Functions
  * @{
  */

/**
  * @brief Deinitializes the external interrupt control registers to their default reset value.
  * @param None
  * @retval None
  */
void EXTI_DeInit(void)
{
  EXTI->CR1 = EXTI_CR1_RESET_VALUE;
  EXTI->CR2 = EXTI_CR2_RESET_VALUE;
  EXTI->CR3 = EXTI_CR3_RESET_VALUE;
  EXTI->SR1 = EXTI_SR1_RESET_VALUE;
  EXTI->SR2 = EXTI_SR2_RESET_VALUE;
  EXTI->CONF = EXTI_CONF_RESET_VALUE;
}

/**
  * @brief  Set the external interrupt sensitivity of the selected port.
  * @note   The modification of external interrupt sensitivity is only possible 
  *         when the interrupts are disabled.
  * @note   The normal behavior is to disable the interrupts before calling this 
  *         function, and re-enable them after.
  * @note   Global interrupts must be disabled before calling this function.
  * @param  EXTI_Port         The port number to access.
  *          This parameter can be any combination of the following values:
  *            @arg EXTI_Port_B:   GPIO Port B
  *            @arg EXTI_Port_D:   GPIO Port D 
  * @param  EXTI_TriggerValue The external interrupt sensitivity value to set.
  *          This parameter can be any combination of the following values:
  *            @arg EXTI_Trigger_Falling_Low:     Interrupt on Falling edge and Low level
  *            @arg EXTI_Trigger_Rising:          Interrupt on Rising edge
  *            @arg EXTI_Trigger_Falling:         Interrupt on Falling edge
  *            @arg EXTI_Trigger_Rising_Falling:  Interrupt on Rising and Falling edges      
  * @retval None
  */
void EXTI_SetPortSensitivity(EXTI_Port_TypeDef EXTI_Port,
                             EXTI_Trigger_TypeDef EXTI_TriggerValue)
{

  /* Check function parameters */
  assert_param(IS_EXTI_PORT(EXTI_Port));
  assert_param(IS_EXTI_Trigger_VALUE(EXTI_TriggerValue));

  /* Clear EXTI  port sensitivity */
  if (EXTI_Port != EXTI_Port_B)
  {
    EXTI->CR3 &= (uint8_t)(~EXTI_CR3_PDIS);
  }
  else /* PortNum == EXTI_Port_B */
  {
    EXTI->CR3 &= (uint8_t)(~EXTI_CR3_PBIS);
  }

  /* Write EXTI  port sensitivity */
  EXTI->CR3 |= (uint8_t)((uint8_t)(EXTI_TriggerValue) << (uint8_t)EXTI_Port);

}

/**
  * @brief  Set the external interrupt sensitivity of the selected pin.
  * @note   The modification of external interrupt sensitivity is only possible 
  *         when the interrupts are disabled.
  * @note   The normal behavior is to disable the interrupts before calling this 
  *         function, and re-enable them after.
  * @note   Global interrupts must be disabled before calling this function.
  * @param  EXTI_PinNum       The pin to configure.
  *          This parameter can be any combination of the following values:
  *            @arg EXTI_Pin_0:     GPIO Pin 0
  *            @arg EXTI_Pin_1:     GPIO Pin 1
  *            @arg EXTI_Pin_2:     GPIO Pin 2
  *            @arg EXTI_Pin_3:     GPIO Pin 3
  *            @arg EXTI_Pin_4:     GPIO Pin 4
  *            @arg EXTI_Pin_5:     GPIO Pin 5
  *            @arg EXTI_Pin_6:     GPIO Pin 6
  *            @arg EXTI_Pin_7:     GPIO Pin 7              
  * @param  EXTI_TriggerValue The external interrupt sensitivity value to set.
  *          This parameter can be any combination of the following values:
  *            @arg EXTI_Trigger_Falling_Low:     Interrupt on Falling edge and Low level
  *            @arg EXTI_Trigger_Rising:          Interrupt on Rising edge
  *            @arg EXTI_Trigger_Falling:         Interrupt on Falling edge
  *            @arg EXTI_Trigger_Rising_Falling:  Interrupt on Rising and Falling edges 
  * @retval None
  */
void EXTI_SetPinSensitivity(EXTI_Pin_TypeDef EXTI_PinNum,
                            EXTI_Trigger_TypeDef EXTI_TriggerValue)
{

  /* Check function parameters */
  assert_param(IS_EXTI_PINNUM(EXTI_PinNum));
  assert_param(IS_EXTI_Trigger_VALUE(EXTI_TriggerValue));

  /* Clear port sensitivity bits */
  switch (EXTI_PinNum)
  {
    case EXTI_Pin_0:
      EXTI->CR1 &= (uint8_t)(~EXTI_CR1_P0IS);
      EXTI->CR1 |= (uint8_t)((uint8_t)(EXTI_TriggerValue) << (uint8_t)EXTI_PinNum);
      break;
    case EXTI_Pin_1:
      EXTI->CR1 &= (uint8_t)(~EXTI_CR1_P1IS);
      EXTI->CR1 |= (uint8_t)((uint8_t)(EXTI_TriggerValue) << (uint8_t)EXTI_PinNum);
      break;
    case EXTI_Pin_2:
      EXTI->CR1 &= (uint8_t)(~EXTI_CR1_P2IS);
      EXTI->CR1 |= (uint8_t)((uint8_t)(EXTI_TriggerValue) << (uint8_t)EXTI_PinNum);
      break;
    case EXTI_Pin_3:
      EXTI->CR1 &= (uint8_t)(~EXTI_CR1_P3IS);
      EXTI->CR1 |= (uint8_t)((uint8_t)(EXTI_TriggerValue) << (uint8_t)EXTI_PinNum);
      break;
    case EXTI_Pin_4:
      EXTI->CR2 &= (uint8_t)(~EXTI_CR2_P4IS);
      EXTI->CR2 |= (uint8_t)((uint8_t)(EXTI_TriggerValue) << ((uint8_t)EXTI_PinNum & (uint8_t)0xEF));
      break;
    case EXTI_Pin_5:
      EXTI->CR2 &= (uint8_t)(~EXTI_CR2_P5IS);
      EXTI->CR2 |= (uint8_t)((uint8_t)(EXTI_TriggerValue) << ((uint8_t)EXTI_PinNum & (uint8_t)0xEF));
      break;
    case EXTI_Pin_6:
      EXTI->CR2 &= (uint8_t)(~EXTI_CR2_P6IS);
      EXTI->CR2 |= (uint8_t)((uint8_t)(EXTI_TriggerValue) << ((uint8_t)EXTI_PinNum & (uint8_t)0xEF));
      break;
    case EXTI_Pin_7:
      EXTI->CR2 &= (uint8_t)(~EXTI_CR2_P7IS);
      EXTI->CR2 |= (uint8_t)((uint8_t)(EXTI_TriggerValue) << ((uint8_t)EXTI_PinNum & (uint8_t)0xEF));
      break;
    default:
      break;
  }
}

/**
  * @brief  Configure the half port interrupt selection.
  * @note   This function must be called once the port sensitivity is configured,
  *          otherwise this function call won't have any effect on the port external interrupt.
  * @param  EXTI_HalfPort The port part  to access (MSB or LSB).
  *          This parameter can be any combination of the following values:
  *            @arg EXTI_HalfPort_B_LSB:     Interrupt selector PB(3:0)
  *            @arg EXTI_HalfPort_B_MSB:     Interrupt selector PB(7:4)
  *            @arg EXTI_HalfPort_D_LSB:     Interrupt selector PE(3:0)
  *            @arg EXTI_HalfPort_D_MSB:     Interrupt selector PE(7:4)
  * @param  NewState  The external interrupt new state.
  * @retval None
  */
void EXTI_SetHalfPortSelection(EXTI_HalfPort_TypeDef EXTI_HalfPort,
                               FunctionalState NewState)
{
  /* Check function parameters */
  assert_param(IS_EXTI_HALFPORT(EXTI_HalfPort));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    EXTI->CONF |= (uint8_t)EXTI_HalfPort; /* Enable port interrupt selector */
  }
  else /*NewState == DISABLE */
  {
    EXTI->CONF &= (uint8_t)(~(uint8_t)EXTI_HalfPort); /* Disable port interrupt selector */
  }
}

/**
  * @brief  Get the external interrupt sensitivity of the selected port.
  * @param  EXTI_Port         The port number to access.
  *          This parameter can be any combination of the following values:
  *            @arg EXTI_Port_B:   GPIO Port B
  *            @arg EXTI_Port_D:   GPIO Port D 
  * @retval EXTI_Trigger_TypeDef The external interrupt sensitivity of the selected port.
  */
EXTI_Trigger_TypeDef EXTI_GetPortSensitivity(EXTI_Port_TypeDef EXTI_Port)
{
  uint8_t value = 0;

  /* Check function parameters */
  assert_param(IS_EXTI_PORT(EXTI_Port));

  if (EXTI_Port != EXTI_Port_B)
  {
    value = (uint8_t)((EXTI->CR3 & EXTI_CR3_PDIS) >> 2);
  }
  else /* PortNum == EXTI_Port_B */
  {
    value = (uint8_t)(EXTI->CR3 & EXTI_CR3_PBIS);
  }
  return((EXTI_Trigger_TypeDef)value);
}

/**
  * @brief  Get the external interrupt sensitivity of the selected pin.
  * @param  EXTI_PinNum       The pin to configure.
  *          This parameter can be any combination of the following values:
  *            @arg EXTI_Pin_0:     GPIO Pin 0
  *            @arg EXTI_Pin_1:     GPIO Pin 1
  *            @arg EXTI_Pin_2:     GPIO Pin 2
  *            @arg EXTI_Pin_3:     GPIO Pin 3
  *            @arg EXTI_Pin_4:     GPIO Pin 4
  *            @arg EXTI_Pin_5:     GPIO Pin 5
  *            @arg EXTI_Pin_6:     GPIO Pin 6
  *            @arg EXTI_Pin_7:     GPIO Pin 7 
  * @retval EXTI_Trigger_TypeDef The external interrupt sensitivity of the selected port.
  */
EXTI_Trigger_TypeDef EXTI_GetPinSensitivity(EXTI_Pin_TypeDef EXTI_PinNum)
{
  uint8_t value = 0;

  /* Check function parameters */
  assert_param(IS_EXTI_PINNUM(EXTI_PinNum));

  switch (EXTI_PinNum)
  {
    case EXTI_Pin_0:
      value = (uint8_t)(EXTI->CR1 & EXTI_CR1_P0IS);
      break;
    case EXTI_Pin_1:
      value = (uint8_t)((EXTI->CR1 & EXTI_CR1_P1IS) >> (uint8_t)EXTI_Pin_1);
      break;
    case EXTI_Pin_2:
      value = (uint8_t)((EXTI->CR1 & EXTI_CR1_P2IS) >> (uint8_t)EXTI_Pin_2);
      break;
    case EXTI_Pin_3:
      value = (uint8_t)((EXTI->CR1 & EXTI_CR1_P3IS) >> (uint8_t)EXTI_Pin_3);
      break;
    case EXTI_Pin_4:
      value = (uint8_t)(EXTI->CR2 & EXTI_CR2_P4IS);
      break;
    case EXTI_Pin_5:
      value = (uint8_t)((EXTI->CR2 & EXTI_CR2_P5IS) >> ((uint8_t)EXTI_Pin_5 & (uint8_t)0x0F));
      break;
    case EXTI_Pin_6:
      value = (uint8_t)((EXTI->CR2 & EXTI_CR2_P6IS) >> ((uint8_t)EXTI_Pin_6 & (uint8_t)0x0F));
      break;
    case EXTI_Pin_7:
      value = (uint8_t)((EXTI->CR2 & EXTI_CR2_P7IS) >> ((uint8_t)EXTI_Pin_7 & (uint8_t)0x0F));
      break;
    default:
      break;
  }
  return((EXTI_Trigger_TypeDef)value);
}

/**
  * @brief  Get the external interrupt half port configuration.
  * @param  EXTI_HalfPort The port part  to access (MSB or LSB).
  *          This parameter can be any combination of the following values:
  *            @arg EXTI_HalfPort_B_LSB:     Interrupt selector PB(3:0)
  *            @arg EXTI_HalfPort_B_MSB:     Interrupt selector PB(7:4)
  *            @arg EXTI_HalfPort_D_LSB:     Interrupt selector PE(3:0)
  *            @arg EXTI_HalfPort_D_MSB:     Interrupt selector PE(7:4)
  * @retval The external interrupt state of the selected port.
  */
FunctionalState EXTI_GetHalfPortSelection(EXTI_HalfPort_TypeDef EXTI_HalfPort)
{
  FunctionalState value = DISABLE;
  /* Check function parameters */
  assert_param(IS_EXTI_HALFPORT(EXTI_HalfPort));
  if ((EXTI->CONF & (uint8_t)EXTI_HalfPort) != (uint8_t)DISABLE)
  {
    value = ENABLE;
  }
  else
  {
    value = DISABLE;
  }

  return(value);
}

/**
  * @brief  Get the external interrupt status.
  * @param  EXTI_IT Specifies the interrupt to read.
  *          This parameter can be any combination of the following values:
  *            @arg EXTI_IT_0:     GPIO Pin pos 0
  *            @arg EXTI_IT_1:     GPIO Pin pos 1
  *            @arg EXTI_IT_2:     GPIO Pin pos 2
  *            @arg EXTI_IT_3:     GPIO Pin pos 3
  *            @arg EXTI_IT_4:     GPIO Pin pos 4
  *            @arg EXTI_IT_5:     GPIO Pin pos 5
  *            @arg EXTI_IT_6:     GPIO Pin pos 6
  *            @arg EXTI_IT_7:     GPIO Pin pos 7 
  *            @arg EXTI_IT_PortB: GPIO Port B
  *            @arg EXTI_IT_PortD: GPIO Port D 
  * @retval The status of the specified interrupt.
  */
ITStatus EXTI_GetITStatus(EXTI_IT_TypeDef EXTI_IT)
{
  ITStatus status = RESET;
  /* Check function parameters */
  assert_param(IS_EXTI_ITPENDINGBIT(EXTI_IT));

  if (((uint8_t)EXTI_IT & (uint8_t)0xF0) == 0xF0)
  {
    status = (ITStatus)(EXTI->SR2 & ((uint8_t)EXTI_IT & (uint8_t)0x0F));
  }
  else
  {
    status = (ITStatus)(EXTI->SR1 & (uint8_t)EXTI_IT);
  }
  return((ITStatus)status);
}

/**
  * @brief  Clear the specified interrupt pending bit
  * @param  EXTI_IT Specifies the interrupt to clear
  *          This parameter can be any combination of the following values:
  *            @arg EXTI_IT_0:     GPIO Pin pos 0
  *            @arg EXTI_IT_1:     GPIO Pin pos 1
  *            @arg EXTI_IT_2:     GPIO Pin pos 2
  *            @arg EXTI_IT_3:     GPIO Pin pos 3
  *            @arg EXTI_IT_4:     GPIO Pin pos 4
  *            @arg EXTI_IT_5:     GPIO Pin pos 5
  *            @arg EXTI_IT_6:     GPIO Pin pos 6
  *            @arg EXTI_IT_7:     GPIO Pin pos 7 
  *            @arg EXTI_IT_PortB: GPIO Port B
  *            @arg EXTI_IT_PortD: GPIO Port D   
  * @retval None
  */
void EXTI_ClearITPendingBit(EXTI_IT_TypeDef EXTI_IT)
{
  /* Check function parameters */
  assert_param(IS_EXTI_ITPENDINGBIT(EXTI_IT));

  if (((uint8_t)EXTI_IT & (uint8_t)0xF0) == 0xF0)
  {
    EXTI->SR2 = (uint8_t)((uint8_t)EXTI_IT & (uint8_t)0x0F);
  }
  else
  {
    EXTI->SR1 = (uint8_t)EXTI_IT;
  }
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
