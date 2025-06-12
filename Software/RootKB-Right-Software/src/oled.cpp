#include <Adafruit_SSD1306.h>
// #include <Adafruit_GFX.h>
#include <Wire.h>
#include "oled.h"

namespace oled {
    Adafruit_SSD1306 display(128, 32, &Wire, -1);

    void init_oled() {
        display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

        delay(2000);
        
        display.clearDisplay();
        display.setTextSize(2);
        display.setTextColor(WHITE);
        display.setCursor(20, 10);
        display.println("RootKB");
        display.display();
    }
}