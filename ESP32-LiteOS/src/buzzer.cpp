#include "inc.h"

#define BUZZER GPIO_NUM_0

extern float temprature;
extern float humidity;
extern int smoke_number;
extern int light_status;

/**
 * @brief 蜂鸣器初始化
 */
void buzzer_init()
{
  pinMode(BUZZER, OUTPUT);
  // 默认静音
  digitalWrite(BUZZER, HIGH);
}

/**
 * @brief 蜂鸣器工作
 */
void buzzer_work()
{
  if (temprature > 30 || smoke_number > 300) {
    digitalWrite(BUZZER, LOW);
  } else {
    digitalWrite(BUZZER, HIGH);
  }
}
