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
uint8_t wifi_config_flag;
nvs_wifi_config_t nvsWifiConfig;

void TaskWifiUpdate(void *pvParameters) {
	while(1) {
		long now = millis();
		if (WiFi.status() != WL_CONNECTED && (now - wifi_last_connect_time) > 5000) {
			printf("Reconnecting Wifi\n");
			wifi_last_connect_time = now;
			if (wifi_config_flag == WIFI_CONFIGURED){
				setup_wifi(nvsWifiConfig);
			}else{
				setup_wifi();
			}
		}
		delay(5);
	}
}

void HAL::wifi_init()
{
	wifi_config_flag = check_wifi_config_in_nvs(&nvsWifiConfig);
	ESP_LOGI(TAG, "setup_wifi task");
	xTaskCreatePinnedToCore(
		TaskWifiUpdate,
		"WifiThread",
		4096,
		nullptr,
		2,
		&handleTaskWifi,
		ESP32_RUNNING_CORE);
}

static uint8_t check_wifi_config_in_nvs(nvs_wifi_config_t* nvsWifiConfig)
{
	nvs_handle_t wifi_config_get_handle;
	wifi_config_t wifi_config;
	esp_err_t err;
	uint8_t u8WifiConfigVal = 0;
	uint8_t u8Ssid[33] = { 0 };
	uint8_t u8Password[65] = { 0 };
	size_t Len = 0;
	uint8_t u8GetWifiFlag = 0;

	bzero(&wifi_config, sizeof(wifi_config_t));

	nvs_open(WIFI_CONFIG_STORAGE_NAMESPACE, NVS_READWRITE, &wifi_config_get_handle);
	nvs_get_u8(wifi_config_get_handle, "WifiConfigFlag", &u8WifiConfigVal);
	printf("wifi: check_wifi_config_in_nvs, wifi_config val:%X \r\n", u8WifiConfigVal);
	if (u8WifiConfigVal == WIFI_CONFIGURED)
	{
		Len = sizeof(u8Ssid);
		err = nvs_get_str(wifi_config_get_handle, "SSID", (char*)u8Ssid, &Len);
		if (err == ESP_OK)
		{
			memcpy(wifi_config.sta.ssid, u8Ssid, sizeof(wifi_config.sta.ssid));
			ESP_LOGI(TAG, "ssid:%s,len:%d", u8Ssid, Len);
			u8GetWifiFlag++;
		}
		Len = sizeof(u8Password);
		err = nvs_get_str(wifi_config_get_handle, "PASSWORD", (char*)u8Password, &Len);
		if (err == ESP_OK)
		{
			memcpy(wifi_config.sta.password, u8Password, sizeof(wifi_config.sta.password));
			ESP_LOGI(TAG, "password:%s,len:%d", u8Password, Len);
			u8GetWifiFlag++;
		}
		nvs_close(wifi_config_get_handle);
		nvsWifiConfig->ssid = (char*)wifi_config.sta.ssid;
		nvsWifiConfig->password = (char*)wifi_config.sta.password;
		return u8WifiConfigVal;
	}
	else
	{
		nvs_close(wifi_config_get_handle);
		return u8WifiConfigVal;
	}
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
	}else{
		printf("connect to network %s Success\n", ssid);
	}
}

void setup_wifi(nvs_wifi_config_t wifiConfig)
{
	char* ssid = wifiConfig.ssid;
	printf("connecting to WiFi..: %s\n", ssid);
	WiFi.begin(ssid, wifiConfig.password);
	while (WiFi.status() != WL_CONNECTED)
	{
		printf(".");
		delay(500);
	}
	printf("Connected to network %s\n", ssid);
}