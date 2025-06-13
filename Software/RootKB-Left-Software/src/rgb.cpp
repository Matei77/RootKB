#include "rgb.h"

namespace rgb {
    bool leds_reset_needed = true;
    rgb_info_t rgb_info = {rgb_mode_t::NONE, 0, 0, 0};
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
    // Update hue
    
    void hue_up() {
        if (rgb_info.mode != rgb_mode_t::ALL) {
            return;
        }

        if (rgb_info.hue + 10 > 250) {
            rgb_info.hue = 250;
        } else {
            rgb_info.hue = rgb_info.hue + 10;
            
            send_rgb_info_to_right_half();
            display_rgb_info();

            leds_reset_needed = true;
            set_all_leds(rgb_info.hue, rgb_info.saturation, rgb_info.brightness);

            data_manager::save_rgb_hue(rgb_info.hue);
        }
    }

    void hue_down() {
        if (rgb_info.mode != rgb_mode_t::ALL) {
            return;
        }

        if (rgb_info.hue - 10 < 0) {
            rgb_info.hue = 0;
        } else {
            rgb_info.hue = rgb_info.hue - 10;
            
            send_rgb_info_to_right_half();
            display_rgb_info();

            leds_reset_needed = true;
            set_all_leds(rgb_info.hue, rgb_info.saturation, rgb_info.brightness);

            data_manager::save_rgb_hue(rgb_info.hue);
        }
    }

    // -------------------------------------------------------------------------
    // Update brightness

    void brightness_up() {
        if (rgb_info.brightness + 25 > 250) {
            rgb_info.brightness = 250;
        } else {
            rgb_info.brightness = rgb_info.brightness + 25;
            
            send_rgb_info_to_right_half();
            display_rgb_info();

            leds_reset_needed = true;
            set_all_leds(rgb_info.hue, rgb_info.saturation, rgb_info.brightness);

            data_manager::save_rgb_brightness(rgb_info.brightness);
        }
    }

    void brightness_down() {
        if (rgb_info.brightness - 25 < 0) {
            rgb_info.brightness = 0;
        } else {
            rgb_info.brightness = rgb_info.brightness - 25;
            
            send_rgb_info_to_right_half();
            display_rgb_info();

            leds_reset_needed = true;
            set_all_leds(rgb_info.hue, rgb_info.saturation, rgb_info.brightness);

            data_manager::save_rgb_brightness(rgb_info.brightness);
        }
    }

    // -------------------------------------------------------------------------
    // Update saturation

    void saturation_up() {
        if (rgb_info.mode != rgb_mode_t::ALL) {
            return;
        }

        if (rgb_info.saturation + 25 > 250) {
            rgb_info.saturation = 250;
        } else {
            rgb_info.saturation = rgb_info.saturation + 25;
            
            send_rgb_info_to_right_half();
            display_rgb_info();

            leds_reset_needed = true;
            set_all_leds(rgb_info.hue, rgb_info.saturation, rgb_info.brightness);

            data_manager::save_rgb_saturation(rgb_info.saturation);
        }
    }

    void saturation_down() {
        if (rgb_info.mode != rgb_mode_t::ALL) {
            return;
        }

        if (rgb_info.saturation - 25 < 0) {
            rgb_info.saturation = 0;
        } else {
            rgb_info.saturation = rgb_info.saturation - 25;
            
            send_rgb_info_to_right_half();
            display_rgb_info();

            leds_reset_needed = true;
            set_all_leds(rgb_info.hue, rgb_info.saturation, rgb_info.brightness);

            data_manager::save_rgb_saturation(rgb_info.saturation);
        }
    }

    // -------------------------------------------------------------------------
    // Update current mode

    void mode_up() {
        rgb_info.mode = (rgb_mode_t)((rgb_info.mode + 1) % rgb_mode_t::EFFECTS_NR);
        if (rgb_info.mode != rgb_mode_t::RAINBOW) {
            leds_reset_needed = true;
        }

        send_rgb_info_to_right_half();
        data_manager::save_rgb_mode(rgb_info.mode);
    }

    void mode_down() {
        rgb_info.mode = (rgb_mode_t)((rgb_info.mode + EFFECTS_NR - 1) % rgb_mode_t::EFFECTS_NR);
        if (rgb_info.mode != rgb_mode_t::RAINBOW) {
            leds_reset_needed = true;
        }

        send_rgb_info_to_right_half();
        data_manager::save_rgb_mode(rgb_info.mode);
    }

    // -------------------------------------------------------------------------
    // Sending rgb info to right half or app

    void send_rgb_info_to_right_half() {
        right_half_com::send_request(right_half_com::request_t::SET_RGB);
        send_rgb_info_on_serial(Serial1);
    }

    void send_rgb_info_on_serial(Stream& serial) {
        size_t written_bytes = 0;
        while (written_bytes != sizeof(rgb_info)) {
            size_t bytes_left = sizeof(rgb_info) - written_bytes;
            if (serial.availableForWrite() >= (int)bytes_left) {
                size_t count = serial.write((byte *)&rgb_info + written_bytes, bytes_left);
                written_bytes += count;
            }
        }
        
        serial.flush();
    }

    // -------------------------------------------------------------------------
    // Show RGB confing on display

    void display_rgb_info() {
        oled::show_rgb_info(rgb_info.brightness, rgb_info.hue, rgb_info.saturation);
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
