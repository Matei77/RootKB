#include <Arduino.h>
#include "matrix.h"

namespace matrix {
    matrix_t matrix_left = 0;
    matrix_t matrix_right = 0;
    matrix_t matrix_all = 0;

    void init_matrix_pins() {
        for (uint8_t row_index = 0; row_index < MATRIX_ROWS; ++row_index) {
            pinMode(MATRIX_ROW_PINS[row_index], INPUT_PULLUP);
        }

        for (uint8_t col_index = 0; col_index < MATRIX_COLS; ++col_index) {
            pinMode(MATRIX_COL_PINS[col_index], INPUT);
        }
    }

    void get_matrix_right() {        
        if (Serial1.available() >= (int)sizeof(matrix_right)) {
            size_t read_bytes = 0;
            while (read_bytes != sizeof(matrix_right)) {
                size_t bytes_left = sizeof(matrix_right) - read_bytes;
                size_t count = Serial1.readBytes((byte *)&matrix_right, bytes_left);
                read_bytes += count;
            }
        }
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
        read_matrix();
        get_matrix_right();

        matrix_all = matrix_left | matrix_right;
    }

    void print_matrix(uint64_t matrix) {
        for (uint8_t row_index = 0; row_index < MATRIX_ROWS; ++row_index) {
            if (row_index < 10) {
                Serial.print(F("0"));
            }
            Serial.print(row_index);
            Serial.print(F(": "));

            for (uint8_t col_index = 0; col_index < MATRIX_COLS_BOTH; ++col_index) {
                Serial.print(get_matrix_key_global(matrix, row_index, col_index));
                if (col_index < MATRIX_COLS_BOTH - 1) {
                    Serial.print(F(", "));
                }
            }
            Serial.println("");
        }
        Serial.println("");
    }

} // namespace matrix