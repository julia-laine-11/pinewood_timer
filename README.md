# pinewood_timer
Timer system for a pinewood derby track. My grandma asked me to help her make one since her boy scout troop's track does not have one. I currently havent seen it yet but I want to be able to tell her what I can do when I get home

Main schematic
Timer Display
Placement Display
End of track sensors
Mainboard

#### requirements for sure:
- be able to be operated by random people
- 4 lanes
- time to the thousandths
- display placement

(for a total of 20 7-seg displays)

each lane:
    - stop sensor
    - start sensor? or are they uniformly released
    - 4 small seven seg displays (probs a TDCR1050M)
    - 1 larger seven seg display
    
- 3 tlc59211 shift reg (display bits to 8 segment displays each)
- 3 74HC138 to multiplex the signal
- 20 pn2907a one for each display's anode
- 20 150 ohm resistors

pins needed:
- 3 per 74hc138  (9)
- 7 per tlc59211 (21)
- 1 per sensor   (8 max, 4 min) //probs at least 1 adc too if the sensor returns an analog value



Sensors
- it looks like the stop sensors go below the track (ir sensors)
- online, a derby timer company uses a microswitch attached to the lever to start the timer

- ir transceiver instead of ir led and receiver

    - transceiver : 5.09
    - led and receiver: 2.00


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

chips i was looking at:

|  chip  | timers | price |
|--------|--------|-------|
| c091rc | 7      | $2.24 |
| l010r8 | 4      | $2.25 |
| g070rb | 6      | $2.35 |
| l051r6 | 4      | $2.67 |
| l071rb | 7      | $3.62 |
| f030rc | 8      | $3.78 |
