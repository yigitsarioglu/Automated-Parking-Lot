#include <RCC.h>
#include <ISER.h>
#include <TIMERS.h>

void init_timers(void){
	/* TIM6 */
	RCC_APB1ENR1 |= (1 << 4);

	TIM6->PSC = 3999;

	TIM6->ARR = 999; // Auto-reload value for 1-second interval

	TIM6->DIER|= (1 << 0);

	TIM6->CR1 |= (1 << 0);

	ISER1 |= (1 << 17);


	/* TIM17 For Servo PWM  */
	RCC_APB2ENR |= (1 << 18); // Enable Timer 17

	TIM17->PSC = 399; // 1 clock cycle corresponds to 0.1 ms

	TIM17->ARR = 200; // 20 ms Period

	TIM17->BDTR |= (1 << 15); // MOE

	TIM17->CCMR1 |= (3 << 5); // PWM1

	TIM17->CCER |= 1; // Enable output

	TIM17->CCR1 = 10; // 1 ms duty cycle for closed position.

	TIM17->CR1 |= 1; // Enable Timer


	/* TIM 15 For ICOC Ultrasonic Sensor */
	// OC PART
	RCC_APB2ENR |= 1 << 16;   //TIM15x_CLK is enabled, running at 4MHz

	TIM15->PSC = 7;                  // Set prescaler
	TIM15->ARR = 29999;              // Set auto-reload value



	// IC PART

	TIM15->CCMR1 &= ~(0xF << 12);    // Clear input filter bits
	TIM15->CCMR1 |= (2 << 12);        // Set filter to 4 clock cycles
	TIM15->CCMR1 &= ~(3 << 10);		//  Set input capture prescaler to 1

	/*	Select mode as capture	*/
	TIM15->CCMR1 &= ~(3 << 8);
	TIM15->CCMR1 |= (1 << 8);		// Set CC2 as input ,IC2 is mapped on TI2

	/* 	Set the edge direction as both edge	*/
	TIM15->CCER |= (1 << 7);       // Enable capture on both edges
	TIM15->CCER |= (1 << 5);
	TIM15->CCER |= (1 << 4);		// Capture mode enabled


	TIM15->DIER |= (1 << 2);		// Enable interrupt for CC1, CC2
	ISER2 |= (1 << 5);				// Enaable interrupt for TIM15, enable TIM15 interrupt in NVIC
	TIM15->CR1 |= 1;

	/* TIM 2 For ICOC Ultrasonic Sensor */
	// OC PART
	RCC_APB1ENR1  |= 1 << 0;   //TIM2x_CLK is enabled, running at 4MHz

	TIM2->PSC = 7;                  // Set prescaler
	TIM2->ARR = 29999;              // Set auto-reload value


	/* Configure CC1 as output in toggle mode */


	// IC PART

	TIM2->CCMR1 &= ~(0xF << 12);    // Clear input filter bits

	TIM2->CCMR1 |= (2 << 12);       // Set filter to 4 clock cycles

	TIM2->CCMR1 &= ~(3 << 2);      // no prescaler, capture is done each time an edge is detected on the capture input

	TIM2->CCMR1 &= ~(3 << 8);       // clear bits
	TIM2->CCMR1 |= (1 << 8);        // CC2 channel is configured as input, IC2 is mapped on TI2..


	TIM2->CCER |= (1 << 7);
	TIM2->CCER |= (1 << 5);
	TIM2->CCER |= (1 << 4);

	TIM2->DIER |= (1 << 2);
	ISER1 |= (1 << 13);				// Enable interrupt for TIM2
	TIM2->CR1 |= (1 << 0);          // Enable TIM2

	/* 7 Segment Timer */
	RCC_APB1ENR1 |= 1 << 3; //TIM5x_CLK is enabled, running at 4MHz
	TIM5->PSC = 3999; //Set Prescaler
	TIM5->ARR = 4; //Set Delay
	TIM5->CR1 &= ~(1<<1); //OVF will generate an event
	TIM5->DIER |= 1; //NEW! enable UIF to generate an interrupt
	ISER1 |= 1 << 16;//NEW! enable global signaling for TIM6 interrupt
	// ISER1 position is inferred from page 530 in rm0438 PDF
	TIM5->CR1 |= 1; //TIM5_CNT is enabled (clocked)
	TIM5->CNT = 0;

	/* ADC Timer */

	RCC_APB1ENR1 |= 1 << 5; //TIM7x_CLK is enabled, running at 4MHz
	TIM7->PSC = 3999; //Set Prescaler
	TIM7->ARR = 4999; //Set Delay
	TIM7->CR1 &= ~(1<<1); //OVF will generate an event
	TIM7->DIER |= 1; //NEW! enable UIF to generate an interrupt
	ISER1 |= 1 << 18;//NEW! enable global signaling for TIM7 interrupt
	// ISER1 position is inferred from page 530 in rm0438 PDF
	TIM7->CR1 |= 1; //TIM7_CNT is enabled (clocked)
	TIM7->CNT = 0;

	//TIM 16 As Common OC

	RCC_APB2ENR |= (1 << 17);

	TIM16->PSC = 29;
	TIM16->ARR = 49998;

	TIM16->BDTR |= (1 << 15);

	TIM16->CCMR1 |= (3 << 5);

	TIM16->CCER |= 1;

	TIM16->CCR1 = 1;

	TIM16->CR1 |= 1;

}
