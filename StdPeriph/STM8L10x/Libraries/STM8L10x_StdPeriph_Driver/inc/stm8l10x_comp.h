/**
  ******************************************************************************
  * @file    stm8l10x_comp.h
  * @author  MCD Application Team
  * @version V1.2.1
  * @date    30-September-2014
  * @brief   This file contains all functions prototype and macros for the COMP 
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
#ifndef __STM8L10x_COMP_H
#define __STM8L10x_COMP_H


/* Includes ------------------------------------------------------------------*/
#include "stm8l10x.h"

/* Exported variables ------------------------------------------------------- */
/* Exported types ------------------------------------------------------------*/

/** @addtogroup COMP_Exported_Types
  * @{
  */

/**
  * @brief COMP TIM2 configuration
  */
typedef enum
{
  COMP_TIM2Config_IC1 = ((uint8_t)0x00), /*!< Input capture 1 selection. */
  COMP_TIM2Config_BK = ((uint8_t)0x80)  /*!<  Break selection */
}COMP_TIM2Config_TypeDef;

/**
  * @brief COMPs Selection
  */
typedef enum
{
  COMP_Selection_None    = ((uint8_t)0x00), /*!< None comparator enable. */
  COMP_Selection_COMP1   = ((uint8_t)0x02), /*!< First comparator enable.*/
  COMP_Selection_COMP2   = ((uint8_t)0x04), /*!< Second comparator enable. */
  COMP_Selection_All     = ((uint8_t)0x06)  /*!< Both comparator enable. */
}COMP_Selection_TypeDef;

/**
  * @brief COMP Polarity
  */
typedef enum
{
  COMP_Polarity_High  = ((uint8_t)0x00), /*!< For a detected event, output comparator is 1 */
  COMP_Polarity_Low     = ((uint8_t)0x10)  /*!< For a detected event, output comparator is 0 */
}COMP_Polarity_TypeDef;

/**
  * @brief COMP reference
  */
typedef enum
{
  COMP_Reference_Internal = ((uint8_t)0x00), /*!< Comparator reference is internal */
  COMP_Reference_External = ((uint8_t)0x08)  /*!< Comparator reference is external */
}COMP_Reference_TypeDef;

/**
  * @brief COMP interrupt sources
  */
typedef enum
{
  COMP_IT_ITEN1    = ((uint8_t)0x20), /*!< First comparator interrupt enable */
  COMP_IT_ITEN2    = ((uint8_t)0x80), /*!< Second comparator interrupt enable */
  COMP_IT_CEF1     = ((uint8_t)0x10), /*!< First comparator pending bit */
  COMP_IT_CEF2     = ((uint8_t)0x40)  /*!< Second comparator pending bit */
}COMP_IT_TypeDef;

/**
  * @brief COMP Flags
  */
typedef enum
{
  COMP_FLAG_COMP1 = ((uint8_t)0x10),  /*!< First comparator event flag. */
  COMP_FLAG_COMP2 = ((uint8_t)0x40)   /*!< Second comparator event flag. */
}COMP_FLAG_TypeDef;

/**
  * @brief COMP Output
  */
typedef enum
{
  COMP_Output_COMP1 = ((uint8_t)0x01),  /*!< First comparator output. */
  COMP_Output_COMP2 = ((uint8_t)0x02)   /*!< Second comparator output. */
}COMP_Output_TypeDef;


/**
  * @brief COMP w/ TIMx Connection Mode
  */
typedef enum
{
  COMP_TimersConnection_None                             = ((uint8_t)0x00), /*!< No connection */
  COMP_TimersConnection_COMP1ToTIM2IC1BK                 = ((uint8_t)0x20), /*!< Comparator 1 sent to Input capture 1/ Break TIM2 */
  COMP_TimersConnection_COMP1ToTIM2IC1BK_COMP2ToTIM2IC2  = ((uint8_t)0x40), /*!< Comparator 1 sent to Input capture 1/ Break TIM2 and comparator 2 sent to Input capture 2 TIM2 */
  COMP_TimersConnection_COMP1ToTIM2IC1BK_COMP2ToTIM3IC2  = ((uint8_t)0x60)  /*!< Comparator 1 sent to Input capture 1/ Break TIM2 and comparator 2 sent to Input capture 1 TIM3 */
}COMP_TimersConnection_TypeDef;


/**
  * @brief COMP Switch
  */
typedef enum
{
  COMP_Switch_COMP1Ch1   = ((uint8_t)0x01), /*!< Comparator 1 Switch 1 Enable. */
  COMP_Switch_COMP1Ch2   = ((uint8_t)0x02), /*!< Comparator 1 Switch 2 Enable. */
  COMP_Switch_COMP1Ch3   = ((uint8_t)0x04), /*!< Comparator 1 Switch 3 Enable. */
  COMP_Switch_COMP1Ch4   = ((uint8_t)0x08), /*!< Comparator 1 Switch 4 Enable. */
  COMP_Switch_COMP2Ch1   = ((uint8_t)0x10), /*!< Comparator 2 Switch 1 Enable. */
  COMP_Switch_COMP2Ch2   = ((uint8_t)0x20), /*!< Comparator 2 Switch 2 Enable. */
  COMP_Switch_COMP2Ch3   = ((uint8_t)0x40), /*!< Comparator 2 Switch 3 Enable. */
  COMP_Switch_COMP2Ch4   = ((uint8_t)0x80)  /*!< Comparator 2 Switch 4 Enable. */
}COMP_Switch_TypeDef;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/

