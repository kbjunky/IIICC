/*
Copyright 2020 kbjunky

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

#pragma once

#include "config_common.h"


/* USB Device descriptor parameter */
#define VENDOR_ID 0xFEED
#define PRODUCT_ID 0x0000
#define DEVICE_VER 0x0001
#define MANUFACTURER kbjunky
#define PRODUCT IIICC
#define DESCRIPTION Three Split keyboard with macropad

/* Macropad */
//#define MACROPAD_ENABLE //uncomment to enable macropad

/* OLED settings */
//#define OLED_DISPLAY_ADDRESS 0x78 //128x64 sometimes run on 0x3C just like 128x32, that was the case for me
#define OLED_DISPLAY_128X64
#define OLED_FONT_H "keyboards/IIICC/glcdfont.c"
#define OLED_TIMEOUT 0
//full matrix, we skip macropad scanning in matrix.c if not defined here
#define MATRIX_ROWS 5
#define MATRIX_COLS 20

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 10

#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION

/* Leader key */
#define LEADER_TIMEOUT 450
#define LEADER_PER_KEY_TIMING

/* Tapping timout */
#define TAP_CODE_DELAY 20
#define TAPPING_TERM 200
#define PERMISSIVE_HOLD
#define IGNORE_MOD_TAP_INTERRUPT

/* RGB Light */
#define RGB_DI_PIN F4
#ifdef RGB_DI_PIN
   #define RGBLED_NUM 16
   #define RGBLIGHT_HUE_STEP 10
   #define RGBLIGHT_SAT_STEP 15
   #define RGBLIGHT_VAL_STEP 15
   #define RGBLIGHT_LIMIT_VAL 255 /* The maximum brightness level */
   #define RGBLIGHT_SLEEP  /* If defined, the RGB lighting will be switched off when the host goes to sleep */
 /*== all animations enable ==*/
   #define RGBLIGHT_ANIMATIONS
 /*== or choose animations ==*/
//    #define RGBLIGHT_EFFECT_BREATHING
//    #define RGBLIGHT_EFFECT_RAINBOW_MOOD
//    #define RGBLIGHT_EFFECT_RAINBOW_SWIRL
//    #define RGBLIGHT_EFFECT_SNAKE
//    #define RGBLIGHT_EFFECT_KNIGHT
//    #define RGBLIGHT_EFFECT_CHRISTMAS
//    #define RGBLIGHT_EFFECT_STATIC_GRADIENT
//    #define RGBLIGHT_EFFECT_RGB_TEST
//    #define RGBLIGHT_EFFECT_ALTERNATING
// /*== customize breathing effect ==*/
//   /*==== (DEFAULT) use fixed table instead of exp() and sin() ====*/
//   #define RGBLIGHT_BREATHE_TABLE_SIZE 256      // 256(default) or 128 or 64
//   /*==== use exp() and sin() ====*/
//   #define RGBLIGHT_EFFECT_BREATHE_CENTER 1.85  // 1 to 2.7
//   #define RGBLIGHT_EFFECT_BREATHE_MAX    255   // 0 to 255
 #endif