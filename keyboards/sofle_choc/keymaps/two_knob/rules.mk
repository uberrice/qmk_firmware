# Copyright 2022 Ryan Neff (@JellyTitan)
# SPDX-License-Identifier: GPL-2.0-or-later

# Turn on rotary encoders:
ENCODER_ENABLE = yes

# Replicates the normal keyswitch layer handling functionality, but with encoders:
ENCODER_MAP_ENABLE = yes

# Turn on Oleds
OLED_ENABLE = yes
# WPM for oled bongo cat: 
WPM_ENABLE = yes

# Enable per-key lighting
RGB_MATRIX_ENABLE = yes

# Enable audio keys and system control
EXTRAKEY_ENABLE = no

# Enable link time optimization
# Trade longer compile time for smaller firmware size
LTO_ENABLE = yes

# Change keymaps without flashing
# https://caniusevia.com/
# Had to switch this off to make build size smaller.
VIA_ENABLE = no

# Turn on mouse:
MOUSEKEY_ENABLE = yes

# Turn on tap dance:
TAP_DANCE_ENABLE = yes

# Dynamic Tapping Term:
DYNAMIC_TAPPING_TERM_ENABLE = no

# Trim off some features to free up space.
SPACE_CADET_ENABLE = no
GRAVE_ESC_ENABLE = no 
MAGIC_ENABLE = no
MUSIC_ENABLE = no
VERBOSE = no
CONSOLE_ENABLE = no
COMMAND_ENABLE = no