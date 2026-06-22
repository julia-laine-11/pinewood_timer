#ifndef PINEWOOD_DISPLAY_H
#define PINEWOOD_DISPLAY_H

#include <stdint.h>

void display_init(void);
void display_refresh_step(void);
void display_set_status_leds(uint8_t ready, uint8_t running, uint8_t finished);

#endif
