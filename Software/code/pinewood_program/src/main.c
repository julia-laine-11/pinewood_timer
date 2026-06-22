#include "stm32f0xx.h"
#include <stdint.h>
#include <stdio.h>

#include "display.h"
#include "race.h"
#include "pins.h"
#include "uart.h"

void internal_clock(void);

static void enable_gpio_clocks(void)
{
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN | RCC_AHBENR_GPIOBEN | RCC_AHBENR_GPIOCEN;
    /* GPIOD enabled in uart5_init() for PD2 RX. */
}

/*
 * Configure PA0-PA10 (or PB/PC) as outputs:
 * MODER nibble pattern 0101 0101 0101 0101 0100 = output on pins 0-10.
 */
static void configure_display_port(GPIO_TypeDef *port)
{
    port->MODER &= ~0x03FF03FFU;
    port->MODER |= 0x01540154U;
}

static void configure_inputs(void)
{
    /* PB11-PB14 finish sensors — input with pull-up. */
    FINISH_PORT->MODER &= ~0x3C000000U;
    FINISH_PORT->PUPDR &= ~0x3C000000U;
    FINISH_PORT->PUPDR |= 0x28000000U;

    /* PC11 start switch — input with pull-up. */
    START_PORT->MODER &= ~(3U << (11U * 2U));
    START_PORT->PUPDR &= ~(3U << (11U * 2U));
    START_PORT->PUPDR |= (1U << (11U * 2U));

    /* PA15 reset button — input with pull-up (PC12 is UART5_TX). */
    RESET_PORT->MODER &= ~(3U << (15U * 2U));
    RESET_PORT->PUPDR &= ~(3U << (15U * 2U));
    RESET_PORT->PUPDR |= (1U << (15U * 2U));
}

static void configure_status_leds(void)
{
    /* PC13, PC14, PC15 — outputs, start off. */
    GPIOC->MODER &= ~0xFC000000U;
    GPIOC->MODER |= 0x54000000U;
    GPIOC->ODR &= ~(LED_READY_PIN | LED_RUNNING_PIN | LED_FINISHED_PIN);
}

/* TIM14 — 48 MHz / 48 / 1000 = 1 kHz lane time ticks. */
static void setup_tim14(void)
{
    RCC->APB1ENR |= RCC_APB1ENR_TIM14EN;

    TIM14->PSC = 48U - 1U;
    TIM14->ARR = 1000U - 1U;
    TIM14->DIER |= TIM_DIER_UIE;
    NVIC->ISER[0] = (1U << TIM14_IRQn);
    TIM14->CR1 |= TIM_CR1_CEN;
}

/* TIM6 — 48 MHz / 48 / 500 = 2 kHz sensor poll + display mux. */
static void setup_tim6(void)
{
    RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;

    TIM6->PSC = 48U - 1U;
    TIM6->ARR = 500U - 1U;
    TIM6->DIER |= TIM_DIER_UIE;
    NVIC->ISER[0] = (1U << TIM6_DAC_IRQn);
    TIM6->CR1 |= TIM_CR1_CEN;
}

static void update_status_leds(void)
{
    switch (race_state()) {
    case RACE_IDLE:
        display_set_status_leds(1, 0, 0);
        break;
    case RACE_RUNNING:
        display_set_status_leds(0, 1, 0);
        break;
    case RACE_FINISHED:
        display_set_status_leds(0, 0, 1);
        break;
    }
}

void TIM14_IRQHandler(void)
{
    TIM14->SR &= ~TIM_SR_UIF;
    race_tick_times();
}

void TIM6_DAC_IRQHandler(void)
{
    TIM6->SR &= ~TIM_SR_UIF;
    race_poll_inputs();
    display_refresh_step();
    update_status_leds();
}

int main(void)
{
    internal_clock();
    enable_gpio_clocks();

    configure_display_port(PLACEMENT_PORT);
    configure_display_port(TIMER_L12_PORT);
    configure_display_port(TIMER_L34_PORT);
    configure_inputs();
    configure_status_leds();

    race_init();
    display_init();
    uart5_init();

    setup_tim14();
    setup_tim6();

    puts("PINEWOOD READY\r\n");

    while (1) {
        __WFI();
    }
}
