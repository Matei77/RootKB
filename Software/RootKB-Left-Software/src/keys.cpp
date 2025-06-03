#include "keys.h"
#include "matrix.h"
#include "rgb.h"
#include <Keyboard.h>

namespace keys {
    matrix_t layer1_mask = 0;
    matrix_t layer2_mask = 0;
    matrix_t layer3_mask = 0;

    matrix_t last_matrix_state = 0;
    matrix_t last_read_matrix_state = 0;
    matrix_t matrix_state = 0;

    uint8_t last_layer = 0;
    uint8_t current_layer = 0;

    const uint64_t DEBOUNCE_DELAY = 6;
    uint64_t last_debounce = 0;

    bool check_key(raw_keycode_t key) {
        return (key > MACRO2);
    }


    void init_keys() {
        Keyboard.begin();

        // set the masks for the layers
        for (uint8_t row_index = 0; row_index < MATRIX_ROWS; ++row_index) {
            for (uint8_t col_index = 0; col_index < MATRIX_COLS_BOTH; ++col_index) {
                if (layouts[0][row_index][col_index] == K_LAY1) {
                    matrix::set_matrix_key_global(layer1_mask, row_index, col_index);
                } else if (layouts[0][row_index][col_index] == K_LAY2) {
                    matrix::set_matrix_key_global(layer2_mask, row_index, col_index);
                } else if (layouts[0][row_index][col_index] == K_LAY3) {
                    matrix::set_matrix_key_global(layer3_mask, row_index, col_index);
                }
            }
        }
    }


    void send_keys() {
        uint64_t read_matrix_state = matrix::matrix_all;

        if (read_matrix_state != last_read_matrix_state) {
            last_debounce = millis();
        }
        
        if ((millis() - last_debounce) > DEBOUNCE_DELAY) {
            if (matrix_state != read_matrix_state) {
                matrix_state = read_matrix_state;
                
                Serial.println("matrix state:");
                matrix::print_matrix(matrix_state);
                
                if (matrix_state & layer1_mask) {
                    current_layer = 1;
                } else if (matrix_state & layer2_mask) {
                    current_layer = 2;
                } else if (matrix_state & layer3_mask) {
                    current_layer = 3;
                } else {
                    current_layer = 0;
                }
                
                // if layer changed, release all keys from the last layer
                if (current_layer != last_layer) {
                    Keyboard.releaseAll();
                    last_layer = current_layer;
                }
                
                for (uint8_t row_index = 0; row_index < MATRIX_ROWS; ++row_index) {
                    for (uint8_t col_index = 0; col_index < MATRIX_COLS_BOTH; ++col_index) {
                        raw_keycode_t key = layouts[current_layer][row_index][col_index];
                        
                        if (matrix::get_matrix_key_global(matrix_state, row_index, col_index) !=
                        matrix::get_matrix_key_global(last_matrix_state, row_index, col_index)) {
                            
                            if (matrix::get_matrix_key_global(matrix_state, row_index, col_index) == 1) {
                                
                                if (key == K_COLORUP) {
                                    rgb::hue_up();
                                } else if (key == K_COLORDOWN) {
                                    rgb::hue_down();
                                } else if (key == K_BRIGHTUP) {
                                    rgb::brightness_up();
                                } else if (key == K_BRIGHTDOWN) {
                                    rgb::brightness_down();
                                } else if (key == K_SATUP) {
                                    rgb::saturation_up();
                                } else if (key == K_SATDOWN) {
                                    rgb::saturation_down();
                                    
                                } else if (check_key(key)) {
                                    Keyboard.press(key);
                                }
                                
                            } else {
                                if (check_key(key)) {
                                    Keyboard.release(key);
                                }
                            }
                        }
                    }
                }
            }
            last_matrix_state = matrix_state;
        }
        last_read_matrix_state = read_matrix_state;
    }
} // namespace keys
