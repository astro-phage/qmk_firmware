/* Copyright 2024 @ Keychron (https://www.keychron.com)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/* 

Important Configuration: 
  Ensure TAP_DANCE_ENABLE = yes is set in rules.mk to enable the tap dance functionality.

Keymap contains:
- Activate Caps Lock: Double tapping the <Shift> key twice will toggle Caps Lock on and off.
- Umlauts: FN2 (momentary) or RShift (Toggle) activates a layer specifically for writing umlauts ("writing mode").
- Caps Lock Key Reassigned to Win_FN_2.
- LED Color Change for Layer Switches: LED colors adjust to indicate active layers. When switching to layers with Umlaut functionality, or when RGB settings change, LEDs will reflect these changes by highlighting the relevant keys in a different color than the rest of the keyboard.
- LED Color for Caps Lock: When Caps Lock is activated, all letter keys’ LEDs will change color to indicate that Caps Lock is on.

- Knob Functionality:
    Win Layer: Rotating the knob adjusts the system volume.
    Win_FN Layer: When toggling to Win_FN using the Right Shift key, knob rotation adjusts the volume (to not unexpectedly change the track while in writing mode).
    Win_FN_2 Layer: Using Momentary Layer (MO) functionality, knob rotation changes the track (previous/next). This feature is accessible through Caps Lock.

- WIN_FN_2 Customizations:
    Space -> Backspace
    Number Row (1-0) -> Function Keys (F1-F10)
    Numpad Numbers -> Arrow Keys
    IJKL Keys -> Arrow Keys
    Backspace -> Delete

- WIN_FN (Writing Mode):
    Tap Hold for Umlauts: Holding down keys while in WIN_FN layer will output BASE layer values instead of umlauts. For example:
        ä -> '
        ö -> ;
        ü -> [

- Commented-Out Features:
    Tab Hold for Base Layer Values: Implemented but commented out due to potential issues. This feature would allow a tap hold on certain keys to output base layer values like quotes (' =>ä), backslashes, and brackets, while holding the key would output umlauts instead. This was commented out to avoid disrupting the usability of the base layer.
*/

#include QMK_KEYBOARD_H
#include "keychron_common.h"
#include <quantum.h>

#define MODS_SHIFT_MASK  (MOD_BIT(KC_LSFT)|MOD_BIT(KC_RSFT))

// DOUBLE TAP OF SHIFT TO CAPS LOCK
enum {
    TD_LSFT_CAPSLOCK = 0,
};

void dance_lshift_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        register_code(KC_LSFT);
    } else if (state->count == 2) {
        register_code(KC_CAPS);
        unregister_code(KC_CAPS);
    }
}

void dance_lshift_reset(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        unregister_code(KC_LSFT);
    }
}

tap_dance_action_t tap_dance_actions[] = {
    [TD_LSFT_CAPSLOCK] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_lshift_finished, dance_lshift_reset),
};

// LAYER DEFINITION
enum layers {
    MAC_BASE,
    MAC_FN,
    WIN_BASE,
    WIN_FN,
    WIN_FN_2,
};

// CUSTOM KEYCODES
enum custom_keycodes {
    UM_U = SAFE_RANGE,
    UM_O,
    UM_A,

    UM_U_HOLD, // technically unnecessary but good to separe hold functionality from umlaut functionanlity to switch back quickly if needed by replacing UM_*_HOLD with UM_*
    UM_O_HOLD,
    UM_A_HOLD,

