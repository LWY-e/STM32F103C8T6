#include "app_main.h"
#include "brightness_control.h"
#include "main.h"      // HAL 라이브러리와 huart1 선언을 가져오기 위해 필요
#include <stdlib.h> 
#include <stdio.h>
#include <string.h>

// [추가] main.c에 정의된 huart1 변수를 이 파일에서도 쓰겠다고 선언
extern UART_HandleTypeDef huart1; 

void App_Init(void){
    LED_Init();
}

void App_Process_Command(char* cmd){
    int brightness = atoi(cmd);
    
    // [확인용] 받은 숫자를 다시 돌려보내기
    char debug_msg[25];
    sprintf(debug_msg, "SET:%d\n", brightness);
    
    // 이제 huart1을 인식할 수 있습니다.
    HAL_UART_Transmit(&huart1, (uint8_t*)debug_msg, strlen(debug_msg), 10);

    LED_SetBrightness((uint8_t)brightness);
}