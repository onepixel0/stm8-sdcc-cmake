/**
  ******************************************************************************
  * @file    stm8l10x_clk.c
  * @author  MCD Application Team
  * @version V1.2.1
  * @date    30-September-2014
  * @brief   This file contains all the functions for the CLK peripheral.
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

#include "stm8l10x_clk.h"

/** @addtogroup STM8L10x_StdPeriph_Driver
  * @{
  */
/** @defgroup CLK 
  * @brief CLK driver modules
  * @{
  */ 
  
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private Constants ---------------------------------------------------------*/

/**
  * @addtogroup CLK_Private_Constants
  * @{
  */

CONST uint8_t HSIDivFactor[4] = {1, 2, 4, 8}; /*!< Holds the different HSI Dividor factors */

/**
  * @}
  */

/**
  * @addtogroup CLK_Private_Functions
  * @{
  */

/**
  * @brief  Deinitializes the CLK peripheral registers to their default reset values.
  * @param  None
  * @retval None
  */
void CLK_DeInit(void)
{
  CLK->CKDIVR = CLK_CKDIVR_RESET_VALUE;
  CLK->PCKENR = CLK_PCKENR_RESET_VALUE;
  CLK->CCOR  = CLK_CCOR_RESET_VALUE;
}

/**
  * @brief  Enables or disable the Configurable Clock Output (CCO).
  * @param  NewState New state of CCEN bit (CCO register).
  * @retval None
  */
void CLK_CCOCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Set CCOEN bit */
    CLK->CCOR |= CLK_CCOR_CCOEN;
  }
  else
  {
    /* Reset CCOEN bit */
    CLK->CCOR &= (uint8_t)(~CLK_CCOR_CCOEN);
  }

}

/**
  * @brief  Enables or disables the specified peripheral CLK.
  * @param  CLK_Peripheral: specifies the peripheral to gate its clock.
  *          This parameter can be any combination of the following values:
  *            @arg CLK_Peripheral_TIM2:       TIM2 clock
  *            @arg CLK_Peripheral_TIM3:       TIM3 clock 
  *            @arg CLK_Peripheral_TIM4:       TIM4 clock
  *            @arg CLK_Peripheral_I2C:        I2C clock
  *            @arg CLK_Peripheral_SPI:        SPI clock
  *            @arg CLK_Peripheral_USART:      USART clock
  *            @arg CLK_Peripheral_AWU:        AWU clock
  * @param  NewState: new state of the specified peripheral clock.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void CLK_PeripheralClockConfig(CLK_Peripheral_TypeDef CLK_Peripheral, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    assert_param(IS_CLK_PERIPHERAL(CLK_Peripheral));

    if (NewState != DISABLE)
    {
      /* Enable the peripheral Clock */
      CLK->PCKENR |= ((uint8_t)CLK_Peripheral);
    }
    else
    {
      /* Disable the peripheral Clock */
      CLK->PCKENR &= (uint8_t)(~(uint8_t)CLK_Peripheral);
    }
}

/**
  * @brief  Configures the HSI master clock dividers.
  * @param  CLK_MasterPrescaler Specifies the HSI clock divider to apply.
  *           This parameter can be any combination of the following values:
  *            @arg CLK_MasterPrescaler_HSIDiv1:       High speed internal clock not divided
  *            @arg CLK_MasterPrescaler_HSIDiv2:       High speed internal clock divided by 2
  *            @arg CLK_MasterPrescaler_HSIDiv4:       High speed internal clock divided by 4
  *            @arg CLK_MasterPrescaler_HSIDiv8:       High speed internal clock divided by 8     
  * @retval None
  */
void CLK_MasterPrescalerConfig(CLK_MasterPrescaler_TypeDef CLK_MasterPrescaler)
{
  /* check parameters */
  assert_param(IS_CLK_MASTER_PRESCALER(CLK_MasterPrescaler));

  CLK->CKDIVR &= (uint8_t)(~CLK_CKDIVR_HSIDIV);
  CLK->CKDIVR = (uint8_t)CLK_MasterPrescaler;
}

/**
  * @brief  Output the selected clock on a dedicated I/O pin.
  * @note   The I/O dedicated to the CCO pin must be set in output push-pull mode.
  * @param  CLK_Output Specifies the clock source.
  *          This parameter can be any combination of the following values:
  *            @arg CLK_Output_ClockMaster:           Clock Output CKM
  *            @arg CLK_Output_ClockMasterDiv2:       Clock Output CKM/2
  *            @arg CLK_Output_ClockMasterDiv4:       Clock Output CKM/4
  *            @arg CLK_Output_ClockMasterDiv16:      Clock Output CKM/16      
  * @retval None
  */
void CLK_CCOConfig(CLK_Output_TypeDef CLK_Output)
{
  /* check parameters */
  assert_param(IS_CLK_OUTPUT(CLK_Output));

  /* Clears of the CCO type bits part */
  CLK->CCOR &= (uint8_t)(~CLK_CCOR_CCOSEL);

  /* Selects the source provided on cco_ck output */
  CLK->CCOR |= ((uint8_t)CLK_Output);

  /* Enable the clock output */
  CLK->CCOR |= CLK_CCOR_CCOEN;
}

/**
  * @brief  This function returns the frequencies of different on chip clocks.
  * @param  None
  * @retval The master clock frequency
  */
uint32_t CLK_GetClockFreq(void)
{
  uint32_t clockfrequency = 0;
  uint8_t tmp = 0, presc = 0;

  tmp = (uint8_t)(CLK->CKDIVR & CLK_CKDIVR_HSIDIV);
  presc = HSIDivFactor[tmp];
  clockfrequency = HSI_VALUE / presc;

  return((uint32_t)clockfrequency);
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

/**
  * @}
  */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
