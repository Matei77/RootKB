#include <FastLED.h>
#include "rgb.h"

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

    void read_rgb_info() {
        if (Serial1.available() >= 3) {
            uint8_t rgb_info[3];
            Serial1.readBytes(rgb_info, 3);

            hue = rgb_info[0];
            saturation = rgb_info[1];
            brightness = rgb_info[2];

            for (uint8_t led_index = 0; led_index < NUM_LEDS; ++led_index) {
                leds[led_index] = CHSV(hue, saturation, brightness);
            }

            FastLED.show();
        }
    }
}