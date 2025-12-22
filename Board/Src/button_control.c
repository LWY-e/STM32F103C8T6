#include "button_control.h"

// 이전 버튼 상태를 저장하여 디바운싱(Debouncing) 역할을 합니다.
// 버튼을 한번만 눌렀을 때 여러 번 토글되는 것을 방지합니다.
static GPIO_PinState prev_button_state = GPIO_PIN_SET;

/**
  * @brief  사용자 버튼의 상태를 확인하고 LED 동작을 제어합니다.
  * 버튼이 눌릴 때(Low)만 LED를 토글하고 디바운싱 로직을 적용합니다.
  * @param  None
  * @retval None
  */
void Check_Button_And_Toggle_LED(void)
{
    // 1. 현재 버튼 상태 읽기 (버튼이 눌리면 GPIO_PIN_RESET, 풀업 저항 설정 가정)
    // CubeMX에서 생성된 버튼 GPIO 포트와 핀 이름을 사용합니다.
    GPIO_PinState current_button_state = HAL_GPIO_ReadPin(button_GPIO_Port, button_Pin);

    // 2. 버튼 상태 확인 및 토글 로직
    // (이전 상태는 High(눌리지 않음)였고, 현재 상태는 Low(눌림)인 경우)
    if (prev_button_state == GPIO_PIN_SET && current_button_state == GPIO_PIN_RESET)
    {
        // 버튼이 '눌리는 순간' 감지! (Falling Edge)

        // LED 토글 (LED_GPIO_Port와 LED_Pin은 main.h에 정의되어 있어야 함)
        HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);

        // 짧은 지연을 주어 디바운싱 효과를 강화합니다.
        HAL_Delay(50); 
    }

    // 3. 현재 상태를 이전 상태로 업데이트
    prev_button_state = current_button_state;
}