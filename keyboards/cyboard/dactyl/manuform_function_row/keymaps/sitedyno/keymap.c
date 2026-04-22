#include <stdint.h>
#include "action.h"
#include "keycodes.h"
#include "matrix.h"
#include "quantum.h"
#include "quantum_keycodes.h"
#include "send_string_keycodes.h"
#include "time.h"
#include QMK_KEYBOARD_H
#include "users/sitedyno/sitedyno.h"

enum custom_keycodes {
    RPT_KEY_V = SAFE_RANGE,
    RPT_KEY_X,
    RPT_SPACE,
    DO_NOT_USE
};

bool repeat_active = false;
int last_key_code = DO_NOT_USE;
static uint16_t key_timer;
static uint16_t repeat_delay = 100;

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT_manuform_fun(
        KC_ESC,  KC_F1,        KC_F2,        KC_F3,        KC_F4,         KC_F5,                                              KC_F6,          KC_F7,        KC_F8,        KC_F9,        KC_F10,          KC_F11,
        KC_EQL,  KC_1,         KC_2,         KC_3,         KC_4,          KC_5,                                               KC_6,           KC_7,         KC_8,         KC_9,         KC_0,            KC_MINS,
        KC_TAB,  KC_Q,         KC_W,         KC_E,         KC_R,          KC_T,                                               KC_Y,           KC_U,         KC_I,         KC_O,         KC_P,            KC_BSLS,
        KC_EQL,  LGUI_T(KC_A), LALT_T(KC_S), LCTL_T(KC_D), LSFT_T(KC_F),  KC_G,                                               KC_H,           RSFT_T(KC_J), RCTL_T(KC_K), RALT_T(KC_L), RGUI_T(KC_QUOT), KC_SCLN,
        KC_LSFT, KC_Z,         KC_X,         KC_C,         KC_V,          KC_B,                                               KC_N,           KC_M,         KC_COMM,      KC_DOT,       KC_SLSH,         KC_RSFT,
        KC_LGUI, KC_LBRC,      KC_DOWN,      KC_UP,          LT(3, KC_ESC), LT(1, KC_SPC), LT(2, KC_TAB),/**/LT(5, KC_ENT), LT(4, KC_BSPC), LT(6, KC_DEL),  KC_LEFT,      KC_RIGHT,     KC_RBRC,         TO(7),
                                                             KC_HOME,       KC_END,        KC_ESC,       /**/KC_GRAVE,      CW_TOGG,        KC_APP
    ),

    [1] = LAYOUT_manuform_fun(
        _______, _______, _______, _______, _______, _______,                          _______, _______,  _______, _______,  _______, _______,
        _______, _______, _______, _______, _______, _______,                          _______, _______,  _______, _______,  _______, _______,
        _______, _______, _______, _______, _______, _______,                          KC_AGIN, KC_PASTE, KC_COPY, KC_CUT,   KC_UNDO, _______,
        _______, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, _______,                          KC_LEFT, KC_DOWN,  KC_UP,   KC_RIGHT, _______, CW_TOGG,
        _______, _______, _______, _______, _______, _______,                          KC_HOME, KC_PGDN,  KC_PGUP, KC_END,   KC_INS,  _______,
        _______, _______, _______, _______,   _______, _______, _______,/**/KC_ENT,  KC_BSPC, KC_DEL,     _______, _______,  _______, _______,
                                              _______, _______, _______,/**/_______, _______, _______
    ),

    [2] = LAYOUT_manuform_fun(
        _______, _______, _______, _______, _______, _______,                          _______, _______,  _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                          _______, KC_ACL0,  KC_ACL1, KC_ACL2, _______, _______,
        _______, _______, _______, _______, _______, _______,                          KC_AGIN, KC_PASTE, KC_COPY, KC_CUT,  KC_UNDO, _______,
        _______, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, _______,                          KC_MS_L, KC_MS_D,  KC_MS_U, KC_MS_R, _______, _______,
        _______, _______, _______, _______, _______, _______,                          KC_WH_L, KC_WH_D,  KC_WH_U, KC_WH_R, _______, _______,
        _______, _______, _______, _______,   _______, _______, _______,/**/KC_BTN3, KC_BTN1, KC_BTN2,    _______, _______, _______, _______,
                                              _______, _______, _______,/**/_______, _______, _______
    ),

    [3] = LAYOUT_manuform_fun(
        _______, _______, _______, _______, _______, _______,                           _______, _______, _______, _______, QK_REBOOT, QK_BOOT,
        _______, _______, _______, _______, _______, _______,                           _______, _______, _______, _______, _______,   _______,
        _______, _______, _______, _______, _______, _______,                           _______, KC_F20,  _______, _______, _______,   _______,
        _______, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, _______,                           KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, _______,   KC_PSCR,
        _______, _______, _______, _______, _______, _______,                           _______, _______, _______, _______, _______,   _______,
        _______, _______, _______, _______,   _______, _______, _______,/**/KC_MSTP, KC_MPLY, KC_MUTE,    _______, _______, _______,   _______,
                                              _______, _______, _______,/**/_______, _______, KC_F20
    ),

    [4] = LAYOUT_manuform_fun(
        _______, _______, _______, _______, _______, _______,                          _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                          _______, _______, _______, _______, _______, _______,
        _______, KC_LBRC, KC_7,    KC_8,    KC_9,    KC_RBRC,                          _______, _______, _______, _______, _______, _______,
        _______, KC_SCLN, KC_4,    KC_5,    KC_6,    KC_EQL,                          _______, KC_RSFT, KC_RCTL, KC_RALT, KC_RGUI, _______,
        _______, KC_GRV,  KC_1,    KC_2,    KC_3,    KC_BSLS,                          _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______,   KC_DOT,  KC_0,    KC_MINS,/**/_______, _______, _______,   _______, _______, _______, _______,
                                              _______, _______, _______,/**/_______, _______, _______
    ),

    [5] = LAYOUT_manuform_fun(
        _______, _______, _______, _______, _______, _______,                                                  _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                                                  _______, _______, _______, _______, _______, _______,
        _______, LSFT(KC_LBRC), LSFT(KC_7), LSFT(KC_8), LSFT(KC_9), LSFT(KC_RBRC),                             _______, _______, _______, _______, _______, _______,
        _______, LSFT(KC_SCLN), LSFT(KC_4), LSFT(KC_5), LSFT(KC_6), LSFT(KC_EQL),                             _______, KC_RSFT, KC_RCTL, KC_RALT, KC_RGUI, _______,
        _______, LSFT(KC_GRV),  LSFT(KC_1), LSFT(KC_2), LSFT(KC_3), LSFT(KC_BSLS),                             _______, _______, _______, _______, _______, _______,
        _______, _______,       _______,    _______,      LSFT(KC_9), LSFT(KC_0), LSFT(KC_MINS),/**/_______, _______, _______,   _______, _______, _______, _______,
                                                          _______,    _______,    _______,      /**/_______, _______, _______
    ),

    [6] = LAYOUT_manuform_fun(
        _______, _______, _______, _______, _______, _______,                          _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                          _______, _______, _______, _______, _______, _______,
        _______, KC_F12,  KC_F7,   KC_F8,   KC_F9,   KC_PSCR,                          _______, _______, _______, _______, _______, _______,
        _______, KC_F11,  KC_F4,   KC_F5,   KC_F6,   KC_SCRL,                          _______, KC_RSFT, KC_RCTL, KC_RALT, KC_RGUI, _______,
        _______, KC_F10,  KC_F1,   KC_F2,   KC_F3,   KC_PAUS,                          _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______,   KC_MENU, KC_SPC,  KC_TAB, /**/_______, _______, _______,   _______, _______, _______, _______,
                                              _______, _______, _______,/**/_______, _______, _______
    ),

    [7] = LAYOUT_manuform_fun(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3, KC_F4,          KC_F5,                                   KC_F6,   KC_F7,  KC_F8,   KC_F9,    KC_F10,  KC_F11,
        KC_GRV,  KC_1,    KC_2,    KC_3,  KC_4,           KC_5,                                    KC_6,    KC_7,   KC_8,    KC_9,     KC_0,    KC_MINS,
        KC_TAB,  KC_Q,    KC_W,    KC_E,  KC_R,           KC_T,                                    KC_Y,    KC_U,   KC_I,    KC_O,     KC_P,    KC_BSLS,
        KC_EQL,  KC_A,    KC_S,    KC_D,  KC_F,           KC_G,                                    KC_H,    KC_J,   KC_K,    KC_L,     KC_QUOT, KC_SCLN,
        KC_LSFT, KC_Z,    RPT_KEY_X,    KC_C,  RPT_KEY_V,   KC_B,                                    KC_N,    KC_M,   KC_COMM, KC_DOT,   KC_SLSH, KC_RSFT,
        KC_LGUI, KC_LBRC, KC_DOWN, KC_UP,   LCTL_T(KC_ESC), RPT_SPACE,  LALT_T(KC_TAB),/**/KC_ENT,  KC_BSPC, KC_DEL,   KC_LEFT, KC_RIGHT, KC_LBRC, TO(0),
                                            _______,        _______, _______,       /**/_______, _______, _______
    ),

    [8] = LAYOUT_manuform_fun(
        _______, _______, _______, _______, _______, _______,                           _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                           _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                           _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                           _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                           _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______, _______, _______,
                                            _______, _______, _______,         _______, _______, _______
    ),

    [9] = LAYOUT_manuform_fun(
        _______, _______, _______, _______, _______, _______,                           _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                           _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                           _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                           _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                           _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______, _______, _______,
                                            _______, _______, _______,         _______, _______, _______
    )
};
//clang-format on

