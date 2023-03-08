#ifndef __HASS_DEVICE_SYNC_COMM_H__
#define __HASS_DEVICE_SYNC_COMM_H__

#include "HassDeviceSyncModel.h"
#include "HassDeviceSyncView.h"
namespace Page
{
	class HassDeviceSyncComm : public PageBase
	{
	 public:
		HassDeviceSyncComm();
		virtual ~HassDeviceSyncComm();

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
		void hass_device_sync_init();
		void hass_device_do_sync(int knob_value);

	 private:
		HassDeviceSyncView* View;
		HassDeviceSyncModel* Model;
		lv_timer_t* timer;
	};

}
#endif