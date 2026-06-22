#ifndef PINEWOOD_RACE_H
#define PINEWOOD_RACE_H

#include <stdint.h>
#include "pins.h"

/* High-level race states reflected on status LEDs and UART output. */
typedef enum {
    RACE_IDLE = 0,   /* Waiting for start — READY LED on */
    RACE_RUNNING,    /* Timers counting — RUNNING LED on */
    RACE_FINISHED    /* All lanes done — FINISHED LED on */
} race_state_t;

void race_init(void);
void race_reset(void);
void race_poll_inputs(void);
void race_tick_times(void);

race_state_t race_state(void);
uint16_t race_lane_time(uint8_t lane);       /* Milliseconds x 1 (1 kHz ticks) */
uint8_t race_lane_running(uint8_t lane);     /* 1 while timer is counting */
uint8_t race_lane_placement(uint8_t lane); /* 0 = none yet, 1-4 = finish order */

#endif
