#include <FastLED.h>
#include "rgb.h"
#include "oled.h"
#include "request.h"
#include "data_manager.h"

namespace rgb {
    bool leds_reset = true;
    rgb_mode_t current_mode = rgb_mode_t::ALL;
    uint8_t brightness = 250;
    uint8_t saturation = 0;
    uint8_t hue = 0;
    CRGB leds[NUM_LEDS];
    const uint64_t effect_speed = 25;
    uint64_t effect_reset_time = 0;

    
    void init_rgb() {
        FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
        FastLED.setBrightness(250);

        current_mode = (rgb_mode_t)data_manager::get_rgb_mode();
        hue = data_manager::get_rgb_hue();
        saturation = data_manager::get_rgb_saturation();
        brightness = data_manager::get_rgb_brightness();
        
        // send_rgb_info();
        
        if (current_mode != RAINBOW) {
            leds_reset = true;
        } 
        // set_all_leds(hue, saturation, brightness);

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

    void hue_up() {
        if (current_mode != rgb_mode_t::ALL) {
            return;
        }

        if (hue + 10 > 250) {
            hue = 250;
        } else {
            hue = hue + 10;
            
            send_rgb_info();
            display_rgb_info();

            leds_reset = true;
            set_all_leds(hue, saturation, brightness);

            data_manager::save_rgb_hue(hue);
        }
    }

    void hue_down() {
        if (current_mode != rgb_mode_t::ALL) {
            return;
        }

        if (hue - 10 < 0) {
            hue = 0;
        } else {
            hue = hue - 10;
            
            send_rgb_info();
            display_rgb_info();

            leds_reset = true;
            set_all_leds(hue, saturation, brightness);

            data_manager::save_rgb_hue(hue);
        }
    }

    void brightness_up() {
        if (brightness + 25 > 250) {
            brightness = 250;
        } else {
            brightness = brightness + 25;
            
            send_rgb_info();
            display_rgb_info();

            leds_reset = true;
            set_all_leds(hue, saturation, brightness);

            data_manager::save_rgb_brightness(brightness);
        }
    }

    void brightness_down() {
        if (brightness - 25 < 0) {
            brightness = 0;
        } else {
            brightness = brightness - 25;
            
            send_rgb_info();
            display_rgb_info();

            leds_reset = true;
            set_all_leds(hue, saturation, brightness);

            data_manager::save_rgb_brightness(brightness);
        }
    }

    void saturation_up() {
        if (current_mode != rgb_mode_t::ALL) {
            return;
        }

        if (saturation + 25 > 250) {
            saturation = 250;
        } else {
            saturation = saturation + 25;
            
            send_rgb_info();
            display_rgb_info();

            leds_reset = true;
            set_all_leds(hue, saturation, brightness);

            data_manager::save_rgb_saturation(saturation);
        }
    }

    void saturation_down() {
        if (current_mode != rgb_mode_t::ALL) {
            return;
        }

        if (saturation - 25 < 0) {
            saturation = 0;
        } else {
            saturation = saturation - 25;
            
            send_rgb_info();
            display_rgb_info();

            leds_reset = true;
            set_all_leds(hue, saturation, brightness);

            data_manager::save_rgb_saturation(saturation);
        }
    }

    void mode_up() {
        current_mode = (rgb_mode_t)((current_mode + 1) % rgb_mode_t::EFFECTS_NR);
        if (current_mode != RAINBOW) {
            leds_reset = true;
        }
        send_rgb_info();

        data_manager::save_rgb_mode(current_mode);
    }

    void mode_down() {
        current_mode = (rgb_mode_t)((current_mode + EFFECTS_NR - 1) % rgb_mode_t::EFFECTS_NR);
        if (current_mode != RAINBOW) {
            leds_reset = true;
        }
        send_rgb_info();

        data_manager::save_rgb_mode(current_mode);
    }

    void send_rgb_info() {
        request::send_request(request::SET_RGB);

        uint8_t rgb_info[4] = {(uint8_t)current_mode, hue, saturation, brightness};

        size_t written_bytes = 0;
        while (written_bytes != sizeof(rgb_info)) {
            size_t bytes_left = sizeof(rgb_info) - written_bytes;
            if (Serial1.availableForWrite() >= (int)bytes_left) {
                size_t count = Serial1.write(rgb_info + written_bytes, bytes_left);
                written_bytes += count;
            }
        }
        
        Serial1.flush();
    }

    void display_rgb_info() {
        oled::show_rgb_info(brightness, hue, saturation);
    }

    void rainbow_effect() {
        static uint8_t baseHue = 0;
        
        if (millis() > effect_reset_time) {
            for (uint8_t i = 0; i < NUM_LEDS; ++i) {
                leds[i] = CHSV(baseHue + (i * 5), 250, brightness);
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