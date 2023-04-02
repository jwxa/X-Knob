//
// Created by Jwxa-Desktop on 2023/3/11.
//
#include <FreeRTOS.h>
#include <cstdio>
#include <cJSON.h>
#include <cstring>
#include <nvs.h>
#include <task.h>
#include <esp32-hal.h>
#include <nvs_flash.h>
#include "HassDeviceManager.h"
#include "config.h"
#include "app/Pages/HASS/HassView.h"
#include "app/Accounts/Account_Master.h"

#define HASS_DEVICE_STORAGE_NAMESPACE "HASS_STORAGE"
const char* HASS_DEVICE_STORAGE_KEY_PREFIX = "HASS_DEVICE:%u";
const char* HASS_DEVICE_NUM_KEY = "HASS_DEVICE_NUM";
TaskHandle_t handleTask;
hass_device_info_t* nvs_hass_device_info_arr;
uint16_t nvs_hass_device_info_arr_length = 0;
bool is_nvs_busy = false;
Account* account;
[[noreturn]] void TaskHassDeviceStateUpdate(void* pvParameters)
{
	printf("TaskHassDeviceStateUpdate start\n");
	bool read_nvs_info_flag = true;
	while (true)
	{
		uint16_t hass_device_arr_length = 0;
		hass_device_t* hass_device_arr;
		if (read_nvs_info_flag)
		{
			//读取hass设备数量
			bool readHassDeviceNumResult = HassDeviceManager::readHassDeviceNumFromNvs(&hass_device_arr_length);
			if (!readHassDeviceNumResult)
			{
				printf("HassDeviceManager: TaskHassDeviceStateUpdate readHassDeviceNumFromNvs failed\n");
			}
			printf("TaskHassDeviceStateUpdate readHassDeviceNumResult:%d\n", readHassDeviceNumResult);
			//读取hass设备信息
			hass_device_arr = new hass_device_t[hass_device_arr_length];
			bool result = HassDeviceManager::readHassDeviceFromNvs(hass_device_arr, hass_device_arr_length);
			if (!result)
			{
				printf("HassDeviceManager: TaskHassDeviceStateUpdate readHassDeviceFromNvs failed");
			}
			read_nvs_info_flag = false;
			nvs_hass_device_info_arr_length = hass_device_arr_length;
			//解析
			auto* hass_device_arr_info_new = new hass_device_info_t[hass_device_arr_length];
			for (int i = 0; i < hass_device_arr_length; ++i)
			{
				hass_device_t hassDevice = hass_device_arr[i];
//					printf("HassDeviceManager: hassDevice type: %s\n", hassDevice.type);
				hass_device_info_t hass_device_info;
				if (strcmp(hassDevice.type, "light") == 0)
				{
					//构建hass页面所需要的数据
					hass_device_info.entity_id = hassDevice.entity_id;
					hass_device_info.type = hassDevice.type;
					hass_device_info.friendly_name = hassDevice.friendly_name;
					hass_device_info.img_src = "home_bulb";
					hass_device_info.device_type = DEVICE;
					hass_device_info.is_on_off = true;
					hass_device_info.is_set_value = true;
//						printf("HassDeviceManager: TaskHassDeviceStateUpdate: light:%s\n", hassDevice.entity_id);
				}
				else if (strcmp(hassDevice.type, "switch") == 0)
				{
					hass_device_info.entity_id = hassDevice.entity_id;
					hass_device_info.type = hassDevice.type;
					hass_device_info.friendly_name = hassDevice.friendly_name;
					hass_device_info.img_src = "home_fan";
					hass_device_info.device_type = DEVICE;
					hass_device_info.is_on_off = true;
					hass_device_info.is_set_value = true;
//						printf("HassDeviceManager: TaskHassDeviceStateUpdate: switch:%s\n", hassDevice.entity_id);
				}
				else
				{
					//todo
				}
				hass_device_arr_info_new[i] = hass_device_info;
			}
			//释放上一次的内存
			delete[] nvs_hass_device_info_arr;
			//重新指向新的数组
			nvs_hass_device_info_arr = hass_device_arr_info_new;
		}
		//开始解析以及发送mqtt获取设备状态
		{
			for (int i = 0; i < nvs_hass_device_info_arr_length; ++i)
			{
				hass_device_info_t hass_device_info = nvs_hass_device_info_arr[i];
				char* entity_id = hass_device_info.entity_id;
				char topic_name[128];
				snprintf(topic_name, sizeof(topic_name), "%s/HOME/device/%s", MQTT_HOST, entity_id);
				struct timeval tp;
				gettimeofday(&tp, NULL);
				long int ms = tp.tv_sec * 1000 + tp.tv_usec / 1000;
				cJSON* root = cJSON_CreateObject();
				cJSON_AddStringToObject(root, "msg_type", "hass_device_state_sync");
				cJSON_AddStringToObject(root, "entity_id", entity_id);
				cJSON_AddNumberToObject(root, "timestamp", ms);
				cJSON_AddStringToObject(root, "msg_body", "");
				char* msg = cJSON_Print(root);
				HAL::mqtt_publish(topic_name, msg);
				//释放cJson的root节点下的所有内存
				cJSON_Delete(root);
				//释放生成的json字符串的内存
				cJSON_free(msg);
			}
			delay(HASS_DEVICE_SYNC_INTERVAL);
		}
	}
}

