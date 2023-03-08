#include "HassDeviceSyncModel.h"
#include "hal/hal.h"

using namespace Page;

HassDeviceSyncModel::HassDeviceSyncModel()
{
	app = APP_MODE_HOME_ASSISTANT_DEVICE_SYNC;
}

void HassDeviceSyncModel::GetKnobStatus(HassDeviceSyncInfo * info)
{
//	PlaygroundModel::GetKnobStatus(info);
	info->mqtt_is_connected = true;
}

void HassDeviceSyncModel::SetPlaygroundMode(int16_t mode)
{

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