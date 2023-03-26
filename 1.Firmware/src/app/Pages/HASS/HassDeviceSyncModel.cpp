#include "HassDeviceSyncModel.h"
#include "hal/hal.h"
#include "HassModel.h"

using namespace Page;

HassDeviceSyncModel::HassDeviceSyncModel()
{
	app = APP_MODE_HOME_ASSISTANT_DEVICE_SYNC;
}

void HassDeviceSyncModel::GetKnobStatus(HassDeviceSyncInfo* info)
{
	PlaygroundModel::GetKnobStatus(info);
	info->mqtt_is_connected = HAL::is_mqtt_connected();
}

void HassDeviceSyncModel::SetPlaygroundMode(int16_t mode)
{
	PlaygroundModel::SetPlaygroundMode(mode);
}

void HassDeviceSyncModel::ChangeMotorMode(int mode)
{
	PlaygroundModel::ChangeMotorMode(mode);
}

void HassDeviceSyncModel::Init()
{
	PlaygroundModel::Init();
}

void HassDeviceSyncModel::Deinit()
{
	PlaygroundModel::Deinit();
}