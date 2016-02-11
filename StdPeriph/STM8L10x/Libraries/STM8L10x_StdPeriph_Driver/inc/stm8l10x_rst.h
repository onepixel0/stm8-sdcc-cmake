/**
  ******************************************************************************
  * @file    stm8l10x_rst.h
  * @author  MCD Application Team
  * @version V1.2.1
  * @date    30-September-2014
  * @brief   This file contains all functions prototypes and macros for the RST 
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
#ifndef __STM8L10X_RST_H
#define __STM8L10X_RST_H

/* Includes ------------------------------------------------------------------*/
#include "stm8l10x.h"

/* Exported variables ------------------------------------------------------- */
/* Exported types ------------------------------------------------------------*/

/** @addtogroup RST_Exported_Types
  * @{
  */

/**
  * @brief RST Flag possible values
  */
typedef enum {
  RST_FLAG_POR_PDR     = (uint8_t)0x01, /*!< POR/PDR reset flag */
  RST_FLAG_SWIMF       = (uint8_t)0x08, /*!< SWIM reset flag */
  RST_FLAG_ILLOPF      = (uint8_t)0x04, /*!< Illigal opcode reset flag */
  RST_FLAG_IWDGF       = (uint8_t)0x02  /*!< Independent watchdog reset flag */
} RST_Flag_TypeDef;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/

/** @addtogroup RST_Private_Macros
  * @{
  */

/**
  * @brief Macro used by the assert function to check the different RST flags.
  */
#define IS_RST_FLAG(FLAG) \
  (((FLAG) == RST_FLAG_POR_PDR) || \
   ((FLAG) == RST_FLAG_IWDGF)   || \
   ((FLAG) == RST_FLAG_ILLOPF)  || \
   ((FLAG) == RST_FLAG_SWIMF))

/**
  * @}
  */


/* Exported functions ------------------------------------------------------- */
/** @addtogroup RST_Exported_Functions
  * @{
  */

FlagStatus RST_GetFlagStatus(RST_Flag_TypeDef RST_Flag);
void RST_ClearFlag(RST_Flag_TypeDef RST_Flag);
void RST_GPOutputEnable(void);

/**
  * @}
  */

#endif /* __STM8L10X_RST_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
