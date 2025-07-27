## mainboard

This board will be placed in a central location on the track. It connects to the power, reset button, start sensors, display at the end, and end sensors. I havent decided yet, but either a 12v or 5v power supply will be used to power it. 

The chip has a 5v to 3v3 regulator for power. To program it, the chip has a JTAG for the STLink and a USB-TTL. 

*currently has incorrect chip (L151 instead of F091). I was going to change what I was using, but the f091 has everything that I need and I already know how to program it. 
The L151 does not have what I need (I thought it did at first) and I would have to change my settings and upload code to be able to communicate with it.

#### Current schematic

7/26/25 - changed stm. added jtag. added usb for power. edited 3v3 supply. current schematic messy but its still in the works

<img width="1374" height="864" alt="image" src="https://github.com/user-attachments/assets/374ef408-f1aa-4cd4-b154-9ff41ccb32d6" />



Old:

Unfinished schematic

missing:
- connectors
- power in
- jtag
- usb - ttl

<img width="1035" height="844" alt="image" src="https://github.com/user-attachments/assets/bb63cc30-f836-4b68-8cf4-8bbf2e25eb59" />


