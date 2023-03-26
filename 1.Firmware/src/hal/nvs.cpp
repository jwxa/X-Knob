//
// Created by Jwxa-Desktop on 2023/3/12.
//
#include "hal.h"
#include <stdio.h>
#include "nvs_flash.h"
#include "nvs.h"

void HAL::nvs_init()
{
	// Initialize NVS
	esp_err_t err = nvs_flash_init();
	if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND)
	{
		// NVS partition was truncated and needs to be erased
		// Retry nvs_flash_init
		ESP_ERROR_CHECK(nvs_flash_erase());
		err = nvs_flash_init();
	}
	ESP_ERROR_CHECK(err);
}