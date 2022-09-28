// Copyright 2022 Ryan Neff (@JellyTitan)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* Turn off RGB light when host is asleep. */
#define RGBLIGHT_SLEEP

/* The default encoder resolution is 2. Unset and redeclare. */
#ifdef ENCODER_RESOLUTION
    #undef ENCODER_RESOLUTION
#endif
#define ENCODER_RESOLUTION 4

/* Number of LEDs. Unset and redeclare. */
#ifdef RGBLED_NUM
    #undef RGBLED_NUM
#endif
#define RGBLED_NUM 3 