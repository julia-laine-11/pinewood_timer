# Pinewood Timer — Software Index

Documentation map for the PlatformIO firmware in this folder.  
For project background and hardware overview, see [README2.md](../../README2.md) at the repo root.

---

## Quick links

| Document | Purpose |
|----------|---------|
| [README2.md](../../README2.md) | Full project readme (software + operation) |
| [../code.md](../code.md) | Original design notes (variables, timing plan) |
| [../../README.md](../../README.md) | Original repo readme (unchanged) |
| [platformio.ini](platformio.ini) | Build, upload, and monitor settings |
| [openocd.cfg](openocd.cfg) | JTAG / SWD upload via OpenOCD |
| [src/pins.h](src/pins.h) | **Authoritative GPIO pin map** |

---

## Source files

| File | Role |
|------|------|
| [src/main.c](src/main.c) | Entry point, GPIO setup, timer init, ISR wiring |
| [src/clock.c](src/clock.c) | 48 MHz PLL from internal HSI |
| [src/pins.h](src/pins.h) | Pin names, masks, mux presets, polarity flags |
| [src/race.c](src/race.c) | Race state machine, timers, placement queue, sensor debounce |
| [src/race.h](src/race.h) | Public race API and `race_state_t` enum |
| [src/display.c](src/display.c) | 7-segment multiplexing (TLC59211 + 74HC138) |
| [src/display.h](src/display.h) | Display driver API |
| [src/font.h](src/font.h) | Segment patterns for digits 0–9 |
| [src/uart.c](src/uart.c) | USART5 serial (PC12 TX, PD2 RX), `printf` retarget |
| [src/uart.h](src/uart.h) | UART init and race log helpers |

---

## Interrupts and timing

| IRQ handler | Timer | Rate | Work |
|-------------|-------|------|------|
| `TIM14_IRQHandler` | TIM14 | **1 kHz** | Increment running lane times |
| `TIM6_DAC_IRQHandler` | TIM6 | **2 kHz** | Poll start/reset/finish inputs; mux displays; update status LEDs |
| `USART3_4_5_6_IRQHandler` | USART5 | async | Handle serial commands (`R`, `?`) |

System clock: **48 MHz** (`board_build.f_cpu` in `platformio.ini`).

---

## GPIO summary

### Displays (output)

| Bank | MCU pins | Function |
|------|----------|----------|
| Placement | **PA0–PA10** | 4 large placement digits |
| Timer L1–L2 | **PB0–PB10** | Quad 7-seg timers, lanes 1 & 2 |
| Timer L3–L4 | **PC0–PC10** | Quad 7-seg timers, lanes 3 & 4 |

Each bank: **PA/PB/PC 0–7** = segment data, **8–10** = 74HC138 mux A0–A2.

### Inputs

| Pin | Mask | Function |
|-----|------|----------|
| **PC11** | `0x0800` | Start lever (all lanes) |
| **PA15** | `0x8000` | Reset button (placeholder pin) |
| **PB11** | `0x0800` | Lane 1 finish IR |
| **PB12** | `0x1000` | Lane 2 finish IR |
| **PB13** | `0x2000` | Lane 3 finish IR |
| **PB14** | `0x4000` | Lane 4 finish IR |

### UART5 (FT232RL)

| Pin | Mask | Function |
|-----|------|----------|
| **PC12** | `0x1000` | USART5_TX → adapter RX |
| **PD2** | `0x0004` | USART5_RX ← adapter TX |

### Status LEDs (output, active high)

| Pin | Mask | LED |
|-----|------|-----|
| **PC13** | `0x2000` | READY |
| **PC14** | `0x4000` | RUNNING |
| **PC15** | `0x8000` | FINISHED |

---

## Serial protocol (115200 8N1)

**MCU → PC (automatic on events)**

| Line | Meaning |
|------|---------|
| `PINEWOOD READY` | Boot complete |
| `START` | Race started |
| `FIN <lane> <time> <place>` | Lane finished (lane 1–4, time in ms, place 1–4) |
| `RESET` | Race cleared |

**PC → MCU (send single character)**

| Key | Action |
|-----|--------|
| `R` or `r` | Reset race |
| `?` | Print state and four lane times |

---

## Race logic (from `code.md`)

- **Time** — 16-bit counter per lane; +1 every 1 ms while running. Display as **d.ddd** (e.g. `1234` → **1.234** s).
- **Placement queue** — starts at `1234`; each finish takes `queue/1000` as place, then `queue = (queue % 1000) * 10`.
- **Running flag** — per lane; cleared when that lane’s IR triggers.
- **States** — `IDLE` → `RUNNING` → `FINISHED` (or back to `IDLE` on reset).

---

## Build and upload

```bash
cd Software/code/pinewood_program
pio run
pio run -t upload
pio device monitor
```

Upload uses OpenOCD + JTAG (`openocd.cfg`). Serial monitor: **115200** baud.

---

## Tuning checklist

1. **Wrong digit / lane on display** — edit mux presets in [src/pins.h](src/pins.h) (`0x017C`, `0x0244`, `0x02A8`, `0x02BC`).
2. **Sensor polarity wrong** — set `BUTTON_ACTIVE_HIGH` / `FINISH_SENSOR_ACTIVE_HIGH` in [src/pins.h](src/pins.h).
3. **Reset pin moved** — update `RESET_PORT` / `RESET_PIN_MASK` in [src/pins.h](src/pins.h) (PC12 is UART TX).
4. **No serial** — check FT232 wiring to PC12/PD2 and COM port in PlatformIO monitor.
