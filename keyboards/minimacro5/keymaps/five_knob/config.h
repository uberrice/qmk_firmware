// Copyright 2022 Ryan Neff (@JellyTitan)
// SPDX-License-Identifier: GPL-2.0-or-later

// #pragma once

// /* Turn off RGB light when host is asleep. (Doesn't seem to work for mac)? */
// #define RGBLIGHT_SLEEP
// #define RGBLIGHT_LAYERS

/* The default encoder resolution is 2. Unset and redeclare */
#ifdef ENCODER_RESOLUTION
    #undef ENCODER_RESOLUTION
#endif
#define ENCODER_RESOLUTION 1