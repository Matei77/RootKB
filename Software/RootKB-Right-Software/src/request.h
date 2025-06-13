#pragma once

#include <Arduino.h>

#include "rgb.h"
#include "matrix.h"

namespace request {
    enum request_t: uint8_t {
        GET_MATRIX,
        SET_RGB
    };

    // -------------------------------------------------------------------------

    void manage_request();

} // namespace request
