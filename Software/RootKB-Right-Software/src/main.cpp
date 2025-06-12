#include <Arduino.h>

#include "matrix.h"
#include "rgb.h"
#include "oled.h"
#include "request.h"

// RootKB Right

void setup() {
    // Serial.begin(9600);
    Serial1.begin(115200);

    matrix::init_matrix_pins();
    rgb::init_rgb();
    oled::init_oled();

    delay(1000);
}


void loop() {
    request::manage_request();
    rgb::light_rgb_effect();
}