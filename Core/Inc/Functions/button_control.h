#ifndef __BUTTON_CONTROL_H
#define __BUTTON_CONTROL_H

// HAL 라이브러리 사용을 위해 main.h 포함 (GPIO 구조체 접근 목적)
#include "main.h"

// 버튼 상태를 확인하고 LED 동작을 제어하는 함수 선언
void Check_Button_And_Toggle_LED(void);

#endif /* __BUTTON_CONTROL_H */