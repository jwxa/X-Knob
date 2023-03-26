#ifndef __HASS_HAL_COMM_H__
#define __HASS_HAL_COMM_H__

#include "HassModel.h"
#include "HassView.h"

namespace Page
{
	class HassHalComm : public PageBase
	{
	 public:
		HassHalComm();
		virtual ~HassHalComm();

		virtual void onCustomAttrConfig();
		virtual void onViewLoad();
		virtual void onViewDidLoad();
		virtual void onViewWillAppear();
		virtual void onViewDidAppear();
		virtual void onViewWillDisappear();
		virtual void onViewDidDisappear();
		virtual void onViewDidUnload();

		static void hass_hal_init();
		void HassEventHandler(lv_event_t* event, lv_event_code_t code);

	 private:
		void Update();
		void AttachEvent(lv_obj_t* obj);
		static void onTimerUpdate(lv_timer_t* timer);
		static void onEvent(lv_event_t* event);

		int hass_hal_send(const char* device_name, int knob_value);
	 private:
		HassView* View;
		HassModel* Model;
		lv_timer_t* timer;
	};
}


#endif /*   __HASS_HAL_COMM_H__ */