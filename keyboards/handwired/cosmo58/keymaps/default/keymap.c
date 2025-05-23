// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum layers {
	_KB,
	_UTIL,
	_KP,
	_SYSTEM,
	_GAME
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
     /*
      * ┌───┬───┬───┬───┬───┬───┐           ┌───┬───┬───┬───┬───┬───┐
      * │`  │ 1 │ 2 │ 3 │ 4 │ 5 │           │ 6 │ 7 │ 8 │ 9 │ 0 │ - │
      * ├───┼───┼───┼───┼───┼───┤           ├───┼───┼───┼───┼───┼───┤
      * │Tab│ Q │ W │ E │ R │ T │           │ Y │ U │ I │ O │ P │ = │
      * ├───┼───┼───┼───┼───┼───┤           ├───┼───┼───┼───┼───┼───┤
      * │Sft│ A │ S │ D │ F │ G │           │ H │ J │ K │ L │ ; │ ' │
      * ├───┼───┼───┼───┼───┼───┤           ├───┼───┼───┼───┼───┼───┤
      * │Sft│ Z │ X │ C │ V │ B │           │ N │ M │ , │ . │ / │Sft│
      * └───┴───┴───┴───┴───┴───┘           └───┴───┴───┴───┴───┴───┘
      *         ┌───┐───┐───┐                   ┌───┐───┐───┐
      *         │   │   │GUI├───┐           ┌───┤Alt│   │   │
      *         └───┴───└───┤Bsp├───┐   ┌───┤Ent├───┘───┴───┘
      *                     └───┤   │   │   ├───┘
      *                         └───┘   └───┘
      */
  	[_KB] = LAYOUT(
	    KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5,                          KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS,
		KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T,                          KC_Y, KC_U, KC_I, KC_O, KC_P, KC_EQL,
	    KC_LSFT, KC_A, KC_S, KC_D, KC_F, KC_G,                         KC_H, KC_J, KC_K, KC_L, KC_SCLN, RSFT_T(KC_QUOT),
	    OSM(MOD_LGUI), KC_Z, KC_X, KC_C, KC_V, KC_B,                   KC_N, KC_M, KC_COMM, KC_DOT, RCAG_T(KC_SLSH), KC_BSLS,
	    KC_LCTL, KC_LALT, MT(MOD_LGUI, KC_ESC), KC_SPC, MO(_UTIL),     LT(_SYSTEM,KC_DEL), KC_BSPC, LT(_KP,KC_ENT), KC_LBRC, KC_RBRC
	),
	[_UTIL] = LAYOUT(
	  KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6,                         KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12,
	  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,             KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
	  KC_GRV, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC,                 KC_MINS, KC_EQL, KC_PLUS, KC_LPRN, KC_RPRN, KC_TILD,
	  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,             KC_UNDS, KC_SLSH, KC_BSLS, KC_LCBR, KC_RCBR, KC_PIPE,
	  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                      KC_TRNS, KC_DEL, KC_ENT, KC_TRNS, KC_PRINT_SCREEN
	),
	[_KP] = LAYOUT(
	  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,           KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_AUDIO_VOL_UP,
	  KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5,                           KC_6, KC_7, KC_8, KC_9, KC_0, KC_AUDIO_VOL_DOWN,
	  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_COLN, KC_PIPE,           KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_HOME, KC_END,
	  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_EXLM,           KC_PLUS, KC_MINS, KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS,
	       KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS,           KC_TRNS,  KC_TRNS, KC_TRNS,       KC_TRNS, KC_TRNS
	),
	[_SYSTEM] = LAYOUT(
	   QK_BOOT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
	   KC_NO, KC_NO, KC_NO, KC_NO, EH_RGHT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
	   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, EH_LEFT, KC_NO, KC_NO,
	   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
	   KC_TRNS, KC_TRNS, KC_TRNS, CG_TOGG,      CG_SWAP,   CG_NORM,         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
	),
};
