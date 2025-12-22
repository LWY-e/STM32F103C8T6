#include "blink.h" // 위에서 만든 헤더 파일 포함

// HAL 라이브러리를 사용하여 LED를 토글하는 함수 정의
void Blink_LED(void)
{
    HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
    HAL_Delay(1000); // 500ms 지연
}