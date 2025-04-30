#include "stm32f0xx.h"
#include <math.h>   // for M_PI
#include <stdint.h>
#include <stdio.h>


//variables
char disp[9]         = "Hello...";  //this is for the display
uint8_t col          = 0;           
uint8_t mode         = 'A';         //this is for the display
int8_t thrust_down   = 0;           //same as before
int8_t thrust_side   = 0;           //or do we need 2, one for left and one for right?
int16_t fuel         = 800;
int16_t alt          = 4500;
int16_t velo_down    = 0;
int16_t velo_side    = 0;

int main(){
    return 1;
}