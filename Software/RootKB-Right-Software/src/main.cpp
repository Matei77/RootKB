#include <Arduino.h>
#include <Keyboard.h>
#include <Wire.h>
#include <FastLED.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "matrix.h"
#include "config.h"

// RootKB Right

void setup() {
    Serial.begin(9600);
    Serial1.begin(115200);

    matrix::init_matrix_pins();

    delay(1000);
}


void loop() {
    if (Serial.read() == 'p') {
        matrix::print_matrix();
    }

    matrix::send_matrix();
}