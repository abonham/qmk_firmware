#include QMK_KEYBOARD_H
#include "config.h"
#ifdef CONSOLE_ENABLE
#include "print.h"
#endif

bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;

bool is_windows = false;

enum custom_keycodes {
  ALT_TAB = SAFE_RANGE,
  ALT_GRAVE,
  TOGGLE_WINDOWS,
  SSHOT
};

enum {
  TD_MOD_7,
  TD_GUI_MOD_7_SPC,
  TD_GUI_MOD_7_ENT,
  TD_QUOTE
};

#ifdef TAP_DANCE_ENABLE
// Define a type containing as many tapdance states as you need
typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_SINGLE_TAP,
    TD_DOUBLE_TAP_HOLD
} td_state_t;

static td_state_t mod_7_td_state;
static td_state_t mod_7_spc_td_state;
static td_state_t mod_7_ent_td_state;

// Declare your tapdance functions:

// Function to determine the current tapdance state
td_state_t cur_dance(qk_tap_dance_state_t *state);

// `finished` and `reset` functions for each tapdance keycode
void modSeven_finished(qk_tap_dance_state_t *state, void *user_data);
void modSeven_reset(qk_tap_dance_state_t *state, void *user_data);
void gui_mod_7_spc_finished(qk_tap_dance_state_t *state, void *user_data);
void gui_mod_7_spc_reset(qk_tap_dance_state_t *state, void *user_data);
void gui_mod_7_ent_finished(qk_tap_dance_state_t *state, void *user_data);
void gui_mod_7_ent_reset(qk_tap_dance_state_t *state, void *user_data);
#endif

#ifdef ANALOG_JOYSTICK_ENABLE
joystick_config_t_joystick_axes[JOYSTICK_AXES_COUNT] = {
    [0] = JOYSTICK_AXIS_VIRTUAL,
    [1] = JOYSTICK_AXIS_VIRTUAL,
    [2] = JOYSTICK_AXIS_VIRTUAL,
};
#endif

// clang-format off
// layer 0
#define _QWERTY LAYOUT_split_3x5_2( \
    KC_Q, KC_W, KC_E, KC_R, KC_T,                                   KC_Y, KC_U, KC_I, KC_O, KC_P, \
    LSFT_T(KC_A), LT(1,KC_S), LT(2,KC_D), LT(3,KC_F), KC_G,         KC_H, LT(4,KC_J), LT(2,KC_K), LT(5,KC_L), LSFT_T(KC_SCLN), \
    SGUI_T(KC_Z), LCTL_T(KC_X), LALT_T(KC_C), KC_V,  KC_B,  KC_N, KC_M, LALT_T(KC_COMM), LCTL_T(KC_DOT), LCAG_T(KC_SLSH), \
    TD(TD_MOD_7), TD(TD_GUI_MOD_7_SPC),                             RGUI_T(KC_BSPC), TD(TD_GUI_MOD_7_ENT) \
)

// layer 1
#define _MORE_SYMBOLS LAYOUT_split_3x5_2( \
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                    KC_BSLS, KC_AMPR, KC_ASTR, KC_GRV, KC_TRNS, \
    LSFT_T(KC_ESC), KC_TRNS, KC_NO, KC_TRNS, KC_TRNS,               KC_QUOT, KC_DLR, KC_PERC, KC_CIRC, RSFT_T(KC_QUOT), \
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                    KC_SLSH, KC_EXLM, KC_AT, KC_HASH, KC_TRNS, \
    KC_TRNS, KC_TRNS,                                               KC_TRNS, KC_TRNS \
)

// layer 2
#define _NUMBERS LAYOUT_split_3x5_2( \
    KC_LPRN, KC_AMPR, KC_ASTR, KC_GRV, KC_RPRN,                     KC_PAST, KC_7, KC_8, KC_9, KC_PMNS, \
    KC_LCBR, KC_DLR, KC_PERC, KC_CIRC, KC_RCBR,                     KC_0, KC_4, KC_5, KC_6, KC_PPLS, \
    KC_LBRC, KC_EXLM, KC_AT, KC_HASH, KC_RBRC,                      KC_PDOT, KC_1, KC_2, KC_3, KC_PEQL, \
    LT(7,KC_ESC), KC_TRNS,                                          KC_TRNS, LT(7,KC_ENT) \
)

// layer 3
#define _SYMBOLS LAYOUT_split_3x5_2( \
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                    KC_TRNS, KC_UNDS, KC_PIPE, KC_QUOT, KC_TRNS, \
    KC_CIRC, KC_ASTR, KC_AMPR, KC_NO, KC_TRNS,                      KC_HASH, KC_TILD, KC_SLSH, KC_DQUO, KC_DLR, \
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                    KC_TRNS, KC_MINS, KC_BSLS, KC_GRV, KC_TRNS, \
    KC_VOLD, KC_MUTE,                                               KC_TRNS, KC_VOLU \
)

