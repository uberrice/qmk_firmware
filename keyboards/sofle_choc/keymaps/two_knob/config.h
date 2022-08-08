// Copyright 2022 Ryan Neff (@JellyTitan)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// Plug USB into the left half of the keyboard
// see https://docs.qmk.fm/#/feature_split_keyboard?id=setting-handedness
#define MASTER_LEFT

// Enabling this option changes the startup behavior to listen for an
// active USB communication to delegate which part is master and which
// is slave. With this option enabled and theres’s USB communication,
// then that half assumes it is the master, otherwise it assumes it
// is the slave.
//
// I've found this helps with some ProMicros where the slave does not boot
#define SPLIT_USB_DETECT

/* If you type too fast, it confuses the Mod key combos. This resolves it: */
#define IGNORE_MOD_TAP_INTERRUPT

/* Set tapdance speed */
// @todo - turn this back on when it's removed from the default settings. (Awaitng pull request)
#define TAPPING_TERM 210

/* Clear out the default encoder resolution, effectively setting it to "1" */
#ifdef ENCODER_RESOLUTION
    #undef ENCODER_RESOLUTION
#endif

/* Allows for the setting of constant mouse speed levels. */
/* Delay between pressing a movement key and cursor movement */
#define MOUSEKEY_DELAY 10
/* Time between cursor movements in milliseconds */
#define MOUSEKEY_INTERVAL 16
/* Step size */
#define MOUSEKEY_MOVE_DELTA 8
/* Maximum cursor speed at which acceleration stops */
#define MOUSEKEY_MAX_SPEED 2
/* Time until maximum cursor speed is reached */
#define MOUSEKEY_TIME_TO_MAX 40
/* Maximum number of scroll steps per scroll action */
#define MOUSEKEY_WHEEL_MAX_SPEED 42
/* Time until maximum scroll speed is reached */
#define MOUSEKEY_WHEEL_TIME_TO_MAX 15

// Tweak how the mouse cursor moves. https://docs.qmk.fm/#/feature_mouse_keys
// Accelerated mode (default).
// MOUSEKEY_DELAY  10  Delady between pressing a movement key and cursor movement
// MOUSEKEY_INTERVAL 20  Time between cursor movements in milliseconds
// MOUSEKEY_MOVE_DELTA 8 Step size
// MOUSEKEY_MAX_SPEED  10  Maximum cursor speed at which acceleration stops
// MOUSEKEY_TIME_TO_MAX  30  Time until maximum cursor speed is reached
// MOUSEKEY_WHEEL_DELAY  10  Delay between pressing a wheel key and wheel movement
// MOUSEKEY_WHEEL_INTERVAL 80  Time between wheel movements
// MOUSEKEY_WHEEL_MAX_SPEED  8 Maximum number of scroll steps per scroll action
// MOUSEKEY_WHEEL_TIME_TO_MAX  40  Time until maximum scroll speed is reached

// Kinetic mode, alternate to the default mode.
// MK_KINETIC_SPEED  undefined Enable kinetic mode
// MOUSEKEY_DELAY  5 Delay between pressing a movement key and cursor movement
// MOUSEKEY_INTERVAL 10  Time between cursor movements in milliseconds
// MOUSEKEY_MOVE_DELTA 5 Step size for accelerating from initial to base speed
// MOUSEKEY_INITIAL_SPEED  100 Initial speed of the cursor in pixel per second
// MOUSEKEY_BASE_SPEED 1000  Maximum cursor speed at which acceleration stops
// MOUSEKEY_DECELERATED_SPEED  400 Decelerated cursor speed
// MOUSEKEY_ACCELERATED_SPEED  3000  Accelerated cursor speed
// MOUSEKEY_WHEEL_INITIAL_MOVEMENTS  16  Initial number of movements of the mouse wheel
// MOUSEKEY_WHEEL_BASE_MOVEMENTS 32  Maximum number of movements at which acceleration stops
// MOUSEKEY_WHEEL_ACCELERATED_MOVEMENTS  48  Accelerated wheel movements
// MOUSEKEY_WHEEL_DECELERATED_MOVEMENTS  8 Decelerated wheel movements



