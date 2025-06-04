#include <FastLED.h>
#include "rgb.h"
#include "oled.h"

namespace rgb {
    uint8_t brightness = 250;
    uint8_t saturation = 250;
    uint8_t hue = 0;
    CRGB leds[NUM_LEDS];

    void init_rgb() {
        FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
        FastLED.setBrightness(brightness);

        for (uint8_t led_index = 0; led_index < NUM_LEDS; ++led_index) {
            leds[led_index] = CHSV(hue, saturation, brightness);
        }

        FastLED.show();
    }

    void hue_up() {
        if (hue + 10 > 250) {
            hue = 250;
        } else {
            hue = hue + 10;

            send_rgb_info();
            display_rgb_info();

            for (uint8_t led_index = 0; led_index < NUM_LEDS; ++led_index) {
                leds[led_index] = CHSV(hue, saturation, brightness);
            }

            FastLED.show();
        }
    }

    void hue_down() {
        if (hue - 10 < 0) {
            hue = 0;
        } else {
            hue = hue - 10;

            send_rgb_info();
            display_rgb_info();

            for (uint8_t led_index = 0; led_index < NUM_LEDS; ++led_index) {
                leds[led_index] = CHSV(hue, saturation, brightness);
            }
    
            FastLED.show();
        }
    }

    void brightness_up() {
        if (brightness + 25 > 250) {
            brightness = 250;
        } else {
            brightness = brightness + 25;

            send_rgb_info();
            display_rgb_info();

            for (uint8_t led_index = 0; led_index < NUM_LEDS; ++led_index) {
                leds[led_index] = CHSV(hue, saturation, brightness);
            }

            FastLED.show();
        }
    }

    void brightness_down() {
        if (brightness - 25 < 0) {
            brightness = 0;
        } else {
            brightness = brightness - 25;

            send_rgb_info();
            display_rgb_info();

            for (uint8_t led_index = 0; led_index < NUM_LEDS; ++led_index) {
                leds[led_index] = CHSV(hue, saturation, brightness);
            }

            FastLED.show();
        }
    }

    void saturation_up() {
        if (saturation + 25 > 250) {
            saturation = 250;
        } else {
            saturation = saturation + 25;
        
            send_rgb_info();
            display_rgb_info();

            for (uint8_t led_index = 0; led_index < NUM_LEDS; ++led_index) {
                leds[led_index] = CHSV(hue, saturation, brightness);
            }

            FastLED.show();
        }
    }

    void saturation_down() {
        if (saturation - 25 < 0) {
            saturation = 0;
        } else {
            saturation = saturation - 25;

            send_rgb_info();
            display_rgb_info();
            
            for (uint8_t led_index = 0; led_index < NUM_LEDS; ++led_index) {
                leds[led_index] = CHSV(hue, saturation, brightness);
            }

            FastLED.show();

        }
    }

    void send_rgb_info() {
        uint8_t rgb_info[3] = {hue, saturation, brightness};
        if (Serial1.availableForWrite() >= 3) {
            Serial1.write(rgb_info, 3);
        }
    }

    void display_rgb_info() {
        oled::show_rgb_info(brightness, hue, saturation);
    }
}