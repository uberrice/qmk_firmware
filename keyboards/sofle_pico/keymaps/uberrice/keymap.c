// Copyright 2022 Ryan Neff (@JellyTitan)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum custom_layers { _QWERTY, _GAMING, _LOWER, _RAISE };

/* Defines macros for use with the configurators "Any" key. (These are non-standard macros using the "Magnet" app on Mac). */
/* Move active application right WSP. */
#define KC_CSGRA LCTL(LSFT(LGUI(KC_RGHT)))
/* Move active application to left WSP. */
#define KC_CSGLA LCTL(LSFT(LGUI(KC_LEFT)))
/* Move active application to right WSP. */
#define KC_WS_RIGHT LCTL(LGUI(KC_RGHT))
#define KC_WS_LEFT LCTL(LGUI(KC_LEFT))

/* Maximize active application. */
#define KC_MAXIM LCTL(LSFT(LGUI(KC_UP)))
/* Minimize active application. */
#define KC_MINIM LCTL(LSFT(LGUI(KC_DOWN)))

enum custom_keycodes {
    QWERTY = SAFE_RANGE,
    LOWER,
    RAISE,
    CMD_TAB_CW,
    CMD_TAB_CCW,
};

/* Rotary encoder variables used to hold down Command (GUI) key while cycling through open programs. */
bool     is_cmd_tab_active = false;
uint16_t cmd_tab_timer     = 0;

/**
 * Tap Dance declarations
 */
enum tapdances {
    _TD_FIVE_ENTER,
};

/* Tapdance */
#define TD5ENT TD(_TD_FIVE_ENTER)

/**
 * Tap Dance definitions
 *
 * To use this in the configurator, enter the name 'TD5ENT' in the "Any" key.
 */
tap_dance_action_t tap_dance_actions[] = {
    /* Tap once for 5, twice for Enter. */
    [_TD_FIVE_ENTER] = ACTION_TAP_DANCE_DOUBLE(KC_5, KC_ENT),
};

// Leader key stuff

void leader_start_user(void) {
// Do something when the leader key is pressed
}

void leader_end_user(void) {
    if (leader_sequence_one_key(KC_F)) {
        // Leader, f => Types the below string
        SEND_STRING("QMK is awesome.");
    } else if (leader_sequence_three_keys(KC_D, KC_D, KC_S)) {
        // Leader, d, d, s => Types the below string
        SEND_STRING("https://start.duckduckgo.com\n");
    } else if (leader_sequence_two_keys(KC_S, KC_S)) {
        // Leader, s, s => GUI+S
        // Take screenshot
        tap_code16(LGUI(LSFT(KC_S)));
    }
}

