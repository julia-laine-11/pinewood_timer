## Contents:


- [display_15_in](https://github.com/julia-laine-11/pinewood_timer/tree/main/Hardware/display_15_in)
*will be printed
   - whats inside:
    - kicad project
      - schematic
      - pcb
  - about:
    - combines placement_disp and timer_display_pcb since it is cheaper to put both on the same pcb - even though its so much larger
    - also includes the sensors for the end of track


- [mainboard](https://github.com/julia-laine-11/pinewood_timer/tree/main/Hardware/mainboard)
*will be printed
  - whats inside:
    - kicad project
      - schematic
      - pcb
  - about:
    - main board where the stm32f091rct6 lives
    - jst connectors to each board/input/output around the system

- [pinewood_timer](https://github.com/julia-laine-11/pinewood_timer/tree/main/Hardware/pinewood_timer)
*will *not* be printed
  - whats inside:
    - kicad project
      - schematic
      - no pcb - there are individual ones for each part of the system
  - about:
    - overall schematic of all of the systems

- [timer_display_pcb](https://github.com/julia-laine-11/pinewood_timer/tree/main/Hardware/timer_display_pcb)
*will *not* be printed
  - whats inside:
    - kicad project(s)
      - schematic
      - pcb
  - about
    - time display over each lane
    - not the actual 'timer'
      - the 'timer' is in the software
      - updates every .001 seconds
     
    - will not be printed because display_15_in will replace it
     

## Photos

### display_15_in

#### schematics
<img width="1219" height="826" alt="image" src="https://github.com/user-attachments/assets/4cb9bf95-1b1e-40a3-8243-5a72f573ad1c" />

<img width="1421" height="806" alt="image" src="https://github.com/user-attachments/assets/2d729cd5-5aa3-4c08-b62b-01f7afd81ca5" />

<img width="1121" height="772" alt="image" src="https://github.com/user-attachments/assets/c425650e-8fb8-4a01-acc2-31cd55653c25" />

<img width="952" height="772" alt="image" src="https://github.com/user-attachments/assets/f3f43ed6-036c-44b8-be7e-dc3683e3d7cc" />

#### PCB

<img width="1337" height="425" alt="image" src="https://github.com/user-attachments/assets/d95a411a-8a28-48d1-adf7-7f63b618df35" />

* the receivers will be pointing down

<img width="1484" height="586" alt="image" src="https://github.com/user-attachments/assets/27c7fcff-c3cb-446f-a2e7-b69c1fd69b7c" />


### mainboard

#### schematic

*currently has incorrect chip (L151 instead of F091)

<img width="1035" height="844" alt="image" src="https://github.com/user-attachments/assets/bb63cc30-f836-4b68-8cf4-8bbf2e25eb59" />


### timer_display_pcb 
*no longer in use

#### schematic

<img width="1112" height="847" alt="image" src="https://github.com/user-attachments/assets/92671e34-fa27-45ec-a857-133cc7a651c6" />

#### PCB

<img width="1122" height="530" alt="image" src="https://github.com/user-attachments/assets/caab6907-3968-49f7-88a2-cd96f284845b" />

<img width="1122" height="530" alt="image" src="https://github.com/user-attachments/assets/3e8145db-2857-4a3b-8103-7f1f65c161cf" />

<img width="1122" height="530" alt="image" src="https://github.com/user-attachments/assets/90ac04bd-f18d-4112-8fbe-d7dba5d5e411" />

