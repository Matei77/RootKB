#include "matrix.h"
#include "keyboard.h"
#include "rgb.h"
#include "oled.h"
#include "app_com.h"
#include "data_manager.h"

// RootKB Left

void setup() {
    Serial.begin(9600);
    Serial1.begin(115200);
    
    matrix::init_matrix_pins();
    keyboard::init_keyboard();
    rgb::init_rgb();
    oled::init_oled();

    delay(1000);
}

void loop() {
    rgb::light_rgb_effect();
    oled::display_logo();
    matrix::get_full_matrix();
    keyboard::process_keypresses();
    app_com::manage_app_request();
}
