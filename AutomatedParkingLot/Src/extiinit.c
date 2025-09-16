#include <EXTI.h>
#include <ISER.h>
void init_exti_interrupts(void) {


    // Configure EXTI for switch pin

    EXTI_IMR1 |= 1 << 5; // Enable EXTI5 interrupt
    EXTI_IMR1 |= 1 << 6; // Enable EXTI6 interrupt
    EXTI_IMR1 |= 1 << 7; // Enable EXTI7 interrupt

    EXTI_RTSR1 |= 1 << 5; // Enable rising edge trigger for EXTI5
    EXTI_FTSR1 |= 1 << 5; // Enable falling edge trigger for EXTI5

    EXTI_RTSR1 |= 1 << 6; // Enable rising edge trigger for EXTI6
    EXTI_FTSR1 |= 1 << 6; // Enable falling edge trigger for EXTI6

    EXTI_RTSR1 |= 1 << 7; // Enable rising edge trigger for EXTI7
    EXTI_FTSR1 |= 1 << 7; // Enable falling edge trigger for EXTI7

    ISER0 |= 1 << 16; // Enable EXTI5 in NVIC(position 16)
    ISER0 |= 1 << 17; // Enable EXTI6 in NVIC(position 17)
    ISER0 |= 1 << 18; // Enable EXTI7 in NVIC(position 18)

}
