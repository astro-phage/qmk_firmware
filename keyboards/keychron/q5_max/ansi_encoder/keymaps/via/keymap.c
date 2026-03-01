/* Copyright 2024 @ Keychron (https://www.keychron.com)
 *
 * This program is free software: you can redistribute it and/or modify
 * ... [Standard License Header] ...
 */

#include QMK_KEYBOARD_H
#include "keychron_common.h"

// 1. Define your layers. Added WIN_CTRL for your Caps Lock layer.
enum layers {
    MAC_BASE,
    MAC_FN,
    WIN_BASE,
    WIN_FN,
    WIN_CTRL, 
};

// 2. Define custom keycodes for your Umlauts
enum custom_keycodes {
    MACRO_OE = SAFE_RANGE,
    MACRO_AE,
    MACRO_UE
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [MAC_BASE] = LAYOUT_ansi_101(
        KC_ESC,             KC_BRID,  KC_BRIU,  KC_MCTRL, KC_LNPAD, RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,    KC_VOLD,  KC_VOLU,            KC_DEL,   KC_F13,   KC_F14 ,  KC_F15,     KC_MPLY,
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,    KC_EQL,   KC_BSPC,            KC_PGUP,  KC_NUM,   KC_PSLS,  KC_PAST,    KC_PMNS,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,    KC_RBRC,  KC_BSLS,            KC_PGDN,  KC_P7,    KC_P8,    KC_P9,
        KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,              KC_ENT,             KC_HOME,  KC_P4,    KC_P5,    KC_P6,      KC_PPLS,
        KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,              KC_RSFT,  KC_UP,              KC_P1,    KC_P2,    KC_P3,
        KC_LCTL,  KC_LOPTN, KC_LCMMD,                                         KC_SPC,                                   KC_RCMMD, MO(MAC_FN), KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT,            KC_P0,    KC_PDOT,    KC_PENT),

    [MAC_FN] = LAYOUT_ansi_101(
        _______,            KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,     KC_F11,   KC_F12,             _______,  _______,  _______,  _______,    RGB_TOG,
        _______,  BT_HST1,  BT_HST2,  BT_HST3,  P2P4G,    _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,            _______,  _______,  _______,  _______,    _______,
        RGB_TOG,  RGB_MOD,  RGB_VAI,  RGB_HUI,  RGB_SAI,  RGB_SPI,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,            _______,  _______,  _______,  _______,
        _______,  RGB_RMOD, RGB_VAD,  RGB_HUD,  RGB_SAD,  RGB_SPD,  _______,  _______,  _______,  _______,  _______,  _______,              _______,            KC_END,   _______,  _______,  _______,    _______,
        _______,            _______,  _______,  _______,  _______,  BAT_LVL,  NK_TOGG,  _______,  _______,  _______,  _______,              _______,  _______,            _______,  _______,  _______,
        _______,  _______,  _______,                                          _______,                                  _______,  _______,    _______,  _______,  _______,  _______,            _______,  _______,    _______),

    // --- WINDOWS BASE LAYER ---
    [WIN_BASE] = LAYOUT_ansi_101(
        KC_ESC,             KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,     KC_F11,   KC_F12,             KC_PSCR,   KC_CALC,   _______,   KC_CALC,    KC_MPLY, // 3rd key next to wheel -> KC_CALC
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,    KC_EQL,   KC_BSPC,            KC_HOME,  KC_ESC,   KC_PSLS,  KC_PAST,    KC_PMNS,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,    KC_RBRC,  KC_BSLS,            KC_END,  KC_P7,    KC_P8,    KC_P9,
        MO(WIN_CTRL), KC_A, KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,              KC_ENT,             KC_DEL,  KC_P4,    KC_P5,    KC_P6,      KC_PPLS, // Caps Lock -> MO(WIN_CTRL)
        KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,              KC_RSFT,  KC_UP,              KC_P1,    KC_P2,    KC_P3,
        KC_LCTL,  KC_LWIN,  KC_LALT,                                          KC_SPC,                                   KC_RALT,  MO(WIN_FN), KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT,            KC_P0,    KC_PDOT,    KC_PENT),

