/**
  ******************************************************************************
  * @file    stm8l10x_flash.h
  * @author  MCD Application Team
  * @version V1.2.1
  * @date    30-September-2014
  * @brief   This file contains all functions prototypes and macros for the FLASH
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
#ifndef __STM8L10X_FLASH_H
#define __STM8L10X_FLASH_H

/* Includes ------------------------------------------------------------------*/
#include "stm8l10x.h"

/* Exported variables ------------------------------------------------------- */
/* Exported constants --------------------------------------------------------*/

/** @addtogroup FLASH_Exported_Constants
  * @{
  */

/**
  * @brief Macro used by the assert function to check the different functions parameters.
  */

#define FLASH_START_PHYSICAL_ADDRESS  ((uint16_t)0x8000) /*!< Flash: start address */ 
#define FLASH_END_PHYSICAL_ADDRESS    ((uint16_t)0x9FFF)   /*!< Flash: end address */
#define FLASH_BLOCK_NUMBER            ((uint8_t)0x80)       /*!< Flash memory: total number of Block */
#define FLASH_BLOCK_SIZE              ((uint8_t)0x40)        /*!< Number of bytes in a Block 
                                                                              (common for Program and Data EEprom memories) */
#define FLASH_RASS_KEY1               ((uint8_t)0x56)    /*!< First RASS key */
#define FLASH_RASS_KEY2               ((uint8_t)0xAE)    /*!< Second RASS key */
#define FLASH_READOUTPROTECTION_KEY   ((uint8_t)0xAA)     /*!< Read out protection key */

/**
  * @}
  */

/* Exported types ------------------------------------------------------------*/

/** @addtogroup FLASH_Exported_Types
  * @{
  */

/**
  * @brief FLASH Memory types
  */
typedef enum
{
  FLASH_MemType_Program      = (uint8_t)0xFD, /*!< Program memory */
  FLASH_MemType_Data         = (uint8_t)0xF7  /*!< Data EEPROM memory */
} FLASH_MemType_TypeDef;

/**
  * @brief FLASH programming modes
  */
typedef enum
{
  FLASH_ProgramMode_Standard = (uint8_t)0x00, /*!< Standard programming mode */
  FLASH_ProgramMode_Fast     = (uint8_t)0x10  /*!< Fast programming mode */
} FLASH_ProgramMode_TypeDef;

/**
  * @brief FLASH fixed programming time
  */
typedef enum
{
  FLASH_ProgramTime_Standard = (uint8_t)0x00, /*!< Standard programming time fixed at 1/2 tprog */
  FLASH_ProgramTime_TProg    = (uint8_t)0x01  /*!< Programming time fixed at tprog */
} FLASH_ProgramTime_TypeDef;

/**
  * @brief FLASH status of the last operation
  */
typedef enum
{
  FLASH_Status_Write_Protection_Error = (uint8_t)0x01, /*!< Write attempted to protected Block */
  FLASH_Status_TimeOut = (uint8_t)0x02, /*!< Time out error */
  FLASH_Status_Successful_Operation   = (uint8_t)0x04  /*!< End of operation flag */
} FLASH_Status_TypeDef;

/**
  * @brief FLASH flags definition
 * - Warning : FLAG value = mapping position register
  */
typedef enum {
  FLASH_FLAG_DUL       = (uint8_t)0x08,     /*!< Data EEPROM unlocked flag */
  FLASH_FLAG_EOP       = (uint8_t)0x04,     /*!< End of programming (write or erase operation) flag */
  FLASH_FLAG_PUL       = (uint8_t)0x02,     /*!< Flash Program memory unlocked flag */
  FLASH_FLAG_WR_PG_DIS = (uint8_t)0x01      /*!< Write attempted to protected page flag */
} FLASH_FLAG_TypeDef;

/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/

/** @addtogroup FLASH_Private_Macros
  * @{
  */

/**
  * @brief Macro used by the assert function in order to check the different sensitivity values for the flash Address
  */

