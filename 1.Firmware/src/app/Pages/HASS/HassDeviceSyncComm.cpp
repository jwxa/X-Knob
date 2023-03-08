#include "HassDeviceSyncComm.h"
#include "hal/hal.h"
#include "config.h"
using namespace Page;

const char* device_sync_topic_name = "devices/sync";

HassDeviceSyncComm::HassDeviceSyncComm()
{
}

HassDeviceSyncComm::~HassDeviceSyncComm()
{
}

void HassDeviceSyncComm::onCustomAttrConfig()
{
	SetCustomCacheEnable(false);
	// SetCustomLoadAnimType(PageManager::LOAD_ANIM_OVER_BOTTOM, 500, lv_anim_path_bounce);
}

void HassDeviceSyncComm::onViewLoad()
{
	printf("HassDeviceSyncComm: onViewLoad\n");
	Model = new HassDeviceSyncModel();
	View = new HassDeviceSyncView();
	hass_device_sync_init();

	Model->Init();
	View->Create(root);


	// lv_label_set_text(View->ui.labelTitle, Name);

	AttachEvent(root);
	AttachEvent(View->ui.meter);

//	if (app == APP_MODE_HOME_ASSISTANT) {
//		AttachEvent(((HassView*)View)->m_ui.fan.cont);
//		AttachEvent(((HassView*)View)->m_ui.monitor_light.cont);
//		AttachEvent(((HassView*)View)->m_ui.air_conditioning.cont);
//		AttachEvent(((HassView*)View)->m_ui.wash_machine.cont);
//		AttachEvent(((HassView*)View)->m_ui.settings.cont);
//	}

}

void HassDeviceSyncComm::onViewDidLoad()
{

}

void HassDeviceSyncComm::onViewWillAppear()
{

//	Model->ChangeMotorMode(app_config[app].motor_mode);
//	Model->SetPlaygroundMode(app);
//	View->SetPlaygroundMode(app);

	timer = lv_timer_create(onTimerUpdate, 10, this);
}

void HassDeviceSyncComm::onTimerUpdate(lv_timer_t* timer)
{
	HassDeviceSyncComm* instance = (HassDeviceSyncComm*)timer->user_data;

	instance->Update();
}

void HassDeviceSyncComm::Update()
{
	HassDeviceSyncInfo info;
	Model->GetKnobStatus(&info);
	//对旋钮选中的对象进行操作,比如hass就是发送mqtt

	View->UpdateView(&info);
}

void HassDeviceSyncComm::onViewDidAppear()
{

}

void HassDeviceSyncComm::onViewWillDisappear()
{

}

void HassDeviceSyncComm::onViewDidDisappear()
{
	lv_timer_del(timer);
}

void HassDeviceSyncComm::onEvent(lv_event_t* event)
{
	lv_obj_t* obj = lv_event_get_target(event);
	lv_event_code_t code = lv_event_get_code(event);
	auto* instance = (HassDeviceSyncComm*)lv_obj_get_user_data(obj);
	instance->HassDeviceSyncEventHandler(event, code);
}

void HassDeviceSyncComm::onViewDidUnload()
{
	View->Delete();
	Model->Deinit();

	delete View;
	delete Model;

}

void HassDeviceSyncComm::HassDeviceSyncEventHandler(lv_event_t* event, lv_event_code_t code)
{
	lv_obj_t* obj = lv_event_get_target(event);
	lv_obj_t* label = lv_obj_get_child(obj, 1);
	if (code == LV_EVENT_PRESSED)
	{
		printf("HassDeviceSyncComm: HassDeviceSyncEventHandler press\n");
	}
	else if (code == LV_EVENT_LONG_PRESSED_REPEAT)
	{
		printf("HassDeviceSyncComm: HassDeviceSyncEventHandler LV_EVENT_LONG_PRESSED_REPEAT\n");
		Model->ChangeMotorMode(MOTOR_UNBOUND_COARSE_DETENTS);
		Manager->Pop();
	}
	else if (code == LV_EVENT_RELEASED)
	{
		// return to memu
		printf("HassDeviceSyncComm: HassDeviceSyncEventHandler LV_EVENT_RELEASED\n");
	}
}

void HassDeviceSyncComm::AttachEvent(lv_obj_t* obj)
{
	lv_obj_set_user_data(obj, this);
	lv_obj_add_event_cb(obj, onEvent, LV_EVENT_ALL, this);
}

void HassDeviceSyncComm::hass_device_sync_init()
{
	printf("hass_device_sync_init\n");
}

void HassDeviceSyncComm::hass_device_do_sync(int knob_value)
{
	printf("hass_device_do_sync\n");
}
