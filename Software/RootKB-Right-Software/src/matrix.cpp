#include "matrix.h"

namespace matrix {
    matrix_t matrix_right;

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
        matrix_right = 0;

        for (uint8_t row_index = 0; row_index < MATRIX_ROWS; ++row_index) {
            uint8_t cur_row_pin = MATRIX_ROW_PINS[row_index];
            pinMode(cur_row_pin, OUTPUT);

            digitalWrite(cur_row_pin, LOW);

            for (uint8_t col_index = 0; col_index < MATRIX_COLS; ++col_index) {
                uint8_t cur_col_pin = MATRIX_COL_PINS[col_index];
                pinMode(cur_col_pin, INPUT_PULLUP);

                if (digitalRead(cur_col_pin) == LOW) {
                    set_matrix_key_right(matrix_right, row_index, col_index);
                }

                pinMode(cur_col_pin, INPUT);
            }

            // disable the row
            pinMode(cur_row_pin, INPUT);
        }
    }

    void send_matrix() {
        read_matrix();
        
        // if (Serial1.availableForWrite() >= (int)sizeof(matrix_right)) {
        size_t written_bytes = 0;
        while (written_bytes != sizeof(matrix_right)) {
            size_t bytes_left = sizeof(matrix_right) - written_bytes;
            size_t count = Serial1.write((byte *)&matrix_right + written_bytes, bytes_left);
            written_bytes += count;
        }
        
        Serial1.flush();
        // }      
    }

} // namespace matrix