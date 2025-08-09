#include "sitedyno.h"
#include "color.h"

rgb_t sd_limited_rgb_from_hsv(uint8_t hue, uint8_t sat, uint8_t val) {
    if (val > rgb_matrix_get_val()) {
        val = rgb_matrix_get_val();
    }
    hsv_t hsv = {hue, sat, val};
    return hsv_to_rgb(hsv);
}

void sd_capslock_warning(uint8_t led_min, uint8_t led_max) {
    if (host_keyboard_led_state().caps_lock) {
        // uprintf("%d\n", rgb_matrix_get_val());
        for (uint8_t i = led_min; i < led_max; i++) {
            if (g_led_config.flags[i] & LED_FLAG_KEYLIGHT) {
                rgb_t rgb_red = sd_limited_rgb_from_hsv(HSV_RED);
                rgb_matrix_set_color(i, rgb_red.r, rgb_red.g, rgb_red.b);
            }
        }
    }
}

void sd_layer_rgb(uint8_t led_min, uint8_t led_max) {
    rgb_t rgb_color;
    for (uint8_t i = led_min; i < led_max; i++) {
        switch (get_highest_layer(layer_state | default_layer_state)) {
            case 1:
                rgb_color = sd_limited_rgb_from_hsv(HSV_BLUE);
                rgb_matrix_set_color(i, rgb_color.r, rgb_color.g, rgb_color.b);
                break;
            case 2:
                rgb_color = sd_limited_rgb_from_hsv(HSV_PURPLE);
                rgb_matrix_set_color(i, rgb_color.r, rgb_color.g, rgb_color.b);
                break;
            case 3:
                rgb_color = sd_limited_rgb_from_hsv(HSV_CORAL);
                rgb_matrix_set_color(i, rgb_color.r, rgb_color.g, rgb_color.b);
                break;
            case 4:
                rgb_color = sd_limited_rgb_from_hsv(HSV_CYAN);
                rgb_matrix_set_color(i, rgb_color.r, rgb_color.g, rgb_color.b);
                break;
            case 5:
                rgb_color = sd_limited_rgb_from_hsv(HSV_GOLD);
                rgb_matrix_set_color(i, rgb_color.r, rgb_color.g, rgb_color.b);
                break;
            case 6:
                rgb_color = sd_limited_rgb_from_hsv(HSV_GREEN);
                rgb_matrix_set_color(i, rgb_color.r, rgb_color.g, rgb_color.b);
                break;
            case 7:
                rgb_color = sd_limited_rgb_from_hsv(HSV_WHITE);
                rgb_matrix_set_color(i, rgb_color.r, rgb_color.g, rgb_color.b);
                break;
            case 8:
                rgb_color = sd_limited_rgb_from_hsv(HSV_PINK);
                rgb_matrix_set_color(i, rgb_color.r, rgb_color.g, rgb_color.b);
                break;
            case 9:
                rgb_color = sd_limited_rgb_from_hsv(HSV_TEAL);
                rgb_matrix_set_color(i, rgb_color.r, rgb_color.g, rgb_color.b);
                break;
            default:
                break;
        }
    }
}
