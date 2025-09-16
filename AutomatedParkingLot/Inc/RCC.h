
#ifndef RCC_H_
#define RCC_H_

#include <stdint.h>

#define RCC_BASE 0X40021000
#define RCC_AHB2ENR *((volatile uint32_t *) 0x4002104C)
#define RCC_APB2ENR *((volatile uint32_t *) 0X40021060 )

#define RCC_APB1ENR1 *( (volatile uint32_t *) 0X40021058)
#define RCC_APB1ENR2  (*((volatile uint32_t *)(0x4002105C)))
#define RCC_CCIPR1 *((volatile uint32_t *) 0x40021088)

#define RCC_BDCR *((volatile uint32_t *) 0x40021090)

#define RCC_CR *((volatile uint32_t *)  0x40021000 )



#endif /* RCC_H_ */
