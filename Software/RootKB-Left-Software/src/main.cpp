#include "matrix.h"
#include "keys.h"
#include "rgb.h"
#include "oled.h"
#include "app_com.h"
#include "data_manager.h"

// RootKB Left

// int send_keys = 1;
// keys::raw_keycode_t custom_layout[keys::LAYERS_NUM][MATRIX_ROWS][MATRIX_COLS_BOTH];

void setup() {
    Serial.begin(9600);
    Serial1.begin(115200);
    
    matrix::init_matrix_pins();
    keys::init_keys();
    rgb::init_rgb();
    oled::init_oled();
    // data_manager::init_eeprom();

    delay(1000);
}

void loop() {
    rgb::light_rgb_effect();
    oled::display_logo();
    matrix::get_full_matrix();
    keys::send_keys();
    app_com::receive_layout();
        
        // Serial.print("received: ");
        // Serial.print(received_code);
        
        // if (received_code == keys::K_A) {
            //     rgb::hue_up();
            // }
        
        // if (Serial.read() == 'p') {
            //     Serial.println("matrix all:");
            //     matrix::print_matrix(matrix::matrix_all);
            // }
            
            // if (matrix::get_matrix_key_global(matrix::matrix_all, 0, 0) == 1) {
                //     send_keys = 0;
                //     Serial.println("Send keys off");
                // }
                
    // if (send_keys == 1) {
    // }

}
