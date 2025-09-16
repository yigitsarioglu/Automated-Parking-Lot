#include <LPUART.h>
#include <RCC.h>
#include <ISER.h>


void init_lpuart(void){

	RCC_APB1ENR2 |= (1); // Enable LPUART1


	RCC_CCIPR1 |= (1U << 10); // SYSCLOCK As LPUART1 clock

	LPUART1->BRR = 8888; // 115200 Baud Rate

	LPUART1->CR1 |= (3 << 2); //Tx and Rx Enabled

	LPUART1->CR1 |= (1 << 29); //FIFO

	LPUART1->CR1 |= (1 << 5); //FIFO Not Empty Interrupt



	ISER2 |= (1 << 2); //NVIC 66

	LPUART1->CR1 |= 1; //Enable LPUART
}


