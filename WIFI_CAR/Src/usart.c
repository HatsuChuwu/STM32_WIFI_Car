/**
  ******************************************************************************
  * File Name          : USART.c
  * Description        : This file provides code for the configuration
  *                      of the USART instances.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "usart.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;
UART_HandleTypeDef huart3;

/* USART1 init function */

/**
 * @brief 初始化USART1的UART功能
 *
 * 该函数用于配置并初始化USART1的UART功能，包括波特率、字长、停止位、奇偶校验、模式、硬件流控制等参数。
 */
void MX_USART1_UART_Init(void)
{
    // 配置USART1实例
    huart1.Instance = USART1;

    // 设置波特率为115200
    huart1.Init.BaudRate = 115200;
    // 设置字长为8位
    huart1.Init.WordLength = UART_WORDLENGTH_8B;
    // 设置停止位为1位
    huart1.Init.StopBits = UART_STOPBITS_1;
    // 设置无奇偶校验
    huart1.Init.Parity = UART_PARITY_NONE;
    // 设置收发模式
    huart1.Init.Mode = UART_MODE_TX_RX;
    // 设置无硬件流控制
    huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    // 设置过采样为16
    huart1.Init.OverSampling = UART_OVERSAMPLING_16;

    // 初始化UART
    if (HAL_UART_Init(&huart1) != HAL_OK)
    {
        // 如果初始化失败，则调用错误处理函数
        Error_Handler();
    }

}
/* USART2 init function */

/**
 * @brief 初始化USART2为UART模式
 *
 * 该函数用于初始化USART2外设，设置其波特率、数据位、停止位、校验位、工作模式、硬件流控制和过采样率等参数，
 * 并调用HAL_UART_Init函数完成初始化。如果初始化失败，则调用Error_Handler函数处理错误。
 */
void MX_USART2_UART_Init(void)
{
    // 配置USART2的实例
    huart2.Instance = USART2;

    // 配置波特率
    huart2.Init.BaudRate = 115200;

    // 配置数据位长度
    huart2.Init.WordLength = UART_WORDLENGTH_8B;

    // 配置停止位
    huart2.Init.StopBits = UART_STOPBITS_1;

    // 配置奇偶校验
    huart2.Init.Parity = UART_PARITY_NONE;

    // 配置模式（收发）
    huart2.Init.Mode = UART_MODE_TX_RX;

    // 配置硬件流控制
    huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;

    // 配置过采样
    huart2.Init.OverSampling = UART_OVERSAMPLING_16;

    // 初始化UART
    if (HAL_UART_Init(&huart2) != HAL_OK)
    {
        // 如果初始化失败，调用错误处理函数
        Error_Handler();
    }

}
/* USART3 init function */

/**
 * @brief 初始化 USART3 UART
 *
 * 该函数用于初始化 USART3 UART 的相关参数，包括波特率、字长、停止位、校验位、模式、硬件流控制和过采样率。
 * 如果初始化失败，则调用 Error_Handler 函数。
 */
void MX_USART3_UART_Init(void)
{

  // 初始化USART3实例
  huart3.Instance = USART3;

  // 设置波特率为115200
  huart3.Init.BaudRate = 115200;

  // 设置数据位长度为8位
  huart3.Init.WordLength = UART_WORDLENGTH_8B;

  // 设置停止位为1位
  huart3.Init.StopBits = UART_STOPBITS_1;

  // 设置无奇偶校验
  huart3.Init.Parity = UART_PARITY_NONE;

  // 设置模式为发送和接收
  huart3.Init.Mode = UART_MODE_TX_RX;

  // 设置无硬件流控制
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;

  // 设置过采样为16
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;

  // 初始化UART
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    // 初始化失败时调用错误处理函数
    Error_Handler();
  }

}

/**
 * @brief 初始化UART外设的中断和GPIO
 *
 * 该函数根据传入的UART句柄（uartHandle）配置相应的USART外设的中断和GPIO。
 *
 * @param uartHandle UART句柄，指向需要初始化的UART_HandleTypeDef结构体
 */
