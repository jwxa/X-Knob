#include "HassDeviceSyncComm.h"
#include "hal/hal.h"
#include "config.h"
#include "app/Utils/HassDeviceManager/HassDeviceManager.h"
using namespace Page;

const char* device_sync_topic_name = "devices/sync";
const int motor_mode = MOTOR_ON_OFF_STRONG_DETENTS;
const int app_mode = PLAYGROUND_MODE_ON_OFF;

HassDeviceSyncComm::HassDeviceSyncComm()
{
}

HassDeviceSyncComm::~HassDeviceSyncComm()
{
}

void HassDeviceSyncComm::onCustomAttrConfig()
{
	SetCustomCacheEnable(false);
}

void HassDeviceSyncComm::onViewLoad()
{
	printf("HassDeviceSyncComm: onViewLoad\n");
	Model = new HassDeviceSyncModel();
	View = new HassDeviceSyncView();

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

	Model->ChangeMotorMode(motor_mode);
	Model->SetPlaygroundMode(app_mode);
	View->SetPlaygroundMode(app_mode);
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
//	printf("HassDeviceSyncComm: Update xkonb_value:%u",info.xkonb_value);
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
	HassDeviceSyncInfo info;
	Model->GetKnobStatus(&info);
	if (code == LV_EVENT_PRESSED)
	{
		printf("HassDeviceSyncComm: HassDeviceSyncEventHandler LV_EVENT_PRESSED\n");
		printf("HassDeviceSyncComm: HassDeviceSyncEventHandler info.xkonb_value:%u\n", info.xkonb_value);
		if (info.xkonb_value == 0)
		{
			lv_label_set_text(View->m_ui.sync_status_msg_label, "starting sync device info");
			hass_device_sync_init();
		}
		else if (info.xkonb_value == 1)
		{
			lv_label_set_text(View->m_ui.sync_status_msg_label, "starting clean all device config");
			HassDeviceManager::hass_device_task_delete();
			bool erase_result = HassDeviceManager::eraseAllHassDeviceInfoFromNvs();
			printf("HassDeviceSyncComm: HassDeviceSyncEventHandler erase_result:%d\n", erase_result);
			HassDeviceManager::hass_device_task_init();
			lv_label_set_text(View->m_ui.sync_status_msg_label, "clean all device completed");
		}
	}
	else if (code == LV_EVENT_LONG_PRESSED_REPEAT)
	{
		printf("HassDeviceSyncComm: HassDeviceSyncEventHandler LV_EVENT_LONG_PRESSED_REPEAT\n");
		//退出该页面前关闭hass设备监听
		HassDeviceSyncComm::hass_device_sync_completed();
		HAL::encoder_enable();
		Model->ChangeMotorMode(motor_mode);
		Manager->Pop();
	}
	else if (code == LV_EVENT_RELEASED)
	{
		// return to menu
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
	printf("HassDeviceSyncComm: hass_device_sync_init\n");
	char topic_name[128];
	snprintf(topic_name, sizeof(topic_name), "%s/HOME/%s", MQTT_HOST, device_sync_topic_name);
	HAL::mqtt_publish(topic_name, "PING");
	HAL::mqtt_subscribe(topic_name);
}

void HassDeviceSyncComm::hass_device_sync_completed()
{
	printf("HassDeviceSyncComm: hass_device_sync_completed\n");
	char topic_name[128];
	snprintf(topic_name, sizeof(topic_name), "%s/HOME/%s", MQTT_HOST, device_sync_topic_name);
	HAL::mqtt_unsubscribe(topic_name);
}