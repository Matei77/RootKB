#include "matrix.h"

namespace matrix {
    matrix_t matrix_left = 0;
    matrix_t matrix_right = 0;
    matrix_t matrix_all = 0;
    const uint64_t read_interval = 20;
    uint64_t reset_time = 0;

    // -------------------------------------------------------------------------

    void init_matrix_pins() {
        for (uint8_t row_index = 0; row_index < MATRIX_ROWS; ++row_index) {
            pinMode(MATRIX_ROW_PINS[row_index], INPUT_PULLUP);
        }

        for (uint8_t col_index = 0; col_index < MATRIX_COLS; ++col_index) {
            pinMode(MATRIX_COL_PINS[col_index], INPUT);
        }
    }

    // -------------------------------------------------------------------------

    void get_matrix_right() {
        matrix_right = 0;

        right_half_com::send_request(right_half_com::GET_MATRIX);
        serial::safe_read_serial(Serial1, (byte *)&matrix_right, sizeof(matrix_right));
    }

    // -------------------------------------------------------------------------

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

    // -------------------------------------------------------------------------

    void get_full_matrix() {
        if (millis() > reset_time) {
            read_matrix();
            get_matrix_right();

            matrix_all = matrix_left | matrix_right;

            reset_time = millis() + read_interval;
        }

    }

} // namespace matrix
