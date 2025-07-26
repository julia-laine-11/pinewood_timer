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

Updated:

- still needs
  - power and ground traces
  - drill holes for mounting
  - test points

<img width="1580" height="520" alt="image" src="https://github.com/user-attachments/assets/d8a26ed5-c3b9-41e5-bfd3-bb7db28228ed" />

<img width="1580" height="520" alt="image" src="https://github.com/user-attachments/assets/c76ade93-dba6-412e-a0c0-d625e25c8b5a" />

<img width="1580" height="520" alt="image" src="https://github.com/user-attachments/assets/4c7d8327-6291-4680-8b2d-1e896bc45c61" />

<img width="1288" height="474" alt="image" src="https://github.com/user-attachments/assets/3869232f-928e-4960-aeb8-e45214dde6c2" />

<img width="1852" height="926" alt="image" src="https://github.com/user-attachments/assets/786e9d03-2366-467e-baa3-49f028db93bb" />


All traces routed (for now)

<img width="1577" height="540" alt="image" src="https://github.com/user-attachments/assets/4acf42a8-fe9e-420e-8e30-5f6940c504da" />

<img width="1577" height="540" alt="image" src="https://github.com/user-attachments/assets/5f2f6020-4e9b-46b8-8be1-b808064010df" />

<img width="1577" height="540" alt="image" src="https://github.com/user-attachments/assets/0f0b0fa2-d67a-4a51-8a10-5d71a757d872" />

<img width="1577" height="540" alt="image" src="https://github.com/user-attachments/assets/21049428-7b66-4496-b260-d3b44a39e3a4" />

<img width="1577" height="540" alt="image" src="https://github.com/user-attachments/assets/acb07117-1993-43da-a77d-488e5d2033b3" />



#### Log

7/12/25 - moved all of the components needed over to one project

7/13/25 - worked out connections between sheets and found connectors for mainboard. began layout (no traces)

7/19/25 - laying more traces and revising old ones. i am starting to hate the connector but i must use it

<img width="473" height="296" alt="image" src="https://github.com/user-attachments/assets/27d0d57a-237c-408e-8229-7ba29f3d0f83" />

7/20/25 - sorted out the connector from hell. well, i at least made it better. i also discovered the "distribute evenly" and "align" functions

<img width="403" height="256" alt="image" src="https://github.com/user-attachments/assets/6993aa78-a049-4b92-b40a-ac1c6fdc106a" />

7/25/25 - finished traces, added test points

<img width="408" height="184" alt="image" src="https://github.com/user-attachments/assets/e4a56572-b35b-4585-aa7f-af17a3c7ff8c" />




