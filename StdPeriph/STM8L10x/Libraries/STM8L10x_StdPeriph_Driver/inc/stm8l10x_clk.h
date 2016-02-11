/**
  ******************************************************************************
  * @file    stm8l10x_clk.h
  * @author  MCD Application Team
  * @version V1.2.1
  * @date    30-September-2014
  * @brief   This file contains all functions prototypes and macros for the CLK 
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
#ifndef __STM8L10X_CLK_H
#define __STM8L10X_CLK_H

/* Includes ------------------------------------------------------------------*/
#include "stm8l10x.h"

/* Exported variables ------------------------------------------------------- */
/* Exported types ------------------------------------------------------------*/

/** @addtogroup CLK_Exported_Types
  * @{
  */

/**
  * @brief CLK Clock Output
  */
typedef enum {
  CLK_Output_ClockMaster          = (uint8_t)0x00, /*!< Clock Output CKM */
  CLK_Output_ClockMasterDiv2      = (uint8_t)0x02, /*!< Clock Output CKM/2 */
  CLK_Output_ClockMasterDiv4      = (uint8_t)0x04, /*!< Clock Output CKM/4 */
  CLK_Output_ClockMasterDiv16     = (uint8_t)0x06  /*!< Clock Output CKM/16 */
} CLK_Output_TypeDef;

/**
  * @brief CLK Enable peripheral PCKEN
  */
typedef enum {
  CLK_Peripheral_TIM2  = (uint8_t)0x01,  /*!< Peripheral Clock Enable 1, TIM2 */
  CLK_Peripheral_TIM3  = (uint8_t)0x02,  /*!< Peripheral Clock Enable 1, TIM3 */
  CLK_Peripheral_TIM4  = (uint8_t)0x04,  /*!< Peripheral Clock Enable 1, TIM4 */
  CLK_Peripheral_I2C     = (uint8_t)0x08,  /*!< Peripheral Clock Enable 1, I2C */
  CLK_Peripheral_SPI     = (uint8_t)0x10,  /*!< Peripheral Clock Enable 1, SPI */
  CLK_Peripheral_USART   = (uint8_t)0x20,  /*!< Peripheral Clock Enable 1, USART */
  CLK_Peripheral_AWU     = (uint8_t)0x40  /*!< Peripheral Clock Enable 1, AWU */
} CLK_Peripheral_TypeDef;

/**
  * @brief CLK Clock Divisor
  */
typedef enum {
  CLK_MasterPrescaler_HSIDiv1   = (uint8_t)0x00,  /*!< High speed internal clock prescaler: 1 */
  CLK_MasterPrescaler_HSIDiv2   = (uint8_t)0x01,  /*!< High speed internal clock prescaler: 2 */
  CLK_MasterPrescaler_HSIDiv4   = (uint8_t)0x02,  /*!< High speed internal clock prescaler: 4 */
  CLK_MasterPrescaler_HSIDiv8   = (uint8_t)0x03  /*!< High speed internal clock prescaler: 8 */
} CLK_MasterPrescaler_TypeDef;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/

/** @addtogroup CLK_Exported_Constants
  * @{
  */

#define HSI_VALUE   ((uint32_t)16000000)  /*!< Typical Value of the HSI in Hz */
#define LSI_VALUE   ((uint32_t)32000)     /*!< Typical Value of the LSI in Hz */

/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/

/** @addtogroup CLK_Private_Macros
  * @{
  */

/**
  * @brief Macro used by the assert function to check the different functions parameters.
  */

/**
  * @brief  Macro used by the assert function to check the different Output clock.
  */
#define IS_CLK_OUTPUT(OUTPUT) \
  (((OUTPUT) == CLK_Output_ClockMaster)  ||\
   ((OUTPUT) == CLK_Output_ClockMasterDiv2) ||\
   ((OUTPUT) == CLK_Output_ClockMasterDiv4) ||\
   ((OUTPUT) == CLK_Output_ClockMasterDiv16))

/**
  * @brief  Macro used by the assert function to check the different periheral to clock.
  */
#define IS_CLK_PERIPHERAL(PERIPHERAL) ((((PERIPHERAL) & (uint8_t)0x80) == (uint8_t)0x00) && ((PERIPHERAL) != (uint8_t)0x00))

/**
  * @brief  Macro used by the assert function to check the different clock prescaler.
  */
#define IS_CLK_MASTER_PRESCALER(PRESCALER) \
  (((PRESCALER) == CLK_MasterPrescaler_HSIDiv1 ) ||\
   ((PRESCALER) == CLK_MasterPrescaler_HSIDiv2 ) ||\
   ((PRESCALER) == CLK_MasterPrescaler_HSIDiv4 ) ||\
   ((PRESCALER) == CLK_MasterPrescaler_HSIDiv8))

/**
  * @}
  */

/* Exported functions ------------------------------------------------------- */
/** @addtogroup CLK_Exported_Functions
  * @{
  */

void CLK_DeInit(void);
void CLK_CCOCmd(FunctionalState NewState);
void CLK_PeripheralClockConfig(CLK_Peripheral_TypeDef CLK_Peripheral,
                               FunctionalState NewState);
void CLK_MasterPrescalerConfig(CLK_MasterPrescaler_TypeDef CLK_MasterPrescaler);
void CLK_CCOConfig(CLK_Output_TypeDef CLK_Output);
uint32_t CLK_GetClockFreq(void);

/**
  * @}
  */

#endif /* __STM8L10X_CLK_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
