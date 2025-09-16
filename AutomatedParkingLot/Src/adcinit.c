#include <RCC.h>
#include <ADC.h>
#include <ISER.h>

// Calibration and ready busy waits
void init_adc(void){
	RCC_AHB2ENR |= 1 << 13; //enable ADC clock
	ADC1->CR &= ~(1 << 29); //take ADC module from deep-power down
	ADC1->CR |= (1 << 28); //turn on ADC voltage regulator
	RCC_CCIPR1 |= 3 << 28; //main ADC clock is system clock (HCLK = SYSCLK =4MHz out of reset)
	ADC->CCR |= 3 << 16; //ADC_CLK = 1MHz (HCLK/4)
	ADC1->SMPR1 |= 0b111 << 18; //sampling time= 640.5 ADC12_IN6 clock cycles
	ADC1->SQR1 &= ~(0b1111 << 0); // Set number of conversions to 1
	ADC1->SQR1 |= 3 << 6; // 1st conversion is ADC12_IN3
	ADC1->CR |= (1 << 31); //calibrate ADC
	while((ADC1->CR & (1 << 31)) != 0) {} //wait until calibration is complete
	ADC1->CR |= 1; //turn on ADC module
	while((ADC1->ISR & 1) == 0) {} //wait until ADC is ready
	ADC1->CR |= 1 << 2; //start conversion
	ADC1->IER |= 1 << 2; //turn on EOC interrupts
	ISER1 |= 1 << 5;//enable global signaling for ADC1_2 interrupt
}
