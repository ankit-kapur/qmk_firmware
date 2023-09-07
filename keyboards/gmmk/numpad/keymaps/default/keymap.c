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
#include "print.h"
#include "inttypes.h"
#include "stdint.h"
#include "stdio.h"

// Tap Dance declarations
enum {
    TD_NUM_KEY = 0,
    TD_SLASH_KEY,
    TD_SLASH_KEY_LAYER_2,
    TD_ASTERISK_KEY,
    TD_ASTERISK_KEY_LAYER_2,
    TD_MINUS_KEY,
    TD_MINUS_KEY_LAYER_2,
    TD_PLUS_KEY,
    TD_PLUS_KEY_LAYER_2,
    TD_ROTARY_BUTTON,
    TD_KC_P0,
    TD_KC_P0_LAYER_2,
    TD_KC_P1,
    TD_KC_P1_LAYER_2,
    TD_KC_P2,
    TD_KC_P2_LAYER_2,
    TD_KC_P3,
    TD_KC_P3_LAYER_2,
    TD_KC_P4,
    TD_KC_P5,
    TD_KC_P6,
    TD_KC_P7,
    TD_KC_P8,
    TD_KC_P9,
    TD_ENTER_KEY,
    TD_ENTER_KEY_LAYER_2,
    TD_DOT_KEY,
    TD_DOT_KEY_LAYER_2,
    TD_ROTARY_BUTTON_LAYER_2,
};

// Tap Dance (TD) definitions
tap_dance_action_t tap_dance_actions[] = {
    // Tap once for 'NUMS LOCK Toggle', twice for 'Calculator'
    [TD_NUM_KEY] = ACTION_TAP_DANCE_DOUBLE(MO(1), KC_CALC),

    [TD_SLASH_KEY] = ACTION_TAP_DANCE_DOUBLE(KC_PSLS, KC_P),
    [TD_SLASH_KEY_LAYER_2] = ACTION_TAP_DANCE_DOUBLE(KC_X, KC_F1),
    
    [TD_ASTERISK_KEY] = ACTION_TAP_DANCE_DOUBLE(KC_PAST, KC_O),
    [TD_ASTERISK_KEY_LAYER_2] = ACTION_TAP_DANCE_DOUBLE(KC_Y, KC_F2),

    [TD_MINUS_KEY] = ACTION_TAP_DANCE_DOUBLE(KC_PMNS, KC_N),
    [TD_MINUS_KEY_LAYER_2] = ACTION_TAP_DANCE_DOUBLE(KC_Z, KC_F5),

    [TD_PLUS_KEY] = ACTION_TAP_DANCE_DOUBLE(KC_PLUS, KC_M),
    [TD_PLUS_KEY_LAYER_2] = ACTION_TAP_DANCE_DOUBLE(KC_AT, KC_HASH),

    [TD_ROTARY_BUTTON] = ACTION_TAP_DANCE_DOUBLE(KC_Q, KC_R),
    [TD_ROTARY_BUTTON_LAYER_2] = ACTION_TAP_DANCE_DOUBLE(KC_S, KC_T),

    // Media: Previous, Play/Pause, Next
    [TD_KC_P0] = ACTION_TAP_DANCE_DOUBLE(KC_P0, KC_A),
    [TD_KC_P0_LAYER_2] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_F4),

    [TD_KC_P1] = ACTION_TAP_DANCE_DOUBLE(KC_P1, KC_B),
    [TD_KC_P2] = ACTION_TAP_DANCE_DOUBLE(KC_P2, KC_C),
    [TD_KC_P3] = ACTION_TAP_DANCE_DOUBLE(KC_P3, KC_D),

    [TD_KC_P4] = ACTION_TAP_DANCE_DOUBLE(KC_P4, KC_E),
    [TD_KC_P5] = ACTION_TAP_DANCE_DOUBLE(KC_P5, KC_F),
    [TD_KC_P6] = ACTION_TAP_DANCE_DOUBLE(KC_P6, KC_G),

    [TD_KC_P7] = ACTION_TAP_DANCE_DOUBLE(KC_P7, KC_H),
    [TD_KC_P8] = ACTION_TAP_DANCE_DOUBLE(KC_P8, KC_I),
    [TD_KC_P9] = ACTION_TAP_DANCE_DOUBLE(KC_P9, KC_J),

    [TD_ENTER_KEY] = ACTION_TAP_DANCE_DOUBLE(KC_ENTER, KC_K),
    [TD_ENTER_KEY_LAYER_2] = ACTION_TAP_DANCE_DOUBLE(KC_V, KC_W),

    [TD_DOT_KEY] = ACTION_TAP_DANCE_DOUBLE(KC_PDOT, KC_L),
    [TD_DOT_KEY_LAYER_2] = ACTION_TAP_DANCE_DOUBLE(KC_TILD, KC_EXCLAIM),

    [TD_KC_P1_LAYER_2] = ACTION_TAP_DANCE_DOUBLE(KC_SEMICOLON, KC_DOLLAR),
    [TD_KC_P2_LAYER_2] = ACTION_TAP_DANCE_DOUBLE(KC_CIRC, KC_PERCENT),
    [TD_KC_P3_LAYER_2] = ACTION_TAP_DANCE_DOUBLE(KC_AMPERSAND, KC_ASTERISK)
    
};

