#pragma once

#include <stdint.h>

namespace data_manager {
    void save_rgb(uint8_t mode, uint8_t hue, uint8_t saturation, uint8_t brightness);
    void save_rgb_mode(uint8_t mode);
    void save_rgb_hue(uint8_t hue);
    void save_rgb_saturation(uint8_t saturation);
    void save_rgb_brightness(uint8_t brightness);

    uint8_t get_rgb_mode();
    uint8_t get_rgb_hue();
    uint8_t get_rgb_saturation();
    uint8_t get_rgb_brightness();

} // namespace data_manager
