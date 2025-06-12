#pragma once

#include "keys.h"

namespace oled {
    void init_oled();
    void display_logo();
    void show_rgb_info(uint8_t brightness, uint8_t hue, uint8_t saturation);
    void displayVal(keys::raw_keycode_t num);
    void displaySize(size_t num);
}