void HassDeviceManager::Init()
{
	printf("HassDeviceManager: Init\n");
	//定义发布者的buf容量 否则无法发送
	account = new Account("HassDeviceManager", AccountSystem::Broker(), sizeof(hass_device_event), nullptr);
	hass_device_task_init();
}

void HassDeviceManager::Deinit()
{
	hass_device_task_delete();
	if (account)
	{
		delete account;
		account = nullptr;
	}
}

void HassDeviceManager::hass_device_task_init()
{
	printf("HassDeviceManager: hass_device_task_init init hass device task\n");
	if (handleTask != nullptr)
	{
		printf("HassDeviceManager: hass_device_task has already inited, skip\n");
		return;
	}
	xTaskCreatePinnedToCore(
		TaskHassDeviceStateUpdate,
		"HassDeviceManagerThread",
		4096,
		nullptr,
		2,
		&handleTask,
		ESP32_RUNNING_CORE);
}

void HassDeviceManager::hass_device_task_delete()
{
	if (handleTask != nullptr)
	{
		vTaskDelete(handleTask);
		handleTask = nullptr;
		printf("HassDeviceManager: hass_device_task_delete delete hass deivce task completed\n");
	}
}

void HassDeviceManager::onHassDeviceSyncEvent(char* msg_body)
{
	printf("HassDeviceManager: onHassDeviceSyncEvent, msg_body:%s\n", msg_body);
	//想要转换成设备结构体
	//json 转换成为一个数组
	cJSON* pInfoItem = NULL;
	cJSON* pJsonArrayRoot = cJSON_Parse(msg_body);
	if (pJsonArrayRoot == NULL)
	{
		printf("HassDeviceManager: onHassDeviceSyncEvent parse msg_body json object failed, return\n");
		cJSON_Delete(pJsonArrayRoot);
		return;
	}

	int arrayLength = cJSON_GetArraySize(pJsonArrayRoot);
	for (int i = 0; i < arrayLength; i++)
	{
		pInfoItem = cJSON_GetArrayItem(pJsonArrayRoot, i);
		if (pInfoItem == NULL)
		{
			printf("HassDeviceManager: onHassDeviceSyncEvent jsonArray[%u] is blank in loop, continue\n", i);
			continue;
		}

		char* device_info_json = cJSON_Print(pInfoItem);
		hass_device_task_delete();
		bool result = HassDeviceManager::writeHassDeviceIntoNvs(device_info_json);
		//这里需要主动释放的是json生成的字符串的内存
		cJSON_free(device_info_json);
		if (result)
		{
			//写入成功后做点啥?
		}
		hass_device_task_init();
	}
	//释放内存
	cJSON_Delete(pJsonArrayRoot);
}

