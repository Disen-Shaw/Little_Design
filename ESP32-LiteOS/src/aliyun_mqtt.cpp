#include "inc.h"
static WiFiClient esp_client;

/* {
  "ProductKey": "h6h3grZfn20",
  "DeviceName": "ESP32",
  "DeviceSecret": "8ead64313b1101716fd4c9631b8fbd1d"
} */

extern float temprature;
extern float humidity;
extern int smoke_number;
extern int light_status;
extern bool work_mode;
extern int fans_mode;

#define PRODUCT_KEY "h6h3grZfn20"                        //替换自己的PRODUCT_KEY
#define DEVICE_NAME "ESP32"                              //替换自己的DEVICE_NAME
#define DEVICE_SECRET "8ead64313b1101716fd4c9631b8fbd1d" //替换自己的DEVICE_SECRET
#define REGION_ID "cn-shanghai"                          //默认cn-shanghai

// 更新的信息描述值
char* sign_liteos_temprature = "liteos_temprature";
char* sign_liteos_humidity = "liteos_humidity";
char* sign_liteos_smoke = "liteos_smoke";
char* sign_liteos_light = "liteos_light_status";

char* sign_liteos_workmode = "liteos_workmode";
char* sign_liteos_fans = "liteos_fans";

unsigned long lastMsMain = 0;

/**
 * @brief 连接阿里云 MQTT 服务器
 */
void static aliyun_connect(void)
{
  AliyunIoTSDK::begin(esp_client, PRODUCT_KEY, DEVICE_NAME, DEVICE_SECRET, REGION_ID);
}

/**
 * @brief 检测阿里云 MQTT 服务器的控制信息
 */
void static aliyun_ctrl_local(void)
{
  AliyunIoTSDK::bindData(sign_liteos_workmode, work_mode_ctl);
  AliyunIoTSDK::bindData(sign_liteos_fans, fans_ctrl);
}

/**
 * @brief 设置工作模式
 *
 * @param L
 */
void static work_mode_ctl(JsonVariant L)
{
  work_mode = L[sign_liteos_workmode];
  if (work_mode == 0) {
    pinMode(GPIO_NUM_2, OUTPUT);
    digitalWrite(GPIO_NUM_2, LOW);
  } else {
    pinMode(GPIO_NUM_2, OUTPUT);
    digitalWrite(GPIO_NUM_2, HIGH);
  }
}

void static fans_ctrl(JsonVariant L)
{
  bool status = L[sign_liteos_fans];
  if (status == true) {
    fans_mode = 1;
  } else {
    fans_mode = 0;
  }
}

void aliyun_init(void)
{
  aliyun_connect();
  aliyun_ctrl_local();
}

/**
 * @brief 更新阿里云数据信息
 */
void aliyun_info_update(void)
{
  AliyunIoTSDK::loop(); //必要函数

  if (millis() - lastMsMain >= 2000) //每2秒发送一次
  {
    lastMsMain = millis();

    //发送LED状态到云平台
    AliyunIoTSDK::send(sign_liteos_temprature, temprature);
    AliyunIoTSDK::send(sign_liteos_humidity, humidity);
    AliyunIoTSDK::send(sign_liteos_smoke, smoke_number);
    AliyunIoTSDK::send(sign_liteos_light, light_status);
    AliyunIoTSDK::send(sign_liteos_workmode, work_mode);
    AliyunIoTSDK::send(sign_liteos_fans, fans_mode);
  }
}
