#include "Hass.h"
#include "hal/hal.h"
#include "config.h"
#include "app/Enums/DeviceTypeEnum.cpp"

using namespace Page;

constexpr auto state_on = "on";
constexpr auto state_off = "off";
const int motor_mode = MOTOR_SUPER_DIAL;
const int app_mode = APP_MODE_HOME_ASSISTANT;

Hass::Hass()
{
}

Hass::~Hass()
{

}

void Hass::onCustomAttrConfig()
{
	SetCustomCacheEnable(false);
	// SetCustomLoadAnimType(PageManager::LOAD_ANIM_OVER_BOTTOM, 500, lv_anim_path_bounce);
}

void Hass::onViewLoad()
{
	printf("Hass: onViewLoad\n");
	Model = new HassModel();
	View = new HassView();

	Model->Init();
	View->Create(root);

	AttachEvent(root);
	AttachEvent(View->ui.meter);
	//APP_MODE_HOME_ASSISTANT

	uint16_t device_len = ((HassView*)View)->m_ui.device_len;
	for (int i = 0; i < device_len; ++i)
	{
		device_t device = ((HassView*)View)->m_ui.device_arr[i];
		AttachEvent(device.cont);
	}
	AttachEvent(((HassView*)View)->m_ui.settings.cont);
}

void Hass::AttachEvent(lv_obj_t* obj)
{
	lv_obj_set_user_data(obj, this);
	lv_obj_add_event_cb(obj, onEvent, LV_EVENT_ALL, this);
}

void Hass::onViewDidLoad()
{

}

void Hass::onViewWillAppear()
{
	printf("Hass: onViewWillAppear\n");
	Model->ChangeMotorMode(motor_mode);
	Model->SetPlaygroundMode(app_mode);
	View->SetPlaygroundMode(app_mode);

	timer = lv_timer_create(onTimerUpdate, 10, this);
}

void Hass::onViewDidAppear()
{

}

void Hass::onViewWillDisappear()
{

}

void Hass::onViewDidDisappear()
{
	lv_timer_del(timer);
}

void Hass::onViewDidUnload()
{
	View->Delete();
	Model->Deinit();

	delete View;
	delete Model;

}

void Hass::Update()
{
	printf("Hass::Update\n");
	HassInfo info;
	Model->GetKnobStatus(&info);
	printf("Hass::GetKnobStatus\n");
	if (info.konb_direction != SUPER_DIAL_NULL)
	{
		device_t* device;
		char* entity_id = ((HassView*)View)->GetEditedDevice(&device);
		if (entity_id != NULL)
		{
			//找到当前设备的信息
			DeviceTypeEnum deviceTypeEnum = getDeviceTypeEnum(device->type);
			int knob_value = info.xkonb_value;
			printf("22222222222222 Hass::Update knob_value:%u, device->type:%s\n", knob_value, device->type);
			switch (deviceTypeEnum)
			{
			case DeviceTypeEnum::LIGHT:
				//todo 判断第一个view是控制开关 第二个view是控制亮度
				if (knob_value == 1)
				{
					HassDeviceManager::turnOnLight(entity_id);

					device->state = const_cast<char*>(state_on);
					HassModel::setStateMap(entity_id, state_on);
				}
				else if (knob_value == 0)
				{
					HassDeviceManager::turnOffLight(entity_id);
					device->state = const_cast<char*>(state_off);
					HassModel::setStateMap(entity_id, state_off);
				}
				else
				{
					//只要不是确定的值 do nothing
				}
				break;
			case DeviceTypeEnum::SWITCH:
				if (knob_value == 1)
				{
					HassDeviceManager::turnOnSwitch(entity_id);
					device->state = const_cast<char*>(state_on);
					HassModel::setStateMap(entity_id, state_on);
				}
				else if (knob_value == 0)
				{
					HassDeviceManager::turnOffSwitch(entity_id);
					device->state = const_cast<char*>(state_off);
					HassModel::setStateMap(entity_id, state_off);
				}
				else
				{
					//只要不是确定的值 do nothing
				}
				break;
			default:
				break;
			}

		}
	}
	View->UpdateView(&info);
}

void Hass::onTimerUpdate(lv_timer_t* timer)
{
	Hass* instance = (Hass*)timer->user_data;

	instance->Update();
}

void Hass::HassEventHandler(lv_event_t* event, lv_event_code_t code)
{
	lv_obj_t* obj = lv_event_get_target(event);
	lv_obj_t* label = lv_obj_get_child(obj, 1);

	if (code < LV_EVENT_RELEASED)
	{
		printf("code: %d\n", code);
	}

	if (code == LV_EVENT_FOCUSED)
	{
		if (label != NULL)
		{
			printf("fouces, name:%s\n", lv_label_get_text(label));
			((HassView*)View)->UpdateFocusedDevice(lv_label_get_text(label));
		}
	}
	if (code == LV_EVENT_PRESSED)
	{
		printf("Hass: LV_EVENT_PRESSED\n");
		if (!lv_obj_has_state(obj, LV_STATE_EDITED))
		{
			if (label != NULL)
			{
				printf("Control device: %s\n", lv_label_get_text(label));
			}
			lv_obj_add_state(obj, LV_STATE_EDITED);
			device_t* device;
			string entity_id_str = View->GetEditedDevice(&device);
			char* entity_id = device->entity_id;
			Model-> setBusyDeviceEntityId(entity_id);
			View->SetCtrView(obj, root);
			HAL::encoder_disable();
			if (View->GetViewMode() == VIEW_MODE_ON_OFF)
			{
				Model->ChangeMotorMode(MOTOR_ON_OFF_STRONG_DETENTS);
			}
		}
		else
		{
			//todo 切换view到下一个
//			uint32_t device_index = lv_obj_get_index(obj);
//			device_t* device = &(((HassView*)View)->m_ui.device_arr[device_index]);
//			hass_hal_send(device->entity_id, HASS_PUSH);
		}
	}
	else if (code == LV_EVENT_LONG_PRESSED)
	{
		printf("Hass: LV_EVENT_LONG_PRESSED\n");
		if (lv_obj_has_state(obj, LV_STATE_EDITED))
		{
			Model-> setBusyDeviceEntityId(nullptr);
			((HassView*)View)->ClearCtrView(obj);
			lv_obj_clear_state(obj, LV_STATE_EDITED);
			HAL::encoder_enable();
			Model->ChangeMotorMode(motor_mode);
		}
	}
	else if (code == LV_EVENT_LONG_PRESSED_REPEAT)
	{
		// return to memu
		if (!lv_obj_has_state(obj, LV_STATE_EDITED))
		{
			printf("Hass: LV_EVENT_LONG_PRESSED_REPEAT\n");
			Model->ChangeMotorMode(MOTOR_UNBOUND_COARSE_DETENTS);
			Manager->Pop();
		}
	}

}

void Hass::onEvent(lv_event_t* event)
{
	lv_obj_t* obj = lv_event_get_target(event);
	lv_event_code_t code = lv_event_get_code(event);
	auto* instance = (Hass*)lv_obj_get_user_data(obj);

	instance->HassEventHandler(event, code);
}