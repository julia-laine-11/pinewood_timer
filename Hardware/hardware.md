## Contents:

- [breakout_board](https://github.com/julia-laine-11/pinewood_timer/tree/main/Hardware/breakout_board)
  - whats inside:
    - kicad project
      - schematic
      - pcb
  - about:
    - main board where the stm32f091rct6 lives
    - jst connectors to each board/input/output around the system

- [display_15_in](https://github.com/julia-laine-11/pinewood_timer/tree/main/Hardware/display_15_in)
  - whats inside:
    - kicad project
      - schematic
      - pcb
  - about:
    - combines placement_disp and timer_display_pcb since it is cheaper to put both on the same pcb - even though its so much larger
    - also includes the sensors for the end of track

- [pinewood_timer](https://github.com/julia-laine-11/pinewood_timer/tree/main/Hardware/pinewood_timer)
  - whats inside:
    - kicad project
      - schematic
      - no pcb - there are individual ones for each part of the system
  - about:
    - overall schematic of all of the systems
      
- [placement_disp](https://github.com/julia-laine-11/pinewood_timer/tree/main/Hardware/placement_disp)
  - whats inside:
    - readme
  - about:
    - placement display over each lane
    - 4x 7-seg displays 1 inch tall
      
- [timer_display_pcb](https://github.com/julia-laine-11/pinewood_timer/tree/main/Hardware/timer_display_pcb)
  - whats inside:
    - kicad project(s)
      - schematic
      - pcb
  - about
    - time display over each lane
    - not the actual 'timer'
      - the 'timer' is in the software
      - updates every .001 seconds
     

## Photos

### breakout_board
