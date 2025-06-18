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

now i gotta decide how many timers i need for this and if the c091rct6 has enough :(

chips i was looking at:

|  chip  | timers | price |
|--------|--------|-------|
| c091rc | 7      | $2.24 |
| l010r8 | 4      | $2.25 |
| g070rb | 6      | $2.35 |
| l051r6 | 4      | $2.67 |
| l071rb | 7      | $3.62 |
| f030rc | 8      | $3.78 |

my bom is read only on this computer so i cant edit it currently :(
Resistors: (all 0805 imperial)

[56k](https://www.digikey.com/en/products/detail/koa-speer-electronics-inc/RK73B2ATTD563J/10236546)


[10k](https://www.digikey.com/en/products/detail/yageo/RC0805JR-0710KL/728241)


[1k5](https://www.digikey.com/en/products/detail/yageo/RC0805FR-071K5L/727496)


[1k](https://www.digikey.com/en/products/detail/stackpole-electronics-inc/RNCP0805FTD1K00/2240229) 

[220](https://www.digikey.com/en/products/detail/koa-speer-electronics-inc/RK73B2ATTD221J/10236562)


[150](https://www.digikey.com/en/products/detail/koa-speer-electronics-inc/RK73B2ATTD151J/10236460)


[51](https://www.digikey.com/en/products/detail/koa-speer-electronics-inc/RK73B2ATTD510J/10236476)



Capacitors:

[22uf](https://www.digikey.com/en/products/detail/samsung-electro-mechanics/CL21A226MQQNNNE/3886758)


[10uf](https://www.digikey.com/en/products/detail/kemet/C0805C103K5RACTU/411157)


[1uf](https://www.digikey.com/en/products/detail/samsung-electro-mechanics/CL21B105KBFNNNE/3886687)


[.1uf (100nf) decoupling:](https://www.digikey.com/en/products/detail/yageo/CC0805KRX7R9BB104/302874)


[10nf (10k pf, .01 uf)](https://www.digikey.com/en/products/detail/kemet/C0805C103K5RACTU/411157)


[10pf ](https://www.digikey.com/en/products/detail/yageo/CC0805JRNPO9BN100/302833)



ICs

[led driver](https://www.digikey.com/en/products/detail/texas-instruments/TLC59211IPWR/2183121)

[mux](https://www.digikey.com/en/products/detail/texas-instruments/SN74HC138DR/276836)

[3.3v reg](https://www.digikey.com/en/products/detail/texas-instruments/TLV74033PDBVR/12642183)

[16mhz osc](https://www.digikey.com/en/products/detail/ecs-inc/ECS-2520MV-160-CN-TR/9742387)



Misc

[spdt boot0](https://www.digikey.com/en/products/detail/nidec-components-corporation/CSS-1210TB/1124209
)

[ferrite bead (0805) ](https://www.digikey.com/en/products/detail/murata-electronics/BLM18KG121TN1D/1982762)


