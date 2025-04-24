// Copyright 2021 Andrzej Kotulski (@akotulski)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#define RAISE MO(_RAISE)
#define LOWER MO(_LOWER)
#define RAISE_ESC LT(RAISE, KC_ESC)
#define LOWER_ENT LT(LOWER, KC_ENT)

enum layer_names {
    _BASE,
    _RAISE,
    _LOWER
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [1] = { ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN)},
    [2] = { ENCODER_CCW_CW(KC_UP, KC_DOWN)  },
};
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base (qwerty)
     * +-----------------------------------------+                             +-----------------------------------------+
     * | ESC  |   q  |   w  |   e  |   r  |   t  |                             |   y  |   u  |   i  |   o  |   p  |      |
     * |------+------+------+------+------+------|                             |------+------+------+------+------+------|
     * | TAB  |   a  |   s  |   d  |   f  |   g  |                             |   h  |   j  |   k  |   l  |   ;  |      |
     * |------+------+------+------+------+------|                             |------+------+------+------+------+------|
     * | SHFT |   z  |   x  |   c  |   v  |   b  |                             |   n  |   m  |   ,  |   .  |   /  |      |
     * +------+------+------+------+-------------+                             +-------------+------+------+------+------+
     *               |  [   |   ]  |                                                         |      |      |
     *               +-------------+-------------+                             +-------------+-------------+
     *                             |      |      |                             |      |      |
     *                             |------+------|                             |------+------|
     *                             |      |      |                             |      |      |
     *                             +-------------+                             +-------------+
     *                                           +-------------+ +-------------+
     *                                           |      |      | |      |      |
     *                                           |------+------| |------+------|
     *                                           |      |      | |      |      |
     *                                           +-------------+ +-------------+
     */
    [_BASE] = LAYOUT(
        KC_GRAVE,KC_Q,    KC_W,    KC_E,    KC_R,       KC_T,                 KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINS,
        KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,       KC_G,                 KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,       KC_B,                 KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
                 KC_LCTL, KC_LALT, RAISE_ESC, KC_SPACE,   KC_LBRC,            KC_RBRC,   KC_BSPC, LOWER_ENT,   KC_EQL, KC_BSLS,
                                            KC_LGUI,    LT(LOWER, KC_DEL),    LT(RAISE, KC_HOME), KC_RCTL
    ),

    [_LOWER] = LAYOUT(
        QK_BOOT, _______, _______, _______, _______, KC_LBRC,             KC_RBRC, _______,   _______,   _______,   _______, KC_PLUS,
        _______, KC_HOME, KC_PGUP, KC_PGDN, KC_END , _______,             KC_LEFT, KC_DOWN,   KC_UP,   KC_RIGHT,   KC_MINS, KC_PIPE,
        _______, _______, _______, _______, _______, _______,             _______, _______,   _______,   _______,  KC_EQL,  KC_UNDS,
                 _______, _______, _______, _______, _______,             _______, _______,   _______,   _______,  _______,
                                            _______, _______,             _______, _______
    ),

    [_RAISE] = LAYOUT(
        _______, KC_EXCLAIM, KC_AT, KC_HASH , KC_DOLLAR, KC_PERC,         KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_VOLU,
        KC_GRAVE, KC_1, KC_2, KC_3, KC_4, KC_5,                           KC_6, KC_7, KC_8,  KC_9,  KC_0, KC_VOLD,
        _______, _______, _______, _______, _______, _______,             _______, _______, _______, _______, _______, KC_MPLY,
                 _______, _______, _______, _______, _______,             _______, _______,   _______,   _______,  _______,
                                            _______, _______,             _______, _______
    )
};

