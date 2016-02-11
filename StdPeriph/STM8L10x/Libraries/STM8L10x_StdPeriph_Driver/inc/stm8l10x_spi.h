/**
  ******************************************************************************
  * @file    stm8l10x_spi.h
  * @author  MCD Application Team
  * @version V1.2.1
  * @date    30-September-2014
  * @brief   This file contains all functions prototypes and macros for the SPI 
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
#ifndef __STM8L10X_SPI_H
#define __STM8L10X_SPI_H

/* Includes ------------------------------------------------------------------*/
#include "stm8l10x.h"

/* Exported variables ------------------------------------------------------- */
/* Exported types ------------------------------------------------------------*/

/** @addtogroup SPI_Exported_Types
  * @{
  */

/**
  * @brief SPI data direction mode
  * Warning: element values correspond to BDM, BDOE, RXONLY bits position
  */
typedef enum {
  SPI_Direction_2Lines_FullDuplex = (uint8_t)0x00, /*!< 2-line uni-directional data mode enable */
  SPI_Direction_2Lines_RxOnly     = (uint8_t)0x04, /*!< Receiver only in 2 line uni-directional data mode */
  SPI_Direction_1Line_Rx          = (uint8_t)0x80, /*!< Receiver only in 1 line bi-directional data mode */
  SPI_Direction_1Line_Tx          = (uint8_t)0xC0  /*!< Transmit only in 1 line bi-directional data mode */
} SPI_DirectionMode_TypeDef;

/**
  * @brief SPI direction transmit/receive
  */

typedef enum {
  SPI_Direction_Rx = (uint8_t)0x00, /*!< Selects Rx receive direction in bi-directional mode */
  SPI_Direction_Tx = (uint8_t)0x01  /*!< Selects Tx transmission direction in bi-directional mode */
} SPI_Direction_TypeDef;

/**
  * @brief SPI master/slave mode
  * Warning: element values correspond to MSTR bit position
  */
typedef enum {
  SPI_Mode_Master = (uint8_t)0x04, /*!< SPI Master configuration */
  SPI_Mode_Slave  = (uint8_t)0x00  /*!< SPI Slave configuration */
} SPI_Mode_TypeDef;

/**
  * @brief SPI Slave Select management
  * Warning: element values correspond to LSBFIRST bit position
  */
typedef enum
{
  SPI_NSS_Soft  = (uint8_t)0x02, /*!< Software slave management disabled */
  SPI_NSS_Hard  = (uint8_t)0x00  /*!< Software slave management enabled */
} SPI_NSS_TypeDef;

/**
  * @brief SPI BaudRate Prescaler
  * Warning: element values correspond to BR bits position
  */
typedef enum {
  SPI_BaudRatePrescaler_2   = (uint8_t)0x00, /*!< SPI frequency = frequency(CPU)/2 */
  SPI_BaudRatePrescaler_4   = (uint8_t)0x08, /*!< SPI frequency = frequency(CPU)/4 */
  SPI_BaudRatePrescaler_8   = (uint8_t)0x10, /*!< SPI frequency = frequency(CPU)/8 */
  SPI_BaudRatePrescaler_16  = (uint8_t)0x18, /*!< SPI frequency = frequency(CPU)/16 */
  SPI_BaudRatePrescaler_32  = (uint8_t)0x20, /*!< SPI frequency = frequency(CPU)/32 */
  SPI_BaudRatePrescaler_64  = (uint8_t)0x28, /*!< SPI frequency = frequency(CPU)/64 */
  SPI_BaudRatePrescaler_128 = (uint8_t)0x30, /*!< SPI frequency = frequency(CPU)/128 */
  SPI_BaudRatePrescaler_256 = (uint8_t)0x38  /*!< SPI frequency = frequency(CPU)/256 */
} SPI_BaudRatePrescaler_TypeDef;

/**
  * @brief SPI Clock Polarity
  * Warning: element values correspond to CPOL bit position
  */
typedef enum {
  SPI_CPOL_Low  = (uint8_t)0x00, /*!< Clock to 0 when idle */
  SPI_CPOL_High = (uint8_t)0x02  /*!< Clock to 1 when idle */
} SPI_CPOL_TypeDef;

