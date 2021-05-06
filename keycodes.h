#pragma once
#include "keymap_spanish.h"

enum layers {
    _QWERTY,
    _LOWER,
    _RAISE,
    _ADJUST,
};

enum custom_keycodes {
    QWERTY = SAFE_RANGE,
    LOWER,
    RAISE,
    ADJUST,
    RGBRST
};

enum {
    TD_CD,
    TD_P2P,
    TD_COMI,
    TD_SLA,
    TD_CAPLOCK,
    TD_ALT,
    TD_ABK,
    TD_QU
};

#define KC_LOWER LOWER
#define KC_RAISE RAISE
#define KC_ANGL LSFT(KC_COMM)
#define KC_ANGR LSFT(KC_DOT)


// Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    // Tap once for ;, twice for :
    [TD_CD] = ACTION_TAP_DANCE_DOUBLE(ES_COMM, ES_SCLN),
    [TD_P2P] = ACTION_TAP_DANCE_DOUBLE(ES_DOT, ES_COLN),
    [TD_COMI] = ACTION_TAP_DANCE_DOUBLE(KC_QUOT, LSFT(KC_QUOT)),
    [TD_SLA] = ACTION_TAP_DANCE_DOUBLE(KC_SLSH, LSFT(KC_SLSH)),
    [TD_CAPLOCK] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS),
    [TD_ALT] = ACTION_TAP_DANCE_DOUBLE(KC_LALT,KC_RALT),
    [TD_ABK] = ACTION_TAP_DANCE_DOUBLE(ES_LABK, ES_RABK),
    [TD_QU] = ACTION_TAP_DANCE_DOUBLE(ES_IQUE, ES_QUES),
};

