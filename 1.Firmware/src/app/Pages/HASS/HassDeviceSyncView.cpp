#include "HassDeviceSyncView.h"
#include "app/app.h"

using namespace Page;

void HassDeviceSyncView::Create(lv_obj_t* root)
{
	PlaygroundView::Create(root);

	lv_obj_add_flag(ui.lable_value, LV_OBJ_FLAG_HIDDEN);
	lv_meter_set_scale_ticks(ui.meter, ui.scale_pot, 73, 2, 0, lv_color_make(0xff, 0x00, 0x00));
	lv_meter_set_scale_range(ui.meter, ui.scale_pot, 0, 72, 360, 270);

	m_ui.img_sync_status = lv_img_create(root);

	lv_img_set_src(m_ui.img_sync_status, LV_SYMBOL_DUMMY "MQ");
	lv_obj_align(m_ui.img_sync_status, LV_ALIGN_CENTER, 0, 0);
	printf("HassDeviceSyncView: Created\n");
}

void Page::HassDeviceSyncView::UpdateView(HassDeviceSyncInfo* info)
{
	static bool is_connected = false;
	int32_t motor_pos = info->motor_pos;
	motor_pos = motor_pos % (360/5); // 5 为surface dial 电机模式最小角度
	if (motor_pos < 0) {
		motor_pos = 360/5 + motor_pos;
	}
	lv_meter_set_indicator_value(ui.meter, ui.nd_img_circle, motor_pos);

	if (info->mqtt_is_connected != is_connected) {
		lv_color_t color = info->mqtt_is_connected ? lv_color_make(0x00, 0x82, 0xfc):lv_color_white();
		lv_obj_set_style_img_recolor_opa(m_ui.img_sync_status, LV_OPA_COVER, 0);
		lv_obj_set_style_img_recolor(m_ui.img_sync_status, color, 0);
		is_connected = info->mqtt_is_connected;
	}
}

void HassDeviceSyncView::Delete()
{
	printf("Deleting HassDeviceSyncView\n");
	lv_group_del(ui.group);
	lv_style_reset(&style.meter);
	lv_style_reset(&style.ticks);
	printf("Delete done HassDeviceSyncView\n");
}


