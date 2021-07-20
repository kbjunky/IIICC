/* Copyright 2020 kbjunky
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

#define ICO_SPEAKER 128
#define ICO_BRIGHTNESS 131
#define ICO_HUE 134
#define ICO_SAT 137
#define ICO_CAPSL 140
#define ICO_LOGO 143
#define ICO_BLANK 157
#define ICO_LOGO_WIDTH 14
#define ICO_WIDTH 3 //3x3 characters per icon  
#define CHARS_PER_LINE 32 //in glcdfont.c
#define ICO_UP  24
#define ICO_DOWN 25
#define SCREEN_TIMEOUT 2500
#ifdef OLED_DRIVER_ENABLE
  static uint16_t oled_timer = 0;
#endif

//Boot up LED animation
#define BOOT_ANIM_ENABLED //enable boot animation
#define BOOT_ANIM_DELAY 125 //delay for each step

#define MOVE_UP 1
#define MOVE_DOWN -1
#define MOVE_STOP 0

#define _DFT 0
#define _FN1 10
#define _FN2 11


#define SPCFN1 LT(_FN1, KC_SPC)
#define TABFN2 LT(_FN2, KC_TAB)
#define TABFN1 LT(_FN1, KC_TAB)

#define INSALT MT(MOD_LALT, KC_INS)
#define ENTCTL MT(MOD_LCTL, KC_ENT)
#define CTLLSH MT(MOD_LCTL, KC_SLSH)
#define CTLQOT MT(MOD_RCTL, KC_QUOT)
#define DELRALT MT(MOD_RALT, KC_DEL)

void render_icon_center(uint8_t);  //forward definition
void render_action_icon(uint8_t, uint8_t);
void render_icon(uint8_t, uint8_t, uint8_t);
void clear_icon(uint8_t, uint8_t);

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {\
    /* Base */
    [_DFT] = LAYOUT(\
    KC_ESC,       KC_Q,   KC_W,     KC_E,     KC_R,     KC_T,     KC_BSLS,  KC_MINS,  KC_Y,    KC_U,    KC_I,   KC_O,   KC_P,      KC_BSPC,\
    KC_LSFT,      KC_A,   KC_S,     KC_D,     KC_F,     KC_G,	    KC_LBRC,  KC_RBRC,  KC_H,    KC_J,    KC_K,   KC_L,   KC_EQL,    DELRALT,\
                  KC_Z,   KC_X,     KC_C,     KC_V,     KC_B,     KC_COMM,  KC_DOT,   KC_N,    KC_M,    KC_SCLN,KC_UP,  KC_RGHT,\
                          KC_LEAD,  KC_LALT,  CTLLSH,   SPCFN1,                       ENTCTL,  CTLQOT,  KC_LEFT,KC_DOWN,\
                                                        TABFN2,                       INSALT,\
                                            KC_UP,                                                  KC_VOLU,\
                                  KC_LEFT, KC_ENT, KC_RGHT,                               KC_WBAK, KC_MUTE, KC_MPLY,\
                                            KC_DOWN,                                                KC_VOLD,\
    KC_F1,          KC_VOLU,        KC_F8,\
    KC_F2,          KC_MUTE,        KC_F9,\
    KC_F3,          KC_VOLD,        KC_F10,\
    KC_F4,                          KC_F11,\
    KC_F5,    KC_F6,      KC_F7,    KC_F12\
    ),
    [_FN1] = LAYOUT(\
    A(KC_F4),     KC_1,      KC_2,      KC_3,       KC_4,      KC_5,     KC_BSPC,   KC_TRNS,  KC_1,     KC_2,   KC_3,   KC_4,  KC_5, KC_TRNS,\
    KC_TRNS,      KC_6,      KC_7,      KC_8,       KC_9,      KC_0,     KC_DEL,    KC_TRNS,  KC_6,     KC_7,   KC_8,   KC_9,  KC_0, KC_TRNS,\
                  KC_TRNS,   KC_TRNS,   KC_TRNS,    KC_COMM,   KC_DOT,   KC_MINS,   KC_TRNS,  KC_GRV,   KC_TRNS,KC_TRNS,  KC_PGUP, KC_END,\
                            KC_TRNS,   KC_TRNS,    KC_TRNS,   KC_TRNS,                       KC_TRNS,  KC_TRNS,  KC_HOME,  KC_PGDN,\
                                                              KC_TRNS,                       KC_TRNS,\
                                            KC_MYCM,                                                KC_TRNS,\
                                  LCTL(LSFT(KC_TAB)), G(KC_L), LCTL(KC_TAB),                              KC_TRNS, KC_TRNS, KC_TRNS,\
                                            KC_TRNS,                                                KC_TRNS,\
    KC_F1,          KC_VOLU,        KC_F8,\
    KC_F2,          KC_MUTE,        KC_F9,\
    KC_F3,          KC_VOLD,        KC_F10,\
    KC_F4,                          KC_F11,\
    KC_F5,    KC_F6,      KC_F7,    KC_F12\
    ),
    [_FN2] = LAYOUT(\
    KC_PGUP,      KC_F1,   KC_F2,    KC_F3,   KC_F4,   KC_F5,  C(KC_PGUP), KC_TRNS,  KC_F6,   KC_F7,    KC_F8,    KC_F9,    KC_F10,    KC_HOME,\
    KC_PGDN,      KC_F6,   KC_F7,    KC_F8,   KC_F9,   KC_F10, KC_ENT,     KC_TRNS,  KC_F11,  KC_F12,   KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_END,\
                  KC_TRNS, KC_TRNS,  KC_TRNS, KC_F11,  KC_F12, A(KC_F1),   A(KC_F2), KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,\
                          KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS,                      KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS,  \
                                                      KC_TRNS,                      KC_TRNS,\
                                            RGB_HUI,                                                RGB_VAI,\
                                  RGB_SAD, RGB_M_T, RGB_SAI,                              RGB_M_P, RGB_TOG, RGB_MOD,\
                                            RGB_HUD,                                                RGB_VAD,\
    KC_F1,          KC_VOLU,        KC_F8,\
    KC_F2,          KC_MUTE,        KC_F9,\
    KC_F3,          KC_VOLD,        KC_F10,\
    KC_F4,                          KC_F11,\
    KC_F5,    KC_F6,      KC_F7,    KC_F12 
    )    
};



