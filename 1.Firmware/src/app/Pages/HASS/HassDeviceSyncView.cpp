#include "HassDeviceSyncView.h"
#include "app/app.h"

using namespace Page;

void HassDeviceSyncView::Create(lv_obj_t* root)
{
	PlaygroundView::Create(root);
	//把playground里设置label的样式覆蓋
	lv_obj_remove_style_all(ui.label_value);
	lv_obj_set_pos(ui.label_value, 70, 90);
	lv_obj_set_style_text_color(ui.label_value, lv_color_white(), 0);
	lv_obj_set_size(ui.label_value, 140, 28);
	lv_label_set_long_mode(ui.label_value, LV_LABEL_LONG_SCROLL);
	lv_label_set_text(ui.label_value, "sync mode");

//	//隐藏中间的圆点
//	lv_obj_add_flag(, LV_OBJ_FLAG_HIDDEN);
	//中间放一个图标表示mqtt连接状态
	m_ui.sync_mqtt_status_label = lv_label_create(root);
	lv_obj_set_style_text_color(m_ui.sync_mqtt_status_label, lv_color_white(), 0);
	//创建字体样式
	static lv_style_t icon_label_style;
	lv_style_init(&icon_label_style);
	lv_style_set_text_font(&icon_label_style, &myAwesomeFont);
	lv_label_set_text(m_ui.sync_mqtt_status_label, MY_NETWORK_SYMBOL);
	lv_obj_set_size(m_ui.sync_mqtt_status_label, 20, 20);
	lv_obj_align(m_ui.sync_mqtt_status_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_add_style(m_ui.sync_mqtt_status_label, &icon_label_style, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_move_foreground(m_ui.sync_mqtt_status_label);

	//圆点下方放一个label展示信息
//	ui.label_value = lv_label_create(root);

//	lv_label_set_long_mode(ui.label_value, LV_LABEL_LONG_WRAP);
	m_ui.sync_status_msg_label = lv_label_create(root);
	lv_obj_align(m_ui.sync_status_msg_label, LV_ALIGN_CENTER, 0, 25);
	lv_obj_set_size(m_ui.sync_status_msg_label, 140, 28);
	lv_obj_set_style_text_color(m_ui.sync_status_msg_label, lv_color_white(), 0);
	lv_label_set_text(m_ui.sync_status_msg_label, "");
	lv_label_set_long_mode(m_ui.sync_status_msg_label, LV_LABEL_LONG_SCROLL);


	printf("HassDeviceSyncView: Created\n");
}

void HassDeviceSyncView::UpdateView(HassDeviceSyncInfo* info)
{
	int _value = 0;
	int32_t motor_pos = info->motor_pos;
	motor_pos = motor_pos % 360;
	if (motor_pos < 0)
	{
		motor_pos = 360 + motor_pos;
	}
	//仪表盘
	lv_meter_set_indicator_value(ui.meter, ui.nd_img_circle, motor_pos);
	//数值更新
	_value = info->xkonb_value;
	UpdateBackgroundView(info);
	//圆点上方的label进行更新
	if (_value == 0)
	{
		lv_label_set_text_fmt(
			ui.label_value,
			"%s",
			"sync mode"
		);
	}
	else
	{
		lv_label_set_text_fmt(
			ui.label_value,
			"%s",
			"clear all device"
		);
	}

	//mq连接状态
	if (info->mqtt_is_connected)
	{
		lv_obj_set_style_text_color(m_ui.sync_mqtt_status_label,  lv_color_make(0x00, 0x82, 0xfc), 0);
	}
	else
	{
		lv_obj_set_style_text_color(m_ui.sync_mqtt_status_label,  lv_color_make(0xff, 0x00, 0x00), 0);
	}
}

void HassDeviceSyncView::UpdateBackgroundView(HassDeviceSyncInfo* info)
{
	// lv_style_set_bg_main_stop(&style.meter, 255-xkonb_value);
	// lv_style_set_bg_grad_stop(&style.meter, 255-xkonb_value);
	int value_map = map(info->xkonb_value, 0, MAX_VALUE, 0, 255);
	lv_obj_set_style_bg_main_stop(ui.meter, 255 - value_map, 0);
	lv_obj_set_style_bg_grad_stop(ui.meter, 255 - value_map, 0);
}

/*
 * 默认视图显示： 圆点，原点所在位置 label_value
 * 此函数根据需要增加或 hidden 对象
*/
void HassDeviceSyncView::SetPlaygroundMode(int16_t mode)
{
	//surfaceDial的展示
//	lv_obj_add_flag(ui.label_value, LV_OBJ_FLAG_HIDDEN);
//	lv_meter_set_scale_ticks(ui.meter, ui.scale_pot, 73, 2, 0, lv_color_make(0xff, 0x00, 0x00));
//	lv_meter_set_scale_range(ui.meter, ui.scale_pot, 0, 72, 360, 270);

//OnOffView
	MIN_VALUE = 0;
	MAX_VALUE = 1;
	SCALE_LEFT_BOUND_TICKS = 240;
	SCALE_ANGLE_RANGE = 60;
	lv_meter_set_scale_ticks(ui.meter, ui.scale_pot, 3, 2, 0, lv_color_make(0xff, 0xff, 0xff));
	lv_meter_set_scale_major_ticks(ui.meter, ui.scale_pot, 2, 4, 20, lv_color_make(0xff, 0xff, 0xff), 10);
	lv_meter_set_scale_range(ui.meter, ui.scale_pot, 0, 1, SCALE_ANGLE_RANGE, SCALE_LEFT_BOUND_TICKS);
}

void HassDeviceSyncView::Delete()
{
	printf("Deleting HassDeviceSyncView\n");
	lv_group_del(ui.group);
	lv_style_reset(&style.meter);
	lv_style_reset(&style.ticks);
	printf("Delete done HassDeviceSyncView\n");
}


