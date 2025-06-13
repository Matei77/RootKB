#include <EEPROM.h>

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

    void save_rgb_mode(uint8_t mode) {
        EEPROM.update(0, mode);
    }

    void save_rgb_hue(uint8_t hue) {
        EEPROM.update(1, hue);
    }

    void save_rgb_saturation(uint8_t saturation) {
        EEPROM.update(2, saturation);
    }

    void save_rgb_brightness(uint8_t brightness) {
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
}