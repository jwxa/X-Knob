#if XK_MQTT
#include <Arduino.h>
#include "secrets.h"
#include <PubSubClient.h>
#include <WiFi.h>
#include "config.h"
#include "hal/hal.h"
#include "cJSON.h"
#include "app/Utils/HassDeviceManager/HassDeviceManager.h"

WiFiClient wifi_client;
PubSubClient mqtt_client(wifi_client);
int mqtt_last_connect_time_ = 0;

void mqttCallback(char* topic, const byte* payload, unsigned int length)
{
//	printf("mqttCallback: Message arrived [%s] ,length:%u \n", topic, length);
	String readString = "";
	for (int i = 0; i < length; i++)
	{
		readString += (char)payload[i];
	}
	const char* json = readString.c_str();
//	printf("mqttCallback: Message: %s\n", json);
	cJSON* pJsonRoot = cJSON_Parse(json);
	if (pJsonRoot == NULL)
	{
		printf("mqttCallback: json parse error, return\n");
		// 释放cJSON_CreateObject ()分配出来的内存空间
		cJSON_Delete(pJsonRoot);
		return;
	}

	cJSON* pJsonMsgType = cJSON_GetObjectItem(pJsonRoot, "msg_type");
	if (pJsonMsgType == NULL || !cJSON_IsString(pJsonMsgType))
	{
		printf("mqttCallback: json pJsonMsgType not found, return\n");
		// 释放cJSON_CreateObject ()分配出来的内存空间
		cJSON_Delete(pJsonRoot);
		return;
	}

	char* msg_type = cJSON_GetStringValue(pJsonMsgType);
//	printf("mqttCallback: msg_type:%s\n", msg_type);

	cJSON* pJsonMsgBody = cJSON_GetObjectItem(pJsonRoot, "msg_body");
	if (pJsonMsgBody == NULL)
	{
		printf("mqttCallback: json pJsonMsgBody not found, return\n");
		printf("mqttCallback: Message: %s\n", json);
		// 释放cJSON_CreateObject ()分配出来的内存空间
		cJSON_Delete(pJsonRoot);
		return;
	}
	char* msg_body = cJSON_Print(pJsonMsgBody);
	if (strcmp(msg_type, "hass_device_sync") == 0)
	{
		//同步ha设备到X-Knob中
		HassDeviceManager::onHassDeviceSyncEvent(msg_body);
	}
	else if(strcmp(msg_type, "hass_device_event") == 0)
	{
		//更新X-Knob中的设备状态
		HassDeviceManager::onHassDeviceStateUpdateEvent(msg_body);
	}
	else if (strcmp(msg_type, "hass_device_state_sync") == 0)
	{
		//X-Knob定时发起的给nodered的请求,让其将最新的设备状态更新给X-Knob(通过hass_device_event),无需处理
	}
	else if (strcmp(msg_type, "hass_device_control") == 0)
	{
		//X-Knob定时发起的给nodered的请求,让其请求HA call service,无需处理
	}
	else
	{
//		printf("mqttCallback: unknown msg_type, return\n");
	}
	// 释放cJSON_CreateObject ()分配出来的内存空间
	cJSON_Delete(pJsonRoot);
	// 释放msg
	cJSON_free(msg_body);
}

void connectMQTT()
{
	if (WiFi.status() != WL_CONNECTED)
	{
		printf("connectMQTT need wifi_connected\n");
		return;
	}
	printf("Attempting MQTT connection...\n");
#ifdef MQTT_PASSWORD
	bool result = mqtt_client.connect(MQTT_USER, MQTT_USER, MQTT_PASSWORD);
#else
	bool result = mqtt_client.connect(MQTT_USER);
#endif
	if (result)
	{
		printf("MQTT connected\n");
		//连上mqtt后自动绑定
		char topic_name[128];
		snprintf(topic_name, sizeof(topic_name), "%s/HOME/device/#", MQTT_HOST);
		printf("Hass: hass_hal_init mqtt_subscribe topic_name:%s\n",topic_name);
		HAL::mqtt_subscribe(topic_name);
	}
	else
	{
		printf("MQTT failed rc=%d will try again in 5 seconds\n", mqtt_client.state());
	}
}

TaskHandle_t handleTaskMqtt;
void TaskMqttUpdate(void* pvParameters)
{
	while (1)
	{
		long now = millis();
		if (!mqtt_client.connected() && (now - mqtt_last_connect_time_) > 5000)
		{
			printf("Reconnecting MQTT\n");
			mqtt_last_connect_time_ = now;
			connectMQTT();
		}
		mqtt_client.loop();
		delay(5);
	}
}

bool HAL::is_mqtt_connected()
{
	return mqtt_client.connected();
}

int HAL::mqtt_subscribe(const char* topic)
{
	bool ret = mqtt_client.subscribe(topic);
	if (!ret)
	{
		printf("Subscribe Error to topic:%s\n", topic);
	}
	return ret;
}

int HAL::mqtt_unsubscribe(const char* topic)
{
	bool ret = mqtt_client.unsubscribe(topic);
	if (!ret)
	{
		printf("Unsubscribe Error to topic:%s\n", topic);
	}
	return ret;
}

int HAL::mqtt_publish(const char* topic, const char* playload)
{
	if (!is_mqtt_connected())
	{
		return 0;
	}
	bool ret = mqtt_client.publish(topic, playload);
	if (!ret)
	{
		printf("Publish Error: topic:%s, playload:%s\n", topic, playload);
	}
	return ret;
}

void HAL::mqtt_init()
{
	mqtt_client.setServer(MQTT_SERVER, MQTT_PORT);
	mqtt_client.setCallback(mqttCallback);
	mqtt_client.setBufferSize(1024 * 5);
	mqtt_client.setKeepAlive(60000);
	xTaskCreatePinnedToCore(
		TaskMqttUpdate,
		"MqttThread",
		4096,
		nullptr,
		2,
		&handleTaskMqtt,
		ESP32_RUNNING_CORE);
}
#endif