#include "matrix.h"
#include "config.h"

namespace matrix {
    matrix_t matrix;

    void init_matrix_pins() {
        for (uint8_t row_index = 0; row_index < MATRIX_ROWS; ++row_index) {
            pinMode(MATRIX_ROW_PINS[row_index], INPUT_PULLUP);
        }

        for (uint8_t col_index = 0; col_index < MATRIX_COLS; ++col_index) {
            pinMode(MATRIX_COL_PINS[col_index], INPUT);
        }
    }

    void read_matrix() {
        // read the matrix
        for (uint8_t row_index = 0; row_index < MATRIX_ROWS; ++row_index) {
            uint8_t cur_row_pin = MATRIX_ROW_PINS[row_index];
            pinMode(cur_row_pin, OUTPUT);

            digitalWrite(cur_row_pin, LOW);

            for (uint8_t col_index = 0; col_index < MATRIX_COLS; ++col_index) {
                uint8_t cur_col_pin = MATRIX_COL_PINS[col_index];
                pinMode(cur_col_pin, INPUT_PULLUP);

                if (digitalRead(cur_col_pin) == LOW) {
                    set_matrix_key_right(matrix, row_index, col_index);

                } else {
                    clear_matrix_key_right(matrix, row_index, col_index);
                }

                pinMode(cur_col_pin, INPUT);
            }

            // disable the row
            pinMode(cur_row_pin, INPUT);
        }
    }

    void print_matrix() {
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

    void send_matrix() {
        read_matrix();

        if (Serial1.availableForWrite() >= (int)sizeof(matrix)) {
            Serial1.write((byte *)&matrix, sizeof(matrix));
        }

        delay(50);
    }

} // namespace keys