/**
 * Keymap.
 * The rotary encoders are programmed manually below because the configurator does not support them yet.
 */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // clang-format off
    /*
        QWERTY
        ┌───┬───┬───┬───┬───┬───┐               ┌───┬───┬───┬───┬───┬───┐
        │ = │ 1 │ 2 │ 3 │ 4 │ 5 │               │ 6 │ 7 │ 8 │ 9 │ 0 │ - │
        ├───┼───┼───┼───┼───┼───┤               ├───┼───┼───┼───┼───┼───┤
        │Tab│ Q │ W │ E │ R │ T │               │ Y │ U │ I │ O │ P │Bsp│
        ├───┼───┼───┼───┼───┼───┤               ├───┼───┼───┼───┼───┼───┤
        │CTL│ A │ S │ D │ F │ G │               │ H │ J │ K │ L │ ; │ ' │
        ├───┼───┼───┼───┼───┼───┼───┐       ┌───┼───┼───┼───┼───┼───┼───┤
        │Sft│ Z │ X │ C │ V │ B │Ply│       │LDR│ N │ M │ , │ . │ / │ \ │
        └───┴───┴───┴───┴───┴───┴───┘       └───┴───┴───┴───┴───┴───┴───┘
                ┌───┬───┬───┬───┬───┐       ┌───┬───┬───┬───┬───┐
                │MO3│Win│LAl│Spc│Bsp│       │Ent│RAl│Del│GEs│MO2│ 
                └───┴───┴───┴───┴───┘       └───┴───┴───┴───┴───┘
    */
    [_QWERTY] = LAYOUT(
        KC_EQL,       KC_1,         KC_2,         KC_3,    KC_4,      KC_5,                                         KC_6,   KC_7,         KC_8,     KC_9,         KC_0,            KC_MINS, 
        KC_TAB,       KC_Q,         KC_W,         KC_E,    KC_R,      KC_T,                                         KC_Y,   KC_U,         KC_I,     KC_O,         KC_P,            KC_BACKSPACE, 
        MT(MOD_LCTL, KC_ESC), KC_A,         KC_S,         KC_D,    KC_F,      KC_G,                                         KC_H,   KC_J,         KC_K,     KC_L,         LT(3,KC_SCLN),   LT(2,KC_QUOT), 
        KC_LSFT,      KC_Z,         KC_X,         KC_C,    KC_V,      KC_B,              KC_MPLY,           QK_LEAD,   KC_N,   KC_M,     KC_COMM,  KC_DOT,       RALT_T(KC_SLSH), KC_BSLS, 
                                                TT(3), KC_LGUI,       KC_LALT, KC_SPC,   KC_BACKSPACE,      KC_ENTER,   KC_SPC, KC_DEL,  QK_GESC,  TT(2)
    ),

    /*
        GAMING
        ┌───┬───┬───┬───┬───┬───┐               ┌───┬───┬───┬───┬───┬───┐
        │ = │ 1 │ 2 │ 3 │ 4 │ 5 │               │ 6 │ 7 │ 8 │ 9 │ 0 │ - │
        ├───┼───┼───┼───┼───┼───┤               ├───┼───┼───┼───┼───┼───┤
        │Tab│ Q │ W │ E │ R │ T │               │ Y │ U │ I │ O │ P │Bsp│
        ├───┼───┼───┼───┼───┼───┤               ├───┼───┼───┼───┼───┼───┤
        │CTL│ A │ S │ D │ F │ G │               │ H │ J │ K │ L │ ; │ ' │
        ├───┼───┼───┼───┼───┼───┼───┐       ┌───┼───┼───┼───┼───┼───┼───┤
        │Sft│ Z │ X │ C │ V │ B │Ply│       │LDR│ N │ M │ , │ . │ / │ \ │
        └───┴───┴───┴───┴───┴───┴───┘       └───┴───┴───┴───┴───┴───┴───┘
                ┌───┬───┬───┬───┬───┐       ┌───┬───┬───┬───┬───┐
                │MO2│Win│LAl│Spc│Bsp│       │Ent│RAl│Del│GEs│MO3│ 
                └───┴───┴───┴───┴───┘       └───┴───┴───┴───┴───┘
    */
    [_GAMING] = LAYOUT(
        KC_EQL,       KC_1,         KC_2,         KC_3,    KC_4,      KC_5,                                         KC_6,   KC_7,         KC_8,     KC_9,         KC_0,            KC_MINS, 
        KC_TAB,       KC_Q,         KC_W,         KC_E,    KC_R,      KC_T,                                         KC_Y,   KC_U,         KC_I,     KC_O,         KC_P,            KC_BACKSPACE, 
        KC_LEFT_CTRL, KC_A,         KC_S,         KC_D,    KC_F,      KC_G,                                         KC_H,   KC_J,         KC_K,     KC_L,         LT(3,KC_SCLN),   LT(2,KC_QUOT), 
        KC_LSFT,      KC_Z,         KC_X,         KC_C,    KC_V,      KC_B,              KC_MPLY,           QK_LEAD,   KC_N,   KC_M,     KC_COMM,  KC_DOT,       RALT_T(KC_SLSH), KC_BSLS, 
                                                MO(3), KC_LGUI,       KC_LALT, KC_SPC,   KC_BACKSPACE,      KC_ENTER,   KC_SPC, KC_DEL,  QK_GESC,  MO(2)
    ),

    /*
        Symbols/Numpad Layer
        ┌────┬───┬───┬───┬───┬───┐               ┌───┬───┬───┬───┬───┬────┐
        │BOOT│F1 │F2 │F3 │F4 │F5 │               │F6 │F7 │F8 │F9 │F10│F11 │
        ├────┼───┼───┼───┼───┼───┤               ├───┼───┼───┼───┼───┼────┤
        │____│ ! │ @ │ { │ } │ | │               │QMK│ 7 │ 8 │ 9 │ * │F12 │
        ├────┼───┼───┼───┼───┼───┤               ├───┼───┼───┼───┼───┼────┤
        │____│ # │ $ │ ( │ ) │ ` │               │QMK│ 4 │ 5 │ 6 │ + │____│
        ├────┼───┼───┼───┼───┼───┼───┐       ┌───┼───┼───┼───┼───┼───┼────┤
        │____│ ` │ $ │ [ │ ] │ ~ │___│       │___│QMK│ 1 │ 2 │ 3 │ / │BOOT│
        └────┴───┴───┴───┴───┴───┴───┘       └───┴───┴───┴───┴───┴───┴────┘
                ┌───┬───┬───┬───┬───┐       ┌───┬───┬───┬───┬───┐
                │___│___│___│___│___│       │ 0 │ 0 │ 0 │ 0 │___│
                └───┴───┴───┴───┴───┘       └───┴───┴───┴───┴───┘
    */

    [_LOWER] = LAYOUT(
        QK_BOOT, KC_F1,    KC_F2,   KC_F3,   KC_F4,   KC_F5,                                   KC_F6,   KC_F7, KC_F8, KC_F9, KC_F10,  KC_F11, 
        KC_TRNS, KC_EXLM,  KC_AT,   KC_LCBR, KC_RCBR, KC_PIPE,                                 DT_PRNT, KC_7,  KC_8,  KC_9,  KC_ASTR, KC_F12, 
        KC_TRNS, KC_HASH,  KC_DLR,  KC_LPRN, KC_RPRN, KC_GRV,                                  DT_UP,   KC_4,  KC_5,  KC_6,  KC_PPLS, KC_TRNS, 
        KC_TRNS, KC_GRAVE, KC_DLR,  KC_LBRC, KC_RBRC, KC_TILD,       KC_TRNS,  KC_TRNS,        DT_DOWN, KC_1,  KC_2,  KC_3,  KC_PSLS, QK_BOOT, 
                                    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_P0,   KC_P0, KC_P0,   KC_P0, KC_TRNS
    ),

    /*
        Navigation/Function Layer
        ┌────┬────┬────┬────┬────┬────┐               ┌────┬────┬────┬────┬────┬────┐
        │RGB │ACL0│ACL1│ACL2│____│____│               │____│____│MOD │RMOD│HUI │HUD │
        ├────┼────┼────┼────┼────┼────┤               ├────┼────┼────┼────┼────┼────┤
        │TG1_│____│____│MS_U│____│____│               │____│BTN1│ ↑  │BTN2│SAI │SAD │
        ├────┼────┼────┼────┼────┼────┤               ├────┼────┼────┼────┼────┼────┤
        │____│____│MS_L│MS_D│MS_R│____│               │____│ ←  │ ↓  │ →  │VAI │VAD │
        ├────┼────┼────┼────┼────┼────┼────┐     ┌────┼────┼────┼────┼────┼────┼────┤
        │____│____│____│____│____│____│____│     │____│____│PGUP│____│PGDN│SPI │SPD │
        └────┴────┴────┴────┴────┴────┴────┘     └────┴────┴────┴────┴────┴────┴────┘
                    ┌───┬───┬───┬───┬───┐       ┌───┬───┬───┬───┬───┐
                    │___│___│___│___│QMK│       │QMK│___│___│___│___│
                    └───┴───┴───┴───┴───┘       └───┴───┴───┴───┴───┘
    */ 
    [_RAISE] = LAYOUT(
        RGB_TOG, KC_ACL0, KC_ACL1, KC_ACL2, KC_TRNS, KC_TRNS,                                      KC_TRNS, KC_TRNS, RGB_MOD, RGB_RMOD, RGB_HUI, RGB_HUD, 
        TG(1), KC_TRNS, KC_TRNS, KC_MS_U, KC_TRNS, KC_TRNS,                                      KC_TRNS, KC_BTN1, KC_UP,   KC_BTN2,  RGB_SAI, RGB_SAD, 
        KC_TRNS, KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_R, KC_TRNS,                                      KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT,  RGB_VAI, RGB_VAD, 
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS,    KC_TRNS,        KC_TRNS, KC_PGUP, KC_TRNS, KC_PGDN,  RGB_SPI, RGB_SPD, 
                                    KC_TRNS, KC_TRNS, KC_TRNS, KC_WS_LEFT, KC_CSGLA,   KC_CSGRA, KC_WS_RIGHT, KC_TRNS, KC_TRNS, KC_TRNS)
    // clang-format on
};

