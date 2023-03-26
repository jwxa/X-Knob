//
// Created by Jwxa-Desktop on 2023/3/12.
//

#ifndef INC_1_FIRMWARE_SRC_HAL_WIFI_H_
#define INC_1_FIRMWARE_SRC_HAL_WIFI_H_

#define WIFI_CONFIG_STORAGE_NAMESPACE "WIFI_CONFIG"
typedef enum {
	WIFI_NOT_CONFIGURED  = 0,
	WIFI_CONFIGURED   = 0xAA,
} wifi_info_storage_t;

typedef struct
{
	char* ssid;
	const char* password;
} nvs_wifi_config_t;
static uint8_t check_wifi_config_in_nvs(nvs_wifi_config_t* nvsWifiConfig);
static void setup_wifi();
static void setup_wifi(nvs_wifi_config_t param);

#endif //INC_1_FIRMWARE_SRC_HAL_WIFI_H_
