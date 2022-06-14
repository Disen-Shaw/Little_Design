#include "ArduinoJson.h"
#include <DHT.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <Ticker.h>

// 传感器采集
Ticker sensor_tiker;

// 传感器设置
int analog_smoke = 0; // 烟雾模拟值
int light_status = 0; // 光照值 1: 光照暗 0: 光照亮
DHT dht11(D3, DHT11); // DHT11 对象
float temprature = 0; // 温度值
float humidity = 0;   // 湿度值

// WiFi 设置
const char* WIFI_SSID = "EUJTC";
const char* WIFI_PASSWD = "as123456789";

// 服务器
ESP8266WebServer esp8266_server(80);

String rootjson()
{
  String json_string = "{\"Temprature\": \"";
  json_string += String(dht11.readTemperature());
  json_string += "\",";
  json_string += "\"Humidity: \": \"";
  json_string += String(dht11.readHumidity());
  json_string += "\",";
  json_string += "\"Smoke_Number: \": \"";
  json_string += String(analogRead(A0));
  json_string += "\",";
  json_string += "\"Light_Status: \": \"";
  json_string += String(digitalRead(D7));
  json_string += "\"";
  json_string += "}";
  return json_string;
}

void handleroot(void)
{
  esp8266_server.send(200, "application/json", rootjson());
}

void setup()
{
  // 传感器初始化
  Serial.begin(9600);
  pinMode(A0, INPUT);
  pinMode(D7, INPUT);
  dht11.begin();

  Serial.println("");
  Serial.println("Sensor Ready");

  // 网络初始化
  Serial.println(WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASSWD);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(". ");
    delay(200);
  }
  Serial.println("");
  Serial.print(WiFi.SSID());
  Serial.println(" Connected");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // 服务器
  esp8266_server.begin();
  esp8266_server.on("/", handleroot);
}

void loop()
{
  esp8266_server.handleClient();
}
