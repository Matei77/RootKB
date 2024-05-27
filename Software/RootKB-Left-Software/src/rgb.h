#include <stdint.h>
#include <FastLED.h>

namespace rgb {
    #define NUM_LEDS 22
    #define LED_PIN 8
    #define LED_TYPE WS2812B
    #define COLOR_ORDER GRB

    void init_rgb();
    void hue_up();
    void hue_down();
    void brightness_up();
    void brightness_down();
    void saturation_up();
    void saturation_down();
    void send_rgb_info();
    void display_rgb_info();
}