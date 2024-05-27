#include <stdint.h>
#include <FastLED.h>

namespace rgb {
    #define NUM_LEDS 22
    #define LED_PIN 8
    #define LED_TYPE WS2812B
    #define COLOR_ORDER GRB

    void init_rgb();
    void read_rgb_info();
}