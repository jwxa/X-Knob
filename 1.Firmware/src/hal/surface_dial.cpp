#include "hal/hal.h"
#include "BleKeyboard.h"

BleKeyboard bleKeyboard("Surface Dial(X)");



void HAL::surface_dial_init()
{
    bleKeyboard.begin();
}

bool HAL::surface_dial_is_connected()
{
    return bleKeyboard.isConnected();
}

void HAL::surface_dial_press()
{
    bleKeyboard.sendDialReport(DIAL_PRESS);
}

void HAL::surface_dial_release()
{
    bleKeyboard.sendDialReport(DIAL_RELEASE);
}


void HAL::surface_dial_update(SuperDialMotion direction)
{
    if (bleKeyboard.isConnected()) {

        switch (direction)
        {
        case SUPER_DIAL_LEFT:
            bleKeyboard.sendDialReport(DIAL_L);
            break;
        case SUPER_DIAL_RIGHT:
            bleKeyboard.sendDialReport(DIAL_R);
            break;
        default:
            Serial.println("SuperDial: Error direction parameter");
            break;
        }
    }
}