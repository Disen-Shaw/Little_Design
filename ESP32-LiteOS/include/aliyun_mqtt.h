/**
 * @file aliyun_mqtt.h
 * @brief 阿里云MQTT连接
 * @author Disen Shaw
 * @version V0.1
 * @date 2022-05-24
 */
#ifndef __ALIYUN_MQTT_H__
#define __ALIYUN_MQTT_H__
#include "inc.h"

void static aliyun_connect(void);
void static aliyun_ctrl_local(void);
void static work_mode_ctl(JsonVariant L);
void static fans_ctrl(JsonVariant L);
void aliyun_init(void);
void aliyun_info_update(void);

#endif
