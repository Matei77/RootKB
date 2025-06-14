#pragma once

#include <Arduino.h>

namespace right_half_com {
    enum request_t: uint8_t {
        GET_MATRIX,
        SET_RGB
    };

    void send_request(request_t request);

} // namespace right_half_com
