/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "spi.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "ILI9341_Driver.h"
#include "Touch.h"
#include "display.h"
#include "fractals.h"
#include "stdio.h"
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
uint8_t buffer[LCD_X_SIZE*LCD_Y_SIZE] = {0};
uint16_t zoom = 100;
int16_t X_OFFSET = LCD_X_SIZE/2;
int16_t Y_OFFSET = LCD_Y_SIZE/2;
enum Fractal_type fractal = MANDELBROT;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void CalcAndDisplayFractal(int16_t offset_x, int16_t offset_y, uint16_t zoom);
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
  //MX_SPI1_Init();
  MX_USART2_UART_Init();
  //MX_SPI2_Init();
  /* USER CODE BEGIN 2 */
  ILI9341_Init();
  Touch_SPI_Init();
  ILI9341_Set_Rotation(0);
  ILI9341_Fill_Screen(BLACK);
  HAL_Delay(500);
  ILI9341_Set_Rotation(SCREEN_HORIZONTAL_2);
  //ILI9341_Draw_Empty_Rectangle(YELLOW, 10, 10, 310, 230);

  //tp_dev.adjust();
  /* Initial display in the middle of the screen */
  CalcAndDisplayFractal(LCD_X_SIZE >> 1, LCD_Y_SIZE >> 1, zoom);

  /* USER CODE END 2 */
 
 

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
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
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 100;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/*
 * Calculate and Display fractal.
 * @params: offset_x: X-axis offset in pixels
 * 			offset_y: Y-axis offset in pixels
 * 				zoom: Zoom factor
 */
void CalcAndDisplayFractal(int16_t offset_x, int16_t offset_y, uint16_t zoom){

	char display_string[15]={' '};

	if (fractal == JULIA)
		GenerateJulia_fpu(LCD_X_SIZE, LCD_Y_SIZE, offset_x, offset_y, zoom, buffer);
	else
		GenerateMandelbrot_fpu(LCD_X_SIZE, LCD_Y_SIZE, offset_x, offset_y, zoom, buffer);

	for (int y = 0; y < LCD_Y_SIZE ; y++)
		for (int x = 0; x < LCD_X_SIZE; x++)
			ILI9341_Draw_Pixel(x, y, buffer[x + y*LCD_X_SIZE]);

	snprintf(display_string, 30, "zoom: %d", zoom );
	ILI9341_Draw_String(0, 0, WHITE, BLACK, display_string, 2);
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){

	if (GPIO_Pin == T_IRQ_Pin){
		HAL_NVIC_DisableIRQ(EXTI1_IRQn);

		if (tp_dev.scan(0)) {
			/* If there is a touch, recalculate the offset and increase the zoom. */
			zoom += 100;
			X_OFFSET += (LCD_X_SIZE >> 1) - tp_dev.x;
			Y_OFFSET += (LCD_Y_SIZE >> 1) - tp_dev.y;
			/* Protection so that we don't fall off the edge (module with double the screen size)
			X_OFFSET = X_OFFSET % (LCD_X_SIZE << 1);
			Y_OFFSET = Y_OFFSET % (LCD_Y_SIZE << 1) */

			CalcAndDisplayFractal(X_OFFSET, Y_OFFSET, zoom);
		}

		HAL_NVIC_EnableIRQ(EXTI1_IRQn);
	}
	else if (GPIO_Pin == BLUE_BUTTON_Pin){
		HAL_NVIC_DisableIRQ(EXTI15_10_IRQn);
		zoom = 100;
		X_OFFSET = LCD_X_SIZE/2;
		Y_OFFSET = LCD_Y_SIZE/2;
		fractal = !fractal;

		CalcAndDisplayFractal(X_OFFSET, Y_OFFSET, zoom);
		HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
	}
	else ;
	HAL_Delay(500);
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
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
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
