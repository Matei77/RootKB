#pragma once

#include <stdint.h>
#include <Arduino.h>

constexpr uint8_t MATRIX_ROWS = 4;
constexpr uint8_t MATRIX_COLS = 6;
constexpr uint8_t MATRIX_COLS_BOTH =  2 * MATRIX_COLS;
constexpr uint8_t MATRIX_SIZE = MATRIX_ROWS * MATRIX_COLS;

namespace matrix {
    typedef uint64_t matrix_t;
    typedef bool matrix_key_t;

    const uint8_t MATRIX_ROW_PINS[] = {4, 5, 6, 7};
    const uint8_t MATRIX_COL_PINS[] = {9, 10, 16, 14, 15, A0};

    void init_matrix_pins();
    void read_matrix();
    void print_matrix();
    void send_matrix();

    // set the key in the left matrix using local row and column indexes for the left matrix
    // (0, 0) = ESC
    inline void set_matrix_key_left(matrix_t& matrix, uint8_t row, uint8_t col) {
        matrix |= ((matrix_t)1 << (row  * 2 * MATRIX_COLS + col));
    }

    // set the key in the right matrix using local row and column indexes for the right matrix
    // (0, 0) = Y
    inline void set_matrix_key_right(matrix_t& matrix, uint8_t row, uint8_t col) {
        matrix |= ((matrix_t)1 << (row * 2 * MATRIX_COLS + MATRIX_COLS + col));
    }

    inline void clear_matrix_key_left(matrix_t& matrix, uint8_t row, uint8_t col) {
        matrix &= ~((matrix_t)1 << (row * 2 * MATRIX_COLS + col));
    }

    inline void clear_matrix_key_right(matrix_t& matrix, uint8_t row, uint8_t col) {
        matrix &= ~((matrix_t)1 << (row * 2 * MATRIX_COLS + MATRIX_COLS + col));
    }

    // get the key in the matrix containing both halfs using global row and column indexes
    // (0, 0) = ESC
    // (0, 6) = Y
    inline matrix_key_t get_matrix_key_global(matrix_t matrix, uint8_t row, uint8_t col) {
        return (matrix >> (row * MATRIX_COLS_BOTH + col)) & (matrix_t)1;
    }

} // namespace keys
