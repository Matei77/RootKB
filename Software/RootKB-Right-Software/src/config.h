#pragma once

#include <stdint.h>
#include <Arduino.h>

constexpr uint8_t MATRIX_ROWS = 4;
constexpr uint8_t MATRIX_COLS = 6;
constexpr uint8_t MATRIX_COLS_BOTH =  2 * MATRIX_COLS;
constexpr uint8_t MATRIX_SIZE = MATRIX_ROWS * MATRIX_COLS;

const uint8_t MATRIX_ROW_PINS[] = {4, 5, 6, 7};
const uint8_t MATRIX_COL_PINS[] = {9, 10, 16, 14, 15, A0};
