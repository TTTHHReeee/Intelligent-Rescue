/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#include "adc.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "MyHeader.h"
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

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  MX_TIM5_Init();
  MX_TIM1_Init();
  MX_TIM8_Init();
  MX_TIM9_Init();
  MX_TIM10_Init();
  MX_TIM11_Init();
  MX_TIM12_Init();
  MX_I2C2_Init();
  MX_USART3_UART_Init();
  MX_ADC1_Init();
  /* USER CODE BEGIN 2 */
	HAL_TIM_Encoder_Start(&htim2,TIM_CHANNEL_1);	
	HAL_TIM_Encoder_Start(&htim2,TIM_CHANNEL_2);
	HAL_TIM_Encoder_Start(&htim3,TIM_CHANNEL_1);	
	HAL_TIM_Encoder_Start(&htim3,TIM_CHANNEL_2);	
	HAL_TIM_Encoder_Start(&htim4,TIM_CHANNEL_1);	
	HAL_TIM_Encoder_Start(&htim4,TIM_CHANNEL_2);	
	HAL_TIM_Encoder_Start(&htim5,TIM_CHANNEL_1);	
	HAL_TIM_Encoder_Start(&htim5,TIM_CHANNEL_2);	
	
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_4);
	HAL_TIM_PWM_Start(&htim9,TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim9,TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim10,TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim11,TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim8,TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim8,TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim8,TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim8,TIM_CHANNEL_4);
	OLED_Init();
	OLED_DisplayTurn(0);
  OLED_ColorTurn(0);

	Robot_Init(Diff_wheelSpacing,0,0,HALL_30F, Photoelectric_500, Black_WheelDiameter);
	Wheel_perimeter = Diff_wheelSpacing*PI;
	int count = 10 ,MPU_DMP_ret;
	while(count--)	//陀螺仪初始化  必须水平初始化
	{
			MPU_DMP_ret = MPU6050_DMP_init();			
			if (MPU_DMP_ret == 0)
			{
				Buzz(100);
				count = 0;
				break;
			}
			else{
					Buzz(10);
			}
	}
  HAL_UART_Receive_IT(&huart2, (uint8_t *)&aRxBuffer2, 1);  //maixcam通信函数
	HAL_TIM_Base_Start_IT((TIM_HandleTypeDef *)&htim12);//定时器开启
	int count_flag = 0;  //球的个数
	int ps_flag = 0;  //按下start为1  切换到ps遥控
	uint8_t V_limit = 2; //挡位
	close();	
	HT();
		 while(1){
				ADC_OLED();
				key_scan();
				if(keyNum == 1){
						OLED_DisPlay_Off();
						break;
				}
		}
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		
		PS2_Read_Data();
			
		if(ps_flag == 0){  //自主模式
				if(PS2_Data.Key_Start == 1){
						ps_flag = 1;
						Buzz(100);
				}
				if(count_flag == 0){			
						while(1) {
								pos_speed = 1.5;  //定距离的速度
								if(moveDistance(0.9) == 1){ 
										count_flag = 1;
										break;
								}
						}
				}
				else if(count_flag == 1){
						if(task_WinBall(1) == 1){
								count_flag = 2;
						}
				}
				else if(count_flag == 2){
						if(task_WinBall(1) == 1){
								count_flag = 3;
						}
				}
				else if(count_flag == 3){
						if(task_WinBall(9) == 1){
								count_flag = 4;
						}
				}
				else if(count_flag == 4){
						if(task_WinBall(9) == 1){
								count_flag = 5;
						}
				}
				else if(count_flag == 5){
						if(task_WinBall(9) == 1){
								count_flag = 6;
						}
				}
				else if(count_flag == 6){
						if(task_WinBall(9) == 1){
								count_flag = 7;
						}
				}
				else if(count_flag == 7){
						if(task_WinBall(9) == 1){
								count_flag = 8;
						}
				}
				else if(count_flag == 8){
						if(task_WinBall(9) == 1){
								count_flag = 9;
						}
				}
				else if(count_flag == 9){
						if(task_WinBall(9) == 1){
								count_flag = 10;
						}
				}
				else if(count_flag == 10){
						if(task_WinBall(9) == 1){
								count_flag = 11;
						}
				}
				else if(count_flag == 11){
						if(task_WinBall(9) == 1){
								count_flag = 12;
						}
				}
				else if(count_flag == 12){
						if(task_WinBall(9) == 1){
								count_flag = 13;
						}
				}
				else if(count_flag == 13){
						if(task_WinBall(9) == 1){
								count_flag = 14;
						}
				}
				else if(count_flag == 14){
						if(task_WinBall(9) == 1){
								count_flag = 15;
						}
				}
				else if(count_flag == 15){
						if(task_WinBall(9) == 1){
								count_flag = 16;
						}
				}
		}
		else if(ps_flag == 1){  //遥控模式
				CarMode = 0;
				if(PS2_Data.Key_L1 == 1){
						V_limit = 3;
				}
				if(PS2_Data.Key_R1 == 1){
						V_limit = 2;
				}
				if(PS2_Data.Key_L2 == 1){
						close();
				}
				if(PS2_Data.Key_R2 == 1){
						open(100);
						TS();
						HT();
				}
				int8_t x_enable  = PS2_Data.Rocker_LY / 127;
				int8_t y_enable = PS2_Data.Rocker_RX / 127;
				
				Set_Pwm(-3000*V_limit*x_enable -2000*y_enable, 3000*V_limit*x_enable-2000*y_enable, MOTOR_C.Motor_Pwm, MOTOR_D.Motor_Pwm);
				HAL_Delay(20);
		}

		
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
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
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
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