uint8_t mod_state;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    mod_state = get_mods();

    switch (keycode) {
        case QWERTY:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_QWERTY);
            }
            return false;
        case CMD_TAB_CW:
            if (record->event.pressed) {
                if (!is_cmd_tab_active) {
                    is_cmd_tab_active = true;
                    register_code(KC_LALT);
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
                    register_code(KC_LALT);
                }
                cmd_tab_timer = timer_read();
                tap_code16(S(KC_TAB));
            } else {
                unregister_code(KC_TAB);
            }
            break;
        case KC_BSPC: // if shift is pressed, bspc becomes del
        {
            // Initialize a boolean variable that keeps track
            // of the delete key status: registered or not?
            static bool delkey_registered;
            if (record->event.pressed) {
                // Detect the activation of either shift keys
                if (mod_state & MOD_MASK_SHIFT) {
                    // First temporarily canceling both shifts so that
                    // shift isn't applied to the KC_DEL keycode
                    del_mods(MOD_MASK_SHIFT);
                    register_code(KC_DEL);
                    // Update the boolean variable to reflect the status of KC_DEL
                    delkey_registered = true;
                    // Reapplying modifier state so that the held shift key(s)
                    // still work even after having tapped the Backspace/Delete key.
                    set_mods(mod_state);
                    return false;
                }
            } else { // on release of KC_BSPC
                // In case KC_DEL is still being sent even after the release of KC_BSPC
                if (delkey_registered) {
                    unregister_code(KC_DEL);
                    delkey_registered = false;
                    return false;
                }
        }
    // Let QMK process the KC_BSPC keycode as usual outside of shift
    return true;
}
    }
    return true;
}

