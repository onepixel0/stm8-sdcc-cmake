/**
  ******************************************************************************
  * @file    stm8l10x_itc.h
  * @author  MCD Application Team
  * @version V1.2.1
  * @date    30-September-2014
  * @brief   This file contains all functions prototypes and macros for the ITC 
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
#ifndef __STM8L10X_ITC_H
#define __STM8L10X_ITC_H

/* Includes ------------------------------------------------------------------*/
#include "stm8l10x.h"

/* Exported variables ------------------------------------------------------- */
/* Exported types ------------------------------------------------------------*/

/** @addtogroup ITC_Exported_Types
  * @{
  */

/**
  * @brief ITC Interrupt Lines selection
  */
typedef enum {
  FLASH_IRQn                    = (uint8_t)1,   /*!< Flash interrupt */
  AWU_IRQn                      = (uint8_t)4,   /*!< Auto Wake-Up interrupt   */
  EXTIB_IRQn                    = (uint8_t)6,   /*!< GPIOB interrupt */
  EXTID_IRQn                    = (uint8_t)7,   /*!< GPIOD interrupt */
  EXTI0_IRQn                    = (uint8_t)8,   /*!< PIN0 interrupt  */
  EXTI1_IRQn                    = (uint8_t)9,   /*!< PIN1 interrupt  */
  EXTI2_IRQn                    = (uint8_t)10,  /*!< PIN2 interrupt  */
  EXTI3_IRQn                    = (uint8_t)11,  /*!< PIN3 interrupt  */
  EXTI4_IRQn                    = (uint8_t)12,  /*!< PIN4 interrupt  */
  EXTI5_IRQn                    = (uint8_t)13,  /*!< PIN5 interrupt  */
  EXTI6_IRQn                    = (uint8_t)14,  /*!< PIN6 interrupt  */
  EXTI7_IRQn                    = (uint8_t)15,  /*!< PIN7 interrupt  */
  COMP_IRQn                     = (uint8_t)18,  /*!< Comparator interrupt */
  TIM2_UPD_OVF_TRG_BRK_IRQn     = (uint8_t)19,  /*!< TIM2 UPD/OVF/TRG/BRK interrupt */
  TIM2_CAP_IRQn                 = (uint8_t)20,  /*!< TIM2 CAP interrupt  */
  TIM3_UPD_OVF_TRG_BRK_IRQn     = (uint8_t)21,  /*!< TIM3 overflow interrupt */
  TIM3_CAP_IRQn                 = (uint8_t)22,  /*!< TIM3 input captute/output compare interrupt  */
  TIM4_UPD_OVF_IRQn             = (uint8_t)25,  /*!< TIM4 overflow interrupt */
  SPI_IRQn                      = (uint8_t)26,  /*!< SPI interrupt */
  USART_TX_IRQn                 = (uint8_t)27,  /*!< USART TX interrupt */
  USART_RX_IRQn                 = (uint8_t)28,  /*!< USART RX interrupt */
  I2C_IRQn                      = (uint8_t)29   /*!< I2C RX interrupt */
}IRQn_TypeDef;

/**
  * @brief ITC Priority Levels selection
  */
typedef enum {
  ITC_PriorityLevel_0 = (uint8_t)0x02, /*!< Software priority level 0 (cannot be written) */
  ITC_PriorityLevel_1 = (uint8_t)0x01, /*!< Software priority level 1 */
  ITC_PriorityLevel_2 = (uint8_t)0x00, /*!< Software priority level 2 */
  ITC_PriorityLevel_3 = (uint8_t)0x03  /*!< Software priority level 3 */
} ITC_PriorityLevel_TypeDef;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/

/** @addtogroup ITC_Exported_Constants
  * @{
  */

#define CPU_SOFT_INT_DISABLED ((uint8_t)0x28) /*!< Mask for I1 and I0 bits in CPU_CC register */

/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/

/** @addtogroup ITC_Private_Macros
  * @{
  */

/**
  * @brief Macro used by the assert function in order to check the different IRQ values
  */
#define IS_ITC_IRQ(IRQ) (((IRQ) == FLASH_IRQn) || \
                         ((IRQ) == AWU_IRQn) || \
                         ((IRQ) == EXTIB_IRQn) || \
                         ((IRQ) == EXTID_IRQn) || \
                         ((IRQ) == EXTI0_IRQn) || \
                         ((IRQ) == EXTI1_IRQn) || \
                         ((IRQ) == EXTI2_IRQn) || \
                         ((IRQ) == EXTI3_IRQn) || \
                         ((IRQ) == EXTI4_IRQn) || \
                         ((IRQ) == EXTI5_IRQn) || \
                         ((IRQ) == EXTI6_IRQn) || \
                         ((IRQ) == EXTI7_IRQn) || \
                         ((IRQ) == COMP_IRQn) || \
                         ((IRQ) == TIM2_UPD_OVF_TRG_BRK_IRQn) || \
                         ((IRQ) == TIM2_CAP_IRQn) || \
                         ((IRQ) == TIM3_UPD_OVF_TRG_BRK_IRQn) || \
                         ((IRQ) == TIM3_CAP_IRQn) || \
                         ((IRQ) == TIM4_UPD_OVF_IRQn) || \
                         ((IRQ) == SPI_IRQn) || \
                         ((IRQ) == USART_TX_IRQn) || \
                         ((IRQ) == USART_RX_IRQn) || \
                         ((IRQ) == I2C_IRQn))

/**
  * @brief Macro used by the assert function in order to check the different priority values
  */
#define IS_ITC_PRIORITY(PriorityLevel) \
  (((PriorityLevel) == ITC_PriorityLevel_0) || \
   ((PriorityLevel) == ITC_PriorityLevel_1) || \
   ((PriorityLevel) == ITC_PriorityLevel_2) || \
   ((PriorityLevel) == ITC_PriorityLevel_3))

/**
  * @brief Macro used by the assert function in order to check if the interrupts are disabled
  */
#define IS_ITC_INTERRUPTS_DISABLED (ITC_GetSoftIntStatus() == CPU_SOFT_INT_DISABLED)

/**
  * @}
  */

/* Exported functions ------------------------------------------------------- */

/** @addtogroup ITC_Exported_Functions
  * @{
  */

uint8_t ITC_GetCPUCC(void);
void ITC_DeInit(void);
uint8_t ITC_GetSoftIntStatus(void);
ITC_PriorityLevel_TypeDef ITC_GetSoftwarePriority(IRQn_TypeDef IRQn);
void ITC_SetSoftwarePriority(IRQn_TypeDef IRQn, ITC_PriorityLevel_TypeDef ITC_PriorityLevel);

/**
  * @}
  */

#endif /* __STM8L10X_ITC_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