void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(uartHandle->Instance==USART1)
  {
    /* USER CODE BEGIN USART1_MspInit 0 */
    // 用户代码开始 - USART1 MspInit 0

    /* USER CODE END USART1_MspInit 0 */
    // 用户代码结束 - USART1 MspInit 0
    /* USART1 时钟使能 */
    __HAL_RCC_USART1_CLK_ENABLE();
  
    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**USART1 GPIO 配置    
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX 
    */
    GPIO_InitStruct.Pin = USART1_TX_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(USART1_TX_GPIO_Port, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = USART1_RX_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(USART1_RX_GPIO_Port, &GPIO_InitStruct);

    /* USART1 中断初始化 */
    HAL_NVIC_SetPriority(USART1_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART1_IRQn);
    /* USER CODE BEGIN USART1_MspInit 1 */
    // 用户代码开始 - USART1 MspInit 1

    /* USER CODE END USART1_MspInit 1 */
    // 用户代码结束 - USART1 MspInit 1
  }
  else if(uartHandle->Instance==USART2)
  {
    /* USER CODE BEGIN USART2_MspInit 0 */
    // 用户代码开始 - USART2 MspInit 0

    /* USER CODE END USART2_MspInit 0 */
    // 用户代码结束 - USART2 MspInit 0
    /* USART2 时钟使能 */
    __HAL_RCC_USART2_CLK_ENABLE();
  
    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**USART2 GPIO 配置    
    PA2     ------> USART2_TX
    PA3     ------> USART2_RX 
    */
    GPIO_InitStruct.Pin = USART2_TX_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(USART2_TX_GPIO_Port, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = USART2_RX_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(USART2_RX_GPIO_Port, &GPIO_InitStruct);

    /* USART2 中断初始化 */
    HAL_NVIC_SetPriority(USART2_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART2_IRQn);
    /* USER CODE BEGIN USART2_MspInit 1 */
    // 用户代码开始 - USART2 MspInit 1

    /* USER CODE END USART2_MspInit 1 */
    // 用户代码结束 - USART2 MspInit 1
  }
  else if(uartHandle->Instance==USART3)
  {
    /* USER CODE BEGIN USART3_MspInit 0 */
    // 用户代码开始 - USART3 MspInit 0

    /* USER CODE END USART3_MspInit 0 */
    // 用户代码结束 - USART3 MspInit 0
    /* USART3 时钟使能 */
    __HAL_RCC_USART3_CLK_ENABLE();
  
    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**USART3 GPIO 配置    
    PB10     ------> USART3_TX
    PB11     ------> USART3_RX 
    */
    GPIO_InitStruct.Pin = USART3_TX_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(USART3_TX_GPIO_Port, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = USART3_RX_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(USART3_RX_GPIO_Port, &GPIO_InitStruct);

    /* USART3 中断初始化 */
    HAL_NVIC_SetPriority(USART3_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART3_IRQn);
    /* USER CODE BEGIN USART3_MspInit 1 */
    // 用户代码开始 - USART3 MspInit 1

    /* USER CODE END USART3_MspInit 1 */
    // 用户代码结束 - USART3 MspInit 1
  }
}

/**
 * @brief 反初始化UART外设的MSP（硬件抽象层）
 *
 * 该函数用于反初始化UART外设的MSP，包括禁用外设时钟、反初始化GPIO引脚以及禁用中断。
 *
 * @param uartHandle UART句柄，包含UART配置信息
 */
void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{

  if(uartHandle->Instance==USART1)
  {
    /* USER CODE BEGIN USART1_MspDeInit 0 */
    // 用户代码开始：USART1_MspDeInit 0

    /* USER CODE END USART1_MspDeInit 0 */
    // 用户代码结束：USART1_MspDeInit 0
    /* Peripheral clock disable */
    // 禁用外设时钟
    __HAL_RCC_USART1_CLK_DISABLE();
  
    /**USART1 GPIO Configuration    
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX 
    */
    // USART1 GPIO配置
    // PA9 连接到 USART1_TX
    // PA10 连接到 USART1_RX
    HAL_GPIO_DeInit(GPIOA, USART1_TX_Pin|USART1_RX_Pin);

    /* USART1 interrupt Deinit */
    // 禁用USART1中断
    HAL_NVIC_DisableIRQ(USART1_IRQn);
  /* USER CODE BEGIN USART1_MspDeInit 1 */
    // 用户代码开始：USART1_MspDeInit 1

    /* USER CODE END USART1_MspDeInit 1 */
    // 用户代码结束：USART1_MspDeInit 1
  }
  else if(uartHandle->Instance==USART2)
  {
    /* USER CODE BEGIN USART2_MspDeInit 0 */
    // 用户代码开始：USART2_MspDeInit 0

    /* USER CODE END USART2_MspDeInit 0 */
    // 用户代码结束：USART2_MspDeInit 0
    /* Peripheral clock disable */
    // 禁用外设时钟
    __HAL_RCC_USART2_CLK_DISABLE();
  
    /**USART2 GPIO Configuration    
    PA2     ------> USART2_TX
    PA3     ------> USART2_RX 
    */
    // USART2 GPIO配置
    // PA2 连接到 USART2_TX
    // PA3 连接到 USART2_RX
    HAL_GPIO_DeInit(GPIOA, USART2_TX_Pin|USART2_RX_Pin);

    /* USART2 interrupt Deinit */
    // 禁用USART2中断
    HAL_NVIC_DisableIRQ(USART2_IRQn);
  /* USER CODE BEGIN USART2_MspDeInit 1 */
    // 用户代码开始：USART2_MspDeInit 1

    /* USER CODE END USART2_MspDeInit 1 */
    // 用户代码结束：USART2_MspDeInit 1
  }
  else if(uartHandle->Instance==USART3)
  {
    /* USER CODE BEGIN USART3_MspDeInit 0 */
    // 用户代码开始：USART3_MspDeInit 0

    /* USER CODE END USART3_MspDeInit 0 */
    // 用户代码结束：USART3_MspDeInit 0
    /* Peripheral clock disable */
    // 禁用外设时钟
    __HAL_RCC_USART3_CLK_DISABLE();
  
    /**USART3 GPIO Configuration    
    PB10     ------> USART3_TX
    PB11     ------> USART3_RX 
    */
    // USART3 GPIO配置
    // PB10 连接到 USART3_TX
    // PB11 连接到 USART3_RX
    HAL_GPIO_DeInit(GPIOB, USART3_TX_Pin|USART3_RX_Pin);

    /* USART3 interrupt Deinit */
    // 禁用USART3中断
    HAL_NVIC_DisableIRQ(USART3_IRQn);
  /* USER CODE BEGIN USART3_MspDeInit 1 */
    // 用户代码开始：USART3_MspDeInit 1

    /* USER CODE END USART3_MspDeInit 1 */
    // 用户代码结束：USART3_MspDeInit 1
  }
} 

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
