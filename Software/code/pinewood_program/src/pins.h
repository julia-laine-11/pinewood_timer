#ifndef PINEWOOD_PINS_H
#define PINEWOOD_PINS_H

#include "stm32f0xx.h"
#include <stdint.h>

/*
 * ============================================================================
 *  Pinewood Derby Timer — GPIO map (STM32F091RCT6)
 * ============================================================================
 *
 *  All pin names refer to the MCU package pin function.
 *  Hex masks are bit positions in the port ODR/IDR/BSRR (bit N = PN).
 *
 *  Display data uses TLC59211 parallel inputs D1-D8 (port bits 0-7) plus
 *  74HC138 mux address A0-A2 (port bits 8-10).  Eleven pins per bank.
 *
 *  See INDEX.md and README2.md for full software documentation.
 * ============================================================================
 */

#define NUM_LANES 4

/* -------------------------------------------------------------------------- */
/*  Placement display — GPIOA PA0 .. PA10 (11 pins)                           */
/* -------------------------------------------------------------------------- */
#define PLACEMENT_PORT GPIOA

/* Bits PA0-PA10 enabled: 0x07FF */
#define DISPLAY_PIN_MASK 0x07FFU /* PA0=bit0 .. PA10=bit10 */

/* PA0  — TLC59211 D1 / segment bus bit 0 */
/* PA1  — TLC59211 D2 / segment bus bit 1 */
/* PA2  — TLC59211 D3 / segment bus bit 2 */
/* PA3  — TLC59211 D4 / segment bus bit 3 */
/* PA4  — TLC59211 D5 / segment bus bit 4 */
/* PA5  — TLC59211 D6 / segment bus bit 5 */
/* PA6  — TLC59211 D7 / segment bus bit 6 */
/* PA7  — TLC59211 D8 / segment bus bit 7 */
/* PA8  — 74HC138 A0 (mux bit 0) */
/* PA9  — 74HC138 A1 (mux bit 1) */
/* PA10 — 74HC138 A2 (mux bit 2) */

/* -------------------------------------------------------------------------- */
/*  Timer display lanes 1 & 2 — GPIOB PB0 .. PB10                             */
/* -------------------------------------------------------------------------- */
#define TIMER_L12_PORT GPIOB

/* PB0  — TLC59211 D1 / segment bus bit 0 */
/* PB1  — TLC59211 D2 */
/* PB2  — TLC59211 D3 */
/* PB3  — TLC59211 D4 */
/* PB4  — TLC59211 D5 */
/* PB5  — TLC59211 D6 */
/* PB6  — TLC59211 D7 */
/* PB7  — TLC59211 D8 */
/* PB8  — 74HC138 A0 (mux bit 0) */
/* PB9  — 74HC138 A1 (mux bit 1) */
/* PB10 — 74HC138 A2 (mux bit 2) */

/* -------------------------------------------------------------------------- */
/*  Timer display lanes 3 & 4 — GPIOC PC0 .. PC10                             */
/* -------------------------------------------------------------------------- */
#define TIMER_L34_PORT GPIOC

/* PC0  — TLC59211 D1 / segment bus bit 0 */
/* PC1  — TLC59211 D2 */
/* PC2  — TLC59211 D3 */
/* PC3  — TLC59211 D4 */
/* PC4  — TLC59211 D5 */
/* PC5  — TLC59211 D6 */
/* PC6  — TLC59211 D7 */
/* PC7  — TLC59211 D8 */
/* PC8  — 74HC138 A0 (mux bit 0) */
/* PC9  — 74HC138 A1 (mux bit 1) */
/* PC10 — 74HC138 A2 (mux bit 2) */

/* -------------------------------------------------------------------------- */
/*  Race control inputs                                                         */
/* -------------------------------------------------------------------------- */

/* PC11 — start lever / release switch, mask 0x0800 (bit 11) */
#define START_PORT     GPIOC
#define START_PIN_MASK (1U << 11) /* PC11, 0x0800 */

/*
 * PA15 — reset button (placeholder until mainboard routing is final).
 * Mask 0x8000 (bit 15).  PC12 is reserved for UART5_TX.
 */
#define RESET_PORT     GPIOA
#define RESET_PIN_MASK (1U << 15) /* PA15, 0x8000 */

/* Finish-line IR receivers — GPIOB PB11 .. PB14, one per lane */
#define FINISH_PORT GPIOB

#define FINISH_LANE_MASK(lane) (1U << (11 + (lane)))
/* Lane 1: PB11  0x0800  (bit 11) */
/* Lane 2: PB12  0x1000  (bit 12) */
/* Lane 3: PB13  0x2000  (bit 13) */
/* Lane 4: PB14  0x4000  (bit 14) */

/* -------------------------------------------------------------------------- */
/*  UART5 — FT232RL USB-TTL (not used as GPIO)                                 */
/* -------------------------------------------------------------------------- */
/* PC12 — USART5_TX, AF2, mask 0x1000 (bit 12) — see uart.c */
/* PD2  — USART5_RX, AF2, mask 0x0004 (bit 2)  — see uart.c */

/* -------------------------------------------------------------------------- */
/*  Status LEDs on mainboard — GPIOC PC13 .. PC15, active high                */
/* -------------------------------------------------------------------------- */
#define LED_READY_PORT    GPIOC
#define LED_RUNNING_PORT  GPIOC
#define LED_FINISHED_PORT GPIOC

#define LED_READY_PIN    (1U << 13) /* PC13, 0x2000 */
#define LED_RUNNING_PIN  (1U << 14) /* PC14, 0x4000 */
#define LED_FINISHED_PIN (1U << 15) /* PC15, 0x8000 */

/* -------------------------------------------------------------------------- */
/*  Sensor polarity (change if hardware inverts)                              */
/* -------------------------------------------------------------------------- */
/* 1 = pressed / beam-broken reads logic high.  0 = active low. */
#define BUTTON_ACTIVE_HIGH        1
#define FINISH_SENSOR_ACTIVE_HIGH 1

/* -------------------------------------------------------------------------- */
/*  Display mux helpers                                                       */
/* -------------------------------------------------------------------------- */

/* Shift digit index (0-7) onto mux pins PA8/PB8/PC8 .. PA10/PB10/PC10. */
#define MUX_ADDR(digit) (((uint32_t)(digit) & 0x07U) << 8)

/*
 * Full ODR patterns for each lane (segment + mux preset from bring-up).
 * Decimal values from original notes: 380, 580, 680, 700.
 */
static inline uint16_t lane12_mux_addr(uint8_t lane, uint8_t digit)
{
    static const uint16_t lane_base[2] = {
        0x017CU, /* 380 dec — lane 1, PB2-PB8 pattern */
        0x0244U  /* 580 dec — lane 2 */
    };
    return (uint16_t)(lane_base[lane & 1U] + MUX_ADDR(digit));
}

static inline uint16_t lane34_mux_addr(uint8_t lane, uint8_t digit)
{
    static const uint16_t lane_base[2] = {
        0x02A8U, /* 680 dec — lane 3 */
        0x02BCU  /* 700 dec — lane 4 */
    };
    return (uint16_t)(lane_base[lane & 1U] + MUX_ADDR(digit));
}

static inline uint16_t placement_mux_addr(uint8_t lane)
{
    static const uint16_t lane_mux[4] = {
        0x017CU, /* 380 — placement lane 1, PA2-PA8 */
        0x0244U, /* 580 — placement lane 2 */
        0x02A8U, /* 680 — placement lane 3 */
        0x02BCU  /* 700 — placement lane 4 */
    };
    return lane_mux[lane];
}

#endif