// layer 4
#define _DEV LAYOUT_split_3x5_2( \
    KC_TRNS, KC_COLN, KC_LT, KC_GT, KC_PMNS,                        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
    KC_LCBR, KC_RCBR, KC_LPRN, KC_RPRN, KC_AT,                      KC_TRNS, KC_NO, KC_MINS, KC_PLUS, KC_PERC, \
    KC_TRNS, KC_EXLM, KC_LBRC, KC_RBRC, KC_EQL,                     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
    KC_VOLD, KC_MUTE,                                               KC_MPLY, KC_VOLU \
)

// layer 5
#define _FN LAYOUT_split_3x5_2( \
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                    KC_TRNS, KC_F7, KC_F8, KC_F9, KC_F10, \
    KC_TRNS, KC_NO, LCTL(KC_LALT), KC_TRNS, KC_TRNS,                KC_TRNS, KC_F4, KC_F5, KC_F6, KC_F11, \
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                    KC_TRNS, KC_F1, KC_F2, KC_F3, KC_F12, \
    KC_TRNS, KC_TRNS,                                               KC_TRNS, KC_TRNS \
)

// layer 6
#define _MOUSE LAYOUT_split_3x5_2( \
    KC_BTN3, KC_BTN1, KC_WH_U, KC_BTN2, KC_ACL0,                    DM_PLY1, DM_REC1, DM_RSTP, KC_TRNS, KC_TRNS, \
    KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_ACL1,                    KC_TRNS, KC_TRNS, KC_TRNS, KC_NO, KC_TRNS, \
    KC_TRNS, KC_WH_L, KC_WH_D, KC_WH_R, KC_ACL2,                    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
    KC_TRNS, KC_TRNS,                                               KC_TRNS, KC_TRNS \
)

// layer 7
#define _UTIL LAYOUT_split_3x5_2( \
    TOGGLE_WINDOWS, KC_TRNS, KC_COLN, KC_ESC, KC_INS,               DM_PLY1, DM_REC1, DM_RSTP, SSHOT, KC_HOME, \
    KC_TRNS, KC_PERC, KC_SLSH, KC_ENT, KC_TRNS,                     KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_END, \
    KC_TRNS, KC_TRNS, KC_TRNS, KC_GRV, KC_TAB,                      KC_TAB, KC_GRV, RALT_T(KC_COMM), TG(2), RESET, \
    KC_DEL, KC_TRNS,                                                KC_NO, KC_GRV \
)

#define _GAME LAYOUT_split_3x5_2( \
    KC_GRV, KC_Q, KC_W, KC_E, KC_R,                                 KC_T, KC_Y, KC_U, KC_I, KC_O, \
    KC_TAB, KC_A, KC_S, KC_D, KC_F,                                 KC_G, KC_H, KC_J, KC_K, KC_L,\
    KC_LCTL, KC_Z, KC_X, KC_C, KC_V,                                KC_B, KC_N, KC_M, TG(2), KC_SLASH, \
    KC_LSFT, KC_SPC,                                                KC_BSPC, KC_ENT \
)
// clang-format on

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[0] = _QWERTY,
[1] = _MORE_SYMBOLS,
[2] = _NUMBERS,
[3] = _SYMBOLS,
[4] = _DEV,
[5] = _FN,
[6] = _MOUSE,
[7] = _UTIL,
};

#ifdef TAP_DANCE_ENABLE
// Determine the tapdance state to return
td_state_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
        else return TD_SINGLE_HOLD;
    }

    if (state->count == 2) {
        if (state->interrupted) return TD_DOUBLE_SINGLE_TAP;
        else if (state->pressed) return TD_DOUBLE_TAP_HOLD;
        else return TD_DOUBLE_SINGLE_TAP;
    }

    else return TD_UNKNOWN; // Any number higher than the maximum state value you return above
}

void modSeven_finished(qk_tap_dance_state_t *state, void *user_data) {
    mod_7_td_state = cur_dance(state);
    switch (mod_7_td_state) {
        case TD_SINGLE_TAP:
            register_code16(KC_ESC);
            break;
        case TD_SINGLE_HOLD:
            layer_on(7); // For a layer-tap key, use `layer_on(_MY_LAYER)` here
            break;
        case TD_DOUBLE_SINGLE_TAP: // Allow nesting of 2 parens `((` within tapping term
            tap_code16(KC_ESC);
            register_code16(KC_ESC);
            break;
        case TD_DOUBLE_TAP_HOLD:
            layer_on(7); // For a layer-tap key, use `layer_on(_MY_LAYER)` here
            register_code16(KC_LGUI);
            break;
        default:
            break;
    }
}

void modSeven_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (mod_7_td_state) {
        case TD_SINGLE_TAP:
            unregister_code16(KC_ESC);
            break;
        case TD_SINGLE_HOLD:
            layer_off(7); // For a layer-tap key, use `layer_off(_MY_LAYER)` here
            break;
        case TD_DOUBLE_SINGLE_TAP:
            unregister_code16(KC_ESC);
            break;
        case TD_DOUBLE_TAP_HOLD:
            unregister_code16(KC_LGUI);
            layer_off(7); // For a layer-tap key, use `layer_on(_MY_LAYER)` here
            break;
        default:
            break;
    }
    mod_7_td_state = TD_NONE;
}

