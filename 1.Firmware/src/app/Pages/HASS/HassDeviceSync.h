#ifndef __HASS_DEVICE_SYNC_H__
#define __HASS_DEVICE_SYNC_H__

#include "HassDeviceSyncModel.h"
#include "HassDeviceSyncView.h"
namespace Page
{
	class HassDeviceSync : public PageBase
	{
	 public:
		HassDeviceSync();
		virtual ~HassDeviceSync();

		virtual void onCustomAttrConfig();
		virtual void onViewLoad();
		virtual void onViewDidLoad();
		virtual void onViewWillAppear();
		virtual void onViewDidAppear();
		virtual void onViewWillDisappear();
		virtual void onViewDidDisappear();
		virtual void onViewDidUnload();
		void HassDeviceSyncEventHandler(lv_event_t* event, lv_event_code_t code);

	 private:
		void Update();
		void AttachEvent(lv_obj_t* obj);
		static void onTimerUpdate(lv_timer_t* timer);
		static void onEvent(lv_event_t* event);
		static void hass_device_sync_init();
		static void hass_device_sync_completed();
	 private:
		HassDeviceSyncView* View;
		HassDeviceSyncModel* Model;
		lv_timer_t* timer;
	};

}
#endif