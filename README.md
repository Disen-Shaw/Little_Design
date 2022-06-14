# MQTT IoT

## 介绍

基于 `PlatformIO` 的一个小作品

### 所用到的开发板

+ ESP8266-NodeMCU
+ ESP32-12S

## 主要用到的库

### 上传结点

+ Adafruit_SSD1306 主要用于 OLED 显示
+ arduino-aliyun-iot-sdk-master 用于连接 aliyun 服务器
+ ArduinoJson 用于解析 JSON 数据
+ pubsubclient MQTT相关的功能

### 感知结点

+ DHT sensor library 用于获取DHT11温湿度传感器的值
+ ArduinoJson 用于解析和生成 JSON 数据

## 实现逻辑

通过感知结点获取环境信息，再通过局域网(手机热点)，让上传结点将数据上传到阿里云物联网服务器\
阿里云服务区可以有个调试模式让手机端显示 感知结点的一些信息

