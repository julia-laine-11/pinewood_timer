#include "stm32f0xx.h"
#include <math.h>   // for M_PI
#include <stdint.h>
#include <stdio.h>


void init_everything(){
    RCC -> AHBENR  |= RCC_AHBENR_GPIOAEN;
    GPIOA -> MODER &= ~0xFFC00000;



}



int main(){
    return 1;
}