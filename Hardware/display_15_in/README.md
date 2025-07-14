## display_15_in
This was originally going to be a few seperate boards. I thought it would be easier and cheaper to make. 

It turns out to be cheaper to do it this way since the price of printing 3-4 boards per track and the price of 1 big one is the same. Also, with multiple boards you have to buy connectors and this 1 large board needs way less than 4 small ones.

This board connects to the main board with 1 8x2 connector and 1 12x2 connector.

### Parts
- LTS-3401LG - single 7-seg displays
- 4x TDCR1050M - quad 7-seg displays
- 20x PN2907A - cathode select bjt
- 20x 150 Ohm - mux to bjt
- 16x 47 Ohm - driver to display
- 2x 74HC138 - mux
- 2x TLC59211 - driver

#### pictures

<img src="https://github.com/user-attachments/assets/909f7e72-0a5f-46f2-8a1a-1a243212e213" width="300">

>size comparison of digits 

#### schematics
<img width="1219" height="826" alt="image" src="https://github.com/user-attachments/assets/4cb9bf95-1b1e-40a3-8243-5a72f573ad1c" />

<img width="1421" height="806" alt="image" src="https://github.com/user-attachments/assets/2d729cd5-5aa3-4c08-b62b-01f7afd81ca5" />

<img width="1121" height="772" alt="image" src="https://github.com/user-attachments/assets/c425650e-8fb8-4a01-acc2-31cd55653c25" />

<img width="952" height="772" alt="image" src="https://github.com/user-attachments/assets/f3f43ed6-036c-44b8-be7e-dc3683e3d7cc" />

#### PCB

<img width="1337" height="425" alt="image" src="https://github.com/user-attachments/assets/d95a411a-8a28-48d1-adf7-7f63b618df35" />

* the receivers will be pointing down

<img width="1484" height="586" alt="image" src="https://github.com/user-attachments/assets/27c7fcff-c3cb-446f-a2e7-b69c1fd69b7c" />


#### Log

7/12/25 - moved all of the components needed over to one project

7/13/25 - worked out connections between sheets and found connectors for mainboard. began layout (no traces)
