//
// Created by Jwxa-Desktop on 2023/3/11.
//

#ifndef __HASSDEVICEMANAGER_H__
#define __HASSDEVICEMANAGER_H__

using namespace std;
#include <cJSON.h>

typedef struct hass_device_t
{
	char* entity_id;
	char* type;
	char* friendly_name;
} hass_device_t;

typedef struct hass_device_info_t : hass_device_t
{
	const char* img_src;
	int device_type;
	bool is_on_off;
	bool is_set_value;
} hass_device_info_t;

class HassDeviceManager
{
 public:
	static void Init();
	static void Deinit();
	static void hass_device_task_create();
	static void hass_device_task_delete();
	void static onHassDeviceSyncEvent(char* msg_body);
	static bool readHassDeviceNumFromNvs(uint16_t* hass_device_arr_length_ptr);
	static bool readHassDeviceFromNvs(hass_device_t hass_device_arr[], uint16_t hass_device_arr_length);
	static bool writeHassDeviceIntoNvs(char* device_info_json);
	static bool eraseAllHassDeviceInfoFromNvs();
	static uint16_t getAllDeviceNum();
	static uint16_t getAllDeviceList(hass_device_info_t hass_device_info_arr[], uint16_t hass_device_info_arr_length);
 private:
	static char* getValueFromJsonObj(const cJSON* cJson,const char* attribute_name);
};

#endif //__HASSDEVICEMANAGER_H__
