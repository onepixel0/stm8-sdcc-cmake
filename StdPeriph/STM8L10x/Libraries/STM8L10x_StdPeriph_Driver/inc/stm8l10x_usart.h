/**
  ********************************************************************************
  * @file    stm8l10x_usart.h
  * @author  MCD Application Team
  * @version V1.2.1
  * @date    30-September-2014
  * @brief   This file contains all functions prototypes and macros for the USART
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
#ifndef __STM8L10X_USART_H
#define __STM8L10X_USART_H

/* Includes ------------------------------------------------------------------*/
#include "stm8l10x.h"

/* Exported variables ------------------------------------------------------- */
/* Exported types ------------------------------------------------------------*/

/** @addtogroup USART_Exported_Types
  * @{
  */

/**
  * @brief USART Flag possible values
  */
typedef enum { USART_FLAG_TXE   = (uint16_t)0x0080, /*!< Transmit Data Register Empty flag */
               USART_FLAG_TC    = (uint16_t)0x0040, /*!< Transmission Complete flag */
               USART_FLAG_RXNE  = (uint16_t)0x0020, /*!< Read Data Register Not Empty flag */
               USART_FLAG_IDLE  = (uint16_t)0x0010, /*!< Idle line detected flag */
               USART_FLAG_OR    = (uint16_t)0x0008, /*!< OverRun error flag */
               USART_FLAG_NF    = (uint16_t)0x0004, /*!< Noise error flag */
               USART_FLAG_FE    = (uint16_t)0x0002, /*!< Framing Error flag */
               USART_FLAG_PE    = (uint16_t)0x0001, /*!< Parity Error flag */
               USART_FLAG_SBK   = (uint16_t)0x0101  /*!< Send Break characters Flag */
             } USART_FLAG_TypeDef;

/**
  * @brief USART Interrupt definition
  * USART_IT possible values
  * Elements values convention: 0xZYX
  * X: Position of the corresponding Interrupt
  * Y: Flag position
  * Z: Register index
  */
typedef enum { USART_IT_TXE        = (uint16_t)0x0277, /*!< Transmit interrupt */
               USART_IT_TC         = (uint16_t)0x0266, /*!< Transmission Complete interrupt */
               USART_IT_RXNE       = (uint16_t)0x0255, /*!< Receive interrupt */
               USART_IT_IDLE       = (uint16_t)0x0244, /*!< IDLE line interrupt */
               USART_IT_OR         = (uint16_t)0x0235, /*!< Overrun Error interrupt */
               USART_IT_PE         = (uint16_t)0x0100 /*!< Parity Error interrupt */
             } USART_IT_TypeDef;

/**
  * @brief USART WakeUP Modes
  */
typedef enum
{
  USART_WakeUp_IdleLine      = (uint8_t)0x00, /*!< 0x01 Idle Line wake up */
  USART_WakeUp_AddressMark    = (uint8_t)0x08  /*!< 0x02 Address Mark wake up */
} USART_WakeUp_TypeDef;

/**
  * @brief USART stop bits possible values
  */
typedef enum
{
  USART_StopBits_1   = (uint8_t)0x00,   /*!< One stop bit is  transmitted at the end of frame */
  USART_StopBits_2   = (uint8_t)0x20    /*!< Two stop bits are  transmitted at the end of frame */
} USART_StopBits_TypeDef;

/**
  * @brief USART parity possible values
  */
typedef enum
{
  USART_Parity_No   = (uint8_t)0x00,      /*!< No Parity*/
  USART_Parity_Even = (uint8_t)0x04,      /*!< Even Parity*/
  USART_Parity_Odd = (uint8_t)0x06       /*!< Odd Parity*/
} USART_Parity_TypeDef;

/**
  * @brief USART Word length possible values
  */
typedef enum
{
  USART_WordLength_8D = (uint8_t)0x00,  /*!< 0x00 8 bits Data */
  USART_WordLength_9D = (uint8_t)0x10   /*!< 0x10 9 bits Data */
} USART_WordLength_TypeDef;

/**
  * @brief USART Mode possible values
  */
typedef enum
{
  USART_Mode_Rx    = (uint8_t)0x04,  /*!< 0x04 Receive Enable */
  USART_Mode_Tx    = (uint8_t)0x08   /*!< 0x08 Transmit Enable */
} USART_Mode_TypeDef;

