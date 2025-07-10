#include "stm32f0xx.h"
#include <stdint.h>
#include <stdio.h>


// void init_gpioa(){
//     RCC -> AHBENR |= RCC_AHBENR_GPIOAEN;
//     GPIOA -> MODER &= ~0xFFC00000;
//     GPIOA -> MODER &= ~0x3FFFF;
//     GPIOA -> MODER |=  0x15555;
//     GPIOA->PUPDR &= ~(0xFF);         // Clear pull-up/down bits for PA0–PA3
//     GPIOA->PUPDR |=  (0x55);         // Set PA0–PA3 to pull-up (01) or pull-down (10)
// }

// int read_pin(){
//     int pin_val = GPIOA -> IDR;
//     pin_val &= 0xF;
//     return pin_val;
// }

// void TIM7_IRQHandler(){
//     //acknowledge
//     TIM7 -> SR &= ~TIM_SR_UIF;  
//     //if row != 0, convert the key to usable value (thrust, mode, etc)
//     int row = read_pin();
//         // GPIOA -> BSRR = 1 << 2;
//         // GPIOA -> BRR  = 1 << 3;
    
  
//   }
  
//   /**
//    * @brief Setup timer 7 as described in lab handout
//    * 
//    */
//   void setup_tim7() {
//     //Enable RCC clock for TIM7
//     RCC -> APB1ENR |= RCC_APB1ENR_TIM7EN;

//     TIM7 -> PSC = 480 - 1; //48 000 000 / 480 -> 100 000
//     TIM7 -> ARR = 100 - 1; //100 000 / 100 -> 1kHz
  
//     //Enable UIE bit in DIER (use TIM_DIER_UIE mask)
//     TIM7 -> DIER |= TIM_DIER_UIE;
//     //Enable the TIM7 interrupt (NVIC ISER)
//     NVIC -> ISER[0] |= (1 << TIM7_IRQn);
//     //Enable TIM7 by setting CEN bit in TIM7 CR)  - set TIM_CR1_CEN in TIM7_CR1 (dont set the TIM7_ARR to 0)
//     TIM7 -> CR1 |= TIM_CR1_CEN;
//   }
  

int main(){

    // internal_clock();
    // init_gpioa();
    // // GPIOA -> BSRR = 1 << 2;

    // setup_tim7();


    // while (1) {
    //     __WFI();  // Wait for interrupt (optional, saves power)
    // }
    
    return 1;
}