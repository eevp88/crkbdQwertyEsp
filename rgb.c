#pragma once


#ifdef RGB_MATRIX_ENABLE
extern rgb_config_t rgb_matrix_config;
rgb_config_t        RGB_current_config;

void save_rgb_config(void) {
    RGB_current_config.enable = rgb_matrix_config.enable;
    RGB_current_config.mode   = rgb_matrix_get_mode();
    RGB_current_config.speed  = rgb_matrix_config.speed;
    RGB_current_config.hsv    = rgb_matrix_config.hsv;
}

void restore_rgb_config(void) {
    rgb_matrix_config.speed   = RGB_current_config.speed;
    if (rgb_matrix_config.mode != RGB_current_config.mode) {
        rgb_matrix_mode_noeeprom(RGB_current_config.mode);
    }
    if ((RGB_current_config.hsv.h != rgb_matrix_config.hsv.h) || (RGB_current_config.hsv.s != rgb_matrix_config.hsv.s) || (RGB_current_config.hsv.v != rgb_matrix_config.hsv.v)) {
        rgb_matrix_sethsv_noeeprom(RGB_current_config.hsv.h, RGB_current_config.hsv.s, RGB_current_config.hsv.v);
    }
    if (rgb_matrix_config.enable) {
        rgb_matrix_enable_noeeprom();
    } else {
        rgb_matrix_disable_noeeprom();
    }

}




void rgb_by_layer(int layer) {
    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
    switch (layer) {
        case _ADJUST:
            rgblight_sethsv_noeeprom(9, 255, 255);
            break;
        case _RAISE:
            rgblight_sethsv_noeeprom(HSV_CYAN);
            break;
        case _LOWER:
            rgblight_sethsv_noeeprom(HSV_MAGENTA);
            break;
        default:
            rgblight_sethsv_noeeprom(HSV_RED);
    }
}
#endif
