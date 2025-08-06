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
<img width="1577" height="540" alt="image" src="https://github.com/user-attachments/assets/4acf42a8-fe9e-420e-8e30-5f6940c504da" />

<img width="1577" height="540" alt="image" src="https://github.com/user-attachments/assets/5f2f6020-4e9b-46b8-8be1-b808064010df" />

<img width="1577" height="540" alt="image" src="https://github.com/user-attachments/assets/0f0b0fa2-d67a-4a51-8a10-5d71a757d872" />

<img width="1577" height="540" alt="image" src="https://github.com/user-attachments/assets/21049428-7b66-4496-b260-d3b44a39e3a4" />

<img width="1577" height="540" alt="image" src="https://github.com/user-attachments/assets/acb07117-1993-43da-a77d-488e5d2033b3" />

### mainboard

#### schematic

<img width="1109" height="841" alt="image" src="https://github.com/user-attachments/assets/281be70b-1868-41b1-8632-9cac5c3f1af1" />

<img width="1049" height="791" alt="image" src="https://github.com/user-attachments/assets/477778b3-7c6f-4745-98e7-b9e6f5804d1c" />

<img width="1049" height="791" alt="image" src="https://github.com/user-attachments/assets/bc40e94c-8b9d-430a-8455-4db56607758b" />


#### PCB
<img width="500" height="438" alt="image" src="https://github.com/user-attachments/assets/c72feb9e-f3e9-44c3-a7d2-8d4260fce444" />
<img width="500" height="438" alt="image" src="https://github.com/user-attachments/assets/086f51fa-faa2-488a-a093-5fe30ccb2991" />

<img width="500" height="438" alt="image" src="https://github.com/user-attachments/assets/9628d736-04cb-4d13-aada-4962555546cc" />
<img width="500" height="438" alt="image" src="https://github.com/user-attachments/assets/51526eda-7071-415c-b5b4-eac5f7fa2285" />

<img width="500" height="438" alt="image" src="https://github.com/user-attachments/assets/88018b64-2d49-4cc5-8384-c4de74556ddc" />
<img width="500" height="438" alt="image" src="https://github.com/user-attachments/assets/8f435b2e-8e66-40a3-b62a-6591dd0b8d57" />

<img width="1065" height="832" alt="image" src="https://github.com/user-attachments/assets/2f34e330-9f5f-44d3-97ac-f0cb4f65d8c2" />
<img width="1065" height="832" alt="image" src="https://github.com/user-attachments/assets/fd652a88-4569-41e9-b157-b8150bf279ed" />


### timer_display_pcb 
*no longer in use

#### schematic

<img width="1112" height="847" alt="image" src="https://github.com/user-attachments/assets/92671e34-fa27-45ec-a857-133cc7a651c6" />

#### PCB

<img width="1122" height="530" alt="image" src="https://github.com/user-attachments/assets/caab6907-3968-49f7-88a2-cd96f284845b" />

<img width="1122" height="530" alt="image" src="https://github.com/user-attachments/assets/3e8145db-2857-4a3b-8103-7f1f65c161cf" />

<img width="1122" height="530" alt="image" src="https://github.com/user-attachments/assets/90ac04bd-f18d-4112-8fbe-d7dba5d5e411" />


