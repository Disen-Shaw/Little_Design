#include "inc.h"

// 感知信息
volatile float temprature = 0;
volatile float humidity = 0;
volatile int smoke_number = 0;
volatile int light_status = 0;

// 受控信息
volatile int work_mode = 0;  // 默认自动模式
volatile bool fans_mode = 0; // 默认关闭

void setup()
{
  Serial.begin(9600); // 串口初始化
  Serial.println("");
  oled_init();
  buzzer_init();
  fans_init();
  wifi_connect();
  aliyun_init();
}

void loop()
{
  http_request();       // 向 ESP8266 发送HTTP 请求
  aliyun_info_update(); // 更新阿里云物联网平台信息
  oled_update();        // OLED 显示更新
  buzzer_work();        // 蜂鸣器工作
  fans_work();          // 风扇电机工作
  delay(1500);
}
