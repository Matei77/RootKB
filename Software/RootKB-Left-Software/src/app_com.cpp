#include "app_com.h"

namespace app_com {
    const uint64_t app_com_read_interval = 5;
    uint64_t app_com_reset_time = 0;
    
    // -------------------------------------------------------------------------

    void manage_app_request() {
        if (millis() > app_com_reset_time) {
            app_request_t request;
            
            if (Serial.available() > 0) {
                request = (app_request_t)Serial.read();
                
                switch (request) {
                    case LAYOUT_UPLOAD: 
                        receive_layout();
                        break;
                        
                    case RGB_UPLOAD:
                        receive_rgb();
                        break;

                    case GET_CONFIG:
                        send_config();
                        break;
                        
                    default:
                        break;
                }
            }

            app_com_reset_time = millis() + app_com_read_interval;
        }     
    }

    // -------------------------------------------------------------------------

    void receive_layout() {
        size_t read_bytes = 0;
        while (read_bytes != sizeof(keyboard::layout)) {
            size_t bytes_left = sizeof(keyboard::layout) - read_bytes;
            if (Serial.available() >= int(bytes_left)) {
                size_t count = Serial.readBytes((byte *)&keyboard::layout + read_bytes, bytes_left);
                read_bytes += count;
            }
        }
        data_manager::save_layout(keyboard::layout);
    }
    
    void receive_rgb() {
        
    }

    // -------------------------------------------------------------------------

    void send_layout() {

    }
    
    void send_config() {
        rgb::send_rgb_info_on_serial(Serial);
    }

}  // namespace app_com