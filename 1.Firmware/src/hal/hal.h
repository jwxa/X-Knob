#ifndef __HAL_H__
#define __HAL_H__
#include "button_event.h"
#include "HAL_Def.h"
#include <Arduino.h>
#include "config.h"
#include "CommonMacro.h"

typedef enum {
    SUPER_DIAL_NULL = 0,
    SUPER_DIAL_LEFT = 1,
    SUPER_DIAL_RIGHT= 2,
} SuperDialMotion;

typedef enum {
    HASS_LEFT = 1,
    HASS_RIGHT= 2,
    HASS_PUSH = 3,
    HASS_MAX,
} HassMotion;

namespace HAL
{
    void Init();
    void Update();

    void knob_init();
    void knob_update();
    bool encoder_is_pushed();

    void motor_init();
    // void TaskMotorUpdate(void *pvParameters);
    int get_motor_position();
    void update_motor_mode(int mode);
    void motor_shake(int strength, int delay_time);

    void surface_dial_init();
    void surface_dial_update(SuperDialMotion direction);
    void surface_dial_release();
    void surface_dial_press();
    bool surface_dial_is_connected();

    void power_init();
    void power_off();

    bool is_encoder_enabled();
    void encoder_disable();
    void encoder_enable();

	void nvs_init();
	void wifi_init();

    void mqtt_init();
    int mqtt_publish(const char *topic, const char *playload);
	int mqtt_subscribe(const char *topic);
	int mqtt_unsubscribe(const char *topic);
	bool is_mqtt_connected();
}


#endif