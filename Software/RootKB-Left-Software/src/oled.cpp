#include <Adafruit_SSD1306.h>
// #include <Adafruit_GFX.h>
#include <Wire.h>
#include "oled.h"

namespace oled {
    Adafruit_SSD1306 display(128, 32, &Wire, -1);
    const uint64_t time_window = 3000; // 3 seconds
    uint64_t reset_time = 0;
    bool display_logo_flag = true;

    void init_oled() {
        if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
            Serial.println(F("SSD1306 allocation failed"));
        }

        delay(2000);
        
        display.clearDisplay();
        display.setTextSize(2);
        display.setTextColor(WHITE);
        display.setCursor(20, 10);
        display.println("RootKB");
        display.display();
        display_logo_flag = true;
    }

    void display_logo() {
        if (millis() < reset_time || display_logo_flag == true) {
            return;
        }

        display.clearDisplay();
        display.setTextSize(2);
        display.setTextColor(WHITE);
        display.setCursor(20, 10);
        display.println("RootKB");
        display.display();
        display_logo_flag = true;
    }

    void show_rgb_info(uint8_t brightness, uint8_t hue, uint8_t saturation) {
        String brightness_str = String(brightness);
        String hue_str = String(hue);
        String saturation_str = String(saturation);
        
        display.clearDisplay();
        display.setTextSize(1);
        display.setTextColor(WHITE);
        display.setCursor(0, 0);

        display.print("B: " + brightness_str 
                  + "\nH: " + hue_str 
                  + "\nS: " + saturation_str);
        
        display.display();
        display_logo_flag = false;

        reset_time = millis() + time_window;
    }
}