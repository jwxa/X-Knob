#include <cstring>
#include "HassView.h"
#include "Hass.h"
#include "app/Utils/HassDeviceManager/HassDeviceManager.h"
#include "HassModel.h"
#include "app/Enums/DeviceTypeEnum.cpp"

using namespace Page;
#define ITEM_PAD 60
static char* SETTINGS_STR = const_cast<char*>("Settings");
/*
 * 默认视图显示： 圆点，原点所在位置 label_value
 * 此函数根据需要增加或 hidden 对象
*/
void HassView::SetPlaygroundMode(int16_t mode)
{
	lv_obj_add_flag(ui.label_value, LV_OBJ_FLAG_HIDDEN);
	// lv_label_set_text(ui.label_value, "Smart Home");
	lv_meter_set_scale_ticks(ui.meter, ui.scale_pot, 73, 2, 0, lv_color_black());
	lv_meter_set_scale_range(ui.meter, ui.scale_pot, 0, 72, 360, 270);
}

void HassView::UpdateFocusedDevice(const char* name)
{
	lv_label_set_text(m_ui.foucs_label, name);
}

void HassView::SetCtrView(lv_obj_t* obj, lv_obj_t* root)
{
	device_t* device = device_map[obj];
	printf("HassView: SetCtrView device->type:%s\n", device->type);
	printf("HassView: SetCtrView device->is_set_value:%d\n", device->is_set_value);
	printf("HassView: SetCtrView device->is_on_off:%d\n", device->is_on_off);
	printf("HassView: SetCtrView device->entity_id:%s\n", device->entity_id);
	DeviceTypeEnum deviceTypeEnum = getDeviceTypeEnum(device->type);
	auto* instance = (Hass*)lv_obj_get_user_data(obj);
	switch (deviceTypeEnum)
	{
	case DeviceTypeEnum::LIGHT:
		//只支持开关
		if (device->is_on_off && !device->is_set_value)
		{
			PlaygroundView::OnOffView();
			//todo 加上ON OFF的label标签
			current_view = VIEW_MODE_ON_OFF;
		}
		//即支持开关 也支持设置数值
		else if (device->is_on_off && device->is_set_value)
		{
			PlaygroundView::OnOffView();
			current_view = VIEW_MODE_ON_OFF;
		}
		printf("set view: %d\n", current_view);
		lv_obj_set_style_bg_opa(obj, LV_OPA_COVER, 0);
		break;
	case DeviceTypeEnum::SWITCH:
		PlaygroundView::OnOffView();
		current_view = VIEW_MODE_ON_OFF;
		break;
	case DeviceTypeEnum::SETTINGS:
		instance->Manager->Push("Pages/HassDeviceSync");
		break;
	default:
		break;
	}
}
/*
 * Gets the name of the controlled device
*/
char* HassView::GetEditedDevice(device_t** device)
{
	std::map<lv_obj_t*, device_t*>::iterator iter;
	iter = device_map.begin();
	while (iter != device_map.end())
	{
		if (lv_obj_has_state(iter->first, LV_STATE_EDITED))
		{
			//找到被选中的设备
			*device = iter->second;
			return (*device)->entity_id;
		}
		iter++;
	}
	return NULL;
}

