I am using an stm32f091rct6 for this project
- vscode with platformio extension
- jtag and usb to ttl



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

control 

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
