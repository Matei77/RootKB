#pragma once

#include <Arduino.h>

namespace serial {
    void safe_write_serial(Stream& serial, byte* buffer, size_t size);
    void safe_read_serial(Stream& serial, byte* buffer, size_t size);

} // namespace serial
