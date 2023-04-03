/*stm32f3xx_it.c*/
#include "stm32f3xx_it.h"
#include "systickms.h"
/*            Cortex-M4 Processor Exceptions Handlers                         */
void NMI_Handler(void)
{
}

void HardFault_Handler(void)
{
	while (1)
	{
	}
}

void MemManage_Handler(void)
{
	while (1)
	{
	}
}

void BusFault_Handler(void)
{
	while (1)
	{
	}
}

void UsageFault_Handler(void)
{
	while (1)
	{
	}
}

void SVC_Handler(void)
{
}

void DebugMon_Handler(void)
{
}

void PendSV_Handler(void)
{
}

void USER_BUTTON_IRQHANDLER(void)
{
  /* Manage Flags */
  if(LL_EXTI_IsActiveFlag_0_31(USER_BUTTON_EXTI_LINE) != RESET)
  {
    LL_EXTI_ClearFlag_0_31(USER_BUTTON_EXTI_LINE);
    LL_GPIO_TogglePin(GPIOE, LED3_PIN|LED4_PIN|LED5_PIN|LED6_PIN
							|LED7_PIN|LED8_PIN|LED9_PIN|LED10_PIN);  
  }
}



void SysTick_Handler(void)
{
	systickms.cnt1ms();
}
