/**
  ******************************************************************************
  * @file    I2C/EEPROM/stm32f4xx_it.c 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    30-September-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_it.h"
#include "usart.h"

/** @addtogroup STM32F4xx_StdPeriph_Examples
  * @{
  */

/** @addtogroup I2C_EEPROM
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
//Systick variables
extern volatile uint8_t status_10ms;
extern volatile uint8_t status_50ms;
volatile uint16_t counter_10ms;
volatile uint16_t counter_50ms;

//usart variabls
extern volatile uint8_t usart_buffer_pointer;
extern volatile uint8_t usart_receive_buffer[256];
extern volatile uint8_t usart_command_status;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M4 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief   This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
	if(counter_10ms)
	{
		counter_10ms--;
	}
	else
	{
		counter_10ms = 1 - 1;
		status_10ms = 1;
	}
	if(counter_50ms)
	{
		counter_50ms--;
	}
	else
	{
		counter_50ms = 5 - 1;
		status_50ms = 1;
	}
}

/******************************************************************************/
/*                 STM32F4xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f4xx.s).                                               */
/******************************************************************************/
void USARTx_IRQHANDLER(void)
{
  if(USART_GetITStatus(Open_USARTx, USART_IT_RXNE) != RESET)
  { 
  	//USART_ClearITPendingBit(USART2,USART_IT_RXNE);
		//printf("\n\rUSART Hyperterminal Interrupts Receive a word: %c\n\r",USART_ReceiveData(Open_USARTx));
		
		///Read the next character from the UART and write it back to the UART.
		usart_receive_buffer[usart_buffer_pointer] = USART_ReceiveData(Open_USARTx);
		USART_SendData(Open_USARTx, (uint8_t)usart_receive_buffer[usart_buffer_pointer]);
		
		// Respond to CR
		if(usart_receive_buffer[usart_buffer_pointer] == '\r')
		{
			//UARTCharPutNonBlocking(UART0_BASE,'\n');
			usart_command_status = 1;
		}
		// Respond to DEL
		else if(usart_receive_buffer[usart_buffer_pointer] == 127)
		{
			if(usart_buffer_pointer)
				usart_buffer_pointer--;
		}
		//ignore the control symbols
		else if(usart_receive_buffer[usart_buffer_pointer] > 31)
			usart_buffer_pointer++;
  }
}

void TIM4_IRQHandler(void)  
{    
	if(TIM4->SR&0X0001)//10ms定时中断
	{   
		printf("Int!\r\n");
//		  TIM4->SR&=~(1<<0);                                         //===清除定时器1中断标志位		 
//		  Encoder=Read_Encoder(2);                                  //===读取编码器的位置数据 初始值是10000，详见encoder.c 和encoder.h
//  		Led_Flash(100);                                           //===LED闪烁;指示单片机正常运行	
//		  Moto1=Position_PID(Encoder,Target_position);              //===位置PID控制器
//		  Xianfu_Pwm();                                             //===PWM限幅
//    	Set_Pwm(Moto1);                                          //===赋值给PWM寄存器  
	}       	
} 

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 

/**
  * @}
  */ 

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