// ------------------------------------------------ Original
// Source: https://github.com/GloriousThrall/qmk_firmware/blob/gmmk_numpad/keyboards/gmmk/numpad/keymaps/default/keymap.c

//      NUM      /       *       -
//      7        8       9       +
//      4        5       6       CALC
//      1        2       3       RET
//      0                        .

//   [0] = LAYOUT(
//     MO(1),   KC_PSLS,   KC_PAST,   KC_PMNS,
//     KC_P7,   KC_P8,     KC_P9,     KC_PPLS,
//     KC_P4,   KC_P5,     KC_P6,     KC_CALC,
//     KC_P1,   KC_P2,     KC_P3,     KC_PENT,
//     KC_P0,                         KC_PDOT
//   ),
//   [1] = LAYOUT(
//     _______,   KC_PSLS,   KC_PAST,   KC_PMNS,
//     KC_P7,     RGB_VAI,   KC_P9,     KC_PPLS,
//     RGB_RMOD,  KC_P5,     RGB_MOD,   KC_CALC,
//     KC_P1,     RGB_VAD,   KC_P3,     KC_PENT,
//     RGB_TOG,                         QK_BOOT
//   )
// };

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {


[0] = LAYOUT(
    MO(1),             TD(TD_SLASH_KEY),  TD(TD_ASTERISK_KEY),   TD(TD_MINUS_KEY),
    TD(TD_KC_P7),      TD(TD_KC_P8),      TD(TD_KC_P9),          TD(TD_PLUS_KEY),
    TD(TD_KC_P4),      TD(TD_KC_P5),      TD(TD_KC_P6),          TD(TD_ROTARY_BUTTON),
    TD(TD_KC_P1),      TD(TD_KC_P2),      TD(TD_KC_P3),          TD(TD_ENTER_KEY),
    TD(TD_KC_P0),                                                TD(TD_DOT_KEY)
  ),

  [1] = LAYOUT(
    _______,   TD(TD_SLASH_KEY_LAYER_2),  TD(TD_ASTERISK_KEY_LAYER_2),   TD(TD_MINUS_KEY_LAYER_2),
    RGB_VAI,  RGB_SPI,   RGB_SAI,   TD(TD_PLUS_KEY_LAYER_2),
    RGB_MOD, RGB_TOG, RGB_HUI,   TD(TD_ROTARY_BUTTON_LAYER_2),
    TD(TD_KC_P1_LAYER_2),  TD(TD_KC_P2_LAYER_2), TD(TD_KC_P3_LAYER_2),   TD(TD_ENTER_KEY_LAYER_2),
    TD(TD_KC_P0_LAYER_2),                        TD(TD_DOT_KEY_LAYER_2)
  )

// ------------------- Backup 6 pm

//      NUM or CALC      / or (       * or )      - or C
//      7                8            9           + or CE
//      4                5            6           Encoder button as MO Switch
//      1                2            3           Enter
//      0                                         .

  // [0] = LAYOUT(
  //   TD(TD_NUM_KEY),   TD(TD_SLASH_KEY),   TD(TD_ASTERISK_KEY),   TD(TD_MINUS_KEY),
  //   KC_P7,             KC_P8,             KC_P9,                 TD(TD_PLUS_KEY),
  //   KC_P4,             KC_P5,             KC_P6,                 MO(1),
  //   KC_P1,             KC_P2,             KC_P3,                 KC_PENT,
  //   KC_P0,                                                       KC_PDOT
  // ),

//  SYS_POWEROFF  MEDIA_PREV   MEDIA_NEXT   MEDIA_PLAY_PAUSE
//  RGB_HUE+      RGB_BRIGHT+  RGB_SAT+     MEDIA_STOP
//  <RGB_MODE     RGB_TOGGLE   RGB_MODE>    ____________
//  RGB_HUE-      RGB_BRIGHT-  RGB_SAT-     MEDIA_PLAYER
//  SYS_SLEEP                               KBD_BOOTLD_MODE

  // [1] = LAYOUT(
  //   KC_PWR,   KC_MPRV,   KC_MNXT,   KC_MPLY,
  //   RGB_HUI,  RGB_VAI,   RGB_SAI,   KC_MSTP,
  //   RGB_RMOD, RGB_TOG,   RGB_MOD,   _______,
  //   RGB_HUD,  RGB_VAD,   RGB_SAD,   KC_MSEL,
  //   KC_SLEP,                        QK_BOOT
  // )
};

