#include <FastLED.h>
#include "rgb.h"

namespace rgb {
    uint8_t brightness = 255;
    uint8_t saturation = 255;
    uint8_t hue = 170;
    CRGB leds[NUM_LEDS];

    void init_rgb() {
        FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
        FastLED.setBrightness(brightness);

        for (uint8_t led_index = 0; led_index < NUM_LEDS; ++led_index) {
            leds[led_index] = CHSV(hue, saturation, brightness);
        }

        FastLED.show();
    }
}