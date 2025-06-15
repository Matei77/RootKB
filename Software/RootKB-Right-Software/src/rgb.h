#pragma once

#include <stdint.h>
#include <FastLED.h>

#include "serial.h"
#include "data_manager.h"

namespace rgb {
    #define NUM_LEDS 22
    #define LED_PIN 8
    #define LED_TYPE WS2812B
    #define COLOR_ORDER GRB

    // -------------------------------------------------------------------------

    enum rgb_mode_t : uint8_t {
        NONE,
        ALL,
        RAINBOW,
        COLOR_CYCLE,
        WAVE,
        EFFECTS_NR
    };

    // -------------------------------------------------------------------------

    struct __attribute__((packed)) rgb_info_t {
        rgb_mode_t mode;
        uint8_t hue;
        uint8_t saturation;
        uint8_t brightness;
    };

    // -------------------------------------------------------------------------

    void init_rgb();
    void set_all_leds(uint8_t hue, uint8_t saturation, uint8_t brightness);
    void reset_leds_if_needed();
    void set_rgb();

    void rainbow_effect();
    void color_cycle_effect();
    void wave_effect();
    void light_rgb_effect();

} // namespace rgb