void HassView::ClearCtrView(lv_obj_t* obj)
{
	device_t* device = device_map[obj];
	printf("on_off: %d, is_set_value: %d\n", device->is_on_off, device->is_set_value);

//	DeviceTypeEnum deviceTypeEnum = getDeviceTypeEnum(device->type);
//	switch (deviceTypeEnum)
//	{
//	case DeviceTypeEnum::LIGHT:
//		//只支持开关
//		if (device->is_on_off && !device->is_set_value)
//		{
//
//		}
//			//即支持开关 也支持设置数值
//		else if (device->is_on_off && device->is_set_value)
//		{
//
//		}
//
//		break;
//	default:
//		break;
//	}
	PlaygroundView::DefaultView();
	current_view = 0;
	lv_obj_set_style_bg_opa(obj, LV_OPA_TRANSP, 0);
}
int HassView::GetViewMode(void)
{
	return current_view;
}
void HassView::UpdateCtrlView(HassInfo* info, const char* entity_id, const char* state, lv_obj_t* lv_img_obj)
{
	int _value = 0;
	switch (current_view)
	{
	case VIEW_MODE_ON_OFF:
		//获取当前设备的状态
		if (strcmp("on", state) == 0)
		{
			printf("6666666666 HassView::UpdateCtrlView state==on\n");
//			info->xkonb_value = 1;
//			info->motor_pos = 1;
			lv_obj_set_style_img_recolor(lv_img_obj, lv_color_hex(0xff9914), 0);
			//这里会发起motor_status事件 非人为转动
			HAL::update_motor_position(1);
		}
		else if(strcmp("off", state) == 0)
		{
			printf("77777777777 HassView::UpdateCtrlView state!=on\n");
//			info->xkonb_value = 0;
//			info->motor_pos = 0;
			lv_obj_set_style_img_recolor(lv_img_obj, lv_color_white(), 0);
			//这里会发起motor_status事件 非人为转动
			HAL::update_motor_position(0);
		}
		else
		{
			//还没有初始化从mqtt获取到状态
			//do nothing
		}
		break;
	default:
		break;
	}
	int32_t motor_pos = info->motor_pos;
	lv_meter_set_indicator_value(ui.meter, ui.nd_img_circle, motor_pos);
	PlaygroundView::UpdateBackgroundView(info);
}
void HassView::UpdateView(HassInfo* info)
{
	printf("HassView::UpdateView\n");
	//图标状态因为mqtt出现的状态变更事件而发生变动
	std::map<std::string, std::string> state_map = HassModel::getStateMap();
	if (current_view)
	{
		//指定设备 进入单设备的编辑模式时的处理逻辑
		device_t* device;
		string entity_id_str = GetEditedDevice(&device);
		auto iter = state_map.find(entity_id_str);
		std::string state;
		if (iter != state_map.end())
		{
			state = iter->second;
		}

		lv_obj_t* lv_img_obj;
		auto iter2 = img_map.find(entity_id_str);
		if (iter2 == img_map.end())
		{
			//没找到设备对应lvgl的对象,跳过不更新
		}
		lv_img_obj = iter2->second;

		//选中设备后，进入设置模式的调整
		UpdateCtrlView(info, entity_id_str.c_str(), state.c_str(), lv_img_obj);
		return;
	}
	//电机角度调整 蓝点的位置调整
	int32_t motor_pos = info->motor_pos;
	motor_pos = motor_pos % (360 / 5); // 5 为surface dial 电机模式最小角度
	if (motor_pos < 0)
	{
		motor_pos = 360 / 5 + motor_pos;
	}
	lv_meter_set_indicator_value(ui.meter, ui.nd_img_circle, motor_pos);
	//图标状态因为mqtt出现的状态变更事件而发生变动
	if (!state_map.empty() && m_ui.device_len > 0)
	{
		printf("HassView::!state_map.empty\n");
		for (int i = 0; i < m_ui.device_len; ++i)
		{
			device_t device = m_ui.device_arr[i];
			std::string entity_id_str = device.entity_id;
			auto iter = img_map.find(entity_id_str);
			if (iter == img_map.end())
			{
				//没找到设备对应lvgl的对象,跳过不更新
				continue;
			}
			lv_obj_t* lv_img_obj = iter->second;

			auto iter2 = state_map.find(entity_id_str);
			if (iter2 == state_map.end())
			{
				//没找到设备对应状态,跳过不更新
				continue;
			}
			std::string state_str = iter2->second;
			if (device.state != nullptr && strcmp(device.state, state_str.c_str()) == 0)
			{
				//当前设备状态没有发生变动,跳过不更新
				continue;
			}
			if (device.state == nullptr)
			{
				//没有初始化状态 代表没有连通 没必要修改状态
				printf("HassView: UpdateView device.state== nullptr, entity_id_str[%s]\n", entity_id_str.c_str());
				continue;
			}
			else
			{
				//释放内存
				free(device.state);
				device.state = nullptr;
			}
			printf("HassView: UpdateView detect entity_id_str[%s] state change\n", entity_id_str.c_str());
			size_t state_str_length = state_str.length();
			device.state = new char[state_str_length + 1];
			std::strcpy(device.state, state_str.c_str());
			DeviceTypeEnum deviceTypeEnum = getDeviceTypeEnum(device.type);
			switch (deviceTypeEnum)
			{
			case DeviceTypeEnum::LIGHT:
			case DeviceTypeEnum::SWITCH:
				if (strcmp(state_str.c_str(), "on") == 0)
				{
					//给它设置一个style
					lv_obj_set_style_img_recolor(lv_img_obj, lv_color_hex(0xff9914), 0);
				}
				else
				{
					lv_obj_set_style_img_recolor(lv_img_obj, lv_color_white(), 0);
				}
				break;
			default:
				printf("HassView: UpdateView unknown device type, do not change anything\n");
				break;
			}
		}
	}
}

