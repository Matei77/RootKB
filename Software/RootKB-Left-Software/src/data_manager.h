#pragma once

#include <stdint.h>

#include "kb_conf.h"

namespace data_manager {
    void save_rgb(uint8_t mode, uint8_t hue, uint8_t saturation, uint8_t brightness);
    void save_rgb_mode(const uint8_t mode);
    void save_rgb_hue(const uint8_t hue);
    void save_rgb_saturation(const uint8_t saturation);
    void save_rgb_brightness(const uint8_t brightness);

    uint8_t get_rgb_mode();
    uint8_t get_rgb_hue();
    uint8_t get_rgb_saturation();
    uint8_t get_rgb_brightness();

    void save_layout(const kb_conf::raw_keycode_t layout[kb_conf::LAYERS][kb_conf::ROWS][kb_conf::COLS]);
    void load_layout(kb_conf::raw_keycode_t layout[kb_conf::LAYERS][kb_conf::ROWS][kb_conf::COLS]);

} // namespace data_manager
