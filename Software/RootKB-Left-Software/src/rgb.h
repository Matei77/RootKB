#pragma once

#include <stdint.h>
#include <FastLED.h>

#include "oled.h"
#include "right_half_com.h"
#include "data_manager.h"
#include "serial.h"

namespace rgb {
    #define NUM_LEDS 22
    #define LED_PIN 8
    #define LED_TYPE WS2812B
    #define COLOR_ORDER GRB

    enum rgb_mode_t : uint8_t {
        NONE,
        ALL,
        RAINBOW,
        EFFECTS_NR
    };

    struct __attribute__((packed)) rgb_info_t {
        rgb_mode_t mode;
        uint8_t hue;
        uint8_t saturation;
        uint8_t brightness;
    };

    void init_rgb();
    void set_all_leds(uint8_t hue, uint8_t saturation, uint8_t brightness);
    void reset_leds_if_needed();

    void hue_up();
    void hue_down();
    void brightness_up();
    void brightness_down();
    void saturation_up();
    void saturation_down();
    void mode_up();
    void mode_down();
    
    void send_rgb_info_to_right_half();
    void send_rgb_info_to_app();

    void receive_rgb_info_from_app();
    
    void display_rgb_info();

    void rainbow_effect();
    void light_rgb_effect();

} // namespace rgb
