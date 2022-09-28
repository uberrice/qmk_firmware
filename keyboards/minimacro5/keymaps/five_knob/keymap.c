// Copyright 2022 Ryan Neff (@JellyTitan)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum layers {
    _MAIN,
};

/* Defines macros for use with the configurators "Any" key. (These are non-standard macros - you'll need to make your own). */
/* Move active application right half. */
#define KC_CSGRA LCTL(LSFT(LGUI(KC_RGHT)))
/* Move active application to left half. */
#define KC_CSGLA LCTL(LSFT(LGUI(KC_LEFT)))
/* Maximize active application. */
#define KC_MAXIM LCTL(LSFT(LGUI(KC_UP)))
/* Minimize active application. */
#define KC_MINIM LCTL(LSFT(LGUI(KC_DOWN)))
/* Lock the mac. */
#define KC_MACLOCK LCTL(LGUI(KC_Q)))

/* Rotary encoder variables used to hold down Command (GUI) key while cycling through open programs. */
bool     is_cmd_tab_active = false;
uint16_t cmd_tab_timer     = 0;

enum custom_keycodes {
    CMD_TAB_CW,
    CMD_TAB_CCW,
};

/**
 * @brief Button assignement.
 * 
 * I've left most of these unassinged because clicking the encoders is awkward.
 * 
 */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = { // buttion closest to usb is first
    /* Right hand */
    [_MAIN] = LAYOUT_ortho_1x5(KC_RGHT, KC_NO, KC_NO, KC_NO, RGB_TOG)
    /* Left hand */
    // [_MAIN] = LAYOUT_ortho_1x5(KC_ENT, KC_NO, KC_NO, KC_NO, KC_MACLOCK);
};
   

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case CMD_TAB_CW:
            if (record->event.pressed) {
                if (!is_cmd_tab_active) {
                    is_cmd_tab_active = true;
                    register_code(KC_LGUI);
                }
                cmd_tab_timer = timer_read();
                register_code(KC_TAB);
            } else {
                unregister_code(KC_TAB);
            }
            break;
        case CMD_TAB_CCW:
            if (record->event.pressed) {
                if (!is_cmd_tab_active) {
                    is_cmd_tab_active = true;
                    register_code(KC_LGUI);
                }
                cmd_tab_timer = timer_read();
                tap_code16(S(KC_TAB));
            } else {
                unregister_code(KC_TAB);
            }
            break;
    }
    return true;
}

/**
 * Rotary Encoder.
 *
 * This can't be programmed through configurator. You must do it here.
 *
 * This uses the amazing "Encoder map" feature which replicates the normal keyswitch layer handling functionality, but with encoders.
 * https://docs.qmk.fm/#/feature_encoders?id=encoder-map
 *
 * Uses a variant of the Super-alt-tab macro to switch between open applications on a mac. (Command-tab)
 * https://docs.qmk.fm/#/feature_macros?id=super-alt%e2%86%aftab
 */
#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [_MAIN] =
        {   
            /* Right hand */
            /* Switch between open apps on Mac. (Command + Tab + timer logic) */
            ENCODER_CCW_CW(CMD_TAB_CCW, CMD_TAB_CW),
            /* Move active application to left/righ half. (Uses custom config in Mac "Magnet" app.) */
            ENCODER_CCW_CW(KC_CSGRA, KC_CSGLA),
            /* Scrolls up and down. (Page Down & Page Up - mouse wheel scroll incraments are too small) */
            ENCODER_CCW_CW(KC_PGDN, KC_PGUP),
            /* Right & left arrow */
            ENCODER_CCW_CW(KC_LEFT, KC_RGHT),
            // /* Jumps to end/start of line. (Gui + arrow). */
            // ENCODER_CCW_CW(G(KC_LEFT), G(KC_RGHT)),
            /* Selects to end/start of line. (Gui + Shift + arrow). */
            ENCODER_CCW_CW(G(S(KC_LEFT)), G(S(KC_RGHT))),
            },
        // {
        //     /* Left hand */
        //     /* Switch between tabs. (Control + Tab). */
        //     ENCODER_CCW_CW(S(C(KC_TAB)), C(KC_TAB)),
        //     /* Maximize/minimize active application. (Uses custom config in Mac "Magnet" app.) */
        //     ENCODER_CCW_CW(S(C(KC_MAXIM)), C(KC_MINIM)),
        //     /* Scrolls left & right. (Shift + Mouse Wheel Up). */
        //     ENCODER_CCW_CW(S(KC_MS_WH_UP), S(KC_MS_WH_DOWN)),
        //     /* Up & down arrow */
        //     ENCODER_CCW_CW(KC_UP, KC_DOWN),
        //     // /* Jumps to end/start of words. (Alt + Shift + Right Arrow). */
        //     // ENCODER_CCW_CW(A(KC_LEFT), A(KC_RGHT)),
        //     /* Selects adjacent words. (Alt + Shift + Right Arrow). */
        //     ENCODER_CCW_CW(A(S(KC_LEFT)), A(S(KC_RGHT))),
        // },
};
#endif

/**
 * Helper function for rotary encoder.
 *
 * If the timer has elapsed, the Command/Gui tab will be released.
 * You can adjust the milliseconds to speed up the CMD key release.
 */
void matrix_scan_user(void) {
    if (is_cmd_tab_active) {
        if (timer_elapsed(cmd_tab_timer) > 900) {
            unregister_code(KC_LGUI);
            is_cmd_tab_active = false;
        }
    }
}
