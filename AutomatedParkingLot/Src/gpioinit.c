#include <GPIO.h>
#include <RCC.h>
#include <LPUART.h>

void exti_gpio(int position, int color){
	if (position == 0){
		if (color){
			GPIOC->ODR |= (1 << 8);
			GPIOC->ODR &= ~(1 << 0);
		}
		else{
			GPIOC->ODR |= (1 << 0);
			GPIOC->ODR &= ~(1 << 8);
		}
	}
	else if (position == 1){
		if (color){
			GPIOC->ODR |= (1 << 10);
			GPIOC->ODR &= ~(1 << 9);
		}
		else{
			GPIOC->ODR |= (1 << 9);
			GPIOC->ODR &= ~(1 << 10);
		}
	}
	else{
		if (color){
			GPIOC->ODR |= (1 << 12);
			GPIOC->ODR &= ~(1 << 11);
		}
		else{
			GPIOC->ODR |= (1 << 11);
			GPIOC->ODR &= ~(1 << 12);
		}
	}
}

void init_gpio(void){
	/* 7 segment */
	RCC_AHB2ENR |= 0b110000;

	GPIOF->MODER &= ~((0x03 << (8 * 2)) | (0x03 << (1 * 2)) | (0x03 << (2 * 2)) | (0x03 << (0 * 2)));
	GPIOF->MODER |= ((0x01 << (8 * 2)) | (0x01 << (1 * 2)) | (0x01 << (2 * 2)) | (0x01 << (0 * 2)));

	for (int i = 2; i <= 8; i++) {
		GPIOE->MODER &= ~(0x03 << (i * 2));
		GPIOE->MODER |= (0x01 << (i * 2));
	}


	/* EXTI */
	RCC_AHB2ENR |= 1;

	GPIOA->MODER &= ~(3 << (5 * 2)); // Set mode register to input
	GPIOA->MODER &= ~(3 << (6 * 2)); // Set mode register to input
	GPIOA->MODER &= ~(3 << (7 * 2)); // Set mode register to input


	RCC_APB1ENR1 |= (1 << 28); // Enable PWR


	PWR_CR2 |= (1 << 9); // Enable GPIOG Power

	// EXTI LEDS
	RCC_AHB2ENR |= (1 << 2);
	GPIOC->MODER &= ~3;
	GPIOC->MODER &= ~(3 << (8*2));
	GPIOC->MODER &= ~(0xFF << (9*2));

	GPIOC->MODER |= 1;
	GPIOC->MODER |= (1 << (8*2));
	GPIOC->MODER |= (0b01010101 << (9*2));

	exti_gpio(0, 0); // Green for every exti led
	exti_gpio(1, 0);
	exti_gpio(2, 0);

	/* ADC GPIO */

	GPIOC->MODER |= 0b11 << 2; //PC2 is analog mode

	/* ADC Fan */

	RCC_AHB2ENR |= 1 << 4; //clock for GPIOA is enabled
	GPIOE->MODER &= ~(0b11 << 20);
	GPIOE->MODER |= (1 << 20);

	/* LPUART And Servo */
	RCC_AHB2ENR |= (1 << 1); // GPIOB
	RCC_AHB2ENR |= (1 << 6); // GPIOG


	GPIOG->MODER &= ~((0xF << (7*2)));
	GPIOG->MODER |= ((10U << (7*2))); // AF mode for PG7-PG8

	GPIOB->MODER &= ~(3 << (9 *2));
	GPIOB->MODER |= (2 << (9 *2)); // AF mode for PB9

	GPIOG->AFRL &= ~(0xF << (7*4));
	GPIOG->AFRH &= ~(0xF); // Clear bits for PG AFs

	GPIOG->AFRL |= (8U << (7*4)); // LPUART TX alternate function
	GPIOG->AFRH |= (8U); // LPUART RX alternate function


	GPIOB->AFRH &= (0xF << 4); // Clear bits for PB AFs

	GPIOB->AFRH |= (14U << 4*1); // TIM17_CH1 Alternate Function


	/* ICOC */
	GPIOA->MODER &= ~(3 << (2*2));		//TIM15_CH1 in PA2 for trigger
	GPIOA->MODER |= (2 << (2*2));

	GPIOA->AFRL &= ~(0xF << (2*4));
	GPIOA->AFRL |= 14 << (2*4);

	// Configure PA3 for alternate function (TIM15_CH2)
	GPIOA->MODER &= ~(3 << (2*3));		//TIM15_CH2 in PA3 for input echo
	GPIOA->MODER |= (2 << (2*3));

	GPIOA->AFRL &= ~(0xF << (3*4));
	GPIOA->AFRL |= 14 << (3*4);



	// PA0- TIM2_CH1  af1 -- chaneel1 for output
	GPIOA->MODER &= ~(3 << (2 * 0));
	GPIOA->MODER |= (2 << (2 * 0));  // Set PA0 to alternate function mode
	GPIOA->AFRL &= ~(0xF << (4 * 0));
	GPIOA->AFRL |= (1 << (4 * 0)); // Alternate function AF1


	// PA1- TIM2_CH2 af1  -- channel 2 input

	GPIOA->MODER &= ~(3 << (2 * 1));
	GPIOA->MODER |= (2 << (2 * 1));  // Set PA1 to alternate function mode
	GPIOA->AFRL &= ~(0xF << (4 * 1));
	GPIOA->AFRL |= (1 << (4 * 1)); // Alternate function AF1


	// PB8 AS Common OC

	GPIOB->MODER &= ~(3 << 8*2);
	GPIOB->MODER |= (2 << 8*2);

	GPIOB->AFRH |= 14;

}