/**
 * Helper function for rotary encoder.
 *
 * If the timer has elapsed, the Command/Gui tab will be released.
 * You can adjust the milliseconds to speed up the CMD key release.
 */
void matrix_scan_user(void) {
    if (is_cmd_tab_active) {
        if (timer_elapsed(cmd_tab_timer) > 900) {
            unregister_code(KC_LALT);
            is_cmd_tab_active = false;
        }
    }
}

/**
 * Rotary Encoder.
 *
 * This can't be programmed through configurator. You must do it here.
 *
 * This uses the amazing "Encoder map" feature which replicates the normal keyswitch layer handling functionality, but with encoders.
 * https://docs.qmk.fm/#/feature_encoders?id=encoder-map
 *
 * Changed to do alt-tab because no mac
 */
#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    /* Left Hand */                             /* Right Hand */
    /* Switch between tabs. (Control + Tab). */ /* Switch between open apps on Mac. (Command + Tab + timer logic) */
    [_QWERTY] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(CMD_TAB_CW, CMD_TAB_CCW)},
    /* Scrolls left & right. (Shift + Mouse Wheel Up). */ /* Scrolls up and down. (Page Down & Page Up - mouse wheel scroll incraments are too small) */
    [_LOWER] = {ENCODER_CCW_CW(S(KC_MS_WH_UP), S(KC_MS_WH_DOWN)), ENCODER_CCW_CW(KC_PGDN, KC_PGUP)},
    /* Selects adjacent words. (Command + Shift + Right Arrow). */ /* Jumps to end/start of line. Hold shift to select. (Gui + arrow). */
    [_RAISE] = {ENCODER_CCW_CW(C(S(KC_LEFT)), C(S(KC_RGHT))), ENCODER_CCW_CW(G(KC_LEFT), G(KC_RGHT))}
};
#endif

// Default timeout for displaying logo on boot.
#ifndef OLED_LOGO_TIMEOUT
    #define OLED_LOGO_TIMEOUT 5000
#endif

#ifdef OLED_ENABLE