void HassDeviceManager::onHassDeviceStateUpdateEvent(char* msg_body){
//	printf("HassDeviceManager: onHassDeviceStateUpdateEvent, msg_body:%s\n", msg_body);
	cJSON* pJsonRoot = cJSON_Parse(msg_body);
	if (pJsonRoot == NULL)
	{
		printf("HassDeviceManager: onHassDeviceStateUpdateEvent parse msg_body json object failed, return\n");
		cJSON_Delete(pJsonRoot);
		return;
	}

	cJSON* pJsonAction = cJSON_GetObjectItem(pJsonRoot, "action");
	if (pJsonAction == NULL || !cJSON_IsString(pJsonAction))
	{
		printf("mqttCallback: json action not found, return\n");
		// 释放cJSON_CreateObject()分配出来的内存空间
		cJSON_Delete(pJsonRoot);
		return;
	}
	std::string action = cJSON_GetStringValue(pJsonAction);
//	printf("HassDeviceManager: onHassDeviceStateUpdateEvent, action:%s\n", action);

	cJSON* pJsonEntityId = cJSON_GetObjectItem(pJsonRoot, "entity_id");
	if (pJsonEntityId == NULL || !cJSON_IsString(pJsonEntityId))
	{
		printf("mqttCallback: json entity_id not found, return\n");
		// 释放cJSON_CreateObject()分配出来的内存空间
		cJSON_Delete(pJsonRoot);
		return;
	}
	std::string entity_id = cJSON_GetStringValue(pJsonEntityId);
//	printf("HassDeviceManager: onHassDeviceStateUpdateEvent, entity_id:%s\n", entity_id);

	cJSON* pJsonState = cJSON_GetObjectItem(pJsonRoot, "state");
	if (pJsonState == NULL || !cJSON_IsString(pJsonState))
	{
		printf("mqttCallback: json state not found, return\n");
		// 释放cJSON_CreateObject()分配出来的内存空间
		cJSON_Delete(pJsonRoot);
		return;
	}
	std::string state = cJSON_GetStringValue(pJsonState);
	hass_device_event hassDeviceEvent;
	hassDeviceEvent.entity_id = entity_id.c_str();
	hassDeviceEvent.action = action.c_str();
	hassDeviceEvent.state = state.c_str();
	cJSON_Delete(pJsonRoot);
	//扔到消息系统主题中
	account->Commit((const void*)&hassDeviceEvent, sizeof(hassDeviceEvent));
	account->Publish();
//	printf("HassDeviceManager: onHassDeviceStateUpdateEvent account->Publish\n");
}

bool HassDeviceManager::writeHassDeviceIntoNvs(char* device_info_json)
{
	nvs_handle_t nvs_handle;
	printf("HassDeviceManager: writeHassDeviceIntoNvs start\n");

//	// erase all
//	esp_err_t err = nvs_flash_erase();
//	if (err != ESP_OK)
//	{
//		printf("HassDeviceManager: nvs_flash_erase failed, err_code:%u\n", err);
//	}
//	else
//	{
//		printf("HassDeviceManager: nvs_flash_erase success\n");
//	}
	// Open
	esp_err_t err = nvs_open(HASS_DEVICE_STORAGE_NAMESPACE, NVS_READWRITE, &nvs_handle);
	if (err != ESP_OK)
	{
		printf("HassDeviceManager: writeHassDeviceIntoNvs nvs_open failed, err_code:%u\n", err);
		return false;
	}
	uint16_t u16HassDeviceVal = 0;
	err = nvs_get_u16(nvs_handle, HASS_DEVICE_NUM_KEY, &u16HassDeviceVal);
	if (err == ESP_ERR_NVS_NOT_FOUND)
	{
		u16HassDeviceVal = 0;
		printf("HassDeviceManager: writeHassDeviceIntoNvs nvs storage not found, doesn't matter, create it\n");
	}
	if (err != ESP_ERR_NVS_NOT_FOUND && err != ESP_OK)
	{
		printf("HassDeviceManager: writeHassDeviceIntoNvs nvs_get_u16 failed, err_code:%u\n", err);
		nvs_close(nvs_handle);
		return false;
	}
	else
	{
		printf("HassDeviceManager: writeHassDeviceIntoNvs HASS_DEVICE_NUM:%u\n", u16HassDeviceVal);
	}
	//first key seq is 1
	u16HassDeviceVal++;
	char key[strlen(HASS_DEVICE_STORAGE_KEY_PREFIX) + 2];
	sprintf(key, HASS_DEVICE_STORAGE_KEY_PREFIX, u16HassDeviceVal);
//	hass_device_t hass_device = *hass_device_ptr;
//	printf("HassDeviceManager: hass_device.type:%s\n",hass_device.type);
//	printf("HassDeviceManager: hass_device.entity_id:%s\n", hass_device.entity_id);
//	printf("HassDeviceManager: nvs key:%s, size:%u\n", key, hass_device_size);
//	err = nvs_set_blob(nvs_handle, key, hass_device_ptr, hass_device_size);
	err = nvs_set_str(nvs_handle, key, device_info_json);
	if (err != ESP_OK)
	{
		printf("HassDeviceManager: writeHassDeviceIntoNvs nvs_set_blob failed\n");
		nvs_close(nvs_handle);
		return false;
	}

	err = nvs_set_u16(nvs_handle, HASS_DEVICE_NUM_KEY, u16HassDeviceVal);
	if (err != ESP_OK)
	{
		printf("HassDeviceManager: writeHassDeviceIntoNvs nvs_set_u16 failed\n");
		nvs_close(nvs_handle);
		return false;
	}
	nvs_commit(nvs_handle);
	nvs_close(nvs_handle);
	printf("HassDeviceManager: writeHassDeviceIntoNvs save finished\n");
	return true;
}