#ifdef RGB_MATRIX_ENABLE

/* Turn off RGB light when host is asleep. (Doesn't seem to work for mac)? */
/* @todo - this seems to be a duplicate of RGB_DISABLE_WHEN_USB_SUSPENDED */
#define RGBLIGHT_SLEEP
#define RGBLIGHT_LAYERS
/* Decrease decay of heatmap rgb effect */
#define RGB_MATRIX_TYPING_HEATMAP_DECREASE_DELAY_MS 50
/* If you're setting colors per key, this is required. */
#define SPLIT_LAYER_STATE_ENABLE

#define RGB_DISABLE_WHEN_USB_SUSPENDED     // turn off effects when suspended
#define SPLIT_TRANSPORT_MIRROR             // If LED_MATRIX_KEYPRESSES or LED_MATRIX_KEYRELEASES is enabled, you also will want to enable SPLIT_TRANSPORT_MIRROR
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 100  // limits maximum brightness of LEDs (max 255). Higher may cause the controller to crash.
#define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_CYCLE_OUT_IN_DUAL

// Animations
// Uncomment any that you want to try. Lifmited by
// space on the microcontroller. The defines below
// mirror the order they animations will cycle through.

// These modes don’t require any additional defines
// #define ENABLE_RGB_MATRIX_ALPHAS_MODS
// #define ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN
// #define ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT
#define ENABLE_RGB_MATRIX_BREATHING
// #define ENABLE_RGB_MATRIX_BAND_SAT
// #define ENABLE_RGB_MATRIX_BAND_VAL
// #define ENABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
// #define ENABLE_RGB_MATRIX_BAND_PINWHEEL_VAL
// #define ENABLE_RGB_MATRIX_BAND_SPIRAL_SAT
// #define ENABLE_RGB_MATRIX_BAND_SPIRAL_VAL
// #define ENABLE_RGB_MATRIX_CYCLE_ALL
// #define ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
// #define ENABLE_RGB_MATRIX_CYCLE_UP_DOWN
#define ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
// #define ENABLE_RGB_MATRIX_CYCLE_OUT_IN
#define ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
// #define ENABLE_RGB_MATRIX_CYCLE_PINWHEEL
// #define ENABLE_RGB_MATRIX_CYCLE_SPIRAL
#define ENABLE_RGB_MATRIX_DUAL_BEACON
// #define ENABLE_RGB_MATRIX_RAINBOW_BEACON
// #define ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS
// #define ENABLE_RGB_MATRIX_RAINDROPS
// #define ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
// #define ENABLE_RGB_MATRIX_HUE_BREATHING
// #define ENABLE_RGB_MATRIX_HUE_PENDULUM
// #define ENABLE_RGB_MATRIX_HUE_WAVE
#define ENABLE_RGB_MATRIX_PIXEL_FRACTAL
// #define ENABLE_RGB_MATRIX_PIXEL_FLOW
// #define ENABLE_RGB_MATRIX_PIXEL_RAIN

// These modes require the RGB_MATRIX_FRAMEBUFFER_EFFECTS define
// #define RGB_MATRIX_FRAMEBUFFER_EFFECTS
// #define ENABLE_RGB_MATRIX_TYPING_HEATMAP
// #define ENABLE_RGB_MATRIX_DIGITAL_RAIN

// These modes require the RGB_MATRIX_KEYPRESSES or RGB_MATRIX_KEYRELEASES define
// #define RGB_MATRIX_KEYPRESSES
// #define RGB_MATRIX_KEYRELEASES
// #define ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
// #define ENABLE_RGB_MATRIX_SOLID_REACTIVE
// #define ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
// #define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
// #define ENABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
// #define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS
// #define ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
// #define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
// #define ENABLE_RGB_MATRIX_SPLASH
// #define ENABLE_RGB_MATRIX_MULTISPLASH
// #define ENABLE_RGB_MATRIX_SOLID_SPLASH
// #define ENABLE_RGB_MATRIX_SOLID_MULTISPLASH

#endif
