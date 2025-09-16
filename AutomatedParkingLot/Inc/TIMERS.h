
#ifndef TIMERS_H_
#define TIMERS_H_
#include <stdint.h>
// TIM15 structure definition

#define OC_CRR_ON 10
#define OC_CRR_OFF 29989

#define HI 1
#define LO 0

typedef struct{
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t SMCR;
	volatile uint32_t DIER;
	volatile uint32_t SR;
	volatile uint32_t EGR;
	volatile uint32_t CCMR1;
	uint32_t reserved1;
	volatile uint32_t CCER;
	volatile uint32_t CNT;
	volatile uint32_t PSC;
	volatile uint32_t ARR;
	volatile uint32_t RCR;
	volatile uint32_t CCR1;
	volatile uint32_t CCR2;
	uint32_t reserved2;
	uint32_t reserved3;
	volatile uint32_t BDTR;
	volatile uint32_t DCR;
	volatile uint32_t DMAR;
	volatile uint32_t OR1;
	uint32_t reserved4[3];
	volatile uint32_t OR2;

}TIM15_Type;
#define TIM15 ((TIM15_Type *) 0x40014000)

// page 90 -memory organization


// TIM2 structure definition
typedef struct{
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t SMCR;
	volatile uint32_t DIER;
	volatile uint32_t SR;
	volatile uint32_t EGR;
	volatile uint32_t CCMR1;
	volatile uint32_t CCMR2;
	volatile uint32_t CCER;

	volatile uint32_t CNT;
	volatile uint32_t PSC;
	volatile uint32_t ARR;

	uint32_t reserved1;
	volatile uint32_t CCR1;
	volatile uint32_t CCR2;
	volatile uint32_t CCR3;
	volatile uint32_t CCR4;
	uint32_t reserved2;
	volatile uint32_t DCR;
	volatile uint32_t DMAR;
	volatile uint32_t OR1;
	uint32_t reserved4[3];
	volatile uint32_t OR2;

}TIM2_Type;
#define TIM2 ((TIM2_Type *)  0x40000000 )


// TIM16 structure definition
typedef struct{
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	uint32_t reserved1;
	volatile uint32_t DIER;
	volatile uint32_t SR;
	volatile uint32_t EGR;
	volatile uint32_t CCMR1;
	uint32_t reserved2;
	volatile uint32_t CCER;
	volatile uint32_t CNT;
	volatile uint32_t PSC;
	volatile uint32_t ARR;
	volatile uint32_t RCR;
	volatile uint32_t CCR1;
	uint32_t reserved3[3];
	volatile uint32_t BDTR;
	volatile uint32_t DCR;
	volatile uint32_t DMAR;
	volatile uint32_t OR1;
	uint32_t reserved4[3];
	volatile uint32_t OR2;

}TIM16_Type;
#define TIM16 ((TIM16_Type *) 0x40014400 )


typedef struct {
	volatile uint32_t CR1;
	volatile uint32_t CR2;
		uint32_t reserved;
	volatile uint32_t DIER;
	volatile uint32_t SR;
	volatile uint32_t EGR;
		uint32_t reserved1;
		uint32_t reserved2;
		uint32_t reserved3;
	volatile uint32_t CNT;
	volatile uint32_t PSC;
	volatile uint32_t ARR;
}TIM6_Type ;
#define TIM6 ((TIM6_Type *)  0x40001000)
#define TIM7 ((TIM6_Type *)  0x40001400)

typedef struct{
	volatile uint32_t CR1, CR2;
	uint32_t reserved1;
	volatile uint32_t DIER, SR, EGR, CCMR1;
	uint32_t reserved2;
	volatile uint32_t CCER, CNT, PSC, ARR, RCR, CCR1;
	uint32_t reserved3[3];
	volatile uint32_t BDTR, DCR, DMAR, OR1;
	uint32_t reserved4[3];
	volatile uint32_t OR2;
} TIM17Type;
#define TIM17 ((TIM17Type*)  0x40014800)


typedef struct{
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t SMCR;
	volatile uint32_t DIER;
	volatile uint32_t SR;
	volatile uint32_t EGR;
	volatile uint32_t CCMR1;
	volatile uint32_t CCMR2;
	volatile uint32_t CCER;
	volatile uint32_t CNT;
	volatile uint32_t PSC;
	volatile uint32_t ARR;
	uint32_t reserved;
	volatile uint32_t CCR1;
	volatile uint32_t CCR2;
	volatile uint32_t CCR3;
	volatile uint32_t CCR4;
} TIM5Type;
#define TIM5 ((TIM5Type*) 0x40000C00)

void init_timers(void);

#endif /* TIMERS_H_ */
