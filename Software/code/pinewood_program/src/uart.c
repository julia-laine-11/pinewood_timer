#include "uart.h"
#include "pins.h"
#include "race.h"

#include <stdio.h>

static void uart5_write_byte(uint8_t byte)
{
    while ((USART5->ISR & USART_ISR_TXE) == 0U) {
    }
    USART5->TDR = byte;
}

void uart5_init(void)
{
    RCC->AHBENR |= RCC_AHBENR_GPIOCEN | RCC_AHBENR_GPIODEN;
    RCC->APB1ENR |= RCC_APB1ENR_USART5EN;

    /* PC12 — USART5_TX, AF2, 0x1000 */
    GPIOC->MODER &= ~(3U << (12U * 2U));
    GPIOC->MODER |= (2U << (12U * 2U));
    GPIOC->AFR[1] = (GPIOC->AFR[1] & ~(0xFU << ((12U - 8U) * 4U))) | (2U << ((12U - 8U) * 4U));

    /* PD2 — USART5_RX, AF2, 0x0004 */
    GPIOD->MODER &= ~(3U << (2U * 2U));
    GPIOD->MODER |= (2U << (2U * 2U));
    GPIOD->AFR[0] = (GPIOD->AFR[0] & ~(0xFU << (2U * 4U))) | (2U << (2U * 4U));

    USART5->BRR = 48000000UL / 115200UL;
    USART5->CR1 = USART_CR1_TE | USART_CR1_RE | USART_CR1_RXNEIE | USART_CR1_UE;

    NVIC->ISER[0] = (1U << USART3_4_5_6_IRQn);
}

static void uart5_handle_rx(uint8_t byte)
{
    switch (byte) {
    case 'r':
    case 'R':
        race_reset();
        uart_log_reset();
        break;
    case '?':
        printf("STATE %u T1 %u T2 %u T3 %u T4 %u\r\n",
               (unsigned)race_state(),
               (unsigned)race_lane_time(0),
               (unsigned)race_lane_time(1),
               (unsigned)race_lane_time(2),
               (unsigned)race_lane_time(3));
        break;
    default:
        break;
    }
}

void uart_log_start(void)
{
    puts("START\r\n");
}

void uart_log_reset(void)
{
    puts("RESET\r\n");
}

void uart_log_finish(uint8_t lane, uint16_t time_ms, uint8_t place)
{
    printf("FIN %u %u %u\r\n",
           (unsigned)(lane + 1U),
           (unsigned)time_ms,
           (unsigned)place);
}

int _write(int file, char *ptr, int len)
{
    (void)file;
    for (int i = 0; i < len; i++) {
        uart5_write_byte((uint8_t)ptr[i]);
    }
    return len;
}

void USART3_4_5_6_IRQHandler(void)
{
    if ((USART5->ISR & USART_ISR_RXNE) != 0U) {
        uart5_handle_rx((uint8_t)USART5->RDR);
    }
}
