#include <FastLED.h>
#include "rgb.h"
#include "data_manager.h"

namespace rgb {
    bool leds_reset_needed = true;
    rgb_info_t rgb_info = {rgb_mode_t::NONE, 250, 250, 250};
    CRGB leds[NUM_LEDS];

    const uint64_t effect_speed = 50;
    uint64_t effect_reset_time = 0;

    // -------------------------------------------------------------------------
    // initialize leds and get rgb_info from eeprom
    
    void init_rgb() {
        FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
        FastLED.setBrightness(250);
        
        rgb_info.mode = (rgb_mode_t)data_manager::get_rgb_mode();
        rgb_info.hue = data_manager::get_rgb_hue();
        rgb_info.saturation = data_manager::get_rgb_saturation();
        rgb_info.brightness = data_manager::get_rgb_brightness();
        
        if (rgb_info.mode != rgb_mode_t::RAINBOW) {
            leds_reset_needed = true;
        } 
    }

    // -------------------------------------------------------------------------
    // Set all leds to a color
    
    void set_all_leds(uint8_t hue, uint8_t saturation, uint8_t brightness) {
        if (leds_reset_needed == true) {
            for (uint8_t led_index = 0; led_index < NUM_LEDS; ++led_index) {
                leds[led_index] = CHSV(hue, saturation, brightness);
            }
            
            FastLED.show();
            
            leds_reset_needed = false;
        }
    }

    // -------------------------------------------------------------------------
    // Read rgb_info from serial and save it to eeprom
    // This function is called when the SET_RGB request is received.

    void set_rgb() {
        size_t read_bytes = 0;
        while (read_bytes != sizeof(rgb_info)) {
            size_t bytes_left = sizeof(rgb_info) - read_bytes;
            if (Serial1.available() >= (int)bytes_left) {
                size_t count = Serial1.readBytes((byte *)&rgb_info + read_bytes, bytes_left);
                read_bytes += count;
            }
        }

        if (rgb_info.mode != rgb_mode_t::RAINBOW) {
            leds_reset_needed = true;
        }

        data_manager::save_rgb((uint8_t)rgb_info.mode, rgb_info.hue, rgb_info.saturation, rgb_info.brightness);
    }

    // -------------------------------------------------------------------------
    // Rainbow Effect

    void rainbow_effect() {
        static uint8_t baseHue = 0;
        
        if (millis() > effect_reset_time) {
            for (uint8_t i = 0; i < NUM_LEDS; ++i) {
                leds[i] = CHSV(baseHue + (i * 5), 250, rgb_info.brightness);
            }
            FastLED.show();
            baseHue++;
            effect_reset_time = millis() + effect_speed;
        }
    }

    // -------------------------------------------------------------------------
    // Manage all light effects. Called in main loop

    void light_rgb_effect() {
        switch (rgb_info.mode) {
            case rgb_mode_t::NONE:
                set_all_leds(0,0,0);
                break;

            case rgb_mode_t::ALL:
                set_all_leds(rgb_info.hue, rgb_info.saturation, rgb_info.brightness);
                break;

            case rgb_mode_t::RAINBOW:
                rainbow_effect();
                break;
            
            default:
                break;
        }
    }

} // namespace rgb
