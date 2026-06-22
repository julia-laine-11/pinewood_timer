#include "display.h"
#include "race.h"
#include "font.h"
#include "pins.h"

/* Busy-wait ~n/48 MHz seconds (assembly loop from ECE362 courseware). */
static void nano_wait(unsigned int n)
{
    asm volatile(
        "        mov r0,%0\n"
        "repeat: sub r0,#83\n"
        "        bgt repeat\n"
        :
        : "r"(n)
        : "r0", "cc");
}

/*
 * Write one multiplexed digit to a display bank.
 * segments — TLC59211 D1-D8 pattern (port bits 0-7).
 * mux      — 74HC138 address + lane preset (port bits 8-10 and presets).
 */
static void write_bank(GPIO_TypeDef *port, uint8_t segments, uint16_t mux)
{
    port->ODR = (uint16_t)((port->ODR & ~DISPLAY_PIN_MASK) |
                           (segments & 0xFFU) |
                           (mux & DISPLAY_PIN_MASK));
    nano_wait(200);
}

/*
 * Convert timer count to four segment bytes.
 * Value 1234 displays as 1.234 (DP on the first digit).
 */
static void time_to_segments(uint16_t time_ms, uint8_t segs[4])
{
    segs[0] = (uint8_t)(font_digit[(time_ms / 1000U) % 10U] | FONT_DP);
    segs[1] = font_digit[(time_ms / 100U) % 10U];
    segs[2] = font_digit[(time_ms / 10U) % 10U];
    segs[3] = font_digit[time_ms % 10U];
}

/*
 * Multiplex one digit across two quad timer displays on the same GPIO bank.
 * Cycles through 8 positions (4 digits x 2 lanes) over successive calls.
 */
static void refresh_timer_pair(uint8_t lane_a, uint8_t lane_b, GPIO_TypeDef *port,
                               uint16_t (*mux_fn)(uint8_t lane, uint8_t digit))
{
    static uint8_t digit = 0;
    uint16_t mux;
    uint8_t segs[4];
    uint8_t lane = (digit < 4U) ? lane_a : lane_b;
    uint8_t lane_digit = (uint8_t)(digit & 3U);

    time_to_segments(race_lane_time(lane), segs);
    mux = mux_fn(lane, lane_digit);
    write_bank(port, segs[lane_digit], mux);

    digit = (uint8_t)((digit + 1U) % 8U);
}

/* Show one placement digit per call; blank until that lane has finished. */
static void refresh_placement(void)
{
    static uint8_t lane = 0;
    uint8_t segment = FONT_BLANK;
    uint16_t mux = placement_mux_addr(lane);

    if (race_lane_placement(lane) != 0U) {
        segment = font_digit[race_lane_placement(lane) % 10U];
    }

    write_bank(PLACEMENT_PORT, segment, mux);
    lane = (uint8_t)((lane + 1U) % NUM_LANES);
}

void display_init(void)
{
    PLACEMENT_PORT->ODR &= ~DISPLAY_PIN_MASK;
    TIMER_L12_PORT->ODR &= ~DISPLAY_PIN_MASK;
    TIMER_L34_PORT->ODR &= ~DISPLAY_PIN_MASK;
    display_set_status_leds(1, 0, 0);
}

/*
 * One step of the display round-robin (called at 2 kHz from TIM6):
 *   0 — timer lanes 1 & 2 (GPIOB)
 *   1 — timer lanes 3 & 4 (GPIOC)
 *   2 — placement digits (GPIOA)
 */
void display_refresh_step(void)
{
    static uint8_t step = 0;

    switch (step) {
    case 0:
        refresh_timer_pair(0, 1, TIMER_L12_PORT, lane12_mux_addr);
        break;
    case 1:
        refresh_timer_pair(2, 3, TIMER_L34_PORT, lane34_mux_addr);
        break;
    default:
        refresh_placement();
        break;
    }

    step = (uint8_t)((step + 1U) % 3U);
}

void display_set_status_leds(uint8_t ready, uint8_t running, uint8_t finished)
{
    uint32_t bsrr = 0;

    if (ready) {
        bsrr |= LED_READY_PIN; /* PC13 */
    } else {
        bsrr |= (uint32_t)LED_READY_PIN << 16;
    }

    if (running) {
        bsrr |= LED_RUNNING_PIN; /* PC14 */
    } else {
        bsrr |= (uint32_t)LED_RUNNING_PIN << 16;
    }

    if (finished) {
        bsrr |= LED_FINISHED_PIN; /* PC15 */
    } else {
        bsrr |= (uint32_t)LED_FINISHED_PIN << 16;
    }

    LED_READY_PORT->BSRR = bsrr;
}