    [WIN_FN] = LAYOUT_ansi_101(
            _______,            KC_BRID,  KC_BRIU,  KC_TASK,  KC_FILE,  RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,    KC_VOLD,  KC_VOLU,            _______,  _______,  _______,  _______,    RGB_TOG,
            _______,  BT_HST1,  BT_HST2,  BT_HST3,  P2P4G,    _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,            _______,  KC_NUM,   _______,  _______,    _______,
            RGB_TOG,  RGB_MOD,  RGB_VAI,  RGB_HUI,  RGB_SAI,  RGB_SPI,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,            _______,  _______,  _______,  _______,
            KC_CAPS,  RGB_RMOD, RGB_VAD,  RGB_HUD,  RGB_SAD,  RGB_SPD,  _______,  _______,  _______,  _______,  _______,  _______,              _______,            KC_END,   _______,  _______,  _______,    _______, // <-- Added KC_CAPS right here
            _______,            _______,  _______,  _______,  _______,  BAT_LVL,  NK_TOGG,  _______,  _______,  _______,  _______,              _______,  _______,            _______,  _______,  _______,
            _______,  _______,  _______,                                          _______,                                  _______,  _______,    _______,  _______,  _______,  _______,            _______,  _______,    _______),
   
    // --- CAPS LOCK LAYER (WIN_CTRL) ---
    // Only mapped keys will do something. '_______' passes through to WIN_BASE, preventing dead keys.
    [WIN_CTRL] = LAYOUT_ansi_101(
        _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,            _______,  _______,  KC_SLEP,  _______,    _______, // 2nd key next to wheel -> KC_SLEP
        _______,    KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,   KC_F9,   KC_F10,   _______,    _______,   KC_DEL,            _______,  KC_NUM,   _______,  _______,    _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_UP,  _______,  _______,  MACRO_UE,   _______,  _______,            _______,  _______,  _______,  _______, // [ -> ü
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_LEFT,  KC_DOWN,  KC_RGHT,  MACRO_OE, MACRO_AE,             _______,            _______,  _______,  _______,  _______,    _______, // ; -> ö, ' -> ä
        _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,              _______,  _______,            _______,  _______,  _______,
        _______,  _______,  _______,                                          _______,                                  _______,  _______,    _______,  _______,  _______,  _______,            _______,  _______,    _______),
};
// clang-format on

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [MAC_BASE] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [MAC_FN]   = {ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},
    // Normal wheel = Volume
    [WIN_BASE] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [WIN_FN]   = {ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},
    // Wheel while holding Caps Lock = Prev/Next Track
    [WIN_CTRL] = {ENCODER_CCW_CW(KC_MPRV, KC_MNXT)},
};
#endif // ENCODER_MAP_ENABLE

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_keychron_common(keycode, record)) {
        return false;
    }
    
    // Process custom macros only on key press
    if (record->event.pressed) {
        // Check if shift is currently held down so we can output capitals
        bool is_shifted = get_mods() & MOD_MASK_SHIFT;

        switch (keycode) {
            case MACRO_OE: // For 'ö' and 'Ö'
                if (is_shifted) {
                    del_mods(MOD_MASK_SHIFT); // Temporarily drop shift to prevent Alt+Shift glitches
                    SEND_STRING(SS_LALT(SS_TAP(X_KP_0) SS_TAP(X_KP_2) SS_TAP(X_KP_1) SS_TAP(X_KP_4))); // Ö
                    // Removed add_mods here to prevent the stuck shift bug!
                } else {
                    SEND_STRING(SS_LALT(SS_TAP(X_KP_0) SS_TAP(X_KP_2) SS_TAP(X_KP_4) SS_TAP(X_KP_6))); // ö
                }
                return false;

            case MACRO_AE: // For 'ä' and 'Ä'
                if (is_shifted) {
                    del_mods(MOD_MASK_SHIFT);
                    SEND_STRING(SS_LALT(SS_TAP(X_KP_0) SS_TAP(X_KP_1) SS_TAP(X_KP_9) SS_TAP(X_KP_6))); // Ä
                } else {
                    SEND_STRING(SS_LALT(SS_TAP(X_KP_0) SS_TAP(X_KP_2) SS_TAP(X_KP_2) SS_TAP(X_KP_8))); // ä
                }
                return false;

            case MACRO_UE: // For 'ü' and 'Ü'
                if (is_shifted) {
                    del_mods(MOD_MASK_SHIFT);
                    SEND_STRING(SS_LALT(SS_TAP(X_KP_0) SS_TAP(X_KP_2) SS_TAP(X_KP_2) SS_TAP(X_KP_0))); // Ü
                } else {
                    SEND_STRING(SS_LALT(SS_TAP(X_KP_0) SS_TAP(X_KP_2) SS_TAP(X_KP_5) SS_TAP(X_KP_2))); // ü
                }
                return false;
        }
    }

    return true;
}