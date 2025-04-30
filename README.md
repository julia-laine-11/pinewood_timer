# pinewood_timer
Timer system for a pinewood derby track. My grandma asked me to help her make one since her boy scout troop's track does not have one. I currently havent seen it yet but I want to be able to tell her what I can do when I get home

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



https://www.st.com/content/st_com/en/stm32-mcu-developer-zone/mcu-portfolio.html

Sensors
- it looks like the stop sensors go below the track (ir sensors)
- online, a derby timer company uses a microswitch attached to the lever to start the timer

- ir transceiver instead of ir led and receiver

    - transceiver : 5.09
    - led and receiver: 2.00

    
    
