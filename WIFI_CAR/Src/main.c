/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "usart1.h"
#include "usart2.h"
#include "usart3.h"
#include "string.h"
#include "atk_mw8266d.h"
#include "state_reg.h" 
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define _DELAY_1000MS_   ((DELAY_NUM%1000)==0)
#define _DELAY_2500MS_   ((DELAY_NUM%2500)==0)
#define _DELAY_5000MS_   ((DELAY_NUM%5000)==0)
uint32_t DELAY_NUM=0;
uint32_t CNT=0;
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void START_DELAY(void);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
  // 用户代码开始，可以添加自定义的初始化代码
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/
  // MCU 配置

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  // 重置所有外设，初始化 Flash 接口和 SysTick
  HAL_Init();

  /* USER CODE BEGIN Init */
  // 用户代码开始，可以添加自定义的初始化代码
  /* USER CODE END Init */

  /* Configure the system clock */
  // 配置系统时钟
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */
  // 用户代码开始，可以添加自定义的系统初始化代码
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  // 初始化所有配置的外设
  MX_GPIO_Init();
  MX_ADC1_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  MX_USART3_UART_Init();

  /* USER CODE BEGIN 2 */
  // 用户代码开始，可以添加自定义的代码
  usart1.initialize(115200);
  usart2.initialize(115200);	
  usart3.initialize(115200);	

  // 自定义代码块1
  ///////////////////////////////////////////////////////
  usart1.printf("usart1 is Running!\r\n");
  HAL_Delay(2000);
  //usart2.printf("usart2 is Running!\r\n");
  HAL_GPIO_WritePin (LED0_GPIO_Port, LED0_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin (LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);
  atk_mw8266d_init();

  // 自定义代码块2
  ///////////////////////////////////////////////////////
  /* USER CODE END 2 */

  /* Infinite loop */
  // 无限循环
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    START_DELAY();
    UART2_COMMAND_PROCESSING();
    if(_DELAY_1000MS_)
    {
      //HAL_GPIO_TogglePin(LED0_GPIO_Port, LED0_Pin);
      HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
      do_query_state();
      GetVolt();
    }
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    // 用户代码开始，可以添加自定义的代码
    //HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** 初始化CPU、AHB和APB总线时钟 */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** 初始化CPU、AHB和APB总线时钟 */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void START_DELAY(void)
{
    // 调用HAL_Delay函数进行延时，参数为0表示不进行实际延时
	HAL_Delay(0);
	// 将DELAY_NUM的值加1
	DELAY_NUM = DELAY_NUM + 1;
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  // 用户可以在此添加自己的实现，以报告HAL错误返回状态
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  // 用户可以添加自己的实现来报告文件名和行号
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
