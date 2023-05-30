/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "control_servo.h"
#include "inverse_kinematic.h"
#include "hexapod.h"
#include "PID.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
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

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/*================== KHAI BAO BIEN ==================*/
	uint8_t rx_angle[2];
	int16_t angle;							// goc cua robot do la ban tra ve
	uint8_t cmd_la_ban;					// bien chua lenh lay data tu la ban, = a : reset la ban, = z : doc la ban
	uint8_t reset_angle = 'a';	// reset la ban
	uint8_t num;
	
	int8_t rx_ros[6];
	uint8_t cout;
	uint8_t get_data;
	
	uint8_t tx_ros[4]={0x02,0,0,0x03};
	
	float angle_output;
/*================== HAM XU LY LA BAN ==================*/
	void read_angle_tx(void)
	{
		if(num++>10)
		{
			HAL_UART_Transmit(&huart2, &cmd_la_ban, 1, 10);
			num = 0;
		}
	}
	
	int16_t _abs(int16_t data)
	{
		if(data<0)
			data = -data;
		return data;
	}
	
	void read_angle_rx(void)
	{
		angle = (rx_angle[0]<<8 | rx_angle[1]);
		while(_abs(angle)>3600)
		{
			angle = angle % 3600;
		}
	}
	
	/*================== HAM TRUYEN NHAN DU LIEU ==================*/
	void rx_angle_ros(void)
	{
		if(cout == 0 && get_data != 0x04)
			return;
		
		if(cout == 5 && get_data != 0x05)
		{
			cout = 0;
			return;
		}
		
		if(cout == 5 && get_data == 0x05)
		{
			cout = 0;
		}
		else
		{
			rx_ros[cout] = get_data;
			cout++;
		}
	}
	
	void tx_imu_ros(void)
	{
		tx_ros[1] = angle>>8;
		tx_ros[2] = angle;
		HAL_UART_Transmit(&huart3,tx_ros ,sizeof(tx_ros),10);
	}
	/*void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
	{
		if(huart->Instance == USART2)
		{
			read_angle_rx();
			HAL_UART_Receive_IT(&huart2, rx_angle, 1);
		}
	}*/
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
	theta_leg_1_last.theta_1 = 90;
	theta_leg_1_last.theta_2 = 90;
	theta_leg_1_last.theta_3 = 90;
	
	theta_leg_2_last.theta_1 = 90;
	theta_leg_2_last.theta_2 = 90;
	theta_leg_2_last.theta_3 = 90;
	
	theta_leg_3_last.theta_1 = 90;
	theta_leg_3_last.theta_2 = 90;
	theta_leg_3_last.theta_3 = 90;
	
	theta_leg_4_last.theta_1 = 90;
	theta_leg_4_last.theta_2 = 90;
	theta_leg_4_last.theta_3 = 90;
	
	theta_leg_5_last.theta_1 = 90;
	theta_leg_5_last.theta_2 = 90;
	theta_leg_5_last.theta_3 = 90;
	
	theta_leg_6_last.theta_1 = 90;
	theta_leg_6_last.theta_2 = 90;
	theta_leg_6_last.theta_3 = 90;
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_USART2_UART_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  MX_TIM5_Init();
  MX_TIM8_Init();
  MX_UART4_Init();
  MX_USART1_UART_Init();
  MX_USART3_UART_Init();
  /* USER CODE BEGIN 2 */
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
	
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);
	
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);
	
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);
	
	HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_3);
	
	HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_3);
	
	HAL_UART_Receive_DMA(&huart2, rx_angle, 2);
	HAL_UART_Receive_DMA(&huart3, &get_data, 1);
	cmd_la_ban = 'a';
	HAL_Delay(50);
	cmd_la_ban = 'z';
	HAL_Delay(50);
	
	LEG_1(90, 90, 90);
	LEG_2(90, 90, 90);
	LEG_3(90, 90, 90);
	LEG_4(90, 90, 90);
	LEG_5(90, 90, 90);
	LEG_6(90, 90, 90);
	HAL_Delay(5000);
	
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		cmd_la_ban = 'z';
		
		//RUN_HEXAPOD((float)rx_ros[1], (float)rx_ros[2], 7, angle_output, rx_ros[4]);
		RUN_HEXAPOD((float)rx_ros[1], (float)rx_ros[2], 7, (float)rx_ros[3], rx_ros[4]);
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

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
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
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