uint16_t startup_timer; 

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    startup_timer = timer_read();

    if (is_keyboard_master()) {
        if(is_keyboard_left()){
        return OLED_ROTATION_90;
        }
        else {
            return OLED_ROTATION_270;
        }
        } else {
            return OLED_ROTATION_90;
        }
}
static void render_qmk_logo(void) {
    static const char PROGMEM qmk_logo[] = {
        0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
        0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
        0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0
    };

    oled_write_P(qmk_logo, false);
}
static void render_logo(void) {
    // @todo - should we split this into a seperate file? kb16 has a good example.
    static const char PROGMEM sofle_pico_logo[] = { 
        // 'sofle-pico-vector-logo-v3bw', 64x128px
        0x00, 0x00, 0xf8, 0xfc, 0xdc, 0x8e, 0x0e, 0x0e, 0x1c, 0x1c, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xfe, 0xfe, 0x87, 0x03, 0x03, 
        0x9f, 0xfe, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x60, 0xe0, 0xe1, 0x83, 0x03, 0x07, 0x87, 0xce, 0xfe, 0xfc, 0x00, 0x00, 0x38, 0xfe, 0xff, 
        0x87, 0x03, 0x03, 0x03, 0x83, 0xef, 0xfe, 0xfc, 0x00, 0x00, 0xff, 0xff, 0xff, 0x03, 0x03, 0x03, 
        0x07, 0xff, 0xff, 0x00, 0x00, 0x30, 0xfe, 0xff, 0xbf, 0x1b, 0x1b, 0x1b, 0x9f, 0xff, 0x9e, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0xe1, 0xe3, 0x63, 0x63, 0x63, 0xe3, 0xe3, 0xc1, 0x80, 0x00, 0x40, 0xe0, 0xe0, 0x41, 
        0x03, 0x03, 0x03, 0x03, 0x03, 0x01, 0x01, 0x00, 0x00, 0x00, 0x01, 0x03, 0x03, 0x00, 0x00, 0x00, 
        0x00, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x03, 0x03, 0x03, 0x03, 0x01, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0xff, 0xff, 0x70, 0x70, 0x30, 0x38, 0x3f, 0x1f, 0x0f, 0x00, 0x00, 0xf8, 0xf8, 0x00, 
        0x00, 0x00, 0xe0, 0xf0, 0x38, 0x1c, 0x1c, 0x1c, 0x1c, 0x38, 0x00, 0x00, 0xe0, 0xf0, 0x78, 0x18, 
        0x1c, 0x1c, 0x1c, 0x38, 0xf8, 0xf0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x1f, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x1f, 0x00, 
        0x00, 0x00, 0x07, 0x0f, 0x1e, 0x1c, 0x18, 0x18, 0x1c, 0x1c, 0x00, 0x00, 0x07, 0x0f, 0x1e, 0x1c, 
        0x18, 0x18, 0x18, 0x1c, 0x0f, 0x07, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0xe0, 0xf0, 0xf0, 0xf0, 0x78, 0x38, 0x38, 0x38, 0x1c, 0x3c, 0x1c, 0x1c, 0x1c, 0x38, 0x38, 
        0x38, 0x38, 0x78, 0x70, 0xf0, 0xe0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xe0, 0xf0, 0x78, 0x38, 0x3c, 0x1c, 0x1c, 0x1c, 
        0x1c, 0x0e, 0x0e, 0x0e, 0x1e, 0x0e, 0x1c, 0x1c, 0x1c, 0x38, 0xb8, 0xf8, 0xf8, 0xf0, 0x00, 0x00, 
        0x00, 0x03, 0x3f, 0x7f, 0xff, 0xf0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x02, 0x04, 0x04, 0x08, 0x18, 
        0x10, 0x30, 0x60, 0xc0, 0xc0, 0xc1, 0xff, 0x7f, 0x3e, 0x80, 0x80, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 
        0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0x80, 0x9e, 0xbf, 0x7f, 0xf1, 0xe0, 0xe0, 0x30, 0x10, 0x08, 0x0c, 
        0x04, 0x02, 0x02, 0x00, 0x01, 0x00, 0x00, 0x80, 0xe0, 0xf8, 0xfe, 0x7f, 0x1f, 0x03, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x07, 0x07, 0x0e, 0x1e, 0x1c, 0x3c, 0x38, 0x38, 0x38, 0x38, 
        0x18, 0x9c, 0xce, 0xef, 0xff, 0xfd, 0xfe, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xf8, 0xfc, 
        0x3f, 0x1f, 0x1f, 0x1f, 0x3f, 0x7f, 0xff, 0xe0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xf0, 0xfe, 0x3f, 0x1f, 0x0f, 0x0f, 0x1f, 0x3f, 
        0xfc, 0xf8, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x3f, 0x7d, 
        0xf0, 0xc0, 0xc0, 0x80, 0x80, 0xc0, 0xfb, 0xff, 0x3f, 0x3f, 0x1f, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 
        0x0e, 0x0e, 0x0e, 0x0e, 0x1f, 0x1f, 0x3f, 0x3f, 0x7f, 0xff, 0xc0, 0xc0, 0xc0, 0xc0, 0xe0, 0xf0, 
        0x7f, 0x3f, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x01, 0x03, 0x03, 0x07, 0x0f, 0x1f, 0x3e, 0x38, 0x70, 0x60, 0xe0, 0xe0, 0xc0, 0xc0, 0xc0, 
        0xc0, 0xc0, 0xc0, 0xc0, 0xe0, 0xe0, 0x70, 0x78, 0x3c, 0x3f, 0x1f, 0x0f, 0x07, 0x03, 0x01, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xc0, 0x80, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x1c, 0x38, 0x0e, 0x00, 0x11, 0x30, 0x26, 0x3f, 0x19, 
        0x00, 0x20, 0x20, 0x00, 0x1f, 0x30, 0x20, 0x31, 0x1f, 0x10, 0x18, 0x1e, 0x1b, 0x3f, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0xd8, 0xfc, 0x6c, 0xfc, 0xd8, 0x00, 0x80, 0x80, 0x18, 0x0c, 0xcc, 0x78, 0x10, 0x00, 
        0x80, 0xe0, 0xf0, 0xf8, 0x80, 0x80, 0x80, 0x00, 0x18, 0x8c, 0xcc, 0x78, 0x10, 0x00, 0xf8, 0x0c, 
        0x0c, 0x98, 0xf0, 0x00, 0x18, 0x8c, 0xcc, 0x78, 0x00, 0x00, 0x18, 0x0c, 0x6c, 0xf8, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 
        0x00, 0x00, 0x01, 0x03, 0x02, 0xc3, 0xc1, 0x00, 0x00, 0xc0, 0x02, 0x03, 0x03, 0x02, 0x02, 0x00, 
        0x01, 0xc1, 0x01, 0xc3, 0x01, 0x00, 0x00, 0x00, 0x03, 0x03, 0xc3, 0xc2, 0xc0, 0xc0, 0xc1, 0x83, 
        0x83, 0x03, 0x80, 0x00, 0x03, 0x03, 0x03, 0x02, 0x00, 0x00, 0x03, 0x03, 0x03, 0x01, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0xfe, 0xa2, 0xb2, 0xfe, 0x00, 0x3f, 0x07, 0x02, 
        0x3e, 0x00, 0xe0, 0x38, 0x0e, 0x01, 0x00, 0x20, 0x30, 0x1f, 0x00, 0x1c, 0x3e, 0x3a, 0x3e, 0x1c, 
        0x1f, 0x3f, 0x00, 0x3f, 0x00, 0x82, 0xce, 0x38, 0x0c, 0x06, 0x00, 0x00, 0x3f, 0x00, 0x00, 0x00, 
        0x3e, 0x00, 0x3f, 0x02, 0x08, 0x3e, 0x22, 0x32, 0x3e, 0x00, 0x3e, 0x1e, 0x02, 0x3e, 0x00, 0x00
    };
    oled_write_raw_P(sofle_pico_logo, sizeof(sofle_pico_logo));
}

