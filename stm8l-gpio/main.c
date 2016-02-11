#include <stm8l15x.h>
#include <stm8l15x_gpio.h>

void main() {
    GPIO_Init(GPIOC, GPIO_Pin_7, GPIO_Mode_Out_PP_Low_Fast);
    GPIO_Init(GPIOE, GPIO_Pin_7, GPIO_Mode_Out_PP_Low_Fast);
    GPIO_ToggleBits(GPIOC, GPIO_Pin_7);
    GPIO_ToggleBits(GPIOE, GPIO_Pin_7);
    while(1);
}