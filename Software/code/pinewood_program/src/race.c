#include "race.h"
#include "uart.h"

/* -------------------------------------------------------------------------- */
/*  Race state (see Software/code.md for variable design notes)               */
/* -------------------------------------------------------------------------- */

static race_state_t state = RACE_IDLE;
static uint16_t lane_time[NUM_LANES];       /* Counts ms at 1 kHz while running */
static uint8_t lane_running[NUM_LANES];     /* 1 = timer incrementing */
static uint8_t lane_placement[NUM_LANES];   /* Finish order, 0 until placed */
static uint16_t placement_queue = 1234;     /* Packed 1-2-3-4 queue (code.md) */

/* 8-sample shift registers for debounced edges. */
static uint8_t start_hist;
static uint8_t reset_hist;
static uint8_t finish_hist[NUM_LANES];

static int button_active(GPIO_TypeDef *port, uint32_t mask)
{
    int level = (port->IDR & mask) != 0U;
#if BUTTON_ACTIVE_HIGH
    return level;
#else
    return !level;
#endif
}

static int finish_active(GPIO_TypeDef *port, uint32_t mask)
{
    int level = (port->IDR & mask) != 0U;
#if FINISH_SENSOR_ACTIVE_HIGH
    return level;
#else
    return !level;
#endif
}

/*
 * Pop the next placement digit from the packed queue (1234 -> 2340 -> 3400 ...).
 * First finish gets 1, second gets 2, etc.
 */
static void assign_placement(uint8_t lane)
{
    if (placement_queue < 1000U) {
        return;
    }

    lane_placement[lane] = (uint8_t)(placement_queue / 1000U);
    placement_queue = (uint16_t)((placement_queue % 1000U) * 10U);
}

static void begin_race(void)
{
    uint8_t lane;

    for (lane = 0; lane < NUM_LANES; lane++) {
        lane_time[lane] = 0;
        lane_running[lane] = 1;
        lane_placement[lane] = 0;
    }

    placement_queue = 1234;
    state = RACE_RUNNING;
    uart_log_start();
}

static void finish_lane(uint8_t lane)
{
    if (state != RACE_RUNNING || !lane_running[lane]) {
        return;
    }

    lane_running[lane] = 0;
    assign_placement(lane);
    uart_log_finish(lane, lane_time[lane], lane_placement[lane]);

    {
        uint8_t lane_idx;
        uint8_t all_done = 1;

        for (lane_idx = 0; lane_idx < NUM_LANES; lane_idx++) {
            if (lane_running[lane_idx]) {
                all_done = 0;
                break;
            }
        }

        if (all_done) {
            state = RACE_FINISHED;
        }
    }
}

/* Detect a low-to-high transition after 7 stable low samples (debounce). */
static void update_button_hist(uint8_t *hist, int active, void (*on_press)(void))
{
    *hist = (uint8_t)((*hist << 1) | (active ? 1U : 0U));

    if (*hist == 0x01U) {
        on_press();
    }
}

static void on_start_press(void)
{
    if (state == RACE_IDLE || state == RACE_FINISHED) {
        begin_race();
    }
}

static void on_reset_press(void)
{
    race_reset();
    uart_log_reset();
}

void race_init(void)
{
    race_reset();
}

void race_reset(void)
{
    uint8_t lane;

    for (lane = 0; lane < NUM_LANES; lane++) {
        lane_time[lane] = 0;
        lane_running[lane] = 0;
        lane_placement[lane] = 0;
        finish_hist[lane] = 0;
    }

    placement_queue = 1234;
    state = RACE_IDLE;
    start_hist = 0;
    reset_hist = 0;
}

void race_poll_inputs(void)
{
    uint8_t lane;

    update_button_hist(&start_hist, button_active(START_PORT, START_PIN_MASK), on_start_press);
    update_button_hist(&reset_hist, button_active(RESET_PORT, RESET_PIN_MASK), on_reset_press);

    if (state != RACE_RUNNING) {
        return;
    }

    for (lane = 0; lane < NUM_LANES; lane++) {
        int active = finish_active(FINISH_PORT, FINISH_LANE_MASK(lane));
        finish_hist[lane] = (uint8_t)((finish_hist[lane] << 1) | (active ? 1U : 0U));

        if (finish_hist[lane] == 0x01U) {
            finish_lane(lane);
        }
    }
}

void race_tick_times(void)
{
    uint8_t lane;

    if (state != RACE_RUNNING) {
        return;
    }

    for (lane = 0; lane < NUM_LANES; lane++) {
        if (lane_running[lane]) {
            lane_time[lane]++;
        }
    }
}

race_state_t race_state(void)
{
    return state;
}

uint16_t race_lane_time(uint8_t lane)
{
    return lane_time[lane];
}

uint8_t race_lane_running(uint8_t lane)
{
    return lane_running[lane];
}

uint8_t race_lane_placement(uint8_t lane)
{
    return lane_placement[lane];
}
