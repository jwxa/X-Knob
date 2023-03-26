#include "HassHalComm.h"
#include "hal/hal.h"
#include "config.h"
using namespace Page;

const char* playload_str[]{
	[SUPER_DIAL_NULL] = "NULL",
	[HASS_LEFT] = "LEFT",
	[HASS_RIGHT] = "RIGHT",
	[HASS_PUSH]  = "ON/OFF"
};

const int motor_mode = MOTOR_SUPER_DIAL;
const int app_mode = APP_MODE_HOME_ASSISTANT;

HassHalComm::HassHalComm()
{
}

HassHalComm::~HassHalComm()
{

}

void Page::HassHalComm::hass_hal_init(void)
{
	HassDeviceManager::hass_device_task_init();
}

int Page::HassHalComm::hass_hal_send(const char* device_name, int knob_value)
{
	char topic_name[128];

	snprintf(topic_name, sizeof(topic_name), "%s/HOME/%s", MQTT_HOST, device_name);
	if (knob_value < HASS_MAX && playload_str[knob_value] != NULL)
	{
		printf("mqtt send: %s:%s\n", topic_name, playload_str[knob_value]);
		return HAL::mqtt_publish(topic_name, playload_str[knob_value]);
	}
	else
	{
		printf("hass_hal_send: xknob_value is invalid\n");
		return -1;
	}
	return 0;
}

void HassHalComm::onCustomAttrConfig()
{
	SetCustomCacheEnable(false);
	// SetCustomLoadAnimType(PageManager::LOAD_ANIM_OVER_BOTTOM, 500, lv_anim_path_bounce);
}

void HassHalComm::onViewLoad()
{
	printf("HassHalComm: onViewLoad\n");
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
//	AttachEvent(((HassView*)View)->m_ui.fan.cont);
//	AttachEvent(((HassView*)View)->m_ui.monitor_light.cont);
//	AttachEvent(((HassView*)View)->m_ui.air_conditioning.cont);
//	AttachEvent(((HassView*)View)->m_ui.wash_machine.cont);
	AttachEvent(((HassView*)View)->m_ui.settings.cont);
}

void HassHalComm::AttachEvent(lv_obj_t* obj)
{
	lv_obj_set_user_data(obj, this);
	lv_obj_add_event_cb(obj, onEvent, LV_EVENT_ALL, this);
}

void HassHalComm::onViewDidLoad()
{

}

void HassHalComm::onViewWillAppear()
{
	printf("HassHalComm: onViewWillAppear\n");
	Model->ChangeMotorMode(motor_mode);
	Model->SetPlaygroundMode(app_mode);
	View->SetPlaygroundMode(app_mode);

	timer = lv_timer_create(onTimerUpdate, 10, this);
}

void HassHalComm::onViewDidAppear()
{

}

void HassHalComm::onViewWillDisappear()
{

}

void HassHalComm::onViewDidDisappear()
{
	lv_timer_del(timer);
}

void HassHalComm::onViewDidUnload()
{
	View->Delete();
	Model->Deinit();

	delete View;
	delete Model;

}

void HassHalComm::Update()
{
	PlaygroundInfo info;
	Model->GetKnobStatus(&info);
	if (info.konb_direction != SUPER_DIAL_NULL)
	{
		char* name = ((HassView*)View)->GetEditedDeviceName();
		if (name != NULL)
		{
			hass_hal_send(name, info.konb_direction);
		}
	}
	View->UpdateView(&info);
}

void HassHalComm::onTimerUpdate(lv_timer_t* timer)
{
	HassHalComm* instance = (HassHalComm*)timer->user_data;

	instance->Update();
}

void HassHalComm::HassEventHandler(lv_event_t* event, lv_event_code_t code)
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
			((HassView*)View)->SetCtrView(obj, root);
			HAL::encoder_disable();
			if (((HassView*)View)->GetViewMode() == VIEW_MODE_ON_OFF)
			{
				Model->ChangeMotorMode(MOTOR_ON_OFF_STRONG_DETENTS);
			}
		}
		else
		{
			uint32_t device_index = lv_obj_get_index(obj);
			device_t* device = &(((HassView*)View)->m_ui.device_arr[device_index]);
			hass_hal_send(device -> entity_id, HASS_PUSH);
		}
	}
	else if (code == LV_EVENT_LONG_PRESSED)
	{
		printf("Hass: LV_EVENT_LONG_PRESSED\n");
		if (lv_obj_has_state(obj, LV_STATE_EDITED))
		{
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

void HassHalComm::onEvent(lv_event_t* event)
{
	lv_obj_t* obj = lv_event_get_target(event);
	lv_event_code_t code = lv_event_get_code(event);
	auto* instance = (HassHalComm*)lv_obj_get_user_data(obj);

	instance->HassEventHandler(event, code);
}