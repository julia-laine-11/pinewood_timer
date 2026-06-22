#ifndef PINEWOOD_FONT_H
#define PINEWOOD_FONT_H

#include <stdint.h>

/*
 * 7-segment segment patterns (common-cathode style via TLC59211 outputs).
 * Bit 7 (0x80) lights the decimal point — always set on the first timer digit.
 */
static const uint8_t font_digit[10] = {
    0x3f, /* 0 */
    0x06, /* 1 */
    0x5b, /* 2 */
    0x4f, /* 3 */
    0x66, /* 4 */
    0x6d, /* 5 */
    0x7d, /* 6 */
    0x07, /* 7 */
    0x7f, /* 8 */
    0x67  /* 9 */
};

#define FONT_BLANK 0x00U
#define FONT_DP    0x80U

#endif
