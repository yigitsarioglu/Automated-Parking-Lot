#include <stdint.h>
#include <RCC.h>
#include <ISER.h>
#include <EXTI.h>
#include <LPUART.h>
#include <GPIO.h>
#include <TIMERS.h>
#include <ADC.h>
#include <SEGMENT.h>

#define parkCount 3


uint32_t park_clock_count[parkCount];
uint32_t cost[parkCount];
uint32_t cost_rate = 5;
uint8_t park_states[parkCount];
int transmittingString = 0;
int stringPos = 0;
char currentStr[256];
int doorState = 0;
int door_timer_counter = 0;
int segment_counter = 0;
uint16_t dig_temp_value;
uint8_t fan_state = 0;
uint8_t fan_counter = 0;

static uint16_t capturedEdge, RTT ;
static uint16_t capturedEdge_TIM2;
static uint16_t RTT_TIM2;


void EXTI5_IRQHandler(void) {

    if ((EXTI_RPR1 & (1U << 5)) != 0) { // Check if EXTI interrupt occurred

        EXTI_RPR1 = 1U << 5; // Clear EXTI interrupt flag
        park_states[0] = 0;
        uint32_t finalCost = park_clock_count[0] * cost_rate;
        if (finalCost > 10){
			char costStr[256];
			sprintf(costStr, "Ticket fee for park slot 1: %d\r\n", finalCost);
			uart_transmit_string(costStr);
		}
        park_clock_count[0] = 0;
        exti_gpio(0, 0);
    }

    if ((EXTI_FPR1 & (1U << 5)) != 0) { // Check if EXTI interrupt occurred
        EXTI_FPR1 = 1U << 5; // Clear EXTI interrupt flag
        park_states[0] = 1;
        exti_gpio(0, 1);

    }

}

void EXTI6_IRQHandler(void) {

    if ((EXTI_RPR1 & (1U << 6)) != 0) { // Check if EXTI interrupt occurred
        EXTI_RPR1 = 1U << 6; // Clear EXTI interrupt flag
        park_states[1] = 0;
		uint32_t finalCost = park_clock_count[1] * cost_rate;
		if (finalCost > 10){
			char costStr[256];
			sprintf(costStr, "Ticket fee for park slot 2: %d\r\n", finalCost);
			uart_transmit_string(costStr);
		}
		park_clock_count[1] = 0;
		exti_gpio(1, 0);
    }

    if ((EXTI_FPR1 & (1U << 6)) != 0) { // Check if EXTI interrupt occurred
        EXTI_FPR1 = 1U << 6; // Clear EXTI interrupt flag
        park_states[1] = 1;
        exti_gpio(1, 1);
    }

}

void EXTI7_IRQHandler(void) {

	if ((EXTI_RPR1 & (1U << 7)) != 0) { // Check if EXTI interrupt occurred
	        EXTI_RPR1 = 1U << 7; // Clear EXTI interrupt flag
	        park_states[2] = 0;
			uint32_t finalCost = park_clock_count[2] * cost_rate;
			if (finalCost > 10){
				char costStr[256];
				sprintf(costStr, "Ticket fee for park slot 3: %d\r\n", finalCost);
				uart_transmit_string(costStr);
			}
			park_clock_count[2] = 0;
			exti_gpio(2, 0);
	    }

	if ((EXTI_FPR1 & (1U << 7)) != 0) { // Check if EXTI interrupt occurred
		EXTI_FPR1 = 1U << 7; // Clear EXTI interrupt flag
		park_states[2] = 1;
		exti_gpio(2, 1);
	}

}

void uart_transmit_string(char* str){
	if (transmittingString){ // Exit the function if the board is already transmitting a string. Can busy wait here for longer transmissions.
		return;
	}
	if (*(str)){ // Check if the length is greater than 0.
		strcpy(currentStr, str); // Copy the string to the global variable.
		transmittingString = 1; // Transmission began.
		LPUART1->TDR = *currentStr; // Transmit the first character.
		stringPos = 1; // Move to the second character
		LPUART1->CR1 |= (1 << 6); //Enable Transmission Complete Interrupt
	}


}

