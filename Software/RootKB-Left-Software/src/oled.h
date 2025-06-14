#pragma once

#include <Adafruit_SSD1306.h>
#include <Wire.h>

namespace oled {
    void init_oled();
    void display_logo();
    void show_rgb_info(uint8_t brightness, uint8_t hue, uint8_t saturation);

} // namespace oled
