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

/* WPM and bongocat need these. */
#define SPLIT_WPM_ENABLE
#define SPLIT_OLED_ENABLE

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

/* Decrease decay of heatmap rgb effect */
#define RGB_MATRIX_TYPING_HEATMAP_DECREASE_DELAY_MS 200

#define RGB_DISABLE_WHEN_USB_SUSPENDED     // turn off effects when suspended
#define SPLIT_TRANSPORT_MIRROR             // If LED_MATRIX_KEYPRESSES or LED_MATRIX_KEYRELEASES is enabled, you also will want to enable SPLIT_TRANSPORT_MIRROR
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 100  // limits maximum brightness of LEDs (max 255). Higher may cause the controller to crash.// #define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_CYCLE_OUT_IN_DUAL
#define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_TYPING_HEATMAP

// Animations
// Uncomment any that you want to try. Lifmited by
// space on the microcontroller. The defines below
// mirror the order they animations will cycle through.
  
// These modes don’t require any additional defines.
// #define ENABLE_RGB_MATRIX_SOLID_COLOR = 1     // Static single hue, no speed support
// #define ENABLE_RGB_MATRIX_ALPHAS_MODS         // Static dual hue, speed is hue for secondary hue
// #define ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN    // Static gradient top to bottom, speed controls how much gradient changes
// #define ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT // Static gradient left to right, speed controls how much gradient changes
// #define ENABLE_RGB_MATRIX_BREATHING           // Single hue brightness cycling animation
// #define ENABLE_RGB_MATRIX_BAND_SAT            // Single hue band fading saturation scrolling left to right
// #define ENABLE_RGB_MATRIX_BAND_VAL            // Single hue band fading brightness scrolling left to right
// #define ENABLE_RGB_MATRIX_BAND_PINWHEEL_SAT   // Single hue 3 blade spinning pinwheel fades saturation
// #define ENABLE_RGB_MATRIX_BAND_PINWHEEL_VAL   // Single hue 3 blade spinning pinwheel fades brightness
// #define ENABLE_RGB_MATRIX_BAND_SPIRAL_SAT     // Single hue spinning spiral fades saturation
// #define ENABLE_RGB_MATRIX_BAND_SPIRAL_VAL     // Single hue spinning spiral fades brightness
// #define ENABLE_RGB_MATRIX_CYCLE_ALL           // Full keyboard solid hue cycling through full gradient
// #define ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT    // Full gradient scrolling left to right
// #define ENABLE_RGB_MATRIX_CYCLE_UP_DOWN       // Full gradient scrolling top to bottom
// #define ENABLE_RGB_MATRIX_CYCLE_OUT_IN        // Full gradient scrolling out to in
// #define ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL      // Full dual gradients scrolling out to in
// #define ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON  // Full gradent Chevron shapped scrolling left to right
// #define ENABLE_RGB_MATRIX_CYCLE_PINWHEEL       // Full gradient spinning pinwheel around center of keyboard
#define ENABLE_RGB_MATRIX_CYCLE_SPIRAL         // Full gradient spinning spiral around center of keyboard
// #define ENABLE_RGB_MATRIX_DUAaaasdasdffasdssdasdfaaaL_BEACON          // Full gradient spinning around center of keyboard
// #define ENABLE_RGB_MATRIX_RAINBOW_BEACON       // Full tighter gradient spinning around center of keyboard
// #define ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS    // Full dual gradients spinning two halfs of keyboard
// #define ENABLE_RGB_MATRIX_RAINDROPS            // Randomly changes a single key's hue
// #define ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS  // Randomly changes a single key's hue and saturation
// #define ENABLE_RGB_MATRIX_HUE_BREATHING        // Hue shifts up a slight ammount at the same time, then shifts back
// #define ENABLE_RGB_MATRIX_HUE_PENDULUM         // Hue shifts up a slight ammount in a wave to the right, then back to the left
// #define ENABLE_RGB_MATRIX_HUE_WAVE             // Hue shifts up a slight ammount and then back down in a wave to the right
// #define ENABLE_RGB_MATRIX_PIXEL_FRACTAL        // Single hue fractal filled keys pulsing horizontally out to edges
// #define ENABLE_RGB_MATRIX_PIXEL_FLOW           // Pulsing RGB flow along LED wiring with random hues
// #define ENABLE_RGB_MATRIX_PIXEL_RAIN           // Randomly light keys with random hues

// These modes require the RGB_MATRIX_FRAMEBUFFER_EFFECTS define
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#define ENABLE_RGB_MATRIX_TYPING_HEATMAP
// #define ENABLE_RGB_MATRIX_DIGITAL_RAIN

// These modes require the RGB_MATRIX_KEYPRESSES or RGB_MATRIX_KEYRELEASES define
// #define RGB_MATRIX_KEYPRESSES
// #define ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE   // Pulses keys hit to hue & value then fades value out
// #define ENABLE_RGB_MATRIX_SOLID_REACTIVE      // Static single hue, pulses keys hit to shifted hue then fades to current hue
// #define ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE       // Hue & value pulse near a single key hit then fades value out
// #define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE  // Hue & value pulse near multiple key hits then fades value out
// #define ENABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS      // Hue & value pulse the same column and row of a single key hit then fades value out
// #define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS // Hue & value pulse the same column and row of multiple key hits then fades value out
// #define ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS      // Hue & value pulse away on the same column and row of a single key hit then fades value out
// #define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS // Hue & value pulse away on the same column and row of multiple key hits then fades value out
// #define ENABLE_RGB_MATRIX_SPLASH,              // Full gradient & value pulse away from a single key hit then fades value out
// #define ENABLE_RGB_MATRIX_MULTISPLASH,         // Full gradient & value pulse away from multiple key hits then fades value out
// #define ENABLE_RGB_MATRIX_SOLID_SPLASH,        // Hue & value pulse away from a single key hit then fades value out
// #define ENABLE_RGB_MATRIX_SOLID_MULTISPLASH,   // Hue & value pulse away from multiple key hits then fades value out

#endif
