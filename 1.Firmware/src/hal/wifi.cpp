//
// Created by Jwxa-Desktop on 2023/3/12.
//
#include <esp_wifi.h>
#include <WiFi.h>
#include "hal.h"
#include "nvs.h"
#include "wifi.h"
#include "secrets.h"

TaskHandle_t handleTaskWifi;
int wifi_last_connect_time = 0;
void TaskWifiUpdate(void *pvParameters) {
	while(1) {
		long now = millis();
		if (WiFi.status() != WL_CONNECTED && (now - wifi_last_connect_time) > 5000) {
			printf("Reconnecting WIFI\n");
			wifi_last_connect_time = now;
			setup_wifi();
		}
		delay(5);
	}
}

void HAL::wifi_init()
{
	printf("HAL: wifi setup_wifi\n");
	setup_wifi();
	printf("HAL: wifi create wifi task\n");
	xTaskCreatePinnedToCore(
		TaskWifiUpdate,
		"WifiThread",
		4096,
		nullptr,
		2,
		&handleTaskWifi,
		ESP32_RUNNING_CORE);
}

void setup_wifi()
{
	const char* ssid = WIFI_SSID;
	printf("connecting to WiFi..: %s\n", ssid);
	wl_status_t wlStatus = WiFi.begin(ssid, WIFI_PASSWORD);
	printf("wlStatus: %u\n", wlStatus);
	if (wlStatus != WL_CONNECTED)
	{
		printf("connect to network %s Failed\n", ssid);
	}
	else
	{
		printf("connect to network %s Success\n", ssid);
	}
}