void HassView::device_item_create(
	device_t** item,
	lv_obj_t* par,
	const char* name,
	char* entity_id,
	const char* img_src,
	bool is_on_off,
	bool is_set_value,
	char* device_type)
{
	*item = (device_t*)calloc(sizeof(device_t), 1);

	lv_obj_t* cont = lv_obj_create(par);
	// lv_obj_remove_style_all(cont);
	// lv_obj_set_size(cont, 42, 62);
	lv_obj_clear_flag(cont, LV_OBJ_FLAG_SCROLLABLE);

	lv_obj_set_flex_flow(cont, LV_FLEX_FLOW_COLUMN);

	lv_obj_t* img = lv_img_create(cont);
	lv_img_set_src(img, Resource.GetImage(img_src));
	// lv_obj_set_size(img, 42, 42);
	lv_obj_set_style_img_recolor_opa(img, LV_OPA_COVER, 0);
	lv_obj_set_style_img_recolor(img, lv_color_white(), 0);

	lv_obj_add_style(cont, &style.focus, LV_STATE_FOCUSED);
	lv_obj_add_style(cont, &style.cont, 0);

	lv_obj_add_style(cont, &style.edit, LV_STATE_EDITED);

	(*item)->cont = cont;

	(*item)->l_dev_name = lv_label_create(cont);
	lv_label_set_text_fmt((*item)->l_dev_name, "%s", name);
	lv_obj_set_size((*item)->l_dev_name, 0, 0);

	lv_obj_set_flex_align(
		cont,
		LV_FLEX_ALIGN_CENTER,
		LV_FLEX_ALIGN_CENTER,
		LV_FLEX_ALIGN_CENTER
	);

	(*item)->type = 0;
	(*item)->is_on_off = is_on_off;
	(*item)->is_set_value = is_set_value;
	(*item)->entity_id = entity_id;
	(*item)->state = (char*)malloc(sizeof(char) * (strlen("off") + 1));;
	(*item)->type = device_type;
	device_map[cont] = (*item);
	img_map[entity_id] = img;
	// lv_obj_add_event_cb(item->cont, on_event, LV_EVENT_ALL, NULL);
	printf("create an item: %p\n", item);
}