LEADER_EXTERNS();

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  switch(keycode) {
    case KC_VOLU:
      if(record->event.pressed) {
        render_action_icon(ICO_SPEAKER, ICO_UP);
      }      
      return true;

    case KC_VOLD:
      if(record->event.pressed) {
        render_action_icon(ICO_SPEAKER, ICO_DOWN);        
      }
      return true;

      case RGB_HUI:
        render_action_icon(ICO_HUE, ICO_UP);
        return true;
      
      case RGB_HUD:
        render_action_icon(ICO_HUE, ICO_DOWN);
        return true;

      case RGB_SAI:
        render_action_icon(ICO_SAT, ICO_UP);
        return true;
      
      case RGB_SAD:
        render_action_icon(ICO_SAT, ICO_DOWN);
        return true;

      case RGB_VAI:
        render_action_icon(ICO_BRIGHTNESS, ICO_UP);
        return true;

      case RGB_VAD:
        render_action_icon(ICO_BRIGHTNESS, ICO_DOWN);
        return true;      
    }      
  
  return true;
}

void matrix_scan_user(void)
{
  
  
  LEADER_DICTIONARY(){
    leading = false;
    leader_end();

/* Windows key */
    //Win
    SEQ_ONE_KEY(KC_W) {
      register_code(KC_LCMD);
      unregister_code(KC_LCMD);
    }

    SEQ_ONE_KEY(KC_B) {
      reset_keyboard();
    }
    //Win+R [Run]
    SEQ_TWO_KEYS(KC_W, KC_R) {
      SEND_STRING(SS_LCMD("r"));
    }

    //Win+L [Logout]
    SEQ_TWO_KEYS(KC_W, KC_L) {
      SEND_STRING(SS_LCMD("l"));
    }

    //Win+Shift+S [Screenshot]
    SEQ_TWO_KEYS(KC_W, KC_S) {
      SEND_STRING(SS_LSFT(SS_LCMD("s")));
    }

    //Win+Tab [Cycle windows]
    SEQ_TWO_KEYS(KC_W, KC_T) {
      SEND_STRING(SS_LCMD(SS_TAP(X_TAB)));
    }
/* System */
    //Ctrl+Alt+Del
    SEQ_THREE_KEYS(KC_C, KC_A, KC_D ) {
      SEND_STRING(SS_LCTL(SS_LALT(SS_TAP(X_DEL))));
    }

    SEQ_THREE_KEYS(KC_C, KC_A, KC_E ) {
      SEND_STRING(SS_LCTL(SS_LALT(SS_TAP(X_END))));
    }

/* FAR */
    //Alt+Shift+Insert [Get path]
    SEQ_ONE_KEY(KC_A) {
      SEND_STRING(SS_LSFT(SS_LALT(SS_TAP(X_INS))));
    }
    //Ctrl+PgU [Level Up]
    SEQ_ONE_KEY(KC_Q) {
      SEND_STRING(SS_LCTL(SS_TAP(X_PGUP)));
    }

/* CAPS LOCK */
    SEQ_ONE_KEY(KC_S) {
      SEND_STRING(SS_TAP(X_CAPS));
      render_icon(ICO_CAPSL, 0, 0);
    }  
  }
}