void keyboard_post_init_user(void) {
    // debug_enable = true;
    // debug_matrix=true;
    // debug_keyboard=true;
    // debug_mouse=true;
}

void send_rpt_string(char key) {
    switch (key) {
        case 'v':
            SEND_STRING(SS_DOWN(X_V) SS_DELAY(75) SS_UP(X_V));
        break;
        case 'x':
            SEND_STRING(SS_DOWN(X_X) SS_DELAY(75) SS_UP(X_X));
        break;
        case '_':
            SEND_STRING(SS_DOWN(X_SPACE) SS_DELAY(75) SS_UP(X_SPACE));
        break;
    }
}

void matrix_scan_user() {
    if ((repeat_active) && (timer_elapsed(key_timer) > repeat_delay)) {
        switch (last_key_code) {
            case KC_V:
                send_rpt_string('v');
            break;
            case KC_X:
                send_rpt_string('x');
            break;
            case KC_SPACE:
                send_rpt_string('_');
            break;
        }
        key_timer = timer_read();
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case RPT_KEY_V:
            if (record->event.pressed) {
                send_rpt_string('v');
                repeat_active = true;
                last_key_code = KC_V;
                key_timer = timer_read();
            } else {
                repeat_active = false;
            }
        break;
        case RPT_KEY_X:
            if (record->event.pressed) {
                send_rpt_string('x');
                repeat_active = true;
                last_key_code = KC_X;
                key_timer = timer_read();
            } else {
                repeat_active = false;
            }
        break;
        case RPT_SPACE:
            if (record->event.pressed) {
                send_rpt_string('_');
                repeat_active = true;
                last_key_code = KC_SPACE;
                key_timer = timer_read();
            } else {
                repeat_active = false;
            }
        break;
    }
    return true;
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    sd_capslock_warning(led_min, led_max);
    sd_layer_rgb(led_min, led_max);
    return false;
}
