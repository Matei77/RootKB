#pragma once

#include <Arduino.h>

#include "keyboard.h"
#include "data_manager.h"

namespace app_com {
    enum app_request_t : uint8_t {
        LAYOUT_UPLOAD,
        RGB_UPLOAD,
        GET_CONFIG
    };

    void manage_app_request();
    void send_config();

} // namespace app_com
