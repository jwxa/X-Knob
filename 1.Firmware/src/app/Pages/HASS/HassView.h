#ifndef __HOME_ASSISTANT_VIEW_H
#define __HOME_ASSISTANT_VIEW_H
#include "Arduino.h"
#include "app/app.h"
#include "../Page.h"
#include "../Playground/PlaygroundView.h"
#include "app/Utils/HassDeviceManager/HassDeviceManager.h"
#include "HassModel.h"
#include <map>

enum HASS_VIEW_MODE {
    VIEW_MODE_ON_OFF = 1,
};

enum VIEW_TYPE {
	DEVICE = 0,
	SETTINGS = 1
};

typedef struct
{
    lv_obj_t* cont;   // include icon and label
    lv_obj_t* l_dev_name;
    char* type;
    bool is_on_off;
    bool is_set_value;
	char* entity_id;
	char* state;
} device_t;

namespace Page
{

class HassView: public PlaygroundView
{
public:
    HassView(){}
    void Create(lv_obj_t* root);
    void Delete();
    void UpdateView(HassInfo *info);
    void SetPlaygroundMode(int16_t mode);
    void UpdateFocusedDevice(const char* name);
    void SetCtrView(lv_obj_t *obj,lv_obj_t *root);
    void ClearCtrView(lv_obj_t *obj);
	void UpdateCtrlView(HassInfo* info, const char* entity_id, const char* state, lv_obj_t* lv_img_obj);
    char* GetEditedDevice(device_t** device);
    int GetViewMode(void);
    struct
    {
		device_t* device_arr;
		uint16_t device_len;
        device_t settings;
        lv_obj_t* foucs_label;
        lv_group_t* group;
    } m_ui;

private:
    int current_view = 0;
	std::map<lv_obj_t*, device_t *>device_map;
	std::map<std::string, lv_obj_t*> img_map;
    struct
    {
        lv_style_t cont;
        lv_style_t focus;
        lv_style_t edit;
        lv_style_t label_name;
    } style;
    void group_init(void);
    void style_init(void);
	void device_item_create(device_t** item, lv_obj_t* par,
		const char* name, char* entity_id, const char* img_src,
		bool is_on_off, bool is_set_value, char* device_type);
    void device_item_create_settings(device_t* item, lv_obj_t* par,
		char* name);
    void AttachEvent(lv_obj_t* obj);

};

}

#endif // !__VIEW_H
