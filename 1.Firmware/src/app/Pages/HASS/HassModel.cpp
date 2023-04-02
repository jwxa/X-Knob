#include "HassModel.h"
#include "app/Accounts/Account_Master.h"
#include "app/Utils/HassDeviceManager/HassDeviceManager.h"

using namespace Page;

/**
* key entity_id value state
*/
static std::map<std::string, std::string> state_map;
const char* busy_device_entity_id;
HassModel::HassModel()
{
	app = APP_MODE_HOME_ASSISTANT;
}

void HassModel::GetKnobStatus(HassInfo* info)
{
	PlaygroundModel::GetKnobStatus(info);
	info->busy_device_entity_id = busy_device_entity_id;
}

int onHassDeviceEvent(Account* account, Account::EventParam_t* param)
{
//	printf("HassModel: onHassDeviceEvent\n");
	auto* event = (hass_device_event*)(param->data_p);
	std::string entity_id_str = event->entity_id;
	std::string action_str = event->action;
	std::string state_str = event->state;
//	printf("HassModel: onEvent hass_device_event,entity_id_str:[%s],action_str:[%s],state_str:[%s]\n",
//		entity_id_str.c_str(),
//		action_str.c_str(),
//		state_str.c_str());
	//更新对应的device内容
	if (strcmp(action_str.c_str(), "state_change") == 0)
	{
		printf("HassModel: state_change, entity_id_str:[%s], state_str:[%s]\n",
			entity_id_str.c_str(),
			state_str.c_str());
		//状态修改逻辑
		//如果设备正处于修改状态下(Hass current_view不为0) 则忽略改动
		if (busy_device_entity_id == nullptr || entity_id_str != busy_device_entity_id)
		{
			state_map[entity_id_str] = state_str;
		}
	}
	else
	{
		//unknown
		printf("HassModel: onHassDeviceEvent unknown action_str, skip\n");
	}
	return 0;
}

std::map<std::string, std::string> HassModel::getStateMap()
{
//	for (const auto& it : state_map)
//	{
//		printf("GetDeviceState it.first:[%s] it.second:[%s]\n", it.first.c_str(), it.second.c_str());
//	}
	return state_map;
}

void HassModel::setStateMap(const char* entity_id, const char* state)
{
	printf("HassModel::setStateMap entity_id：%s,state:%s\n", entity_id, state);
//	string entity_id_str = entity_id;
//	string state_str = state;
//	state_map[entity_id_str] = state_str;
}

void HassModel::setBusyDeviceEntityId(const char* entity_id)
{
	busy_device_entity_id = entity_id;
}

const char* HassModel::getBusyDeviceEntityId()
{
	return busy_device_entity_id;
}

void HassModel::Init()
{
	PlaygroundModel::Init();
	printf("HassModel: Init start\n");
	hassDeviceEventAccount = new Account("HassModel", AccountSystem::Broker(), 0, this);
	hassDeviceEventAccount->SetEventCallback(onHassDeviceEvent);
	hassDeviceEventAccount->Subscribe("HassDeviceManager");
}

void HassModel::Deinit()
{
	PlaygroundModel::Deinit();
	if (hassDeviceEventAccount)
	{
		hassDeviceEventAccount->Unsubscribe("HassDeviceManager");
		delete hassDeviceEventAccount;
		hassDeviceEventAccount = nullptr;
	}
}

void HassModel::ChangeMotorMode(int mode)
{
	PlaygroundModel::ChangeMotorMode(mode);
}

void HassModel::SetPlaygroundMode(int16_t mode)
{
	PlaygroundModel::SetPlaygroundMode(mode);
}