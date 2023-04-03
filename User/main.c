#include "main.h"
#include <stdio.h>
#include "systickms.h" 
#include "keypad.h"
#include "LCD_ILI9325.h"

#include "Saper.h"
 
void SystemClock_Config(void);

int main(void)
{
	SystemClock_Config();
	Init_keypad();
	Init_systickms();    
  init_lcd_ili9325();   
	uint16_t i;
  init_game(10);
  draw_all();
	counting_empty();
	while (1)
		if(systickms.readflag50ms())
		{
			uint32_t keycode = keypad_poll();
			if(keycode)
				for(i=0;i<16;i++)
					if(keycode&(1<<i))
						process_input(i + 1);
		}
}

/**
@brief  уст. такт. 72МГц 
<pre>
	System Clock source            = PLL (HSE) 
	SYSCLK(Hz)                     = 72000000
	HCLK(Hz)                       = 72000000
	AHB Prescaler                  = 1
	APB1 Prescaler                 = 2
	APB2 Prescaler                 = 1
	HSE Frequency(Hz)              = 8000000
	HSE PREDIV                     = 1
	PLLMUL                         = RCC_PLL_MUL9 (9)
	Flash Latency(WS)              = 2
</pre>
*/
void SystemClock_Config(void)
{
	LL_FLASH_SetLatency(LL_FLASH_LATENCY_2); 
	LL_RCC_HSE_Enable(); 
	while(LL_RCC_HSE_IsReady() != 1) 
	{
	};
	LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSE_DIV_1, LL_RCC_PLL_MUL_9);
	LL_RCC_PLL_Enable();
	while(LL_RCC_PLL_IsReady() != 1)
	{
	};
	LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
	LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);
	while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL)
	{
	};
	LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_2);
	LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_1); 
	LL_Init1msTick(72000000);
	LL_SetSystemCoreClock(72000000);
}
///@}
