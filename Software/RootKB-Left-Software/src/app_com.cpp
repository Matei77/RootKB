#include <Arduino.h>
#include "app_com.h"
#include "keys.h"

namespace app_com {

    void receive_layout() {
        if (Serial.available() > 0) {
            size_t read_bytes = 0;
            while (read_bytes != sizeof(keys::layout)) {
                size_t bytes_left = sizeof(keys::layout) - read_bytes;
                size_t count = Serial.readBytes((byte *)&keys::layout, bytes_left);
                read_bytes += count;
                // oled::displaySize(read_bytes);
            }
        }
    }
}