#include "matrix.h"
#include "keys.h"
#include "rgb.h"
#include "oled.h"

// RootKB Left

int send_keys = 1;
// keys::raw_keycode_t custom_layout[keys::LAYERS_NUM][MATRIX_ROWS][MATRIX_COLS_BOTH];

void setup() {
    Serial.begin(9600);
    Serial1.begin(115200);
    
    matrix::init_matrix_pins();
    keys::init_keys();
    rgb::init_rgb();
    oled::init_oled();

    delay(1000);
}

void loop() {
    matrix::get_full_matrix();


    if (Serial.available() > 0) {
        size_t read_bytes = 0;
        while (read_bytes != sizeof(keys::layout)) {
            size_t bytes_left = sizeof(keys::layout) - read_bytes;
            size_t count = Serial.readBytes((byte *)&keys::layout, bytes_left);
            read_bytes += count;
            oled::displaySize(read_bytes);
        }

        // Serial.print("received: ");
        // Serial.print(received_code);

        // if (received_code == keys::K_A) {
        //     rgb::hue_up();
        // }
    }

    // if (Serial.read() == 'p') {
    //     Serial.println("matrix all:");
    //     matrix::print_matrix(matrix::matrix_all);
    // }

    // if (matrix::get_matrix_key_global(matrix::matrix_all, 0, 0) == 1) {
    //     send_keys = 0;
    //     Serial.println("Send keys off");
    // }

    if (send_keys == 1) {
        keys::send_keys();
    }

    oled::display_logo();
}