bool HassDeviceManager::readHassDeviceNumFromNvs(uint16_t* hass_device_arr_length_ptr)
{
	nvs_handle_t nvs_handle;
	printf("HassDeviceManager: readHassDeviceNumFromNvs start\n");
	esp_err_t err;
	// Open
	err = nvs_open(HASS_DEVICE_STORAGE_NAMESPACE, NVS_READONLY, &nvs_handle);
	if (err == ESP_ERR_NVS_NOT_FOUND)
	{
		printf("HassDeviceManager: readHassDeviceNumFromNvs nvs not found, error_code:%u\n", err);
		return false;
	}
	if (err != ESP_OK)
	{
		printf("HassDeviceManager: readHassDeviceNumFromNvs nvs_read failed, error_code:%u\n", err);
		nvs_close(nvs_handle);
		return false;
	}
	err = nvs_get_u16(nvs_handle, HASS_DEVICE_NUM_KEY, hass_device_arr_length_ptr);
	if (err != ESP_OK)
	{
		printf("HassDeviceManager: readHassDeviceNumFromNvs nvs_get_u16 failed, error_code:%u\n", err);
		nvs_close(nvs_handle);
		return false;
	}
	nvs_close(nvs_handle);
	return true;
}

bool HassDeviceManager::eraseAllHassDeviceInfoFromNvs()
{
	//正在操作则放弃
	if (is_nvs_busy)
	{
		printf("HassDeviceManager: eraseAllHassDeviceInfoFromNvs is executing, skip\n");
		return false;
	}
	is_nvs_busy = true;
	printf("HassDeviceManager: eraseAllHassDeviceInfoFromNvs start\n");
	uint16_t hass_device_arr_length = 0;
	readHassDeviceNumFromNvs(&hass_device_arr_length);
	if (hass_device_arr_length <= 0)
	{
		printf("HassDeviceManager: eraseAllHassDeviceInfoFromNvs hass device number is 0, return\n");
		is_nvs_busy = false;
		return true;
	}

	nvs_handle_t nvs_handle;
	esp_err_t err;
	err = nvs_open(HASS_DEVICE_STORAGE_NAMESPACE, NVS_READWRITE, &nvs_handle);
	if (err == ESP_ERR_NVS_NOT_FOUND)
	{
		printf("HassDeviceManager: eraseAllHassDeviceInfoFromNvs nvs not found, error_code:%u\n", err);
		is_nvs_busy = false;
		return false;
	}

	printf("HassDeviceManager: eraseAllHassDeviceInfoFromNvs, hass_device_arr_length_ptr: %u\n",
		hass_device_arr_length);
	for (int i = 0; i < hass_device_arr_length; ++i)
	{
		int seq = i + 1;
		char key[strlen(HASS_DEVICE_STORAGE_KEY_PREFIX) + 2];
		sprintf(key, HASS_DEVICE_STORAGE_KEY_PREFIX, seq);
		err = nvs_erase_key(nvs_handle, key);
		if (err != ESP_OK)
		{
			printf("HassDeviceManager: eraseAllHassDeviceInfoFromNvs, nvs_erase_key [%s] failed.\n", key);
			continue;
		}
		else
		{
			printf("HassDeviceManager: eraseAllHassDeviceInfoFromNvs, nvs_erase_key [%s] success.\n", key);
		}
	}
	err = nvs_erase_key(nvs_handle, HASS_DEVICE_NUM_KEY);
	if (err != ESP_OK)
	{
		printf("HassDeviceManager: nvs_erase_key [%s] failed\n", HASS_DEVICE_NUM_KEY);
		nvs_close(nvs_handle);
		is_nvs_busy = false;
		return false;
	}
	else
	{
		printf("HassDeviceManager: nvs_erase_key [%s] success\n", HASS_DEVICE_NUM_KEY);
	}
	nvs_commit(nvs_handle);
	nvs_close(nvs_handle);
	is_nvs_busy = false;
	return true;
}

