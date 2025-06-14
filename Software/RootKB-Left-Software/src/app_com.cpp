#include "app_com.h"

namespace app_com {
    const uint64_t app_com_read_interval = 50;
    uint64_t app_com_reset_time = 0;
    
    // -------------------------------------------------------------------------

    void manage_app_request() {
        if (millis() > app_com_reset_time) {
            app_request_t request;
            
            if (Serial.available() > 0) {
                request = (app_request_t)Serial.read();
                
                switch (request) {
                    case LAYOUT_UPLOAD: 
                        keyboard::receive_layout_from_app();
                        break;
                        
                    case RGB_UPLOAD:
                        rgb::receive_rgb_info_from_app();
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
    
    void send_config() {
        rgb::send_rgb_info_to_app();
        keyboard::send_layout_to_app();
    }

}  // namespace app_com