    // KC_QUOT_HOLD, Unused could be use for tap_hold to create umlaut
    // KC_SCLN_HOLD, Unused could be use for tap_hold to create umlaut
    // KC_LBRC_HOLD, Unused could be use for tap_hold to create umlaut
    // CLOSE_WINDOW  crashes the keyboard when pressed
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [MAC_BASE] = LAYOUT_ansi_101(
        KC_ESC,             KC_BRID,  KC_BRIU,  KC_MCTRL, KC_LNPAD, RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,    KC_VOLD,  KC_VOLU,            KC_DEL,   KC_F13,   KC_F14 ,  KC_F15,     KC_MUTE,
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,    KC_EQL,   KC_BSPC,            KC_PGUP,  KC_NUM,   KC_PSLS,  KC_PAST,    KC_PMNS,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,    KC_RBRC,  KC_BSLS,            KC_PGDN,  KC_P7,    KC_P8,    KC_P9,
        KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,              KC_ENT,             KC_HOME,  KC_P4,    KC_P5,    KC_P6,      KC_PPLS,
        KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,              KC_RSFT,  KC_UP,              KC_P1,    KC_P2,    KC_P3,
        KC_LCTL,  KC_LOPTN, KC_LCMMD,                               KC_SPC,                                 KC_RCMMD, MO(MAC_FN), KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT,            KC_P0,    KC_PDOT,    KC_PENT),
    [MAC_FN] = LAYOUT_ansi_101(
        _______,            KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,     KC_F11,   KC_F12,             _______,  _______,  _______,  _______,    RGB_TOG,
        _______,  BT_HST1,  BT_HST2,  BT_HST3,  P2P4G,    _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,            _______,  _______,  _______,  _______,    _______,
        RGB_TOG,  RGB_MOD,  RGB_VAI,  RGB_HUI,  RGB_SAI,  RGB_SPI,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,            _______,  _______,  _______,  _______,
        _______,  RGB_RMOD, RGB_VAD,  RGB_HUD,  RGB_SAD,  RGB_SPD,  _______,  _______,  _______,  _______,  _______,  _______,              _______,            KC_END,   _______,  _______,  _______,    _______,
        _______,            _______,  _______,  _______,  _______,  BAT_LVL,  NK_TOGG,  _______,  _______,  _______,  _______,              _______,  _______,            _______,  _______,  _______,
        _______,  _______,  _______,                                _______,                                _______,  _______,    _______,  _______,  _______,  _______,            _______,  _______,    _______),
    [WIN_BASE] = LAYOUT_ansi_101(
        KC_ESC,             KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,     KC_F11,   KC_F12,             KC_PSCR,   KC_CALC,  _______, _______, KC_MPLY,
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,    KC_EQL,   KC_BSPC,            KC_HOME,   KC_ESC,  KC_PSLS,  KC_PAST,    KC_PMNS,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,    KC_RBRC,  KC_BSLS,            KC_END,    KC_P7,   KC_P8,    KC_P9,
        MO(WIN_FN_2),KC_A,  KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,    KC_ENT,             KC_DEL,    KC_P4,   KC_P5,    KC_P6,      KC_PPLS,
        TD(TD_LSFT_CAPSLOCK),         KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,     KC_SLSH,          TG(WIN_FN), KC_UP,             KC_P1,     KC_P2,      KC_P3,
        KC_LCTL,  KC_LWIN,  KC_LALT,                                KC_SPC,                                 KC_RALT,  MO(WIN_FN), KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT,            KC_P0,    KC_PDOT,    KC_PENT),
    
    /* Writing mode with Umlaut */
    [WIN_FN] = LAYOUT_ansi_101(
        _______,            RGB_TOG,  RGB_MOD,  _______,  _______,  RGB_VAD,  RGB_VAI,  RGB_HUD,  RGB_HUI,  RGB_SAD,  RGB_SAI,    RGB_SPD,  RGB_SPI,            KC_END,   _______,  _______,  _______,    KC_MPLY, 
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,            _______,  KC_NUM,   _______,  _______,    _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  UM_U_HOLD,       _______,  _______,            _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  UM_O_HOLD,UM_A_HOLD,                 _______,            _______,  _______,  _______,  _______,    _______,
        _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,              _______,  _______,            _______,  _______,  _______,
        _______,  _______,  _______,                                _______,                                _______,  _______,    _______,  _______,  _______,  _______,            _______,  _______,    _______),
    
