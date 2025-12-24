#include "app_main.h"
#include "brightness_control.h"
// #include "main.h"      // app_main.h에서 이미 포함하므로 주석 처리
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// [추가] main.c에 정의된 huart1 변수를 이 파일에서도 쓰겠다고 선언
extern UART_HandleTypeDef huart1;
extern TIM_HandleTypeDef htim3;

void App_Init(void) { LED_Init(); }

void App_Process_Command(char *rx_buffer) {
  int value = 0;

  // 파이썬에서 "A50\n" 처럼 보낼 때 처리 로직
  if (sscanf((char *)rx_buffer, "A%d", &value) == 1) {
    // 값 범위 제한 (0~100)
    if (value < 0)
      value = 0;
    if (value > 100)
      value = 100;

    // PA6 (TIM3_CH1) PWM 듀티비 설정
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, value);

    // 디버깅 메시지 전송
    char debug_txt[64];
    int len = sprintf(debug_txt, "STM32_ACK: Parsed=%d\r\n", value);
    HAL_UART_Transmit(&huart1, (uint8_t *)debug_txt, len, 100);
  } else {
    HAL_UART_Transmit(&huart1, (uint8_t *)"STM32_ERR: Parse Failed\r\n", 25,
                      100);
  }
}