/**
  * @brief USART Clock possible values
  */
typedef enum
{
  USART_Clock_Disable    = (uint8_t)0x00,  /*!< 0x00 SLK pin disabled */
  USART_Clock_Enable     = (uint8_t)0x08   /*!< 0x08 SLK pin enabled */
} USART_Clock_TypeDef;

/**
  * @brief USART Clock Polarity possible values
  */
typedef enum
{
  USART_CPOL_Low      = (uint8_t)0x00,  /*!< 0x00 SCK to 0 when idle */
  USART_CPOL_High     = (uint8_t)0x04   /*!< 0x04 SCK to 1 when idle.*/
} USART_CPOL_TypeDef;

/**
  * @brief USART Clock Phase possible values
  */
typedef enum
{
  USART_CPHA_1Edge     = (uint8_t)0x00,  /*!< 0x00 The first clock transition is the first data capture edge*/
  USART_CPHA_2Edge     = (uint8_t)0x02   /*!< 0x02 The second clock transition is the first data capture edge*/
} USART_CPHA_TypeDef;

/**
  * @brief USART Last Bit possible values
  */
typedef enum
{
  USART_LastBit_Disable  = (uint8_t)0x00,  /*!< 0x00 The clock pulse of the last data bit is not output to the SCLK pin.*/
  USART_LastBit_Enable   = (uint8_t)0x01   /*!< 0x02 The clock pulse of the last data bit is output to the SCLK pin.*/
} USART_LastBit_TypeDef;


/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/

/** @addtogroup USART_Private_Macros
  * @{
  */

/**
  * @brief Macro used by the assert function to check the different functions parameters.
  */

/**
  * @brief Macro used by the assert_param function in order to check the different sensitivity values
  *  for the FLAGs
  */
#define IS_USART_FLAG(Flag) (((Flag) == USART_FLAG_TXE) || \
                             ((Flag) == USART_FLAG_TC)  || \
                             ((Flag) == USART_FLAG_RXNE) || \
                             ((Flag) == USART_FLAG_IDLE) || \
                             ((Flag) == USART_FLAG_OR) || \
                             ((Flag) == USART_FLAG_NF) || \
                             ((Flag) == USART_FLAG_FE) || \
                             ((Flag) == USART_FLAG_PE) || \
                             ((Flag) == USART_FLAG_SBK))

/**
  * @brief Macro used by the assert_param function in order to check the different sensitivity values
  * for the Interrupts
  */

#define IS_USART_CONFIG_IT(Interrupt) (((Interrupt) == USART_IT_PE) || \
                                       ((Interrupt) == USART_IT_TXE) || \
                                       ((Interrupt) == USART_IT_TC) || \
                                       ((Interrupt) == USART_IT_RXNE ) || \
                                       ((Interrupt) == USART_IT_OR) || \
                                       ((Interrupt) == USART_IT_IDLE))

/**
  * @brief Macro used by the assert function in order to check the different sensitivity values
 *  for the pending bit
  */
#define IS_USART_GET_IT(ITPendingBit) (((ITPendingBit) == USART_IT_TXE)  || \
                                       ((ITPendingBit) == USART_IT_TC)   || \
                                       ((ITPendingBit) == USART_IT_RXNE) || \
                                       ((ITPendingBit) == USART_IT_IDLE) || \
                                       ((ITPendingBit) == USART_IT_OR)  || \
                                       ((ITPendingBit) == USART_IT_PE))

/**
 * @brief Macro used by the assert function in order to check the different sensitivity values for the MODEs
 * possible combination should be one of the following
 */
#define IS_USART_MODE(MODE) ((((MODE) & (uint8_t)0xF3) == 0x00) && ((MODE) != (uint16_t)0x00))

/**
 * @brief Macro used by the assert function in order to check the different sensitivity values for the
 *  Word Lengths
 */
#define IS_USART_WordLength(WordLength)(((WordLength) == USART_WordLength_8D) || \
                                        ((WordLength) == USART_WordLength_9D))

/**
  * @brief Macro used by the assert_param function in order to check the different sensitivity values
  *  for the USART Clock
  */
