#include "keyboard.h"

using namespace kb_conf;

namespace keyboard {
    raw_keycode_t layout[LAYERS][ROWS][COLS] = { raw_keycode_t::K_NO };
    
    matrix::matrix_t layer1_mask = 0;
    matrix::matrix_t layer2_mask = 0;
    matrix::matrix_t layer3_mask = 0;

    matrix::matrix_t last_matrix_state = 0;
    matrix::matrix_t last_read_matrix_state = 0;
    matrix::matrix_t matrix_state = 0;

    uint8_t last_layer = 0;
    uint8_t current_layer = 0;

    const uint64_t DEBOUNCE_DELAY = 6;
    uint64_t last_debounce = 0;

    // -------------------------------------------------------------------------

    bool check_key(raw_keycode_t key) {
        return (key > raw_keycode_t::K_MODEDOWN);
    }

    // -------------------------------------------------------------------------

    void init_layout_keys_masks() {
        // set the masks for the layers
        for (uint8_t row_index = 0; row_index < ROWS; ++row_index) {
            for (uint8_t col_index = 0; col_index < COLS; ++col_index) {
                if (layout[0][row_index][col_index] == raw_keycode_t::K_LAY1) {
                    matrix::set_matrix_key_global(layer1_mask, row_index, col_index);
                } else if (layout[0][row_index][col_index] == raw_keycode_t::K_LAY2) {
                    matrix::set_matrix_key_global(layer2_mask, row_index, col_index);
                } else if (layout[0][row_index][col_index] == raw_keycode_t::K_LAY3) {
                    matrix::set_matrix_key_global(layer3_mask, row_index, col_index);
                }
            }
        }
    }

    // -------------------------------------------------------------------------

    void init_keyboard() {
        Keyboard.begin();

        data_manager::load_layout(layout);

        init_layout_keys_masks();
    }

    // -------------------------------------------------------------------------

    void process_keypresses() {
        uint64_t read_matrix_state = matrix::matrix_all;

        if (read_matrix_state != last_read_matrix_state) {
            last_debounce = millis();
        }
        
        if ((millis() - last_debounce) > DEBOUNCE_DELAY) {
            if (matrix_state != read_matrix_state) {
                matrix_state = read_matrix_state;
                
                
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
                
                for (uint8_t row_index = 0; row_index < ROWS; ++row_index) {
                    for (uint8_t col_index = 0; col_index < COLS; ++col_index) {
                        raw_keycode_t key = layout[current_layer][row_index][col_index];
                        
                        if (matrix::get_matrix_key_global(matrix_state, row_index, col_index) !=
                            matrix::get_matrix_key_global(last_matrix_state, row_index, col_index)) {
                            
                            if (matrix::get_matrix_key_global(matrix_state, row_index, col_index) == 1) {
                                
                                switch (key) {
                                    case raw_keycode_t::K_COLORUP:
                                        rgb::hue_up();
                                        break;
                                    case raw_keycode_t::K_COLORDOWN:
                                        rgb::hue_down();
                                        break;
                                    case raw_keycode_t::K_BRIGHTUP:
                                        rgb::brightness_up();
                                        break;
                                    case raw_keycode_t::K_BRIGHTDOWN:
                                        rgb::brightness_down();
                                        break;
                                    case raw_keycode_t::K_SATUP:
                                        rgb::saturation_up();
                                        break;
                                    case raw_keycode_t::K_SATDOWN:
                                        rgb::saturation_down();
                                        break;
                                    case raw_keycode_t::K_MODEUP:
                                        rgb::mode_up();
                                        break;
                                    case raw_keycode_t::K_MODEDOWN:
                                        rgb::mode_down();
                                        break;
                                    default:
                                        if (check_key(key)) {
                                            Keyboard.press(key);
                                        }
                                        break;
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

    // -------------------------------------------------------------------------

    void receive_layout_from_app() {
        serial::safe_read_serial(Serial, (byte *)&layout, sizeof(layout));
        init_layout_keys_masks();
        data_manager::save_layout(layout);
    }

    void send_layout_to_app() {
        serial::safe_write_serial(Serial, (byte *)&layout, sizeof(layout));
    }

} // namespace keyboard
