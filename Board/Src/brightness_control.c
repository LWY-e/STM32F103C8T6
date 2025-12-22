#include "brightness_control.h"
#include "stm32f1xx_hal_tim.h"
#include "tim.h"

extern TIM_HandleTypeDef htim3;

void LED_Init(void){
    // PWM 신호 발생 시작
    HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_1);
}

void LED_SetBrightness(uint8_t duty_cycle){
    // 0 ~ 100 사이 값으로 제한 ( 안정장치 )
    if(duty_cycle > 100) duty_cycle = 100;

    // Counter Period가 99이므로, 0~100 값을 넣으면 듀티비가 맞음
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, duty_cycle);
}