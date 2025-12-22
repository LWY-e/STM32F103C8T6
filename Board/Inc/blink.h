#ifndef __BLINK_H
#define __BLINK_H

// HAL 라이브러리를 사용하기 위해 필요
// main.h 에 포함여부 확인 후 main.h include 로 사용가능 
#include "main.h" 

// LED 토글 기능을 수행하는 함수 선언
// 이 함수는 main.c의 while(1) 루프에서 호출될 것입니다.
void Blink_LED(void);

#endif /* __BLINK_H */