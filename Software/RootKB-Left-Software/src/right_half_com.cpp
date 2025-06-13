#include "right_half_com.h"

namespace right_half_com {  
    void send_request(request_t request) {
        if (Serial1.availableForWrite() > (int)sizeof(request)) {
            size_t written_bytes = 0;
            
            while (written_bytes != sizeof(request)) {
                size_t count = Serial1.write((uint8_t)request);
                written_bytes += count;
            }
            
            Serial1.flush();
        }
    }

} // namespace right_half_com