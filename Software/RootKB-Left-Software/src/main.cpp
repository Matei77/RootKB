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
    // data_manager::init_eeprom();
    // data_manager::save_layout(keys::initial_layout);

    delay(1000);
}

void loop() {
    rgb::light_rgb_effect();
    oled::display_logo();
    matrix::get_full_matrix();
    keyboard::send_keys();
    // app_com::receive_layout();
}
