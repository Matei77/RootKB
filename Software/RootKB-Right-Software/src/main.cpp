#include "matrix.h"
#include "rgb.h"
#include "oled.h"

// RootKB Right

void setup() {
    Serial.begin(9600);
    Serial1.begin(115200);

    matrix::init_matrix_pins();
    rgb::init_rgb();
    oled::init_oled();

    delay(1000);
}


void loop() {
    // if (Serial.read() == 'p') {
    //     matrix::print_matrix();
    // }

    matrix::send_matrix();

    rgb::read_rgb_info();
}