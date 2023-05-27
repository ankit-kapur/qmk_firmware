/* Copyright 2021 Glorious, LLC <salman@pcgamingrace.com>
 * Modified 2022 by rustedaperture for qmk_firmware

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include "analog.h"
#include "joystick.h"


// Tap Dance declarations
enum {
    TD_NUM_CALC = 0,
    TD_SLS_LPRN,
    TD_AST_RPRN,
    TD_MNS_ESC,
    TD_PLS_DEL
};

// Tap Dance definitions
tap_dance_action_t tap_dance_actions[] = {
    // Tap once for 'NUMS LOCK Toggle', twice for 'Calculator'
    [TD_NUM_CALC] = ACTION_TAP_DANCE_DOUBLE(KC_NUM, KC_CALC),

    // Tap once for '/', twice for '('
    [TD_SLS_LPRN] = ACTION_TAP_DANCE_DOUBLE(KC_PSLS, KC_LPRN),

    // Tap once for '*', twice for ')'
    [TD_AST_RPRN] = ACTION_TAP_DANCE_DOUBLE(KC_PAST, KC_RPRN),

    // Tap once for '-', twice for 'Escape' (used to Clear All in Calculator)
    [TD_MNS_ESC] = ACTION_TAP_DANCE_DOUBLE(KC_PMNS, KC_ESC),

    // Tap once for '+', twice for 'Delete' (used to Clear Entry in Calculator)
    [TD_PLS_DEL] = ACTION_TAP_DANCE_DOUBLE(KC_PPLS, KC_DEL)
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

//      NUM or CALC      / or (       * or )      - or C
//      7                8            9           + or CE
//      4                5            6           Encoder button as MO Switch
//      1                2            3           Enter
//      0                                         .

  [0] = LAYOUT(
    TD(TD_NUM_CALC),   TD(TD_SLS_LPRN),   TD(TD_AST_RPRN),   TD(TD_MNS_ESC),
    KC_P7,             KC_P8,             KC_P9,             TD(TD_PLS_DEL),
    KC_P4,             KC_P5,             KC_P6,             MO(1),
    KC_P1,             KC_P2,             KC_P3,             KC_PENT,
    KC_P0,                                                   KC_PDOT
  ),

//  SYS_POWEROFF  MEDIA_PREV   MEDIA_NEXT   MEDIA_PLAY_PAUSE
//  RGB_HUE+      RGB_BRIGHT+  RGB_SAT+     MEDIA_STOP
//  <RGB_MODE     RGB_TOGGLE   RGB_MODE>    ____________
//  RGB_HUE-      RGB_BRIGHT-  RGB_SAT-     MEDIA_PLAYER
//  SYS_SLEEP                               KBD_BOOTLD_MODE

  [1] = LAYOUT(
    KC_PWR,   KC_MPRV,   KC_MNXT,   KC_MPLY,
    RGB_HUI,  RGB_VAI,   RGB_SAI,   KC_MSTP,
    RGB_RMOD, RGB_TOG,   RGB_MOD,   _______,
    RGB_HUD,  RGB_VAD,   RGB_SAD,   KC_MSEL,
    KC_SLEP,                        QK_BOOT
  )
};

// Slider as joystick
joystick_config_t joystick_axes[JOYSTICK_AXIS_COUNT] = {
    JOYSTICK_AXIS_VIRTUAL,
};

// NOTE: For rescale parameter 0x7C, minimum and maximum values for 'slider_value' are -115 and 119 respectively.
// We let calibration software on the host to rescale them perfectly to [-127, 127].
#define RESCALE_PARAM		0x7C
int8_t slider_reading;
uint8_t divisor = 0;

void slider(void) {
    if (divisor++) { /* only run the slider function 1/256 times it's called */
        return;
    }

    // We maintain a rolling average to reduce jitter
    slider_reading = (slider_reading >> 1) + (int8_t)(analogReadPin(SLIDER_PIN) >> 4);

    int8_t slider_value = ((RESCALE_PARAM - slider_reading) << 1) - 0x7F;

    joystick_set_axis(0, slider_value);
}

void keyboard_post_init_user(void) {
    // NOTE: Raw 'SLIDER_PIN' value is in the range [8, 936]
    slider_reading = (int8_t)(analogReadPin(SLIDER_PIN) >> 3);
}
    
void housekeeping_task_user(void) {
    slider();
}

