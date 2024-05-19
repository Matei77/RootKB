#include <Arduino.h>
#include <Keyboard.h>
#include <Wire.h>
#include <FastLED.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "matrix.h"
#include "keys.h"

// RootKB Left

int send_keys = 1;

void setup() {
    Serial.begin(9600);
    Serial1.begin(115200);
    
    matrix::init_matrix_pins();
    keys::init_keys();

    delay(1000);
}

void loop() {
    matrix::get_full_matrix();

    if (Serial.read() == 'p') {
        Serial.println("matrix all:");
        matrix::print_matrix(matrix::matrix_all);
    }

    if (matrix::get_matrix_key_global(matrix::matrix_all, 0, 0) == 1) {
        send_keys = 0;
        Serial.println("Send keys off");
    }

    if (send_keys == 1) {
        keys::send_keys();
    }
}
