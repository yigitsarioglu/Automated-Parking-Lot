
#ifndef GPIO_H_
#define GPIO_H_
#include <stdint.h>
typedef struct {
	volatile uint32_t MODER;
	volatile uint32_t OTYPER;
	volatile uint32_t OSPEEDR;
	volatile uint32_t PUPDR;
	volatile uint32_t IDR;
	volatile uint32_t ODR;
	volatile uint32_t BSRR;
	volatile uint32_t LCKR;
	volatile uint32_t AFRL;
	volatile uint32_t AFRH;
	volatile uint32_t BRR;
	uint32_t reserved;
	volatile uint32_t SECCFGR;
} GPIO_Type;
#define GPIO_BASE 0x42020000
#define GPIOA ((GPIO_Type *) 0x42020000)
#define GPIOB ((GPIO_Type *) 0x42020400)
#define GPIOC ((GPIO_Type *) 0x42020800)
#define GPIOD ((GPIO_Type *) 0x42020C00)
#define GPIOE ((GPIO_Type *) 0x42021000)
#define GPIOF ((GPIO_Type *) 0x42021400)
#define GPIOG ((GPIO_Type *) 0x42021800)


void exti_gpio(int position, int color);
void init_gpio(void);

#endif /* GPIO_H_ */
