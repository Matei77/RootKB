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
        Serial.println("keys mask:");
        matrix::print_matrix(keys::keys_mask);
        Serial.println("F bit:");
        uint64_t fbit = matrix::get_matrix_bit_global(keys::keys_mask, 2, 4);
        matrix::print_matrix(fbit);
    }

    if (matrix::get_matrix_key_global(matrix::matrix_all, 3, 4) == 1) {
        send_keys = 0;
        Serial.println("Send keys off");
    }

    if (send_keys == 1) {
        keys::send_keys();
    }
}
