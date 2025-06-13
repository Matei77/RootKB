#pragma once

#include <Adafruit_SSD1306.h>
#include <Wire.h>

#include "keyboard.h"

namespace oled {
    void init_oled();
    void display_logo();
    void show_rgb_info(uint8_t brightness, uint8_t hue, uint8_t saturation);
    // void displaySize(size_t num);
    // void displayVal(keyboard::raw_keycode_t num);
} // namespace oled