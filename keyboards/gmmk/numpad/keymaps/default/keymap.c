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
#include "qmk_midi.h"

// Tap Dance declarations
enum {
    TD_MNS_ESC = 0,
    TD_PLS_DEL,
    TD_SLS_LPRN,
    TD_AST_RPRN
};

// Tap Dance definitions
tap_dance_action_t tap_dance_actions[] = {
    // Tap once for '-', twice for 'Escape'
    [TD_MNS_ESC] = ACTION_TAP_DANCE_DOUBLE(KC_PMNS, KC_ESC),
    // Tap once for '+', twice for 'Delete'
    [TD_PLS_DEL] = ACTION_TAP_DANCE_DOUBLE(KC_PPLS, KC_DEL),
    // Tap once for '/', twice for '('
    [TD_SLS_LPRN] = ACTION_TAP_DANCE_DOUBLE(KC_PSLS, KC_LPRN),
    // Tap once for '*', twice for ')'
    [TD_AST_RPRN] = ACTION_TAP_DANCE_DOUBLE(KC_PAST, KC_RPRN)
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

//      NUM      /       *       -
//      7        8       9       +
//      4        5       6       ENCODER
//      1        2       3       RET
//      0                        .

  [0] = LAYOUT(
    MO(1),   TD(TD_SLS_LPRN),   TD(TD_AST_RPRN),   TD(TD_MNS_ESC),
    KC_P7,        KC_P8,             KC_P9,        TD(TD_PLS_DEL),
    KC_P4,        KC_P5,             KC_P6,           KC_CALC,
    KC_P1,        KC_P2,             KC_P3,           KC_PENT,
    KC_P0,                                            KC_PDOT
  ),

//     ___       MEDIA_PREV   MEDIA_NEXT   MEDIA_PLAY_PAUSE
//   RGB_HUE+    RGB_BRIGHT+   RGB_SAT+      MEDIA_STOP
//   <RGB_MODE   RGB_TOGGLE    RGB_MODE>    SYS_POWEROFF
//   RGB_HUE-    RGB_BRIGHT-   RGB_SAT-     MEDIA_PLAYER
// CONTROL_PANEL                           KBD_BOOTLD_MODE

  [1] = LAYOUT(
    _______,   KC_MPRV,   KC_MNXT,   KC_MPLY,
    RGB_HUI,   RGB_VAI,   RGB_SAI,   KC_MSTP,
    RGB_RMOD,  RGB_TOG,   RGB_MOD,   KC_PWR,
    RGB_HUD,   RGB_VAD,   RGB_SAD,   KC_MSEL,
    KC_CONTROL_PANEL,                QK_BOOT
  )
};

// Potentiometer Slider, MIDI Control
uint8_t divisor = 0;

void slider(void) {
    if (divisor++) { /* only run the slider function 1/256 times it's called */
        return;
    }
    midi_send_cc(&midi_device, 2, 0x3E, 0x7F + (analogReadPin(SLIDER_PIN) >> 3));
}

void housekeeping_task_user(void) {
    slider();
}
