# pinewood_timer
Timer system for a pinewood derby track. My grandma asked me to help her make one since her boy scout troop's track does not have one. I currently havent seen it yet but I want to be able to tell her what I can do when I get home

* [Main schematic](https://github.com/julia-laine-11/pinewood_timer/tree/main/pinewood_timer)
  - kicad project
* [Timer Display](https://github.com/julia-laine-11/pinewood_timer/blob/main/timer_display_pcb/tim_disp.md)
  - kicad project
  - readme
* [Placement Display](https://github.com/julia-laine-11/pinewood_timer/blob/main/placement_disp/plc_dsp.md)
  - readme
* End of track sensors
  - nothing yet
* Mainboard
  - nothing yet

### Overview
#### Overall Requirements
- easy operation -> plug and play
- 4 lanes
- time to the thousandths
- displays time in each lane
- displays placement in each lane

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


vars

- 1x placement -> int 1234
  
    when ir sensor crossed 
    1234 / 1000 (as an int) gives 1st number
    to update: (1234 % 1000) * 10 brings it to 2340 and its ready for the next one

- 4x times -> int xxxx
  
    dp is always on so i dont have to deal with decimals :)
    counts up to 1 with each 1khz tick
        starts -> interrupt enabled by lever
        stops  -> interrupt disabled by lever

- 4x running -> 1 or 0
      0 at reset
      1 when lever
      0 when ir crossed


things to control

faster than 1khz (probs 2k is ok)
- check lever
- check ir lane 1 
- check ir lane 2
- check ir lane 3
- check ir lane 4

faster than updates (1k < refresh rate < 2k)
- run lanes 1 & 2 disp
- run lanes 2 & 3 disp
- run score disp

exactly 1khz
- update time for each lane
