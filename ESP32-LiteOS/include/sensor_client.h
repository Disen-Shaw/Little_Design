#ifndef __SENSOR_CLIENT_H__
#define __SENSOR_CLIENT_H__
#include <Arduino.h>
#include <WiFiClient.h>

void http_request(void);
void parse_info(WiFiClient client);
#endif
