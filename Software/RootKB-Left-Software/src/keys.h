#pragma once

#include <stdint.h>
#include <Arduino.h>

#include "matrix.h"

namespace keys {
    const uint8_t LAYOUTS_NUM = 4;

    void init_keys();
    void send_keys();

    enum raw_keycode_t {
        K_NO = -1,
        K_LAY1 = 1,
        K_LAY2 = 2,
        K_LAY3 = 3,
        K_COLORUP = 4,
        K_COLORDOWN = 5,
        K_BRIGHTUP = 6,
        K_BRIGHTDOWN = 7,
        K_SATUP = 8,
        K_SATDOWN = 9,
        MACRO1,
        MACRO2,
        K_A = 140,
        K_B,
        K_C,
        K_D,
        K_E,
        K_F,
        K_G,
        K_H,
        K_I,
        K_J,
        K_K,
        K_L,
        K_M,
        K_N,
        K_O,
        K_P,
        K_Q,
        K_R,
        K_S,
        K_T,
        K_U,
        K_V,
        K_W,
        K_X,
        K_Y,
        K_Z,
        K_1,
        K_2,
        K_3,
        K_4,
        K_5,
        K_6,
        K_7,
        K_8,
        K_9,
        K_0,
        K_ENTER,
        K_ESC,
        K_BACK,
        K_TAB,
        K_SPACE,
        K_MINUS, // - and _
        K_EQUAL, // = and +
        K_LBRACKET, // [ and {
        K_RBRACKET, // ] and }
        K_BACKSLASH, // \ and |
        K_SEMICOLON = 187, // ; and :
        K_QUOTE, // ' and "
        K_GRAVE, // ` and ~
        K_COMMA, // , and <
        K_PERIOD, // . and >
        K_SLASH, // / and ?
        K_LCTRL = 128,
        K_LSFT,
        K_LALT,
        K_LGUI,
        K_RCTRL,
        K_RSFT,
        K_RALT,
        K_RGUI,
        K_HOME = 210,
        K_END = 213,
        K_RIGHT = 215,
        K_LEFT,
        K_DOWN,
        K_UP
    };

    const raw_keycode_t layouts[LAYOUTS_NUM][MATRIX_ROWS][MATRIX_COLS_BOTH] = {
        {
            {K_ESC, K_Q, K_W, K_E, K_R, K_T,                K_Y, K_U, K_I, K_O, K_P, K_BACK},
            {K_TAB, K_A, K_S, K_D, K_F, K_G,                K_H, K_J, K_K, K_L, K_SEMICOLON, K_QUOTE},
            {K_LSFT, K_Z, K_X, K_C, K_V, K_B,               K_N, K_M, K_COMMA, K_PERIOD, K_SLASH, K_RSFT},
            {K_NO, K_NO, K_LALT, K_SPACE, K_LAY1, K_LGUI,   K_LAY3, K_LAY2, K_ENTER, K_RCTRL, K_NO, K_NO}
        },

        {
            {K_ESC, K_NO, K_HOME, K_UP, K_END, K_NO,       K_NO, K_NO, K_NO, K_NO, K_NO, K_BACK},
            {K_TAB, K_NO, K_LEFT, K_DOWN, K_RIGHT, K_NO,   K_NO, K_NO, K_NO, K_NO, K_NO, K_NO},
            {K_LSFT, K_NO, K_NO, K_NO, K_NO, K_NO,         K_NO, K_NO, K_NO, K_NO, K_NO, K_RSFT},
            {K_NO, K_NO, K_LALT, K_SPACE, K_NO, K_LGUI,    K_NO, K_NO, K_ENTER, K_RCTRL, K_NO, K_NO}
        },

        {
            {K_ESC, K_NO, K_7, K_8, K_9, K_NO,   K_NO, K_NO, K_NO, K_NO, K_NO, K_BACK},
            {K_TAB, K_NO, K_4, K_5, K_6, K_NO,   K_NO, K_NO, K_NO, K_NO, K_NO, K_NO},
            {K_LSFT, K_0, K_1, K_2, K_3, K_NO,   K_NO, K_NO, K_NO, K_NO, K_NO, K_RSFT},
            {K_NO, K_NO, K_LALT, K_SPACE, K_NO,  K_LGUI, K_NO, K_NO, K_ENTER, K_RCTRL, K_NO, K_NO}
        },

        {
            {K_NO, K_NO, K_NO, K_NO, K_NO, K_NO,   K_BRIGHTUP, K_COLORUP, K_SATUP, K_NO, K_NO, K_NO},
            {K_NO, K_NO, K_NO, K_NO, K_NO, K_NO,   K_BRIGHTDOWN, K_COLORDOWN, K_SATDOWN, K_NO, K_NO, K_NO},
            {K_NO, K_NO, K_NO, K_NO, K_NO, K_NO,   K_NO, K_NO, K_NO, K_NO, K_NO, K_NO},
            {K_NO, K_NO, K_NO, K_NO, K_NO, K_NO,   K_NO, K_NO, K_NO, K_NO, K_NO, K_NO}
        }
    };


} // namespace keys