#define IS_FLASH_ADDRESS(ADDRESS) (((ADDRESS) >= FLASH_START_PHYSICAL_ADDRESS) && \
                                   ((ADDRESS) <= FLASH_END_PHYSICAL_ADDRESS))

/**
  * @brief Macro used by the assert function in order to check the different sensitivity values for the flash Block number
  */
#define IS_FLASH_BLOCK_NUMBER(BLOCKNUM) ((BLOCKNUM) < FLASH_BLOCK_NUMBER)

/**
  * @brief Macro used by the assert function in order to check the different sensitivity values for the flash memory type
  */
#define IS_MEMORY_TYPE(MEMTYPE) (((MEMTYPE) == FLASH_MemType_Program) || \
                                 ((MEMTYPE) == FLASH_MemType_Data))

/**
  * @brief Macro used by the assert function in order to check the different sensitivity values for the flash program block mode
  */
#define IS_FLASH_PROGRAM_MODE(MODE) (((MODE) == FLASH_ProgramMode_Standard) || \
                                     ((MODE) == FLASH_ProgramMode_Fast))

/**
  * @brief Macro used by the assert function in order to check the program time mode
  */
#define IS_FLASH_PROGRAM_TIME(TIME) (((TIME) == FLASH_ProgramTime_Standard) || \
                                     ((TIME) == FLASH_ProgramTime_TProg))

/**
  * @brief Macro used by the assert function in order to check the different flags values
  */
#define IS_FLASH_FLAGS(FLAG) (((FLAG) == FLASH_FLAG_EOP) || \
                              ((FLAG) == FLASH_FLAG_PUL) || \
                              ((FLAG) == FLASH_FLAG_DUL) || \
                              ((FLAG) == FLASH_FLAG_WR_PG_DIS))

/**
  * @}
  */

/* Exported functions ------------------------------------------------------- */
/* FLASH program and Data EEPROM memories interface configuration functions ***/
FLASH_ProgramTime_TypeDef FLASH_GetProgrammingTime(void);
void FLASH_SetProgrammingTime(FLASH_ProgramTime_TypeDef FLASH_ProgramTime);

/* FLASH program and Data EEPROM memories Programming functions ***************/
void FLASH_DeInit(void);
void FLASH_Unlock(FLASH_MemType_TypeDef FLASH_MemType);
void FLASH_Lock(FLASH_MemType_TypeDef FLASH_MemType);
void FLASH_ProgramByte(uint16_t Address, uint8_t Data);
void FLASH_EraseByte(uint16_t Address);
void FLASH_ProgramWord(uint16_t Address, uint32_t Data);
uint8_t FLASH_ReadByte(uint16_t Address);

/* Option Bytes Programming functions *****************************************/
uint16_t FLASH_GetBootSize(void);
uint16_t FLASH_GetDataSize(void);
FunctionalState FLASH_GetReadOutProtectionStatus(void);

/* Interrupts and flags management functions **********************************/
void FLASH_ITConfig(FunctionalState NewState);
FlagStatus FLASH_GetFlagStatus(FLASH_FLAG_TypeDef FLASH_FLAG);

/* Functions to be executed from RAM ******************************************/
/**
@code
 All the functions declared below must be executed from RAM exclusively, except 
 for the FLASH_WaitForLastOperation function which can be executed from Flash.
 
 Steps of the execution from RAM differs from one toolchain to another.
 for more details refer to stm8l10x_flash.c file.
 
 To enable execution from RAM you can either uncomment the following define 
 in the stm8l10x.h file or define it in your toolchain compiler preprocessor
 - #define RAM_EXECUTION  (1) 

@endcode
*/
IN_RAM(void FLASH_ProgramBlock(uint8_t BlockNum, FLASH_ProgramMode_TypeDef FLASH_ProgramMode, uint8_t *Buffer));
IN_RAM(void FLASH_EraseBlock(uint8_t BlockNum));
IN_RAM(FLASH_Status_TypeDef FLASH_WaitForLastOperation(void));



#endif /*__STM8L10X_FLASH_H*/

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
