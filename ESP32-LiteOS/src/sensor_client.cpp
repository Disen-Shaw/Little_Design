#include "inc.h"

// 全局变量 环境信息
extern float temprature;
extern float humidity;
extern int smoke_number;
extern int light_status;

// ESP8266 服务器信息
const char* sensor_host = "192.168.43.72";
const int http_port = 80;

/**
 * @brief 向ESP8266 结点发送HTTP请求
 */
void http_request(void)
{
  WiFiClient client;
  String http_request = String("GET /") + " HTTP/1.1\r\n" + "Host: " + sensor_host + "\r\n" + "Connection: close\r\n\r\n";

  Serial.print("Connecing to ");
  Serial.println(sensor_host);

  if (client.connect(sensor_host, 80)) {
    Serial.println("Connected to ESP8266 Server!");
    client.print(http_request);
    Serial.println("======================================================");
    Serial.println("Sending Request: ");
    Serial.print(http_request);

    // 获取响应
    String status_response = client.readStringUntil('\n');
    Serial.print("status_response: ");
    Serial.println(status_response);

    // 使用find跳过HTTP响应头
    if (client.find("\r\n\r\n")) {
      Serial.println("Found Header End. Start Parsing.");
    }

    parse_info(client);
  } else {
    Serial.println("Connect to ESP8266 Failed");
  }
  client.stop();
}

/**
 * @brief 解析json文件
 *
 * @param client
 */
void parse_info(WiFiClient client)
{
  StaticJsonDocument<192> doc;
  DeserializationError error = deserializeJson(doc, client);
  if (error) {
    Serial.print("deserializeJson() failed: ");
    Serial.println(error.c_str());
    return;
  }
  const char* Temprature = doc["Temprature"];        // "24.80"
  const char* Humidity_ = doc["Humidity: "];         // "95.00"
  const char* Smoke_Number_ = doc["Smoke_Number: "]; // "77"
  const char* Light_Status_ = doc["Light_Status: "]; // "1"

  temprature = atof(Temprature);
  humidity = atof(Humidity_);
  smoke_number = atof(Smoke_Number_);
  light_status = atof(Light_Status_);
}