void gui_mod_7_spc_finished(qk_tap_dance_state_t *state, void *user_data) {
    mod_7_spc_td_state = cur_dance(state);
    switch (mod_7_spc_td_state) {
        case TD_SINGLE_TAP:
            register_code16(KC_SPC);
            break;
        case TD_SINGLE_HOLD:
            register_code16(KC_LGUI);
            break;
        case TD_DOUBLE_SINGLE_TAP: // Allow nesting of 2 parens `((` within tapping term
            tap_code16(KC_SPC);
            register_code16(KC_SPC);
            break;
        case TD_DOUBLE_TAP_HOLD:
            layer_on(7); // For a layer-tap key, use `layer_on(_MY_LAYER)` here
            register_code16(KC_LGUI);
            break;
        default:
            break;
    }
}

void gui_mod_7_spc_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (mod_7_spc_td_state) {
        case TD_SINGLE_TAP:
            unregister_code16(KC_SPC);
            break;
        case TD_SINGLE_HOLD:
            unregister_code16(KC_LGUI);
            break;
        case TD_DOUBLE_SINGLE_TAP:
            unregister_code16(KC_SPC);
            break;
        case TD_DOUBLE_TAP_HOLD:
            unregister_code16(KC_LGUI);
            layer_off(7); // For a layer-tap key, use `layer_on(_MY_LAYER)` here
            break;
        default:
            break;
    }
    mod_7_spc_td_state = TD_NONE;
}

void gui_mod_7_ent_finished(qk_tap_dance_state_t *state, void *user_data) {
    mod_7_ent_td_state = cur_dance(state);
    switch (mod_7_ent_td_state) {
        case TD_SINGLE_TAP:
            register_code16(KC_ENT);
            break;
        case TD_SINGLE_HOLD:
            layer_on(7);
            break;
        case TD_DOUBLE_SINGLE_TAP:
            tap_code16(KC_ENT);
            register_code16(KC_ENT);
            break;
        case TD_DOUBLE_TAP_HOLD:
            layer_on(7);
            register_code16(KC_LGUI);
            break;
        default:
            break;
    }
}

void gui_mod_7_ent_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (mod_7_ent_td_state) {
        case TD_SINGLE_TAP:
            unregister_code16(KC_ENT);
            break;
        case TD_SINGLE_HOLD:
            layer_off(7);
            break;
        case TD_DOUBLE_SINGLE_TAP:
            unregister_code16(KC_ENT);
            break;
        case TD_DOUBLE_TAP_HOLD:
            unregister_code16(KC_LGUI);
            layer_off(7);
            break;
        default:
            break;
    }
    mod_7_ent_td_state = TD_NONE;
}

// Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_MOD_7] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, modSeven_finished, modSeven_reset),
    [TD_GUI_MOD_7_SPC] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, gui_mod_7_spc_finished, gui_mod_7_spc_reset),
    [TD_GUI_MOD_7_ENT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, gui_mod_7_ent_finished, gui_mod_7_ent_reset),
};
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  #ifdef CONSOLE_ENABLE
      if (record->event.pressed) {
          uprintf("0x%04X,%u,%u,%u,%b,0x%02X,0x%02X,%u\n",
                  keycode,
                  record->event.key.row,
                  record->event.key.col,
                  get_highest_layer(layer_state),
                  record->event.pressed,
                  get_mods(),
                  get_oneshot_mods(),
                  record->tap.count
                  );
      }
  #endif
  switch (keycode) { // This will do most of the grunt work with the keycodes.
    case ALT_TAB:
      if (record->event.pressed) {
        if (!is_alt_tab_active) {
          is_alt_tab_active = true;
          register_code(is_windows ? KC_LALT : KC_LGUI);
        }
        alt_tab_timer = timer_read();
        register_code(KC_TAB);
      } else {
        unregister_code(KC_TAB);
      }
      break;
    case ALT_GRAVE:
      if (record->event.pressed) {
        register_code(is_windows ? KC_LALT : KC_LGUI);
        register_code(KC_GRV);
      } else {
        unregister_code(KC_GRV);
        unregister_code(is_windows ? KC_LALT : KC_LGUI);
      }
      break;
    case TOGGLE_WINDOWS:
      process_magic(MAGIC_TOGGLE_CTL_GUI, record);
      if (record->event.pressed) {
        is_windows = !is_windows;
      }
      break;
    case SSHOT:
      if (is_windows) { break; }
      if (record->event.pressed) {
        register_code(KC_LGUI);
        register_code(KC_LCTL);
        register_code(KC_LSFT);
        register_code(KC_4);
      } else {
        unregister_code(KC_4);
        unregister_code(KC_LGUI);
        unregister_code(KC_LCTL);
        unregister_code(KC_LSFT);
      }
      break;
  }
  return true;
}

void matrix_scan_user(void) {
  if (is_alt_tab_active) {
    if (timer_elapsed(alt_tab_timer) > 1000) {
      unregister_code(is_windows ? KC_LALT : KC_LGUI);
      is_alt_tab_active = false;
    }
  }
}
