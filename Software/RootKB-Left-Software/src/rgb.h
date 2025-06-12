#pragma once

#include <stdint.h>
#include <FastLED.h>

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

    void init_rgb();
    void set_all_leds(uint8_t hue, uint8_t saturation, uint8_t brightness);
    void hue_up();
    void hue_down();
    void brightness_up();
    void brightness_down();
    void saturation_up();
    void saturation_down();
    void send_rgb_info();
    void display_rgb_info();
    void rainbow_effect();
    void mode_up();
    void mode_down();
    void light_rgb_effect();
}