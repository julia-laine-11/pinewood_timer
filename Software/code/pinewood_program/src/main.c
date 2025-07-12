#include "stm32f0xx.h"
#include <stdint.h>
#include <stdio.h>

int disp[4] = {1, 2, 3, 4};


//1
//110

//2
//1011011

//3
//0b1001111

//4
//0b1100110

void enable_ports() {
    RCC -> AHBENR |= RCC_AHBENR_GPIOAEN;

    //segments
    GPIOA -> MODER &=  ~0x3FFF;
    GPIOA -> MODER |=   0x1555;

    //enable
    // 0000 0000 0000 0000 0000 0000 0000 0000
    // 1514 1312 1110 0908 0706 0504 0302 0100
    // ---- ---- 0101 0101 ---- ---- ---- ----
    GPIOA -> MODER &= ~0xFF0000;
    GPIOA -> MODER |=  0x550000;
}

int main(){

    internal_clock();
    enable_ports();
    // 0000 0000 0000 0000
    //       098 7654 3210
    // ---- -111 1
    GPIOA -> BSRR = 0b1000000000;
    GPIOA -> BSRR = 0b110;
    
    return 1;
}