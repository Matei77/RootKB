#include "serial.h"

namespace serial {
    const uint8_t BUFFER_SIZE = 64;

    // Makes sure all data is sent, otherwise blocks
    void safe_write_serial(Stream &serial, byte *buffer, size_t size) {
        size_t written_bytes = 0;
        while (written_bytes != size) {
            size_t bytes_left = size - written_bytes;
            if (serial.availableForWrite() >= (int)min(bytes_left, BUFFER_SIZE)) {
                size_t count = serial.write(buffer + written_bytes, min(bytes_left, BUFFER_SIZE));
                written_bytes += count;
                serial.flush();
            }
        }
    }

    // Makes sure all data is read, otherwise blocks
    void safe_read_serial(Stream &serial, byte *buffer, size_t size) {
        size_t read_bytes = 0;
        while (read_bytes != size) {
            size_t bytes_left = size - read_bytes;
            if (serial.available() >= (int)min(bytes_left, BUFFER_SIZE)) {
                size_t count = serial.readBytes(buffer + read_bytes, min(bytes_left, BUFFER_SIZE));
                read_bytes += count;
            }
        }
    }

} // namespace serial