void LPUART1_IRQHandler(void){
	if ((LPUART1->ISR & (1 << 5))){
		char byte_read = LPUART1->RDR; // Read the byte from the recieved data register.

		if (byte_read == 'O'){
			if (TIM17->CCR1 == 20){ // The duty cycle is already 2ms. This means the door is already open.
				uart_transmit_string("The door is already open.\r\n");
			}
			else{
				TIM17->CCR1 = 20; //Set the duty cycle to 2ms (Servo on position)
				uart_transmit_string("The door has opened.\r\n");
			}
		}
		else if (byte_read == 'C'){
			if (TIM17->CCR1 == 10){ // The duty cycle is already 1ms. This means the door is already closed.
				uart_transmit_string("The door is already closed.\r\n");
			}
			else{
				TIM17->CCR1 = 10; //Set the duty cycle to 1ms (Servo off position)
				uart_transmit_string("The door has closed.\r\n");
			}

		}
	}
	if ((LPUART1->ISR & (1 << 6))){ //Transmission complete interrupt.
		LPUART1->ICR |= (1 << 6); // Clear the isr flag for transmission complete.
		if (*(currentStr + stringPos)){ //Check if the stringPos is within the string bounds.
			LPUART1->TDR = *(currentStr + stringPos); // Transmit the current character.
			stringPos++; // Increase the stringPos counter variable.
		}
		else{ //Transmission completed, set variables to initial position.
			stringPos = 0;
			transmittingString = 0;
			LPUART1->CR1 &= ~(1 << 6); //Disable the Transmission Complete Interrupt
		}
	}
}

void TIM2_IRQHandler(void) {

	static unsigned int IC_PIN = LO;   // State of the input capture pin (LOW/HIGH)


	static uint8_t states = 0;   // State variable for Output Compare



    if ((TIM2->SR & (1 << 2)) != 0) {  // CC2 interrupt flag
        if (IC_PIN == LO  ) {  // Rising edge detected
        	IC_PIN = HI;
            capturedEdge_TIM2 = TIM2->CCR2;
        } else {  // Falling edge detected

        	IC_PIN = LO;
            uint16_t currentEdge = TIM2->CCR2;
            if (currentEdge >= capturedEdge_TIM2) {
                RTT_TIM2 = currentEdge - capturedEdge_TIM2;
            } else {
                RTT_TIM2 = (0xFFFF - capturedEdge_TIM2) + currentEdge + 1;
            }

            //char rttstring[256];
			 //sprintf(rttstring, "RTT TIM2 : %d \r\n", RTT_TIM2);
			 //uart_transmit_string(rttstring);

            // Mesafe hesaplamaları ve LED kontrolü buraya eklenir
            if ( ( (RTT_TIM2/2)/58) <= 1 ) {
        		TIM17->CCR1 = 20;
				door_timer_counter = 0;
				doorState = 1;
			}


        }
        TIM2->SR &= ~(1 << 2);  // Clear interrupt flag
    }
    if ((TIM2->SR & (1 << 10)) != 0){
    		states = 0;
    		capturedEdge_TIM2 = 0;
    		RTT_TIM2 = 0;
    		TIM2->SR &= ~(1 << 10);
    	}

    TIM2->SR &= ~(1 << 0);

}

void TIM6_IRQHandler(void) {
    if (TIM6->SR & (1 << 0)) {
        for (int i = 0; i < parkCount; i++){
            if (park_states[i]){
                park_clock_count[i]++;
            }
        }
        if (doorState){
        	if (door_timer_counter < 5){
        		door_timer_counter++;
        	}
        	else{
        		doorState = 0;
        		TIM17->CCR1 = 10;
        	}
        }
        TIM6->SR &= ~(1 << 0);

    }
}

void TIM7_IRQHandler(void)
{
	TIM7->SR=0; //clear UIF bit
	ADC1->CR |= 1 << 2; //start conversion
}

void TIM15_IRQHandler(void){
	static uint8_t state = 0;   // State variable for Output Compare
	static unsigned int IC_PIN = LO;   // State of the input capture pin (LOW/HIGH)


	// Check for CC2 interrupt (Input Capture)
	if((TIM15->SR & (1 << 2)) != 0){		// Is the CC2 interrupt flag set?
		if(IC_PIN == LO){                   // If the pin state is LOW
			IC_PIN = HI;                     // Update pin state to HIGH
			capturedEdge = TIM15->CCR2;      // Store the time of the first captured edge
		}
		else{                                 // If the pin state changes to LOW (HIGH -> LOW)
			IC_PIN = LO;                       // Update pin state to LOW
			 if (TIM15->CCR2 >= capturedEdge) {
				// No overflow, calculate the time difference
				 RTT = TIM15->CCR2 - capturedEdge;
			 } else {
				 // Overflow occurred, include it in the calculation
			   RTT = (0xFFFF - capturedEdge) + TIM15->CCR2 + 1;
			 }


			 if (park_states[0] && park_states[1] && park_states[2]){
				 ;
			 }
		      // Check distance using RTT (calculated from TIM15 capture values)
			 else if(((RTT/2)/58) <= 1 ){       // Object/Car is very close
				TIM17->CCR1 = 20;
				door_timer_counter = 0;
				doorState = 1;

			}
			 // Uncomment for debugging
			 //char rttstring[256];
			 //sprintf(rttstring, "RTT TIM15: %d \r\n", RTT);
			 //uart_transmit_string(rttstring);


		}
		TIM15->SR &= ~(1 << 2);   // Clear the CC2 interrupt flag
	}
	if ((TIM15->SR & (1 << 10)) != 0){
		state = 0;
		capturedEdge = 0;
		RTT = 0;
		TIM15->SR &= ~(1 << 10);
	}

	TIM15->SR &= ~(1 << 0);  // Clear the general update interrupt flag (if any)
}

