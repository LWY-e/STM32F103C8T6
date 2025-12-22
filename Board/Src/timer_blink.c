#include "timer_blink.h"
#include "main.h" // LED 핀 정의등을 가져오기 위해 
#include "stm32f1xx_hal_gpio.h"

// 타이머 인터럽트에서 호출될 함수
void Toggle_LED_Using_Timer(void)
{
    // 단순히 LED 상태만 반전 ( 시간 지연 x )
    HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
}