#define IS_USART_CLOCK(CLOCK) (((CLOCK) == USART_Clock_Disable) ||((CLOCK) == USART_Clock_Enable))

/**
  * @brief Macro used by the assert_param function in order to check the different sensitivity values
  *  for the USART Clock Polarity
  */
#define IS_USART_CPOL(CPOL) (((CPOL) == USART_CPOL_Low) || ((CPOL) == USART_CPOL_High))

/**
  * @brief Macro used by the assert_param function in order to check the different sensitivity values
 *  for the USART Clock Phase
  */
#define IS_USART_CPHA(CPHA) (((CPHA) == USART_CPHA_1Edge) || ((CPHA) == USART_CPHA_2Edge))

/**
  * @brief Macro used by the assert_param function in order to check the different sensitivity values
  *  for the USART Last Bit
  */
#define IS_USART_LASTBIT(LASTBIT) (((LASTBIT) == USART_LastBit_Disable) || \
                                   ((LASTBIT) == USART_LastBit_Enable))

/**
  * @brief Macro used by the assert function in order to check the different sensitivity values
 *  for the WakeUps
  */
#define IS_USART_WAKEUP(WakeUpMode)(((WakeUpMode) == USART_WakeUp_IdleLine) || \
                                    ((WakeUpMode) == USART_WakeUp_AddressMark))


/**
  * @brief Macro used by the assert function in order to check the different sensitivity values
  *  for the USART_StopBits
  */
#define IS_USART_STOPBITS(StopBit)(((StopBit) == USART_StopBits_1) || \
                                   ((StopBit) == USART_StopBits_2))

/**
 * @brief Macro used by the assert function in order to check the different sensitivity values
 *  for the Paritys
 */
#define IS_USART_PARITY(Parity)(((Parity) == USART_Parity_No)   || \
                                ((Parity) == USART_Parity_Even) || \
                                ((Parity) == USART_Parity_Odd ))

/* BaudRate value should be < 625000 bps */
#define IS_USART_BAUDRATE(NUM) ((NUM) <= (uint32_t)625000)

/**
 * @brief Macro used by the assert function in order to check the different sensitivity values
 *  for the node address
 */
#define USART_ADDRESS_MAX ((uint8_t)16)
#define IS_USART_ADDRESS(address) ((address) < USART_ADDRESS_MAX)

/**
 * @brief Macro used by the assert function in order to check the different sensitivity values
 *  for the data
 */

#define USART_DATA_9BITS_MAX ((uint16_t)0x1FF)
#define IS_USART_DATA_9BITS(DATA) ((DATA) < USART_DATA_9BITS_MAX)
/**
  * @}
  */

/* Exported functions ------------------------------------------------------- */
/** @addtogroup USART_Exported_functions
  * @{
  */

void USART_DeInit(void);
void USART_Init(uint32_t BaudRate, USART_WordLength_TypeDef USART_WordLength, USART_StopBits_TypeDef
                USART_StopBits, USART_Parity_TypeDef USART_Parity, USART_Mode_TypeDef USART_Mode);
void USART_ClockInit(USART_Clock_TypeDef USART_Clock, USART_CPOL_TypeDef USART_CPOL,
                     USART_CPHA_TypeDef USART_CPHA, USART_LastBit_TypeDef USART_LastBit);
void USART_Cmd(FunctionalState NewState);
void USART_ITConfig(USART_IT_TypeDef USART_IT, FunctionalState NewState);
uint8_t USART_ReceiveData8(void);
uint16_t USART_ReceiveData9(void);
void USART_ReceiverWakeUpCmd(FunctionalState NewState);
void USART_SendBreak(void);
void USART_SendData8(uint8_t Data);
void USART_SendData9(uint16_t Data);
void USART_SetAddress(uint8_t Address);
void USART_WakeUpConfig(USART_WakeUp_TypeDef USART_WakeUp);
FlagStatus USART_GetFlagStatus(USART_FLAG_TypeDef USART_FLAG);
void USART_ClearFlag(void);
ITStatus USART_GetITStatus(USART_IT_TypeDef USART_IT);
void USART_ClearITPendingBit(void);

/**
  * @}
  */

#endif /* __STM8L10X_USART_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
