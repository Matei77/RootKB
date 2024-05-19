#include "keys.h"
#include "matrix.h"
#include <Keyboard.h>

namespace keys {
    uint64_t layer1_mask = 0;
    uint64_t layer2_mask = 0;
    uint64_t layer3_mask = 0;
    uint64_t no_key_mask = 0;
    uint64_t keys_mask = 0;

    uint64_t last_matrix_state = 0;

    void init_keys() {
        // set the masks for the keys
        for (uint8_t row_index = 0; row_index < MATRIX_ROWS; ++row_index) {
            for (uint8_t col_index = 0; col_index < MATRIX_COLS_BOTH; ++col_index) {
                if (layout0[row_index][col_index] == K_LAY1) {
                    matrix::set_matrix_key_global(layer1_mask, row_index, col_index);
                } else if (layout0[row_index][col_index] == K_LAY2) {
                    matrix::set_matrix_key_global(layer2_mask, row_index, col_index);
                } else if (layout0[row_index][col_index] == K_LAY3) {
                    matrix::set_matrix_key_global(layer3_mask, row_index, col_index);
                } else if (layout0[row_index][col_index] == K_NO) {
                    matrix::set_matrix_key_global(no_key_mask, row_index, col_index);
                } else {
                    matrix::set_matrix_key_global(keys_mask, row_index, col_index);
                }
            }
        }
    }


    void send_keys() {
        uint64_t matrix_state = matrix::matrix_all;

        if (matrix_state != last_matrix_state) {
            last_matrix_state = matrix_state;

            for (uint8_t row_index = 0; row_index < MATRIX_ROWS; ++row_index) {
                for (uint8_t col_index = 0; col_index < MATRIX_COLS_BOTH; ++col_index) {
                    // check if the key is in the keys_mask (keys_mask contains sendable keys)
                    if (matrix::get_matrix_key_global(keys_mask, row_index, col_index) == 0) {
                        continue;
                    }
                        if (matrix::get_matrix_key_global(matrix_state, row_index, col_index) == 1) {
                            Keyboard.press(layout0[row_index][col_index]);
                        } else {
                                Keyboard.release(layout0[row_index][col_index]);
                        }
                    }
                    
                }
            }
    }
} // namespace keys