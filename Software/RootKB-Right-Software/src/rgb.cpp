#include <FastLED.h>
#include "rgb.h"

namespace rgb {
    bool leds_reset = true;
    rgb_mode_t current_mode = rgb_mode_t::ALL;
    uint8_t brightness = 250;
    uint8_t saturation = 250;
    uint8_t hue = 0;
    CRGB leds[NUM_LEDS];
    const uint64_t effect_speed = 25;
    uint64_t effect_reset_time = 0;

    void init_rgb() {
        FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
        FastLED.setBrightness(brightness);

        for (uint8_t led_index = 0; led_index < NUM_LEDS; ++led_index) {
            leds[led_index] = CHSV(hue, saturation, brightness);
        }

        FastLED.show();
    }

    void set_all_leds(uint8_t hue, uint8_t saturation, uint8_t brightness) {
        if (leds_reset == true) {
            for (uint8_t led_index = 0; led_index < NUM_LEDS; ++led_index) {
                leds[led_index] = CHSV(hue, saturation, brightness);
            }
            
            FastLED.show();

            leds_reset = false;
        }
    }

    void set_rgb() {
        uint8_t rgb_info[4];
        size_t read_bytes = 0;
        while (read_bytes != sizeof(rgb_info)) {
            size_t bytes_left = sizeof(rgb_info) - read_bytes;
            if (Serial1.available() >= (int)bytes_left) {
                size_t count = Serial1.readBytes((byte *)rgb_info + read_bytes, bytes_left);
                read_bytes += count;
            }
        }

        current_mode = (rgb_mode_t)rgb_info[0];
        hue = rgb_info[1];
        saturation = rgb_info[2];
        brightness = rgb_info[3];

        if (current_mode != RAINBOW) {
            leds_reset = true;
        }
    }

    void rainbow_effect() {
        static uint8_t baseHue = 0;
        
        if (millis() > effect_reset_time) {
            for (uint8_t i = 0; i < NUM_LEDS; ++i) {
                leds[i] = CHSV(baseHue + (i * 5), saturation, brightness);
            }
            FastLED.show();
            baseHue++;
            effect_reset_time = millis() + effect_speed;
        }
    }

    void light_rgb_effect() {
        switch (current_mode) {
            case NONE:
                set_all_leds(0,0,0);
                break;

            case ALL:
                set_all_leds(hue, saturation, brightness);
                break;

            case RAINBOW:
                rainbow_effect();
                break;
            
            default:
                break;
        }
    }
}