#ifndef __HASS_DEVICE_SYNC_MODEL_H
#define __HASS_DEVICE_SYNC_MODEL_H
#include "lvgl.h"
#include "../Playground/PlaygroundView.h"
#include "../Playground/PlaygroundModel.h"

typedef struct
{
	int32_t xkonb_value;
	int32_t motor_pos;
	int32_t angle_offset;
	SuperDialMotion konb_direction;
	bool mqtt_is_connected;
} HassDeviceSyncInfo;

namespace Page
{
	class HassDeviceSyncModel : public PlaygroundModel
	{

	 public:
		HassDeviceSyncModel();
		void Init();
		void Deinit();
		void Update(void* pg_ui);
		void GetKnobStatus(HassDeviceSyncInfo* info);
		void ChangeMotorMode(int mode);
		void SetPlaygroundMode(int16_t mode);

		void onEvent(Account* account, Account::EventParam_t* param);
	 private:

	};

}
#endif