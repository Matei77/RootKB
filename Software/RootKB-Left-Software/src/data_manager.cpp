#include <EEPROM.h>
#include "keys.h"

namespace data_manager {

    void init_eeprom() {
        for (uint16_t i = 0 ; i < EEPROM.length() ; i++) {
                EEPROM.write(i, 0);
        }
    }

    void save_rgb(uint8_t mode, uint8_t hue, uint8_t saturation, uint8_t brightness) {
        EEPROM.update(0, mode);
        EEPROM.update(1, hue);
        EEPROM.update(2, saturation);
        EEPROM.update(3, brightness);
    }

    void save_rgb_mode(const uint8_t mode) {
        EEPROM.update(0, mode);
    }

    void save_rgb_hue(const uint8_t hue) {
        EEPROM.update(1, hue);
    }

    void save_rgb_saturation(const uint8_t saturation) {
        EEPROM.update(2, saturation);
    }

    void save_rgb_brightness(const uint8_t brightness) {
        EEPROM.update(3, brightness);
    }

    uint8_t get_rgb_mode() {
        return EEPROM.read(0);
    }

    uint8_t get_rgb_hue() {
        return EEPROM.read(1);
    }

    uint8_t get_rgb_saturation() {
        return EEPROM.read(2);
    }

    uint8_t get_rgb_brightness() {
        return EEPROM.read(3);
    }

    void save_layout(const keys::raw_keycode_t layout[keys::LAYERS_NUM][MATRIX_ROWS][MATRIX_COLS_BOTH]) {
        uint16_t pos = 4;
        for (uint8_t layer = 0; layer < keys::LAYERS_NUM; ++layer) {
            for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
                for (uint8_t col = 0; col < MATRIX_COLS_BOTH; ++col) {
                    EEPROM.update(pos++, layout[layer][row][col]);
                }
            }
        }
    }

    void load_layout(keys::raw_keycode_t layout[keys::LAYERS_NUM][MATRIX_ROWS][MATRIX_COLS_BOTH]) {
        uint16_t pos = 4;
        for (uint8_t layer = 0; layer < keys::LAYERS_NUM; ++layer) {
            for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
                for (uint8_t col = 0; col < MATRIX_COLS_BOTH; ++col) {
                    layout[layer][row][col] = (keys::raw_keycode_t)EEPROM.read(pos++);
                }
            }
        }
    }
}