bool HassDeviceManager::readHassDeviceFromNvs(hass_device_t hass_device_arr[], uint16_t hass_device_arr_length)
{
	nvs_handle_t nvs_handle;
	printf("HassDeviceManager: readHassDeviceFromNvs start\n");
	esp_err_t err;
	// Open
	err = nvs_open(HASS_DEVICE_STORAGE_NAMESPACE, NVS_READONLY, &nvs_handle);
	if (err == ESP_ERR_NVS_NOT_FOUND)
	{
		printf("HassDeviceManager: readHassDeviceFromNvs nvs not found, error_code:%u\n", err);
		return false;
	}
	if (hass_device_arr_length <= 0)
	{
		printf("hass device number is 0\n");
		nvs_close(nvs_handle);
		return true;
	}
	printf("HassDeviceManager: readHassDeviceFromNvs hass_device_arr_length_ptr: %u\n", hass_device_arr_length);
	for (int i = 0; i < hass_device_arr_length; ++i)
	{
		int seq = i + 1;
		char key[strlen(HASS_DEVICE_STORAGE_KEY_PREFIX) + 2];
		sprintf(key, HASS_DEVICE_STORAGE_KEY_PREFIX, seq);
		size_t required_size = 0;
		printf("HassDeviceManager: key: %s\n", key);
		err = nvs_get_str(nvs_handle, key, nullptr, &required_size);
		if (err != ESP_OK && err != ESP_ERR_NVS_NOT_FOUND) return false;
		//再来读取对应的值
		char hass_device_json[required_size];
		err = nvs_get_str(nvs_handle, key, hass_device_json, &required_size);
		if (err == ESP_ERR_NVS_NOT_FOUND)
		{
			printf("HassDeviceManager: readHassDeviceFromNvs, key:%s not exist, skip\n", key);
			continue;
		}
		else if (err == ESP_ERR_NVS_INVALID_NAME)
		{
			printf("HassDeviceManager: readHassDeviceFromNvs, name doesn’t satisfy constraints, key:%s\n", key);
			continue;
		}
		else if (err == ESP_ERR_NVS_INVALID_LENGTH)
		{
			printf("HassDeviceManager: readHassDeviceFromNvs, length is not sufficient to store data, key:%s\n",
				key);
			continue;
		}
		else
		{
			printf("HassDeviceManager: readHassDeviceFromNvs, read success, key:%s\n", key);
		}
		//解析json
		printf("HassDeviceManager: hass_device_json:%s\n", hass_device_json);
		cJSON* pHassDeviceInfoItem = cJSON_Parse(hass_device_json);
		cJSON* pAttrObj = cJSON_GetObjectItem(pHassDeviceInfoItem, "attr");// 解析relay字段字符串内容
		if (pAttrObj == NULL)
		{
			printf("attr is blank in loop, continue\n");
			cJSON_Delete(pHassDeviceInfoItem);
			continue;
		}

		hass_device_t hass_device;
		char* entity_id = getValueFromJsonObj(pHassDeviceInfoItem, "entity_id");
		if (entity_id == nullptr || strcmp(entity_id, "") == 0)
		{
			printf("entity_id is null in loop, continue\n");
			cJSON_Delete(pHassDeviceInfoItem);
			continue;
		}
		hass_device.entity_id = entity_id;

		char* type = getValueFromJsonObj(pHassDeviceInfoItem, "type");
		if (type == nullptr || strcmp(type, "") == 0)
		{
			printf("type is null in loop, continue\n");
			cJSON_Delete(pHassDeviceInfoItem);
			continue;
		}
		hass_device.type = type;

		char* friendly_name = getValueFromJsonObj(pAttrObj, "friendly_name");
		if (friendly_name == nullptr || strcmp(friendly_name, "") == 0)
		{
			printf("friendly_name is null in loop, use entity_id instead.\n");
			friendly_name = entity_id;
		}
		hass_device.friendly_name = friendly_name;
		hass_device_arr[i] = hass_device;
	}
	nvs_close(nvs_handle);
	printf("HassDeviceManager: readHassDeviceFromNvs read finished\n");
	return true;
}

