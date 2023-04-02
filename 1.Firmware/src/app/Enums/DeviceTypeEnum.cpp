//
// Created by Jwxa-Desktop on 2023/3/27.
//
#ifndef HASS_DEVICE_TYPE_ENUM_
#define HASS_DEVICE_TYPE_ENUM_
#include <iostream>
#include <string>
#include <map>
using namespace std;
enum class DeviceTypeEnum
{
	SETTINGS, LIGHT, SWITCH, FAN, MEDIA_PLAYER
};

const string DeviceTypeNames[] = { "settings", "light", "switch", "fan", "media_player" };

static std::map<std::string, DeviceTypeEnum> deviceTypeMap = {
	{ DeviceTypeNames[0], DeviceTypeEnum::SETTINGS },
	{ DeviceTypeNames[1], DeviceTypeEnum::LIGHT },
	{ DeviceTypeNames[2], DeviceTypeEnum::SWITCH },
	{ DeviceTypeNames[3], DeviceTypeEnum::FAN },
	{ DeviceTypeNames[4], DeviceTypeEnum::MEDIA_PLAYER }
};

static char* getDeviceTypeNames(DeviceTypeEnum deviceTypeEnum)
{
	const char* deviceTypeName = DeviceTypeNames[static_cast<int>(deviceTypeEnum)].c_str();
	return const_cast<char*>(deviceTypeName);
}

static DeviceTypeEnum getDeviceTypeEnum(char* deviceType)
{
	auto it = deviceTypeMap.find(deviceType);
	if (it == deviceTypeMap.end())
	{
		throw std::invalid_argument("Invalid device type");
	}
	return it->second;
}
#endif