static void render_status(void) {
    oled_write_P(PSTR("Sofle Pico\nv3.5\n~~~~~~~~~\nrev.\nuberrice\n"), false);
    uint8_t n = get_current_wpm();
    char    wpm_counter[4];
    wpm_counter[3] = '\0';
    wpm_counter[2] = '0' + n % 10;
    wpm_counter[1] = (n /= 10) % 10 ? '0' + (n) % 10 : (n / 10) % 10 ? '0' : ' ';
    wpm_counter[0] = n / 10 ? '0' + n / 10 : ' ';
    oled_write_P(PSTR("WPM:"), false);
    oled_write(wpm_counter, false);
    led_t led_state = host_keyboard_led_state();
    oled_write_P(PSTR("\nCaps: "), false);
    oled_write_P(led_state.caps_lock ? PSTR("on ") : PSTR("off"), false);
    oled_write_P(PSTR("\n"), false);
    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            oled_write_P(PSTR("QWERTY    "), false);
            break;
        case _GAMING:
            oled_write_P(PSTR("Gaming    "), false);
            break;
        case _LOWER:
            oled_write_P(PSTR("Nums+Syms "), false);
            break;
        case _RAISE:
            oled_write_P(PSTR("Navigation"), false);
            break;
        default:
            oled_write_P(PSTR("Unknown   "), false);
            break;
    }
}

bool oled_task_user(void) {
    static bool finished_logo = false;
    if ((timer_elapsed(startup_timer) < OLED_LOGO_TIMEOUT) && !finished_logo) {
        // Display the logo for 5 seconds on boot.
        if (is_keyboard_master()) {
            render_logo();
        } else {
            render_qmk_logo();
        }
    } else {
        // Display the current keyboard state.
        if (!finished_logo) {
            // Clears the OLED.
            oled_clear();
        } else {
            finished_logo = true;
        }
        if (is_keyboard_master()) {
            render_status(); // Renders the current keyboard state (layer, lock, caps, scroll, etc)
        } else {
            render_logo();
        }
        return false;
    }
    return true;
}

#endif