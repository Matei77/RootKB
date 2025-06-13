#include "request.h"


namespace request {
    const uint64_t read_interval = 5;
    uint64_t reset_time = 0;

    // -------------------------------------------------------------------------

    void manage_request() {
        if (millis() > reset_time) {
            request_t request;
            
            if (Serial1.available() > 0) {
                request = (request_t)Serial1.read();
                
                switch (request) {
                    case GET_MATRIX: 
                        matrix::send_matrix();
                        break;
                    
                    case SET_RGB:
                        rgb::set_rgb();
                        break;

                    default:
                        break;
                }
            }

            reset_time = millis() + read_interval;
        }
    }

} // namespace request