    /* Used for when control (caps lock) will be pressed */
    [WIN_FN_2] = LAYOUT_ansi_101(
         _______,           _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,            _______,   _______,  _______,  _______,    KC_MPLY, 
        _______,    KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,   KC_F9,   KC_F10,   _______,    _______,   KC_DEL,            _______,  _______,  _______,  _______,    _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    KC_UP,  _______,  _______,  UM_U,       _______,  _______,            _______,  _______,   KC_UP,    _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_LEFT,  KC_DOWN,  KC_RGHT,  UM_O,     UM_A,                 _______,            _______,  KC_LEFT,  KC_DOWN,  KC_RGHT,    _______,
        _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,              _______,  _______,            _______,  _______,  _______,
        _______,  _______,  _______,                                KC_BSPC,                                _______,  _______,    _______,  _______,  _______,  _______,            _______,  _______,    _______),
};

// clang-format on
#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [MAC_BASE] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [MAC_FN]   = {ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},
    [WIN_BASE] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [WIN_FN] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [WIN_FN_2]   = {ENCODER_CCW_CW(KC_MPRV, KC_MNXT)},
};
#endif // ENCODER_MAP_ENABLE

// ON CAPSLOCK ON SET LETTER TO SPECIFIC RGB COLOR
void set_caps_lock_rgb(void) {
    // Define the key positions for the letters that should change color
    uint8_t key_positions[] = {
        37, 38, 39, 40, 41, 42, 43, 44, 45, 46, // Q to P
        56, 57, 58, 59, 60, 61, 62, 63, 64,     // A to L
        73, 74, 75, 76, 77, 78, 79              // Z to M
    };
    
    // Define the RGB color to set (72, 50, 168)
    uint8_t red = 0;
    uint8_t green = 153;
    uint8_t blue = 153;
    
    // Set the color for each key in the array
    for (uint8_t i = 0; i < sizeof(key_positions) / sizeof(key_positions[0]); i++) {
        rgb_matrix_set_color(key_positions[i], red, green, blue);
    }
}

bool is_caps_lock_on = false;

/*
The function layer_state_set_user() is triggered only when there is a change in layers.
To handle changes in lock states such as Caps Lock, Num Lock, Scroll Lock, etc., you should use led_update_user().
The led_update_user() function is automatically called whenever a lock state changes, ensuring that the LED indicators reflect the current state of these locks.
*/


bool led_update_user(led_t led_state) {
    /* Activate numlock when if off as i always want it on and the num_lock key is used for another functionality */
	if (!led_state.num_lock) {
		tap_code(KC_NUM_LOCK);
	}

    // On CapsLock change
    is_caps_lock_on = led_state.caps_lock;
    if (is_caps_lock_on) {
        set_caps_lock_rgb();
        return true;
    } else {
        //code for if caps lock is off
    }

	return true;
}

/* 
Override the matrix_scan_user function to continuously monitor the Caps Lock state.
This is crucial for maintaining the correct RGB lighting when Caps Lock is active.
Without this override, the RGB lighting changes may be overwritten or not reflect the current Caps Lock status.  
*/                   
void matrix_scan_user(void) {
    if (is_caps_lock_on) {
        set_caps_lock_rgb();
    }
}

