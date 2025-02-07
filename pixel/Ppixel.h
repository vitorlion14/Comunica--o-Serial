#ifndef __PPIXEL_H_
#define __PPIXEL_H_

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"

#include "ws2812.pio.h"
#include "alfabeto.h"

void init_neopixel();
uint32_t urgb_u32(uint8_t r, uint8_t g, uint8_t b);
void renderMatrix(bool letra[MATRIX_LEN][MATRIX_LEN]);
void renderRGBMatrix(uint32_t matrix[MATRIX_LEN][MATRIX_LEN]);

#define NEOPIXEL_PIN 7

#endif