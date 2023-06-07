// Copyright 2022 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later

// Pull the actual keymap code so that we can inspect stuff from it
#include KEYMAP_C

// Allow for keymap or userspace rules.mk to specify an alternate location for the keymap array
#ifdef INTROSPECTION_KEYMAP_C
#    include INTROSPECTION_KEYMAP_C
#endif // INTROSPECTION_KEYMAP_C

#include "keymap_introspection.h"

#define NUM_KEYMAP_LAYERS ((uint8_t)(sizeof(keymaps) / ((MATRIX_ROWS) * (MATRIX_COLS) * sizeof(uint16_t))))

uint8_t keymap_layer_count(void) {
    return NUM_KEYMAP_LAYERS;
}

_Static_assert(NUM_KEYMAP_LAYERS <= MAX_LAYER, "Number of keymap layers exceeds maximum set by LAYER_STATE_(8|16|32)BIT");

#if defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)

#    define NUM_ENCODERMAP_LAYERS ((uint8_t)(sizeof(encoder_map) / ((NUM_ENCODERS) * (2) * sizeof(uint16_t))))

uint8_t encodermap_layer_count(void) {
    return NUM_ENCODERMAP_LAYERS;
}

_Static_assert(NUM_KEYMAP_LAYERS == NUM_ENCODERMAP_LAYERS, "Number of encoder_map layers doesn't match the number of keymap layers");

#endif // defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)