char* HassDeviceManager::getValueFromJsonObj(const cJSON* cJson, const char* attribute_name)
{
	cJSON* json = cJSON_GetObjectItem(cJson, attribute_name);
	// 判断字段是否string类型
	if (json == NULL || !cJSON_IsString(json))
	{
		printf("attribute_name:%s can not be parsed\n", attribute_name);
		return nullptr;
	}
	return json->valuestring;
}

uint16_t HassDeviceManager::getAllDeviceNum()
{
	return nvs_hass_device_info_arr_length;
}

uint16_t HassDeviceManager::getAllDeviceList(hass_device_info_t hass_device_info_arr[],
	uint16_t hass_device_info_arr_length)
{
	printf("HassDeviceManager: getAllDeviceList start, nvs_hass_device_info_arr_length:%u\n",
		nvs_hass_device_info_arr_length);
	if (nvs_hass_device_info_arr == nullptr || nvs_hass_device_info_arr_length == 0)
	{
		printf("HassDeviceManager: getAllDeviceList return 0\n");
		return 0;
	}
	for (int i = 0; i < hass_device_info_arr_length; ++i)
	{
		printf("HassDeviceManager: put nvs_hass_device_info_arr into hass_device_info_arr, index:%u\n", i);
		hass_device_info_arr[i] = nvs_hass_device_info_arr[i];
		printf("HassDeviceManager: nvs_hass_device_info_arr[%u] entity_id:%s\n",
			i,
			nvs_hass_device_info_arr[i].entity_id);
	}
	return nvs_hass_device_info_arr_length;
}

void HassDeviceManager::turnOnLight(const char* entity_id)
{
	std::map<std::string, std::string> property_map;
	callService(entity_id, "light", "turn_on", property_map);
}

void HassDeviceManager::turnOffLight(const char* entity_id)
{
	std::map<std::string, std::string> property_map;
	callService(entity_id, "light", "turn_off", property_map);
}

void HassDeviceManager::toggleLight(const char* entity_id, std::map<std::string, std::string> property_map)
{
	callService(entity_id, "light", "toggle", std::move(property_map));
}

void HassDeviceManager::turnOnSwitch(const char* entity_id)
{
	std::map<std::string, std::string> property_map;
	callService(entity_id, "switch", "turn_on", property_map);
}

void HassDeviceManager::turnOffSwitch(const char* entity_id)
{
	std::map<std::string, std::string> property_map;
	callService(entity_id, "switch", "turn_off", property_map);
}

void HassDeviceManager::callService(const char* entity_id,
	const char* domain,
	const char* service,
	std::map<std::string, std::string> property_map)
{
	char topic_name[128];
	snprintf(topic_name, sizeof(topic_name), "%s/HOME/device/%s", MQTT_HOST, entity_id);
	struct timeval tp;
	gettimeofday(&tp, NULL);
	long int ms = tp.tv_sec * 1000 + tp.tv_usec / 1000;
	cJSON* root = cJSON_CreateObject();
	cJSON_AddStringToObject(root, "msg_type", "hass_device_control");
	cJSON_AddNumberToObject(root, "timestamp", ms);
	cJSON* cJsonMsgBody = cJSON_CreateObject();
	cJSON_AddStringToObject(cJsonMsgBody, "action", "call_service");
	cJSON_AddStringToObject(cJsonMsgBody, "entity_id", entity_id);
	cJSON_AddStringToObject(cJsonMsgBody, "domain", domain);
	cJSON_AddStringToObject(cJsonMsgBody, "service", service);

	if (!property_map.empty())
	{
		std::map<std::string, std::string>::iterator iter;
		iter = property_map.begin();
		while (iter != property_map.end())
		{
			std::string key = iter->first;
			std::string value = iter->second;
			cJSON_AddStringToObject(cJsonMsgBody, key.c_str(), value.c_str());
			iter++;
		}
	}

	cJSON_AddItemToObject(root, "msg_body", cJsonMsgBody);
	char* payload = cJSON_Print(root);
	printf("mqtt send: %s:%s\n", topic_name, payload);
	HAL::mqtt_publish(topic_name, payload);
	cJSON_Delete(root);
	cJSON_free(payload);
}
