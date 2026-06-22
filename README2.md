# Pinewood Derby Timer — Software & Operations Guide

A four-lane pinewood derby finish-line timer built around the **STM32F091RCT6**.  
This document describes the firmware, pin map, serial interface, and day-of-race behavior.

> The original project readme is unchanged at [README.md](README.md).  
> Firmware file index: [Software/code/pinewood_program/INDEX.md](Software/code/pinewood_program/INDEX.md)

---

## What it does

- **Four independent lane timers** start together when the release lever triggers **PC11**.
- Each timer **stops** when its car breaks the IR beam at the finish (**PB11–PB14**).
- **Quad 7-segment displays** above each lane show elapsed time to **0.001 s** (e.g. `1.234`).
- **Large placement digits** show finish order (1st, 2nd, …) as each car crosses; other lanes keep counting until they finish.
- **Reset** clears times and placements (GPIO button on **PA15**, or serial `R`).
- **Status LEDs** on the mainboard: READY / RUNNING / FINISHED.
- **Serial output** over **USART5** (**PC12** TX, **PD2** RX) at 115200 baud via an **FT232RL** USB-TTL adapter.

---

## Hardware context

| Board | Role |
|-------|------|
| **mainboard** | STM32, power, JTAG, connectors, status LEDs, start/reset |
| **display_15_in** | All 7-segment displays, IR receivers, TLC59211 drivers, 74HC138 mux |

Display driving: **TLC59211** LED drivers (parallel D1–D8 + CLK) and **74HC138** decoders for digit/lane multiplexing. See KiCad schematics under `Hardware/`.

---

## Toolchain

- **MCU:** STM32F091RCT6 @ 48 MHz
- **IDE:** VS Code + PlatformIO
- **Upload:** JTAG / SWD via OpenOCD (`Software/code/pinewood_program/openocd.cfg`)
- **Serial:** FT232RL on USART5 — **PC12** (MCU TX) and **PD2** (MCU RX)

### Build

```bash
cd Software/code/pinewood_program
pio run
pio run -t upload
pio device monitor -b 115200
```

Wire FT232RL: **MCU PC12 → adapter RX**, **MCU PD2 ← adapter TX**, common GND.

---

## Pin map (MCU)

Every mask is the bit index in the GPIO port (bit *N* = pin **PN**).

### Timer displays

| Pins | Port | Lanes |
|------|------|-------|
| PB0–PB7 | GPIOB | Segment data (TLC59211 D1–D8), lanes 1–2 |
| PB8–PB10 | GPIOB | Mux A0–A2 (74HC138) |
| PC0–PC7 | GPIOC | Segment data, lanes 3–4 |
| PC8–PC10 | GPIOC | Mux A0–A2 |

### Placement displays

| Pins | Port | Role |
|------|------|------|
| PA0–PA7 | GPIOA | Segment data |
| PA8–PA10 | GPIOA | Mux A0–A2 |

### Sensors & buttons

| Pin | Hex mask | Input |
|-----|----------|--------|
| **PC11** | `0x0800` | Start — shared by all lanes |
| **PA15** | `0x8000` | Reset button *(placeholder; change in `pins.h` if routed elsewhere)* |
| **PB11** | `0x0800` | Lane 1 finish IR |
| **PB12** | `0x1000` | Lane 2 finish IR |
| **PB13** | `0x2000` | Lane 3 finish IR |
| **PB14** | `0x4000` | Lane 4 finish IR |

**Note:** **PC12** is **not** the reset button — it is **USART5_TX**.

### Serial (USART5 / “UART5”)

| Pin | Hex mask | Direction |
|-----|----------|-----------|
| **PC12** | `0x1000` | TX → FT232RL RX |
| **PD2** | `0x0004` | RX ← FT232RL TX |

### Status LEDs (active high)

| Pin | Hex mask | Meaning |
|-----|----------|---------|
| **PC13** | `0x2000` | READY (idle) |
| **PC14** | `0x4000` | RUNNING |
| **PC15** | `0x8000` | FINISHED |

Full definitions with comments: [`Software/code/pinewood_program/src/pins.h`](Software/code/pinewood_program/src/pins.h).

