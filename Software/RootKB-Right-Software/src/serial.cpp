#include "serial.h"

namespace serial {

    // Makes sure all data is sent, otherwise blocks
    void safe_write_serial(Stream &serial, byte *buffer, size_t size) {
        size_t written_bytes = 0;
        while (written_bytes != size) {
            size_t bytes_left = size - written_bytes;
            if (serial.availableForWrite() >= (int)bytes_left) {
                size_t count = serial.write(buffer + written_bytes, bytes_left);
                written_bytes += count;
            }
        }
        
        serial.flush();
    }

    // Makes sure all data is read, otherwise blocks
    void safe_read_serial(Stream &serial, byte *buffer, size_t size) {
        size_t read_bytes = 0;
        while (read_bytes != size) {
            size_t bytes_left = size - read_bytes;
            if (serial.available() >= (int)bytes_left) {
                size_t count = serial.readBytes(buffer + read_bytes, bytes_left);
                read_bytes += count;
            }
        }
    }

} // namespace serial
