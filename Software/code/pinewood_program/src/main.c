#include "stm32f0xx.h"
#include <stdint.h>
#include <stdio.h>

int race_tim_flag = 0;
int placement     = 0;


void enable_ports() {
  RCC -> AHBENR |= RCC_AHBENR_GPIOAEN;

  //A
  GPIOA -> MODER &= ~ 0x3FFFFF;
  GPIOA -> MODER |=   0x155555;  // output -> 0-10 : PLACEMENT DISP

  //B
  GPIOB -> MODER &= ~ 0x3FFFFFFF; // input  -> 11-14 : END SENSORS
  GPIOB -> MODER |=   0x00155555; // output -> 0-10 : TIMER DISP 1


  //C
  GPIOC -> MODER &= ~ 0xFCFFFFFF; // input  -> 11 : RACE START
  GPIOC -> MODER |=   0x54155555; // output -> 0-10 : TIMER DISP 2, 13-15 : STATUS LEDs

  
}


int check_start(){
  int start = GPIOC -> IDR;
  start &= 0x ; //or the mask needed for specific lane

  return start; //just returns 1 or 0 if its on or not. ill be using them as regular io, not ADC
}

void race_tim_en(){
  if( check_start() ) race_tim_flag = 1;
}

///////////////////////////////////////////////////
int index         = 0;
int place_arr[4]  = {1, 2, 3, 4};
//      0x06, 0x5B, 0x4F, 0x66

//or
int place    = 1234;

//each time lane sensor crossed
void move_place_arr(){
  placement = place_arr[index];
  if(index < 4) index++;
  else pos = 4;
}

void move_place_num(int num){
  if(num > 0)
  placement = (int)(num / 1000); //returns first number
  num %= 1000; //chops off first number
  num *= 10;   //keeps it at 4 digits so its easy to get the first number
}

//////////////////////////////////////////////


int check_lane(int lane){
  //  int portc_val = GPIOC -> IDR;
  int sensor_output = GPIOC -> IDR;
  sensor_output &= 0x ; //or the mask needed for specific lane

  if(lane == 1)
    NVIC_DisableIRQ(timer for that one);
    return sensor_output; //just returns 1 or 0 if its on or not. ill be using them as regular io, not ADC
}



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