---

## Operation

1. Power on — **READY** LED on, serial prints `PINEWOOD READY`.
2. Press reset (or send `R`) if needed to clear a previous race.
3. Release the start lever — all four timers begin; **RUNNING** LED on; serial prints `START`.
4. As each car crosses the finish IR, that lane’s time **freezes**, placement digit appears, serial prints e.g. `FIN 1 2847 1` (lane 1, 2.847 s, 1st place).
5. When all four have finished, **FINISHED** LED on.
6. Reset for the next heat.

Lanes that have not finished continue to increment on the display; finished lanes show their frozen time and placement.

---

## Serial protocol

Baud: **115200**, 8 data bits, no parity, 1 stop bit.

### Automatic messages (MCU → PC)

```
PINEWOOD READY
START
FIN <lane> <time_ms> <place>
RESET
```

- `<lane>` — 1 to 4  
- `<time_ms>` — integer milliseconds (display as `<time_ms>/1000` seconds)  
- `<place>` — 1 to 4  

Example: `FIN 2 3102 2` → lane 2 finished second with time 3.102 s.

### Commands (PC → MCU)

| Character | Action |
|-----------|--------|
| `R` or `r` | Reset race |
| `?` | Reply with state and all lane times |

Example query response: `STATE 1 T1 1200 T2 980 T3 0 T4 0`  
(`STATE` 0=idle, 1=running, 2=finished; `T1`…`T4` in ms)

---

## Firmware architecture

```
main.c          Boot, GPIO, timers, ISRs
clock.c         48 MHz clock
pins.h          Pin map and mux constants
race.c          State machine, 1 kHz time base, placement queue
display.c       2 kHz display multiplexing
uart.c          USART5 logging and commands
font.h          7-segment patterns
```

### Timing (matches [Software/code.md](Software/code.md))

| Rate | Source | Task |
|------|--------|------|
| 1 kHz | TIM14 | Increment each running lane timer |
| 2 kHz | TIM6 | Debounce inputs; refresh timer L1–2, L3–4, placement displays |

### Time format

Internal value is an integer counting **milliseconds** at 1 kHz.  
The display always shows a decimal point after the first digit: value `1234` → **1.234**.

### Placement algorithm

Queue starts at **1234** (meaning places 1, 2, 3, 4 are still to assign):

1. Next place = `queue / 1000`
2. Update queue = `(queue % 1000) * 10`

First finisher gets **1**, second **2**, and so on.

---

## Configuration

Edit [`Software/code/pinewood_program/src/pins.h`](Software/code/pinewood_program/src/pins.h):

| Macro | Purpose |
|-------|---------|
| `RESET_PORT` / `RESET_PIN_MASK` | Reset button location (default **PA15**) |
| `BUTTON_ACTIVE_HIGH` | Set to 0 if switches pull low when pressed |
| `FINISH_SENSOR_ACTIVE_HIGH` | Set to 0 if IR pulls low when beam breaks |
| `lane*_mux_addr` presets | Tune if wrong digit or lane lights up |

---

## Troubleshooting

| Symptom | Check |
|---------|--------|
| No upload | JTAG wiring, `openocd.cfg`, power to board |
| Garbled serial | 115200 baud, TX/RX not swapped, common GND |
| Timer never starts | **PC11** start wiring and `BUTTON_ACTIVE_HIGH` |
| Lane never stops | Finish pin **PB11–PB14** and `FINISH_SENSOR_ACTIVE_HIGH` |
| Wrong display digit | Mux constants in `pins.h` (380/580/680/700 presets) |
| Reset does nothing | **PA15** routing, or use serial `R` |

---

## Repository layout

```
pinewood_timer/
├── README.md              ← original readme (do not replace)
├── README2.md             ← this file
├── Hardware/              ← KiCad PCBs and schematics
└── Software/
    ├── code.md            ← original firmware design notes
    └── code/pinewood_program/
        ├── INDEX.md       ← source file index
        ├── platformio.ini
        ├── openocd.cfg
        └── src/           ← firmware
```

---

Built for scout troops who need an accurate, affordable track timer. Good luck at the derby.
