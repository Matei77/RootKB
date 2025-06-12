#include "request.h"
#include "rgb.h"
#include "matrix.h"
#include <Arduino.h>

namespace request {
    void manage_request() {
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
    }

}