/**
  * @brief SPI Clock Phase
  * Warning: element values correspond to CPHA bit position
  */
typedef enum {
  SPI_CPHA_1Edge = (uint8_t)0x00, /*!< The first clock transition is the first data capture edge */
  SPI_CPHA_2Edge = (uint8_t)0x01  /*!< The second clock transition is the first data capture edge */
} SPI_CPHA_TypeDef;

/**
  * @brief SPI Frame Format: MSB or LSB transmitted first
  * Warning: element values correspond to LSBFIRST bit position
  */
typedef enum {
  SPI_FirstBit_MSB = (uint8_t)0x00, /*!< MSB bit will be transmitted first */
  SPI_FirstBit_LSB = (uint8_t)0x80  /*!< LSB bit will be transmitted first */
} SPI_FirstBit_TypeDef;

/**
  * @brief SPI flags definition - Warning : FLAG value = mapping position register
  */
typedef enum {
  SPI_FLAG_BSY    = (uint8_t)0x80, /*!< Busy flag */
  SPI_FLAG_OVR    = (uint8_t)0x40, /*!< Overrun flag */
  SPI_FLAG_MODF   = (uint8_t)0x20, /*!< Mode fault */
  SPI_FLAG_WKUP   = (uint8_t)0x08, /*!< Wake-up flag */
  SPI_FLAG_TXE    = (uint8_t)0x02, /*!< Transmit buffer empty */
  SPI_FLAG_RXNE   = (uint8_t)0x01  /*!< Receive buffer empty */
} SPI_FLAG_TypeDef;

/**
  * @brief SPI_IT possible values
  * Elements values convention: 0xYX
  *   X: Position of the corresponding Interrupt
  *   Y: ITPENDINGBIT position
  */
typedef enum
{
  SPI_IT_WKUP   = (uint8_t)0x34,  /*!< Wake-up interrupt*/
  SPI_IT_OVR    = (uint8_t)0x65,  /*!< Overrun interrupt*/
  SPI_IT_MODF   = (uint8_t)0x55,  /*!< Mode fault interrupt*/
  SPI_IT_TXE    = (uint8_t)0x17,  /*!< Transmit buffer empty interrupt*/
  SPI_IT_RXNE   = (uint8_t)0x06,  /*!< Receive buffer not empty interrupt*/
  SPI_IT_ERR    = (uint8_t)0x05   /*!< Error interrupt*/
} SPI_IT_TypeDef;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/

/** @addtogroup SPI_Private_Macros
  * @brief Macros used by the assert_param function to check the different functions parameters.
  * @{
  */

/**
  * @brief Macro used by the assert function in order to check the data direction mode values
  */
#define IS_SPI_DIRECTION_MODE(MODE) (((MODE) == SPI_Direction_2Lines_FullDuplex) || \
                                     ((MODE) == SPI_Direction_2Lines_RxOnly) || \
                                     ((MODE) == SPI_Direction_1Line_Rx) || \
                                     ((MODE) == SPI_Direction_1Line_Tx))

/**
  * @brief Macro used by the assert function in order to check the mode half duplex data direction values
  */
#define IS_SPI_DIRECTION(DIRECTION) (((DIRECTION) == SPI_Direction_Rx) || \
                                     ((DIRECTION) == SPI_Direction_Tx))

/**
  * @brief Macro used by the assert function in order to check the SPI Mode values
  */
#define IS_SPI_MODE(MODE) (((MODE) == SPI_Mode_Master) || \
                           ((MODE) == SPI_Mode_Slave))

/**
  * @brief Macro used by the assert function in order to check the NSS management values
  */
#define IS_SPI_NSS(NSS) (((NSS) == SPI_NSS_Soft) || \
                         ((NSS) == SPI_NSS_Hard))

/**
  * @brief Macro used by the assert function in order to check the baudrate values
  */
