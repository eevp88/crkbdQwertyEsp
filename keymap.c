#include QMK_KEYBOARD_H
#include "keycodes.h"
#include "keymap_spanish.h"


#ifdef OLED_DRIVER_ENABLE
#    include "oled.c"
#endif

#if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
#    include "rgb.c"
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT(
  //|-----------------------------------------------------|                    |---------------------------------------------------------|
     KC_ESC,  ES_Q,    ES_W,    ES_E,    ES_R,    ES_T,                          ES_Y,    ES_U,    ES_I,    ES_O,    ES_P,    KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+------------|
     KC_TAB,  ES_A,   ES_S,     ES_D,    ES_F,    ES_G,                          ES_H,    ES_J,    ES_K,      ES_L,   ES_NTIL  ,TD(TD_COMI),
  //---------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+------------|
    TD(TD_CAPLOCK), ES_Z, ES_X, ES_C,    ES_V,    ES_B,                          ES_N,    ES_M, TD(TD_CD), TD(TD_P2P), TD(TD_SLA), KC_LCTL,
                                         KC_LGUI , LOWER, KC_SPC,        KC_ENT, RAISE, TD(TD_ALT)
                                      //|--------------------------|  |--------------------------|


  ),

  [_LOWER] = LAYOUT(
  //|-----------------------------------------------------|                    |-----------------------------------------------------|
     KC_ESC,  ES_1,    ES_2,    ES_3,    ES_4,    ES_5,                         ES_6,    ES_7,    ES_8,    ES_9,    ES_0,    KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     _______, KC_ANGL, KC_ANGR, KC_LPRN, KC_RPRN, KC_PGUP,                      KC_MINS, KC_DEL, KC_UP,  _______ ,KC_UP, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     KC_LCTL, XXXXXXX, XXXXXXX, KC_LBRC, KC_RBRC, KC_PGDOWN,                    KC_UNDS, KC_HOME, KC_DOWN, KC_LEFT,  KC_DOWN, KC_RIGHT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                         KC_LGUI, LOWER, KC_SPC,       KC_ENT, RAISE, TD(TD_ALT)
                                      //|--------------------------|  |--------------------------|
  ),

 [_RAISE] = LAYOUT(
  //|-----------------------------------------------------|                    |-----------------------------------------------------|
     ES_FORD,  ES_EXLM, ES_DQUO,  ES_BULT, ES_DLR, ES_PERC,                      ES_AMPR, ES_SLSH, ES_LPRN, ES_RPRN, ES_EQL, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     _______, _______, _______,   _______, _______, _______,                      XXXXXXX, XXXXXXX, _______,ES_CIRC,ES_ASTR, TD(TD_QU),
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     _______, _______, _______, _______, _______, _______,                      XXXXXXX, KC_MINS, KC_PLUS, XXXXXXX, KC_BSLS, ES_DIAE,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, LOWER, KC_SPC,      KC_ENT, RAISE, TD(TD_ALT)
                                      //|--------------------------|  |--------------------------|
  ),

  [_ADJUST] = LAYOUT(
  //|-----------------------------------------------------|                    |-----------------------------------------------------|
     XXXXXXX, CK_RST,  CK_DOWN, CK_UP,   CK_TOGG, RGB_TOG,                       MU_TOG, KC_F12,  KC_F7,   KC_F8,   KC_F9,   XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     XXXXXXX, RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI, RGB_MOD,                       MU_MOD, KC_F11,  KC_F4,   KC_F5,   KC_F6,   RESET,  \
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     XXXXXXX, RGB_HUD, RGB_SAD, RGB_VAD, RGB_SPD, RGBRST,                        AU_TOG, KC_F10,  KC_F1,   KC_F2,   KC_F3,   _______,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                         _______, LOWER, KC_SPC,       KC_ENT, RAISE, KC_VOLU \
                                      //|--------------------------|  |--------------------------|
  )
};
// clang-format off
int RGB_current_mode;

#if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
layer_state_t layer_state_set_user(layer_state_t state) {
    /* For any layer other than default, save current RGB state and switch to layer-based RGB */
    if (layer_state_cmp(state, 0)) {
        restore_rgb_config();
    } else {
        uint8_t layer = get_highest_layer(state);
        if (layer_state_cmp(layer_state, 0)) save_rgb_config();
        rgb_by_layer(layer);
    }
    return state;
}
#endif

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

void matrix_init_user(void) {
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef OLED_DRIVER_ENABLE
    if (record->event.pressed) {
        oled_timer = timer_read();
        add_keylog(keycode);
    }
#endif

    switch (keycode) {
        case LOWER:
            if (record->event.pressed) {
                layer_on(_LOWER);
            } else {
                layer_off(_LOWER);
            }
            update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
            return false;
        case RAISE:
            if (record->event.pressed) {
                layer_on(_RAISE);
            } else {
                layer_off(_RAISE);
            }
            update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
            return false;
        case ADJUST:
            if (record->event.pressed) {
                layer_on(_ADJUST);
            } else {
                layer_off(_ADJUST);
            }
            return false;
            #ifdef RGB_MATRIX_ENABLE
                if (record->event.pressed) {
                    eeconfig_update_rgb_matrix_default();
                    rgb_matrix_enable();
                }
            #endif
            break;


    }
    return true;
}

#ifdef RGB_MATRIX_ENABLE

void suspend_power_down_user(void) {
    rgb_matrix_set_suspend_state(true);
}

void suspend_wakeup_init_user(void) {
    rgb_matrix_set_suspend_state(false);
}

#endif
