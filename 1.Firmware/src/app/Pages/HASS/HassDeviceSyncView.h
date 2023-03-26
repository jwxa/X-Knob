#ifndef __HASS_DEVICE_SYNC_VIEW_H
#define __HASS_DEVICE_SYNC_VIEW_H
#include "Arduino.h"
#include "app/app.h"
#include "../Page.h"
#include "HassDeviceSyncModel.h"
namespace Page
{

	class HassDeviceSyncView: public PlaygroundView
	{
	 public:
		void Create(lv_obj_t* root);
		void Delete();
		void UpdateView(HassDeviceSyncInfo* info);
		void UpdateBackgroundView(HassDeviceSyncInfo* info);
		void SetPlaygroundMode(int16_t mode);

	 public:
		struct
		{
			lv_obj_t* sync_mqtt_status_label;
			lv_obj_t* sync_status_msg_label;
		} m_ui;

	};

}
#endif // !__VIEW_H
