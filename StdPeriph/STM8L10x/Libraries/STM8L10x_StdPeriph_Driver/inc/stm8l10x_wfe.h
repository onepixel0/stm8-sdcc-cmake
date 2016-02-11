/**
  ******************************************************************************
  * @file    stm8l10x_wfe.h
  * @author  MCD Application Team
  * @version V1.2.1
  * @date    30-September-2014
  * @brief   This file contains all functions prototypes and macros for the WFE 
  *          peripheral.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM8L10X_WFE_H
#define __STM8L10X_WFE_H

/* Includes ------------------------------------------------------------------*/
#include "stm8l10x.h"

/* Exported variables ------------------------------------------------------- */
/* Exported types ------------------------------------------------------------*/

/** @addtogroup WFE_Exported_Types
  * @{
  */

/**
  * @brief Signal Sources to generate wake_up events
  */
typedef enum {
  WFE_Source_TIM2_EV0   = (uint16_t)0x0101, /*!< Tim2 Upadte/Trigger and Break interrupt */
  WFE_Source_TIM2_EV1   = (uint16_t)0x0102, /*!< Tim2 Capture/Compare interrupt          */
  WFE_Source_EXTI_EV0   = (uint16_t)0x0110, /*!< I/O port interrupt from Pins 0          */
  WFE_Source_EXTI_EV1   = (uint16_t)0x0120, /*!< I/O port interrupt from Pins 1          */
  WFE_Source_EXTI_EV2   = (uint16_t)0x0140, /*!< I/O port interrupt from Pins 2          */
  WFE_Source_EXTI_EV3   = (uint16_t)0x0180, /*!< I/O port interrupt from Pins 3          */
  WFE_Source_EXTI_EV4   = (uint16_t)0x0201, /*!< I/O port interrupt from Pins 4          */
  WFE_Source_EXTI_EV5   = (uint16_t)0x0202, /*!< I/O port interrupt from Pins 5          */
  WFE_Source_EXTI_EV6   = (uint16_t)0x0204, /*!< I/O port interrupt from Pins 6          */
  WFE_Source_EXTI_EV7   = (uint16_t)0x0208, /*!< I/O port interrupt from Pins 7          */
  WFE_Source_EXTI_EVB   = (uint16_t)0x0210, /*!< I/O port interrupt from port B          */
  WFE_Source_EXTI_EVD   = (uint16_t)0x0220 /*!< I/O port interrupt from Pins D          */
} WFE_Source_TypeDef;



/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/

/** @addtogroup WFE_Private_Macros
  * @{
  */

/**
  * @brief Macro used by the assert function in order to check the different IRQ values
  */

#define IS_WFE_SOURCE_OK(Source) (((Source) == WFE_Source_TIM2_EV0) || \
                                  ((Source) == WFE_Source_TIM2_EV1) || \
                                  ((Source) == WFE_Source_EXTI_EV0) || \
                                  ((Source) == WFE_Source_EXTI_EV1) || \
                                  ((Source) == WFE_Source_EXTI_EV2) || \
                                  ((Source) == WFE_Source_EXTI_EV3) || \
                                  ((Source) == WFE_Source_EXTI_EV4) || \
                                  ((Source) == WFE_Source_EXTI_EV5) || \
                                  ((Source) == WFE_Source_EXTI_EV6) || \
                                  ((Source) == WFE_Source_EXTI_EV7) || \
                                  ((Source) == WFE_Source_EXTI_EVB) || \
                                  ((Source) == WFE_Source_EXTI_EVD))

/**
  * @}
  */

/* Exported functions ------------------------------------------------------- */

/** @addtogroup WFE_Exported_Functions
  * @{
  */

void WFE_DeInit(void);
void WFE_WakeUpSourceEventCmd(WFE_Source_TypeDef WFE_Source, FunctionalState NewState);
FunctionalState WFE_GetWakeUpSourceEventStatus(WFE_Source_TypeDef WFE_Source);

/**
  * @}
  */

#endif /* __STM8L10X_WFE_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
