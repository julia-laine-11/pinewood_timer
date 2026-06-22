#ifndef PINEWOOD_UART_H
#define PINEWOOD_UART_H

#include <stdint.h>

/*
 * USART5 (referred to as UART5 in docs) on:
 *   PC12 — TX, 0x1000
 *   PD2  — RX, 0x0004
 * 115200 baud, 8N1.  Connect FT232RL: MCU TX -> adapter RX, MCU RX -> adapter TX.
 */
void uart5_init(void);

void uart_log_start(void);
void uart_log_reset(void);
void uart_log_finish(uint8_t lane, uint16_t time_ms, uint8_t place);

#endif