void TIM5_IRQHandler(void)
{
	TIM5->SR=0; //clear UIF bit

	if (fan_state){
		if (fan_counter < 10){
			GPIOE->ODR |= (1 << 10);// Turn On Fan
			fan_counter++;
		}
		else if (fan_counter < 20){
			GPIOE->ODR &= ~(1 << 10); // Turn Off Fan
			fan_counter++;
		}
		else{
			fan_counter = 0;
		}
	}
	else{
		GPIOE->ODR &= ~(1 << 10);
	}

	for (int ii = 5; ii < 8; ii++){
		if (GPIOA->IDR & (1 << ii)){
			park_states[ii-5] = 0;
			uint32_t finalCost = park_clock_count[ii-5] * cost_rate;
			if (finalCost > 10){
				char costStr[256];
				sprintf(costStr, "Ticket fee for park slot %d: %d\r\n",(ii - 4) , finalCost);
				uart_transmit_string(costStr);
			}
			park_clock_count[ii-5] = 0;
			exti_gpio(ii-5, 0);
		}
		else{
			EXTI_FPR1 = 1U << 5; // Clear EXTI interrupt flag
			park_states[ii-5] = 1;
			exti_gpio(ii-5, 1);
		}
	}




	if(park_states[0] == 0) {
		GPIOF->ODR |= (1 << 1);
		GPIOF->ODR |= (1 << 2);
		GPIOF->ODR |= (1 << 8);
		GPIOF->ODR &= ~(1);
		display_number_on_segment(SEGMENT_1);
	} else if (park_states[1] == 0) {
		GPIOF->ODR |= (1 << 1);
		GPIOF->ODR |= (1 << 2);
		GPIOF->ODR |= (1 << 8);
		GPIOF->ODR &= ~(1);
		display_number_on_segment(SEGMENT_2);
	} else if (park_states[2] == 0) {
		GPIOF->ODR |= (1 << 1);
		GPIOF->ODR |= (1 << 2);
		GPIOF->ODR |= (1 << 8);
		GPIOF->ODR &= ~(1);
		display_number_on_segment(SEGMENT_3);
	} else {
		if(segment_counter == 0) {
			GPIOF->ODR |= (1 << 1);
			GPIOF->ODR |= (1 << 2);
			GPIOF->ODR |= (1 << 8);
			GPIOF->ODR &= ~(1);
			display_number_on_segment(SEGMENT_L);
			segment_counter = 1;
		} else if(segment_counter == 1) {
			GPIOF->ODR &= ~(1 << 1);
			GPIOF->ODR |= (1 << 2);
			GPIOF->ODR |= (1 << 8);
			GPIOF->ODR |= (1);
			display_number_on_segment(SEGMENT_L);
			segment_counter = 2;
		} else if(segment_counter == 2) {
			GPIOF->ODR |= (1 << 1);
			GPIOF->ODR &= ~(1 << 2);
			GPIOF->ODR |= (1 << 8);
			GPIOF->ODR |= (1);
			display_number_on_segment(SEGMENT_U);
			segment_counter = 3;
		} else if(segment_counter == 3) {
			GPIOF->ODR |= (1 << 1);
			GPIOF->ODR |= (1 << 2);
			GPIOF->ODR &= ~(1 << 8);
			GPIOF->ODR |= (1);
			display_number_on_segment(SEGMENT_F);
			segment_counter = 0;
		}
	}
	TIM5->CNT = 0;
}

void ADC1_2_IRQHandler(void)
{
	if((ADC1->ISR & 1<<2) != 0) {
		dig_temp_value = ADC1->DR;

		if (dig_temp_value > 150) {
			fan_state = 1;
		}
		else {
			fan_state = 0;
		}
		TIM7->CNT = 0;
	}
}

int main(void) {
	init_gpio();
	init_adc();
//    init_exti_interrupts();
    init_lpuart();
    init_timers();


    while (1) {
        __asm volatile("wfi");

    }
}
