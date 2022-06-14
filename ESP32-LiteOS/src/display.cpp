#include "inc.h"

extern float temprature;
extern float humidity;
extern int smoke_number;
extern int light_status;

#define SCREEN_WIDTH 128 // 设置OLED宽度,单位:像素
#define SCREEN_HEIGHT 64 // 设置OLED高度,单位:像素

// 自定义重置引脚,虽然教程未使用,但却是Adafruit_SSD1306库文件所必需的
#define OLED_RESET 4
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void oled_init(void)
{
  // 初始化OLED并设置其IIC地址为 0x3C
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();
}

void static oled_info_display(void)
{
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);

  display.setCursor(0, 0);
  display.print("Temprature: ");
  display.print(temprature);

  display.setCursor(0, 15);
  display.print("Humidity: ");
  display.print(humidity);

  display.setCursor(0, 30);
  display.print("Smoke_Number: ");
  display.print(smoke_number);

  display.setCursor(0, 45);
  display.print("Light_Status: ");
  display.print(light_status);
}

/**
 * @brief 更新屏幕信息
 */
void oled_update(void)
{
  oled_info_display();
  display.display();
}
