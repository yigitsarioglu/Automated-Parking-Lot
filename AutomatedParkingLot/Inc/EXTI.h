/*
 * EXTI.h
 *
 *  Created on: Dec 22, 2024
 *      Author: yigit
 */

#ifndef EXTI_H_
#define EXTI_H_
#include <stdint.h>
#define EXTI_BASE_ADDR 0x4002F400

#define EXTI_IMR1 (*((volatile uint32_t *)(EXTI_BASE_ADDR + 0x80)))
#define EXTI_RTSR1 (*((volatile uint32_t *)(EXTI_BASE_ADDR + 0x00)))
#define EXTI_FTSR1 (*((volatile uint32_t *)(EXTI_BASE_ADDR + 0x04)))
#define EXTI_RPR1 (*((volatile uint32_t *)(EXTI_BASE_ADDR + 0xC)))
#define EXTI_FPR1 (*((volatile uint32_t *)(EXTI_BASE_ADDR + 0x10)))

void init_exti_interrupts(void);




#endif /* EXTI_H_ */