/* Code reference:
https://gist.github.com/itspngu/9159f06153b440a754b33c6d65c5f302
https://www.alt-codes.net/german_alt_codes 
*/
void send_altcode(uint16_t mask, keyrecord_t *record) {
	
	/* Sends the "alt code" defined in mask, i.e. send_altcode(1234) 
	holds left alt while sending KP_1, KP_2, KP_3 and KP_4 taps, 
	then releases left alt if it wasn't being held by the user. 
	
	NOTE: If your alt code starts with a 0, leave that out, else the
	mask will be treated as octal and your firmware won't compile.
	send_altcode(123) will output KP_0, KP_1, KP_2 and KP_3. */
	
	// Check & save mod state	
	static uint8_t lalt_mask;
	lalt_mask = keyboard_report->mods & KC_LALT;
	
	// Split up the mask into its 4 decimals	
	static uint16_t kp[4];
	
	kp[0] = mask / 1000;
	kp[1] = mask / 100 - kp[0] * 100;
	kp[2] = mask / 10 - kp[0] * 1000 - kp[1] * 10;
	kp[3] = mask - kp[0] * 1000 - kp[1] * 100 - kp[2] * 10;
	
	// Convert to keycodes	
	for (uint8_t i=0; i<=3; i++) {
		switch(kp[i]) {
			case 0:
				kp[i] = KC_KP_0; break;
			case 1:
				kp[i] = KC_KP_1; break;
			case 2:
				kp[i] = KC_KP_2; break;
			case 3:
				kp[i] = KC_KP_3; break;
			case 4:
				kp[i] = KC_KP_4; break;
			case 5:
				kp[i] = KC_KP_5; break;
			case 6:
				kp[i] = KC_KP_6; break;
			case 7:
				kp[i] = KC_KP_7; break;
			case 8:
				kp[i] = KC_KP_8; break;
			case 9:
				kp[i] = KC_KP_9; break;
		}
	}
	
	// Put ALT into pressed state	
	if (!lalt_mask) {
		register_code(KC_LALT);
		send_keyboard_report();
	}	
	
	// The send_keyboard_report() spam is not pretty, but necessary.	
	add_key(kp[0]);
	send_keyboard_report();
	del_key(kp[0]);
	send_keyboard_report();
	add_key(kp[1]);
	send_keyboard_report();		
	del_key(kp[1]);
	send_keyboard_report();
	add_key(kp[2]);
	send_keyboard_report();		
	del_key(kp[2]);
	send_keyboard_report();
	add_key(kp[3]);
	send_keyboard_report();
	del_key(kp[3]);
	send_keyboard_report();
	
	// If user wasn't pressing ALT, release it	
	if (!lalt_mask) {
		unregister_code(KC_LALT);
	}
	
	send_keyboard_report();
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint8_t shift_mask;
	shift_mask = get_mods()&MODS_SHIFT_MASK;

    static uint16_t tap_hold_timeout_ms = 200;

    // static uint16_t quot_timer;
    // static uint16_t scln_timer;
    // static uint16_t lrbc_timer;

    static uint16_t umlaut_a_timer;
    static uint16_t umlaut_o_timer;
    static uint16_t umlaut_u_timer;

    // static bool quot_replacement_needed = false;
    // static bool scln_replacement_needed = false;
    // static bool lrbc_replacement_needed = false;

    static bool umlaut_a_replacement_needed = false;
    static bool umlaut_o_replacement_needed = false;
    static bool umlaut_u_replacement_needed = false;

    if (record->event.pressed) { /* Very important otherwise it will get triggered twice = output twice the same key */
        switch (keycode) {
            case UM_A_HOLD:
                umlaut_a_timer = timer_read(); // to check time for TAP-HOLD
                umlaut_a_replacement_needed = false; 
                // Improtant no return so UM_A gets executed as well
            case UM_A:       
                if (shift_mask) {
                    unregister_code(KC_LSFT);
                    unregister_code(KC_RSFT);
                    send_altcode(196, record); // Ä
                    if (shift_mask & MOD_BIT(KC_LSFT)) register_code(KC_LSFT);
                    if (shift_mask & MOD_BIT(KC_RSFT)) register_code(KC_RSFT);
                } else {
                    send_altcode(228, record); // ä
                }
                return false;
            case UM_O_HOLD:
                umlaut_o_timer = timer_read(); // to check time for TAP-HOLD
                umlaut_o_replacement_needed = false; 
                // Improtant no return so UM_O gets executed as well
            case UM_O:
                if (shift_mask) {
                    unregister_code(KC_LSFT);
                    unregister_code(KC_RSFT);
                    send_altcode(214, record); // Ö
                    if (shift_mask & MOD_BIT(KC_LSFT)) register_code(KC_LSFT);
                    if (shift_mask & MOD_BIT(KC_RSFT)) register_code(KC_RSFT);
                } else {
                    send_altcode(246, record); // ö
                }
                return false;
            case UM_U_HOLD:
                umlaut_u_timer = timer_read(); // to check time for TAP-HOLD
                umlaut_u_replacement_needed = false; 
                // Improtant no return so UM_U gets executed as well
            case UM_U:
                if (shift_mask) {
                    unregister_code(KC_LSFT);
                    unregister_code(KC_RSFT);
                    send_altcode(220, record); // Ü
                    if (shift_mask & MOD_BIT(KC_LSFT)) register_code(KC_LSFT);
                    if (shift_mask & MOD_BIT(KC_RSFT)) register_code(KC_RSFT);
                } else {
                    send_altcode(252, record); // ü 
                }
                return false;

            return false;
        }
    } else {
        switch (keycode) {
            case UM_A_HOLD:
                if (timer_elapsed(umlaut_a_timer) > tap_hold_timeout_ms) {
                    umlaut_a_replacement_needed = true;
                }
                if (umlaut_a_replacement_needed) {
                    // Remove the initial key press (if the system supports it)
                    // This part is tricky because usually once a key press is sent, it can't be taken back.
                    // However, in many text editors, sending a backspace might help to simulate this.
                    tap_code(KC_BSPC); // Remove the initial umlaut
                    tap_code(KC_QUOT);
                }
                return false;              

            case UM_O_HOLD:
                if (timer_elapsed(umlaut_o_timer) > tap_hold_timeout_ms) {
                    umlaut_o_replacement_needed = true;
                }
                if (umlaut_o_replacement_needed) {
                    // Remove the initial key press (if the system supports it)
                    // This part is tricky because usually once a key press is sent, it can't be taken back.
                    // However, in many text editors, sending a backspace might help to simulate this.
                    tap_code(KC_BSPC); // Remove the initial umlaut
                    tap_code(KC_SCLN);
                }
                return false;        

            case UM_U_HOLD:
                if (timer_elapsed(umlaut_u_timer) > tap_hold_timeout_ms) {
                    umlaut_u_replacement_needed = true;
                }
                if (umlaut_u_replacement_needed) {
                    // Remove the initial key press (if the system supports it)
                    // This part is tricky because usually once a key press is sent, it can't be taken back.
                    // However, in many text editors, sending a backspace might help to simulate this.
                    tap_code(KC_BSPC); // Remove the initial umlaut
                    tap_code(KC_LBRC);
                }
                return false;      
        }
    }

    
    if (!process_record_keychron_common(keycode, record)) {
        return false;
    }
    return true;
}

