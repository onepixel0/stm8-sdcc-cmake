/**
  ******************************************************************************
  * @file    stm8l10x_irtim.c
  * @author  MCD Application Team
  * @version V1.2.1
  * @date    30-September-2014
  * @brief   This file contains all the functions for the IRTIM peripheral.
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
#include "stm8l10x_irtim.h"

/** @addtogroup STM8L10x_StdPeriph_Driver
  * @{
  */
/** @defgroup IRTIM 
  * @brief IRTIM driver modules
  * @{
  */ 
  
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

/**
  * @addtogroup IRTIM_Private_Functions
  * @{
  */

/**
  * @brief  Deinitializes the IRTIM peripheral registers to their default reset values.
  * @param  None
  * @retval None
  */
void IRTIM_DeInit(void)
{
  IRTIM->CR = IRTIM_CR_RESET_VALUE;
}


/**
  * @brief  Enables or disables the IRTIM peripheral.
  * @param  NewState The new state of the IRTIM peripheral.
  * @retval None
  */
void IRTIM_Cmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  /* set or Reset the EN Bit */
  if (NewState ==  DISABLE)
  {
    IRTIM->CR &= (uint8_t)(~IRTIM_CR_EN);
  }
  else
  {
    IRTIM->CR |= IRTIM_CR_EN;
  }
}

/**
  * @brief  Enables or disables the High sink open drain buffer IRTIM peripheral.
  * @param  NewState The new state of the High sink open drain buffer IRTIM peripheral.
  * @retval None
  */
void IRTIM_HighSinkODCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  /* set or Reset the EN Bit */
  if (NewState == DISABLE)
  {
    IRTIM->CR &= (uint8_t)(~IRTIM_CR_HSEN);
  }
  else
  {
    IRTIM->CR |= IRTIM_CR_HSEN;
  }
}

/**
  * @brief  Checks whether the IRTIM device is enabled or not.
  * @param  None
  * @retval The new state of the IRTIM device.
  */
FunctionalState IRTIM_GetStatus(void)
{
  return ((FunctionalState)(IRTIM->CR & IRTIM_CR_EN));
}

/**
  * @brief  Checks whether the IRTIM High Sink Open Drain buffer is Enabled or not.
  * @param  None
  * @retval The state of High Sink Open Drain buffer.
  */
FunctionalState IRTIM_GetHighSinkODStatus(void)
{
  return ((FunctionalState)(IRTIM->CR & IRTIM_CR_HSEN));
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
