#include QMK_KEYBOARD_H

bool is_app_switch_active = false;
uint16_t app_switch_timer = 0;

enum custom_keycodes {
  CKC_AE = SAFE_RANGE,
  CKC_OE,
  CKC_CAE,
  CKC_COE,
  CKC_APP_SWITCH
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT_split_3x5_3(
	    KC_Q, KC_W, KC_F, KC_P, KC_G, KC_J, KC_L, KC_U, KC_Y, RGUI_T(KC_SCLN), 
	    KC_A, KC_R, KC_S, KC_T, KC_D, KC_H, KC_N, KC_E, KC_I, KC_O, 
	    LSFT_T(KC_Z), KC_X, KC_C, KC_V, LT(5,KC_B), KC_K, KC_M, KC_COMM, KC_DOT, RSFT_T(KC_SLSH), 
	    LCTL_T(KC_TAB), LALT_T(KC_ESC), LGUI_T(KC_BSPC), 
	    LT(2,KC_SPC), LT(1,KC_NO), LSFT_T(KC_ENT)),
	[1] = LAYOUT_split_3x5_3(
	    KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, 
	    KC_0, LSFT(KC_1), LSFT(KC_2), LSFT(KC_3), LSFT(KC_4), LSFT(KC_5), LSFT(KC_6), LSFT(KC_7), LSFT(KC_8), LSFT(KC_9), 
	    LSFT(KC_0), KC_DOT, KC_UNDS, KC_MINS, KC_PLUS, KC_EQL, KC_QUOT, KC_DQUO, CKC_AE, CKC_OE, KC_SLSH, 
	    KC_TRNS, KC_TRNS, KC_TRNS, 
	    LT(3,KC_NO), KC_NO, KC_TRNS),
	[2] = LAYOUT_split_3x5_3(
	    KC_TILD, KC_GRV, KC_PIPE, KC_BSLS, KC_NO, KC_WH_D, KC_MS_L, KC_MS_D, KC_MS_U, 
	    KC_MS_R, CW_TOGG, KC_NO, KC_BTN2, KC_BTN1, KC_NO, KC_WH_U, KC_LEFT, KC_DOWN, KC_UP, 
	    KC_RGHT, KC_TRNS, KC_LCBR, KC_LBRC, KC_RBRC, KC_RCBR, CKC_APP_SWITCH, KC_HOME, KC_PGDN, KC_PGUP, KC_END, 
	    KC_TRNS, KC_TRNS, KC_TRNS, 
	    KC_NO, LT(3,KC_NO), KC_TRNS),
	[3] = LAYOUT_split_3x5_3(
	    KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, 
	    KC_F10, KC_BRIU, KC_NO, KC_NO, KC_NO, KC_NO, KC_VOLU, KC_MNXT, KC_NO, KC_NO, 
	    KC_NO, KC_BRID, KC_NO, KC_NO, KC_NO, KC_NO, KC_VOLD, KC_MPLY, CKC_CAE, CKC_COE, KC_NO, 
	    KC_NO, KC_NO, KC_NO, 
	    KC_NO, KC_NO, KC_NO)
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case CKC_AE:
      if (record->event.pressed) {
        // when the keycode CKC_AE is pressed
        SEND_STRING(SS_LALT("u")"a");
      }
      break;
    case CKC_OE:
      if (record->event.pressed) {
        // when the keycode CKC_OE is pressed
        SEND_STRING(SS_LALT("u")"o");
      }
      break;
    case CKC_CAE:
      if (record->event.pressed) {
        // when the keycode CKC_AE is pressed
        SEND_STRING(SS_LALT("u")"A");
      }
      break;
    case CKC_COE:
      if (record->event.pressed) {
        // when the keycode CKC_OE is pressed
        SEND_STRING(SS_LALT("u")"O");
      }
      break;
    case CKC_APP_SWITCH:
      if (record->event.pressed) {
        if (!is_app_switch_active) {
          is_app_switch_active = true;
          register_code(KC_LGUI);
        }
        app_switch_timer = timer_read();
        register_code(KC_TAB);
      } else {
        unregister_code(KC_TAB);
      }
      break;
  }
  return true;
}

void matrix_scan_user(void) {
  if (is_app_switch_active) {
    if (timer_elapsed(app_switch_timer) > 1000) {
      unregister_code(KC_LGUI);
      is_app_switch_active = false;
    }
  }
}
