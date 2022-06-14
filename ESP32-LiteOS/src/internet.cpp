#include "inc.h"

// WiFi 连接信息
const char* WIFI_SSID = "EUJTC";
const char* WIFI_PASSWD = "as123456789";

/**
 * @brief 连接 wifi
 */
void wifi_connect(void)
{

  // 网络连接
  WiFi.mode(WIFI_STA);
  Serial.print("Connecting to ");
  Serial.println(WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASSWD);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(". ");
    delay(200);
  }
  Serial.print("Connected to ");
  Serial.println(WiFi.SSID());
  Serial.print("Ip Address: ");
  Serial.println(WiFi.localIP());
}