#ifdef OLED_DRIVER_ENABLE

void render_logo(void) {
  oled_timer = timer_read();
  for(uint8_t i = 0; i < ICO_WIDTH; i++) {  
    oled_set_cursor(((oled_max_chars() / 2) - (ICO_LOGO_WIDTH / 2) + 1), (oled_max_lines() / 2) - ICO_WIDTH + i);  
    for(uint8_t j = 0; j < ICO_LOGO_WIDTH; j++) {
      oled_write_char(ICO_LOGO + ((i * CHARS_PER_LINE) + j), false);
    }   
  }
}

void oled_erase(void) {
  for(int i = 0; i < oled_max_chars() * oled_max_lines(); i++) {
      oled_write_char(0, false);
  }
}

void oled_task_user(void) { 
  if(!host_keyboard_led_state().caps_lock) {
      clear_icon(0, 0);  
  }
  
  if(timer_elapsed(oled_timer) > SCREEN_TIMEOUT) {
    oled_erase();  
    if(host_keyboard_led_state().caps_lock) {
      render_icon(ICO_CAPSL, 0, 0);  
    }
  }  
}
#endif

void render_icon(uint8_t icon, uint8_t col, uint8_t row) {
#ifdef OLED_DRIVER_ENABLE
  oled_timer = timer_read();
  for(uint8_t i = 0; i < ICO_WIDTH; i++) {
    oled_set_cursor(col, row + i);
    for(uint8_t j = 0; j < ICO_WIDTH; j++) {
      oled_write_char(icon + ((i * CHARS_PER_LINE) + j), false);
    }   
  }
#endif
}

void render_icon_center(uint8_t icon) {
#ifdef OLED_DRIVER_ENABLE
    render_icon(icon, ((oled_max_chars() / 2) - (ICO_WIDTH / 2)), (oled_max_lines() / 2) - (ICO_WIDTH / 2));
#endif
}

void render_action_icon(uint8_t icon, uint8_t direction) {
#ifdef OLED_DRIVER_ENABLE
  render_icon_center(icon);
  oled_write_char(0, false);
  oled_write_char(direction, false);
#endif
}

void clear_icon(uint8_t col, uint8_t row) {
#ifdef OLED_DRIVER_ENABLE
  for(uint8_t i = 0; i < ICO_WIDTH; i++) {
      oled_set_cursor(col, row + i);
      for(uint8_t j = 0; j < ICO_WIDTH; j++) {
        oled_write_char(0, false);
      }   
    } 
#endif
}


void keyboard_post_init_user(void) {
#ifdef CONSOLE_ENABLE
  // Customise these values to desired behaviour
  debug_enable=true;
  debug_matrix=true;
  debug_keyboard=true;
#endif

#ifdef OLED_DRIVER_ENABLE
  oled_off();
#endif
#ifdef BOOT_ANIM_ENABLED
 #ifdef RGBLIGHT_ENABLE
  rgblight_setrgb_range(0, 0, 0, 0, RGBLED_NUM);

  for(uint8_t i = 0;i < RGBLED_NUM;i++) {
    rgblight_setrgb_range(255, 255, 255, 0, i);
    wait_ms(BOOT_ANIM_DELAY);
  }
  rgblight_reload_from_eeprom();
  #endif
#endif
#ifdef OLED_DRIVER_ENABLE
  render_logo();  
#endif  

}