void HassView::device_item_create_settings(
	device_t* item,
	lv_obj_t* par,
	char* name)
{

	lv_obj_t* cont = lv_obj_create(par);
	// lv_obj_remove_style_all(cont);
	// lv_obj_set_size(cont, 42, 62);
	lv_obj_clear_flag(cont, LV_OBJ_FLAG_SCROLLABLE);

	lv_obj_set_flex_flow(cont, LV_FLEX_FLOW_COLUMN);

	lv_obj_t* img = lv_label_create(cont);
	lv_obj_set_style_text_color(img, lv_color_white(), 0);
	static lv_style_t icon_label_style;
	lv_style_init(&icon_label_style);
	lv_style_set_text_font(&icon_label_style, &lv_font_montserrat_26);
	lv_obj_add_style(img, &icon_label_style, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_label_set_text(img, LV_SYMBOL_SETTINGS);

	// lv_obj_set_size(img, 42, 42);
//	lv_obj_set_style_img_recolor_opa(img, LV_OPA_COVER, 0);
//	lv_obj_set_style_img_recolor(img, lv_color_white(), 0);

	lv_obj_add_style(cont, &style.focus, LV_STATE_FOCUSED);
	lv_obj_add_style(cont, &style.cont, 0);

	lv_obj_add_style(cont, &style.edit, LV_STATE_EDITED);
	item->cont = cont;

	item->l_dev_name = lv_label_create(cont);
	lv_label_set_text_fmt(item->l_dev_name, "%s", name);
	lv_obj_set_size(item->l_dev_name, 0, 0);

	item->type = getDeviceTypeNames(DeviceTypeEnum::SETTINGS);

	lv_obj_set_flex_align(
		cont,
		LV_FLEX_ALIGN_CENTER,
		LV_FLEX_ALIGN_CENTER,
		LV_FLEX_ALIGN_CENTER
	);

	item->is_on_off = true;
	item->is_set_value = false;
	item->entity_id = name;
	device_map[cont] = item;
	img_map[name] = img;
	// lv_obj_add_event_cb(item->cont, on_event, LV_EVENT_ALL, NULL);
	printf("create an settings item: %p\n", item);
}

void on_focus(lv_group_t* g)
{
	lv_obj_t* cont = lv_group_get_focused(g);
	lv_obj_t* cont_row = lv_obj_get_parent(cont);
	lv_coord_t x = lv_obj_get_x(cont);
	lv_coord_t width = lv_obj_get_width(cont);
	printf("device x: %d, width: %d\n", x, width);
	lv_obj_scroll_to_x(cont_row, x, LV_ANIM_ON);
}

void HassView::group_init(void)
{
	m_ui.group = lv_group_create();
	lv_group_set_focus_cb(m_ui.group, on_focus);
	lv_indev_set_group(lv_get_indev(LV_INDEV_TYPE_ENCODER), m_ui.group);

	uint16_t device_len = m_ui.device_len;
	for (int i = 0; i < device_len; ++i)
	{
		device_t device = m_ui.device_arr[i];
		lv_group_add_obj(m_ui.group, device.cont);
	}

	lv_group_add_obj(m_ui.group, m_ui.settings.cont);
	if (device_len > 0)
	{
		lv_group_focus_obj(m_ui.device_arr[0].cont);
	}
	else
	{
		lv_group_focus_obj(m_ui.settings.cont);
	}
}

void HassView::style_init(void)
{
	lv_style_init(&style.cont);
	lv_style_set_width(&style.cont, ITEM_PAD);
	lv_style_set_height(&style.cont, ITEM_PAD + 10);
	lv_style_set_bg_color(&style.cont, lv_color_black());
	lv_style_set_bg_opa(&style.cont, LV_OPA_TRANSP);
	lv_style_set_text_font(&style.cont, Resource.GetFont("bahnschrift_17"));
	lv_style_set_text_color(&style.cont, lv_color_white());

	//设备列表紫色焦点设备的边框
	lv_style_init(&style.focus);
	lv_style_set_border_side(&style.focus, LV_BORDER_SIDE_FULL);
	lv_style_set_border_width(&style.focus, 2);
	lv_style_set_border_color(&style.focus, lv_color_hex(0x9130CC));
	// lv_obj_set_flex_flow(&style.cont, LV_FLEX_FLOW_COLUMN);

	lv_style_init(&style.edit);

	// lv_style_img_recolor_opa(&style.edit, LV_OPA_COVER);
	// lv_style_img_recolor(&style.edit, lv_color_hex(0xFF0633));
	lv_style_set_bg_color(&style.edit, lv_color_hex(0x870AEA));

	static const lv_style_prop_t style_prop[] =
		{
			LV_STYLE_WIDTH,
			LV_STYLE_PROP_INV
		};

	static lv_style_transition_dsc_t trans;
	lv_style_transition_dsc_init(
		&trans,
		style_prop,
		lv_anim_path_overshoot,
		200,
		0,
		NULL
	);
	lv_style_set_transition(&style.focus, &trans);
	lv_style_set_transition(&style.cont, &trans);

	lv_style_init(&style.label_name);
//	lv_style_set_text_font(&style.label_name, Resource.GetFont("bahnschrift_22"));
	lv_style_set_text_font(&style.label_name, &myFont);
	lv_style_set_text_color(&style.label_name, lv_color_white());
}
void HassView::Create(lv_obj_t* root)
{
	printf("HassView: Create start\n");
	PlaygroundView::Create(root);

	lv_obj_t* cont_row = lv_obj_create(root);
	lv_obj_remove_style_all(cont_row);
	lv_obj_set_size(cont_row, ITEM_PAD * 3, 120);
	lv_obj_align(cont_row, LV_ALIGN_CENTER, 0, 5);
	lv_obj_set_flex_flow(cont_row, LV_FLEX_FLOW_ROW);
	lv_obj_set_flex_align(
		cont_row,
		LV_FLEX_ALIGN_START,
		LV_FLEX_ALIGN_START,
		LV_FLEX_ALIGN_CENTER
	);
	lv_obj_set_style_pad_column(cont_row, 10, 0);
	lv_obj_set_style_pad_hor(cont_row, ITEM_PAD, 0);

	// lv_obj_remove_style(obj, style, LV_PART_SCROLLBAR)

	style_init();

	//获取内存中所有设备
	uint16_t hass_device_arr_length = HassDeviceManager::getAllDeviceNum();
	hass_device_info_t* hass_device_info_arr = new hass_device_info_t[hass_device_arr_length];
	HassDeviceManager::getAllDeviceList(hass_device_info_arr, hass_device_arr_length);

	m_ui.device_len = hass_device_arr_length;
	m_ui.device_arr = new device_t[hass_device_arr_length];
	printf("HassView: Create device_len:%u\n", hass_device_arr_length);
	for (int i = 0; i < hass_device_arr_length; ++i)
	{
		hass_device_info_t hass_device_info = hass_device_info_arr[i];
		device_t* device = nullptr;
		device_item_create(
			&device,
			cont_row,
			hass_device_info.friendly_name,
			hass_device_info.entity_id,
			hass_device_info.img_src,
			hass_device_info.is_on_off,
			hass_device_info.is_set_value,
			hass_device_info.type
		);
		m_ui.device_arr[i] = *device;
	}
	delete[] hass_device_info_arr;

	device_item_create_settings(
		&m_ui.settings,
		cont_row,
		SETTINGS_STR);

	m_ui.foucs_label = lv_label_create(root);
	lv_obj_add_style(m_ui.foucs_label, &style.label_name, 0);
	lv_label_set_text_fmt(m_ui.foucs_label, "%s", SETTINGS_STR);
	lv_obj_align(m_ui.foucs_label, LV_ALIGN_CENTER, 0, ITEM_PAD + 10);

	// lv_obj_set_size(m_ui.foucs_label, 42, 20);
	// lv_obj_center(m_ui.foucs_label);

	group_init();
}

void HassView::Delete()
{
	printf("Deleting HassView\n");
	lv_group_del(m_ui.group);
	lv_style_reset(&style.cont);
	lv_style_reset(&style.focus);
	lv_style_reset(&style.edit);
	lv_style_reset(&style.label_name);
	printf("Delete done HassView\n");
}