#define IS_SPI_BAUDRATE_PRESCALER(PRESCALER) (((PRESCALER) == SPI_BaudRatePrescaler_2) || \
    ((PRESCALER) == SPI_BaudRatePrescaler_4) || \
    ((PRESCALER) == SPI_BaudRatePrescaler_8) || \
    ((PRESCALER) == SPI_BaudRatePrescaler_16) || \
    ((PRESCALER) == SPI_BaudRatePrescaler_32) || \
    ((PRESCALER) == SPI_BaudRatePrescaler_64) || \
    ((PRESCALER) == SPI_BaudRatePrescaler_128) || \
    ((PRESCALER) == SPI_BaudRatePrescaler_256))

/**
  * @brief Macro used by the assert function in order to check the polarity values
  */
#define IS_SPI_CPOL(CPOL) (((CPOL) == SPI_CPOL_Low) || \
                           ((CPOL) == SPI_CPOL_High))

/**
  * @brief Macro used by the assert function in order to check the phase values
  */
#define IS_SPI_CPHA(CPHA) (((CPHA) == SPI_CPHA_1Edge) || \
                           ((CPHA) == SPI_CPHA_2Edge))

/**
  * @brief Macro used by the assert function in order to check the first bit to be transmitted values
  */
#define IS_SPI_FIRST_BIT(BIT) (((BIT) == SPI_FirstBit_MSB) || \
                               ((BIT) == SPI_FirstBit_LSB))

/**
  * @brief Macro used by the assert_param function in order to check the different flags values
  */
#define IS_SPI_FLAG(FLAG) (((FLAG) == SPI_FLAG_OVR) || \
                           ((FLAG) == SPI_FLAG_MODF) || \
                           ((FLAG) == SPI_FLAG_WKUP) || \
                           ((FLAG) == SPI_FLAG_TXE) || \
                           ((FLAG) == SPI_FLAG_RXNE) || \
                           ((FLAG) == SPI_FLAG_BSY))

/**
  * @brief Macro used by the assert_param function in order to check the different sensitivity values for the Interrupts
  */
#define IS_SPI_CONFIG_IT(IT) (((IT) == SPI_IT_TXE)  || \
                              ((IT) == SPI_IT_RXNE)  || \
                              ((IT) == SPI_IT_ERR) || \
                              ((IT) == SPI_IT_WKUP))
/**
  * @brief Macro used by the assert_param function in order to check the different sensitivity values for the pending bit
  */
#define IS_SPI_GET_IT(IT) (((IT) == SPI_IT_OVR)  || \
                           ((IT) == SPI_IT_MODF) || \
                           ((IT) == SPI_IT_WKUP) || \
                           ((IT) == SPI_IT_TXE)  || \
                           ((IT) == SPI_IT_RXNE))

/**
  * @}
  */

/* Exported functions ------------------------------------------------------- */
/** @addtogroup SPI_Exported_Functions
  * @{
  */

void SPI_DeInit(void);
void SPI_Init(SPI_FirstBit_TypeDef SPI_FirstBit, SPI_BaudRatePrescaler_TypeDef
              SPI_BaudRatePrescaler, SPI_Mode_TypeDef SPI_Mode, SPI_CPOL_TypeDef
              SPI_CPOL, SPI_CPHA_TypeDef SPI_CPHA, SPI_DirectionMode_TypeDef
              SPI_DirectionMode, SPI_NSS_TypeDef SPI_NSS);
void SPI_Cmd(FunctionalState NewState);
void SPI_ITConfig(SPI_IT_TypeDef SPI_IT, FunctionalState NewState);
void SPI_NSSInternalSoftwareCmd(FunctionalState NewState);
void SPI_BiDirectionalLineConfig(SPI_Direction_TypeDef SPI_Direction);
void SPI_SendData(uint8_t Data);
uint8_t SPI_ReceiveData(void);
FlagStatus SPI_GetFlagStatus(SPI_FLAG_TypeDef SPI_FLAG);
ITStatus SPI_GetITStatus(SPI_IT_TypeDef SPI_IT);
void SPI_ClearFlag(void);
void SPI_ClearITPendingBit(void);

/**
  * @}
  */

#endif /* __STM8L10x_SPI_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