/* Change color depending on layer */
bool rgb_matrix_indicators_user(void) {
    
    // Define common RGB color constants
    const uint8_t red_win_fn = 252;
    const uint8_t green_win_fn = 3;
    const uint8_t blue_win_fn = 186;

    const uint8_t red_win_fn_2 = 24;
    const uint8_t green_win_fn_2 = 3;
    const uint8_t blue_win_fn_2 = 252;

    switch (get_highest_layer(layer_state)) {
        // case MAC_BASE:
        //     rgb_matrix_set_color_all(0,0,0);
        //     rgb_matrix_set_color(6, 204, 255, 204);
        //     return true;
        // case MAC_FN:     
        //     rgb_matrix_set_color_all(0,0,0);
        //     rgb_matrix_set_color(6, 75, 255, 75);
        //     rgb_matrix_set_color(7, 75, 255, 75);
        //     return true;
        case WIN_BASE: //GMAIL Layer
            // rgb_matrix_set_color_all(0, 204, 0);
            return true;
        case WIN_FN:
            rgb_matrix_set_color_all(0, 0, 0);
            rgb_matrix_set_color(1, red_win_fn, green_win_fn, blue_win_fn); // F1
            rgb_matrix_set_color(2, red_win_fn, green_win_fn, blue_win_fn); // F2
            rgb_matrix_set_color(3, red_win_fn, green_win_fn, blue_win_fn); // F3
            rgb_matrix_set_color(4, red_win_fn, green_win_fn, blue_win_fn); // F4
            rgb_matrix_set_color(5, red_win_fn, green_win_fn, blue_win_fn); // F5
            rgb_matrix_set_color(6, red_win_fn, green_win_fn, blue_win_fn); // F6
            rgb_matrix_set_color(7, red_win_fn, green_win_fn, blue_win_fn); // F7
            rgb_matrix_set_color(8, red_win_fn, green_win_fn, blue_win_fn); // F8
            rgb_matrix_set_color(9, red_win_fn, green_win_fn, blue_win_fn); // F9
            rgb_matrix_set_color(10, red_win_fn, green_win_fn, blue_win_fn); // F10
            rgb_matrix_set_color(11, red_win_fn, green_win_fn, blue_win_fn); // F11
            rgb_matrix_set_color(12, red_win_fn, green_win_fn, blue_win_fn); // F12
            // rgb_matrix_set_color(32, red_win_fn, green_win_fn, blue_win_fn); // Num lock
            rgb_matrix_set_color(47, red_win_fn, green_win_fn, blue_win_fn); // Ü
            rgb_matrix_set_color(65, red_win_fn, green_win_fn, blue_win_fn); // Ö
            rgb_matrix_set_color(66, red_win_fn, green_win_fn, blue_win_fn); // Ä
            return true;

        case WIN_FN_2:
            rgb_matrix_set_color_all(0, 0, 0);
            // rgb_matrix_set_color(32, red_win_fn_2, green_win_fn_2, blue_win_fn_2); // Num lock
            rgb_matrix_set_color(47, red_win_fn_2, green_win_fn_2, blue_win_fn_2); // Ü
            rgb_matrix_set_color(65, red_win_fn_2, green_win_fn_2, blue_win_fn_2); // Ö
            rgb_matrix_set_color(66, red_win_fn_2, green_win_fn_2, blue_win_fn_2); // Ä

            rgb_matrix_set_color(18, red_win_fn_2, green_win_fn_2, blue_win_fn_2); // F1 (1)
            rgb_matrix_set_color(19, red_win_fn_2, green_win_fn_2, blue_win_fn_2); // F2 (2)
            rgb_matrix_set_color(20, red_win_fn_2, green_win_fn_2, blue_win_fn_2); // F3 (3)
            rgb_matrix_set_color(21, red_win_fn_2, green_win_fn_2, blue_win_fn_2); // F4 (4)
            rgb_matrix_set_color(22, red_win_fn_2, green_win_fn_2, blue_win_fn_2); // F5 (5)
            rgb_matrix_set_color(23, red_win_fn_2, green_win_fn_2, blue_win_fn_2); // F6 (6)
            rgb_matrix_set_color(24, red_win_fn_2, green_win_fn_2, blue_win_fn_2); // F7 (7)
            rgb_matrix_set_color(25, red_win_fn_2, green_win_fn_2, blue_win_fn_2); // F8 (8)
            rgb_matrix_set_color(26, red_win_fn_2, green_win_fn_2, blue_win_fn_2); // F9 (9)
            rgb_matrix_set_color(27, red_win_fn_2, green_win_fn_2, blue_win_fn_2); // F0 (0)

            rgb_matrix_set_color(30, red_win_fn_2, green_win_fn_2, blue_win_fn_2); // DEL (backspace)

            rgb_matrix_set_color(44, red_win_fn_2, green_win_fn_2, blue_win_fn_2); // Arrow up (U)
            rgb_matrix_set_color(64, red_win_fn_2, green_win_fn_2, blue_win_fn_2); // Arrow right (L)
            rgb_matrix_set_color(63, red_win_fn_2, green_win_fn_2, blue_win_fn_2); // Arrow down (K)
            rgb_matrix_set_color(62, red_win_fn_2, green_win_fn_2, blue_win_fn_2); // Arrow left (J)


            rgb_matrix_set_color(52, red_win_fn_2, green_win_fn_2, blue_win_fn_2); // Arrow up (Numpad 8)
            rgb_matrix_set_color(69, red_win_fn_2, green_win_fn_2, blue_win_fn_2); // Arrow right (Numpad 6)
            rgb_matrix_set_color(70, red_win_fn_2, green_win_fn_2, blue_win_fn_2); // Arrow down (Numpad 5)
            rgb_matrix_set_color(71, red_win_fn_2, green_win_fn_2, blue_win_fn_2); // Arrow left (Numpad 4)

            rgb_matrix_set_color(92, red_win_fn_2, green_win_fn_2, blue_win_fn_2); // backspace (space)

            // rgb_matrix_set_color(14, red_win_fn_2, green_win_fn_2, blue_win_fn_2); // Close Window (Custom key next to knob)

            return true;
        default:
            return false;
    }
}



