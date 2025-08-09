#pragma once

#include "quantum.h"

#define USERSPACE

rgb_t sd_limited_rgb_from_hsv(uint8_t hue, uint8_t sat, uint8_t val);
void  sd_capslock_warning(uint8_t led_min, uint8_t led_max);
void  sd_layer_rgb(uint8_t led_min, uint8_t led_max);
