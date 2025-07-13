#include "stm32f0xx.h"
#include <stdint.h>
#include <stdio.h>

int disp[4] = {1, 2, 3, 4};
//      0x06, 0x5B, 0x4F, 0x66

void enable_ports() {
    RCC -> AHBENR |= RCC_AHBENR_GPIOAEN;

    //segments
    GPIOA -> MODER &=  ~0x3FFF;
    GPIOA -> MODER |=   0x1555;

    //enable
    // 0000 0000 0000 0000 0000 0000 0000 0000
    // 1514 1312 1110 0908 0706 0504 0302 0100
    // ---- ---- 0101 0101 ---- ---- ---- ----
    GPIOA -> MODER &= ~0xFFF000;
    GPIOA -> MODER |=  0x555000;
}


//-------------------------------
// Timer 14 ISR goes here
//-------------------------------
// TODO
void TIM14_IRQHandler(){
  //acknowledge the interrupt
  TIM14 -> SR &= ~TIM_SR_UIF;  
  //call update_variables
  update_variables();
  //call write_display
  write_display();
}


void setup_tim14() {
  RCC -> APB1ENR |= RCC_APB1ENR_TIM14EN;

  // invoke an update interrupt twice per second (2 Hz).
  TIM14 -> PSC = 24000 - 1; //48 000 000 / 480 -> 1000
  TIM14 -> ARR = 1000 - 1; //1000 / 100 -> 1Hz

  //Enable UIE bit in DIER (use TIM_DIER_UIE mask)
  TIM14 -> DIER |= TIM_DIER_UIE;
  //Enable the TIM7 interrupt (NVIC ISER)
  NVIC -> ISER[0] |= (1 << TIM14_IRQn);
  //Enable TIM7 by setting CEN bit in TIM7 CR)  - set TIM_CR1_CEN in TIM7_CR1 (dont set the TIM7_ARR to 0)
  TIM14 -> CR1 |= TIM_CR1_CEN;
}


int main(){

    internal_clock();
    enable_ports();
    // lane select
    // 1   2   3   4
    // 380 580 680 700

    // 0000 0100 0000 0000
    // 0000 0111 0000 0000

    GPIOA -> BSRR = 0x700;
    GPIOA -> BSRR = 0x0001;

    
    return 1;
}