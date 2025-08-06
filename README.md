# pinewood_timer
Timer system for a pinewood derby track. My grandma asked me to help her make one since her boy scout troop's track does not have one. I hope that I can make these more affordable so that her troop and other troops can get accurate timers that dont cost an arm and a leg.

*so whats in here?*
### [Hardware:](https://github.com/julia-laine-11/pinewood_timer/tree/main/Hardware)
* display_15_in
    - schematic
    - pcb
    - holds all the 7-segment displays and sensor receivers at the end of the track

* mainboard
    - schematic
    - pcb
    - holds the brains for the system
    - also where the power cable goes
  
 
### [Software:](https://github.com/julia-laine-11/pinewood_timer/blob/main/Software/code.md)
  - readme
* [Program](https://github.com/julia-laine-11/pinewood_timer/tree/main/Software/code/pinewood_program)
  - platformio project

### Overview
#### Overall Requirements
- easy operation -> plug and play
- 4 lanes
- time to the thousandths
- displays time in each lane
- displays placement in each lane
- cost less than $100-$120
    - <img width="459" height="646" alt="image" src="https://github.com/user-attachments/assets/b4fa9edf-ac52-48f1-865a-c8efdee930d3" />


##### Requirements per each lane
- start sensor - same trigger for all lanes
- stop sensor - seperate per each lane
- time display - 4 seven seg displays
- placement display - 1 larger seven seg display

##### Sensors
- Start sensor triggered by lever release
  - Microswitch is easy to install and get output from
  - I have to wait and see what my grandfather builds as the start mechanism
- Stop sensor - IR LED and IR Receiver
  - Sits in the middle of the groove the cars ride on underneath the finish line
  - Since it will likely be in a gym, the IR receiver should point down for less interference from the large lamps
  - A comparator or the STM ADC can be used if the voltage doesnt drop to an amount the STM recognizes as 0
