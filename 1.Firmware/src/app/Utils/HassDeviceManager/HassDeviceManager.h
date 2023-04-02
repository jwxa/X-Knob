//
// Created by Jwxa-Desktop on 2023/3/11.
//

#ifndef HASSDEVICEMANAGER_HASSDEVICEMANAGER_H_
#define HASSDEVICEMANAGER_HASSDEVICEMANAGER_H_

using namespace std;
#include <cJSON.h>
#include <map>
#include "app/Utils/AccountSystem/Account.h"

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

typedef struct hass_device_light_t : public hass_device_info_t
{
	int brightness;
	int color_temp;
} hass_device_light_t;

typedef struct hass_device_switch_t : public hass_device_info_t
{

} hass_device_switch_t;

typedef struct hass_device_media_player_t : public hass_device_info_t
{
//	char* state;//paused
	char* media_title;
	uint16_t volume_level;
} hass_device_media_player_t;

typedef struct hass_device_event{
	const char* entity_id;
	const char* action;
	const char* state;
} hass_device_event;

class HassDeviceManager
{
 public:
	static void Init();
	static void Deinit();
	static void hass_device_task_init();
	static void hass_device_task_delete();
	static void onHassDeviceSyncEvent(char* msg_body);
	static void onHassDeviceStateUpdateEvent(char* msg_body);
	static bool readHassDeviceNumFromNvs(uint16_t* hass_device_arr_length_ptr);
	static bool readHassDeviceFromNvs(hass_device_t hass_device_arr[], uint16_t hass_device_arr_length);
	static bool writeHassDeviceIntoNvs(char* device_info_json);
	static bool eraseAllHassDeviceInfoFromNvs();
	static uint16_t getAllDeviceNum();
	static uint16_t getAllDeviceList(hass_device_info_t hass_device_info_arr[], uint16_t hass_device_info_arr_length);
	static void turnOnLight(const char* entity_id);
	static void turnOffLight(const char* entity_id);
	static void toggleLight(const char* entity_id,std::map<std::string, std::string> property_map);
	static void turnOnSwitch(const char* entity_id);
	static void turnOffSwitch(const char* entity_id);

 private:
	static char* getValueFromJsonObj(const cJSON* cJson,const char* attribute_name);
	static void callService(const char* entity_id,
		const char* domain,
		const char* service,
		std::map<std::string, std::string> property_map);
};

#endif //HASSDEVICEMANAGER_HASSDEVICEMANAGER_H_