/** @addtogroup COMP_Private_Macros
  * @{
  */

/**
  * @brief Macro used by the assert function to check the different functions parameters.
  */

/**
  * @brief Macro used by the assert function to check the different TIM2 configuration .
  */
#define IS_COMP_TIM2CONFIG(TIM2CONFIG) \
  (((TIM2CONFIG) == COMP_TIM2Config_IC1) || \
   ((TIM2CONFIG) == COMP_TIM2Config_BK))

/**
  * @brief Macro used by the assert function to check the different Comparator selection.
  */
#define IS_COMP_SELECTION(SELECTION) \
  (((SELECTION) == COMP_Selection_None) || \
   ((SELECTION) == COMP_Selection_COMP1)  || \
   ((SELECTION) == COMP_Selection_COMP2)  || \
   ((SELECTION) == COMP_Selection_All))

/**
  * @brief Macro used by the assert function to check the different comparator polarity.
  */
#define IS_COMP_POLARITY(POLARITY) \
  (((POLARITY) == COMP_Polarity_High) || \
   ((POLARITY) == COMP_Polarity_Low))

/**
  * @brief Macro used by the assert function to check the different comparator reference.
  */
#define IS_COMP_REFERENCE(REFERENCE) \
  (((REFERENCE) == COMP_Reference_Internal) || \
   ((REFERENCE) == COMP_Reference_External))

/**
  * @brief Macro used by the assert function to check the different comparator interrupts.
  */
#define IS_COMP_IT(IT) \
  (((IT) == COMP_IT_ITEN1) || \
   ((IT) == COMP_IT_ITEN2))

/**
  * @brief Macro used by the assert function to check the different comparator flags.
  */
#define IS_COMP_FLAG(FLAG) \
  (((FLAG) == COMP_FLAG_COMP1) || \
   ((FLAG) == COMP_FLAG_COMP2) || \
   ((FLAG) == ((uint8_t)COMP_FLAG_COMP2|(uint8_t)COMP_FLAG_COMP2)))

/**
  * @brief Macro used by the assert function to check the different comparator output.
  */
#define IS_COMP_OUTPUT(OUTPUT) \
  (((OUTPUT) == COMP_Output_COMP1) || \
   ((OUTPUT) == COMP_Output_COMP2))

/**
  * @brief Macro used by the assert function to check the different comparator pending bits.
  */
#define IS_COMP_ITPENDINGBIT(PENDINGBIT) \
  (((PENDINGBIT) == COMP_IT_CEF1) || \
   ((PENDINGBIT) == COMP_IT_CEF2))

/**
  * @brief Macro used by the assert function to check the different comparator connection to timer1/2.
  */
#define IS_COMP_TIMCONNECTION(CONNECTION) \
  (((CONNECTION) == COMP_TimersConnection_None)                        || \
   ((CONNECTION) == COMP_TimersConnection_COMP1ToTIM2IC1BK)             || \
   ((CONNECTION) == COMP_TimersConnection_COMP1ToTIM2IC1BK_COMP2ToTIM2IC2) || \
   ((CONNECTION) == COMP_TimersConnection_COMP1ToTIM2IC1BK_COMP2ToTIM3IC2))

/**
  * @brief Macro used by the assert function to check the different comparator switches.
  */
#define IS_COMP_SWITCH(SWITCH) \
  (((SWITCH) == COMP_Switch_COMP1Ch1) || \
   ((SWITCH) == COMP_Switch_COMP1Ch2) || \
   ((SWITCH) == COMP_Switch_COMP1Ch3) || \
   ((SWITCH) == COMP_Switch_COMP1Ch4) || \
   ((SWITCH) == COMP_Switch_COMP2Ch1) || \
   ((SWITCH) == COMP_Switch_COMP2Ch2) || \
   ((SWITCH) == COMP_Switch_COMP2Ch3) || \
   ((SWITCH) == COMP_Switch_COMP2Ch4))
/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @addtogroup COMP_Exported_Functions
  * @{
  */

void COMP_DeInit(void);
void COMP_Init(COMP_Selection_TypeDef COMP_Selection, COMP_Reference_TypeDef COMP_Reference, \
               COMP_Polarity_TypeDef COMP_Polarity);
void COMP_Cmd(FunctionalState NewState);
void COMP_SelectionConfig(COMP_Selection_TypeDef COMP_Selection, FunctionalState NewState);
void COMP_ITConfig(COMP_IT_TypeDef COMP_IT, FunctionalState NewState);
void COMP_TIM2Config(COMP_TIM2Config_TypeDef COMP_TIM2Config);
void COMP_SwitchConfig(COMP_Switch_TypeDef COMP_Switch, FunctionalState NewState);
void COMP_TIMConnect(COMP_TimersConnection_TypeDef COMP_TIMConnection);
void COMP_SelectPolarity(COMP_Polarity_TypeDef COMP_Polarity);
void COMP_SetReference(COMP_Reference_TypeDef COMP_Reference);
FlagStatus COMP_GetOutputStatus(COMP_Output_TypeDef COMP_Output);
FlagStatus COMP_GetFlagStatus(COMP_FLAG_TypeDef COMP_Flag);
void COMP_ClearFlag(COMP_FLAG_TypeDef COMP_Flag);
ITStatus COMP_GetITStatus(COMP_IT_TypeDef COMP_ITPendingBit);
void COMP_ClearITPendingBit(COMP_IT_TypeDef COMP_ITPendingBit);
/**
  * @}
  */

#endif /* __STM8L10x_COMP_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
