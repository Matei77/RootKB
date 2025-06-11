#include "keys.h"
#include "matrix.h"
#include "rgb.h"
#include <Keyboard.h>

namespace keys {
    raw_keycode_t layout[LAYERS_NUM][MATRIX_ROWS][MATRIX_COLS_BOTH] = {
        {
            {K_ESC, K_Q, K_W, K_E, K_R, K_T,                K_Y, K_U, K_I, K_O, K_P, K_BACK},
            {K_TAB, K_A, K_S, K_D, K_F, K_G,                K_H, K_J, K_K, K_L, K_SEMICOLON, K_QUOTE},
            {K_LSFT, K_Z, K_X, K_C, K_V, K_B,               K_N, K_M, K_COMMA, K_PERIOD, K_SLASH, K_RSFT},
            {K_NO, K_NO, K_LCTRL, K_SPACE, K_LAY1, K_LGUI,   K_LAY3, K_LAY2, K_ENTER, K_RALT, K_NO, K_NO}
        },

        {
            {K_ESC, K_NO, K_HOME, K_UP, K_END, K_NO,       K_NO, K_BL1, K_BR1, K_NO, K_NO, K_BACK},
            {K_TAB, K_NO, K_LEFT, K_DOWN, K_RIGHT, K_NO,   K_NO, K_LCB, K_RCB, K_NO, K_NO, K_NO},
            {K_LSFT, K_NO, K_NO, K_NO, K_NO, K_NO,         K_NO, K_BL2, K_BR2, K_NO, K_NO, K_RSFT},
            {K_NO, K_NO, K_LCTRL, K_SPACE, K_NO, K_LGUI,    K_NO, K_NO, K_ENTER, K_RALT, K_NO, K_NO}
        },

        {
            {K_ESC, K_NO, K_7, K_8, K_9, K_0,   K_CHR11, K_CHR12, K_CHR13, K_CHR14, K_CHR15, K_DELETE},
            {K_TAB, K_NO, K_4, K_5, K_6, K_NO,   K_CHR21, K_CHR22, K_CHR23, K_CHR24, K_CHR25, K_CHR26},
            {K_LSFT, K_NO, K_1, K_2, K_3, K_NO,   K_CHR31, K_CHR32, K_CHR33, K_CHR34, K_CHR35, K_RSFT},
            {K_NO, K_NO, K_LCTRL, K_SPACE, K_NO,  K_LGUI, K_NO, K_NO, K_ENTER, K_RALT, K_NO, K_NO}
        },

        {
            {K_NO, K_NO, K_F7, K_F8, K_F9, K_F12,   K_BRIGHTUP, K_COLORUP, K_SATUP, K_NO, K_PRT_SC, K_NO},
            {K_NO, K_NO, K_F4, K_F5, K_F6, K_F11,   K_BRIGHTDOWN, K_COLORDOWN, K_SATDOWN, K_NO, K_NO, K_NO},
            {K_NO, K_NO, K_F1, K_F2, K_F3, K_F10,   K_NO, K_NO, K_NO, K_NO, K_NO, K_NO},
            {K_NO, K_NO, K_NO, K_NO, K_NO, K_NO,   K_NO, K_NO, K_NO, K_NO, K_NO, K_NO}
        }
    };
    
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
                if (layout[0][row_index][col_index] == K_LAY1) {
                    matrix::set_matrix_key_global(layer1_mask, row_index, col_index);
                } else if (layout[0][row_index][col_index] == K_LAY2) {
                    matrix::set_matrix_key_global(layer2_mask, row_index, col_index);
                } else if (layout[0][row_index][col_index] == K_LAY3) {
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
                
                // Serial.println("matrix state:");
                // matrix::print_matrix(matrix_state);
                
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
                        raw_keycode_t key = layout[current_layer][row_index][col_index];
                        
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
