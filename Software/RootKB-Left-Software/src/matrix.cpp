#include <Arduino.h>
#include "matrix.h"
#include "request.h"

namespace matrix {
    matrix_t matrix_left = 0;
    matrix_t matrix_right = 0;
    matrix_t matrix_all = 0;
    const uint64_t read_interval = 20;
    uint64_t reset_time = 0;


    void init_matrix_pins() {
        for (uint8_t row_index = 0; row_index < MATRIX_ROWS; ++row_index) {
            pinMode(MATRIX_ROW_PINS[row_index], INPUT_PULLUP);
        }

        for (uint8_t col_index = 0; col_index < MATRIX_COLS; ++col_index) {
            pinMode(MATRIX_COL_PINS[col_index], INPUT);
        }
    }

    void get_matrix_right() {
        matrix_right = 0;
        request::send_request(request::GET_MATRIX);
        
        // Serial.println(Serial1.available());
        size_t read_bytes = 0;
        while (read_bytes != sizeof(matrix_right)) {
            size_t bytes_left = sizeof(matrix_right) - read_bytes;
            if (Serial1.available() >= (int)bytes_left) {
                size_t count = Serial1.readBytes((byte *)&matrix_right + read_bytes, bytes_left);
                read_bytes += count;
            } 
            // else {
            //     Serial.print("Waiting for more bytes");
            // }
        }
        // }
        // Serial.print("Read bytes: ");
        // Serial.println(read_bytes);
            // Serial.print("Received right half: ");
            // byte* bytePtr = (byte*)&matrix_right;
            // for (size_t i = 0; i < sizeof(matrix_right); i++) {
            //     // Serial.print("0x");
            //     // if (bytePtr[i] < 0x10) Serial.print("0");
            //     Serial.print(bytePtr[i], BIN);
            //     Serial.print(" ");
            // }
            // Serial.println();
        // }
    }

    void read_matrix() {
        // read the matrix
        matrix_left = 0;

        for (uint8_t row_index = 0; row_index < MATRIX_ROWS; ++row_index) {
            uint8_t cur_row_pin = MATRIX_ROW_PINS[row_index];
            pinMode(cur_row_pin, OUTPUT);

            digitalWrite(cur_row_pin, LOW);

            for (uint8_t col_index = 0; col_index < MATRIX_COLS; ++col_index) {
                uint8_t cur_col_pin = MATRIX_COL_PINS[col_index];
                pinMode(cur_col_pin, INPUT_PULLUP);

                if (digitalRead(cur_col_pin) == LOW) {
                    set_matrix_key_left(matrix_left, row_index, col_index);
                }

                pinMode(cur_col_pin, INPUT);
            }

            // disable the row
            pinMode(cur_row_pin, INPUT);
        }
    }

    void get_full_matrix() {

        if (millis() > reset_time) {
            read_matrix();
            get_matrix_right();

            matrix_all = matrix_left | matrix_right;
            // Serial.print("Matrix all: ");
            // byte* bytePtr = (byte*)&matrix_all;
            // for (size_t i = 0; i < sizeof(matrix_all); i++) {
            //     // Serial.print("0x");
            //     // if (bytePtr[i] < 0x10) Serial.print("0");
            //     Serial.print(bytePtr[i], BIN);
            //     Serial.print(" ");
            // }
            // Serial.println();

            reset_time = millis() + read_interval;
        }

    }

    // void print_matrix(uint64_t matrix) {
    //     for (uint8_t row_index = 0; row_index < MATRIX_ROWS; ++row_index) {
    //         if (row_index < 10) {
    //             Serial.print(F("0"));
    //         }
    //         Serial.print(row_index);
    //         Serial.print(F(": "));

    //         for (uint8_t col_index = 0; col_index < MATRIX_COLS_BOTH; ++col_index) {
    //             Serial.print(get_matrix_key_global(matrix, row_index, col_index));
    //             if (col_index < MATRIX_COLS_BOTH - 1) {
    //                 Serial.print(F(", "));
    //             }
    //         }
    //         Serial.println("");
    //     }
    //     Serial.println("");
    // }

} // namespace matrix