// Slider as joystick
joystick_config_t joystick_axes[JOYSTICK_AXIS_COUNT] = {
    JOYSTICK_AXIS_VIRTUAL,
};

// NOTE: For rescale parameter 0x7C, minimum and maximum values for 'slider_value' are -115 and 119 respectively.
// We let calibration software on the host to rescale them perfectly to [-127, 127].
#define RESCALE_PARAM		0x7C
int8_t prev_slider_reading = 0;
int8_t prev_slider_value = 0;
uint8_t divisor = 0;

void slider(void) {
    if (divisor++) { /* only run the slider function 1/256 times it's called */
        return;
    }

    // How this works:
    //      if slider_reading has gone up or down (store prev value and compare),
    //      then send KC_VOL_UP/DOWN keystroke.

    // // We maintain a rolling average to reduce jitter
    int8_t slider_reading = (slider_reading >> 1) + (int8_t)(analogReadPin(SLIDER_PIN) >> 4);
    int8_t slider_value = ((RESCALE_PARAM - slider_reading) << 1) - 0x7F;

    // printf("VALUES ===> slider_value = %d, prev_slider_value = %d \n", 
    //     slider_value, prev_slider_value);

    if (slider_value < prev_slider_value) {

        printf("READING ===> %d;\tPREV ===> = %d\n", slider_reading, prev_slider_reading);
        printf("VALUE ===> %d;\tPREV ===> = %d\n", slider_value, prev_slider_value);

        tap_code_delay(KC_VOLU, 1);

        print("VOLUME INCREASEDDDDDDDD! \n");
    } else if (slider_value > prev_slider_value) {
    
        printf("READING ===> %d;\tPREV ===> = %d\n", slider_reading, prev_slider_reading);
        printf("VALUE ===> %d;\tPREV ===> = %d\n", slider_value, prev_slider_value);

        tap_code_delay(KC_VOLD, 1);

        print("VOLUME REDUCED! \n");
    } else {
        // else do nothing
        // print("NO CHANGE IN VOLUME.\n");
    }

    
    prev_slider_value = slider_value;
    prev_slider_reading = slider_reading;
}
    
void housekeeping_task_user(void) {
    slider();
}

