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

	 public:
		struct
		{
			lv_obj_t* img_sync_status;
		} m_ui;

	};

}
#endif // !__VIEW_H
