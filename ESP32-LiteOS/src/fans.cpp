#include "inc.h"

#define FANS_PIN_A GPIO_NUM_16
#define FANS_PIN_B GPIO_NUM_17

extern float temprature;
extern float humidity;
extern int smoke_number;
extern int light_status;

extern int work_mode; // 默认自动模式
extern int fans_mode; // 默认关闭

/**
 * @brief 风扇电机初始化
 */
void fans_init(void)
{
  pinMode(FANS_PIN_A, OUTPUT);
  pinMode(FANS_PIN_B, OUTPUT);
  digitalWrite(FANS_PIN_A, LOW);
  digitalWrite(FANS_PIN_B, LOW);
}

/**
 * @brief 风扇电机根据工作模式进行工作
 */
void fans_work(void)
{
  // 自动模式
  if (work_mode == 0) {
    if (smoke_number > 300 || temprature > 30) {
      digitalWrite(FANS_PIN_A, HIGH);
      digitalWrite(FANS_PIN_B, LOW);
    } else {
      digitalWrite(FANS_PIN_A, LOW);
      digitalWrite(FANS_PIN_B, LOW);
    }
  }

  // 手动模式
  if (work_mode == 1) {
    if (fans_mode == 1) {
      digitalWrite(FANS_PIN_A, HIGH);
      digitalWrite(FANS_PIN_B, LOW);
    } else {
      digitalWrite(FANS_PIN_A, LOW);
      digitalWrite(FANS_PIN_B, LOW);
    }
  }
}
