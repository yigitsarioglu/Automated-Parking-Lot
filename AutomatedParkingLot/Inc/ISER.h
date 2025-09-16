
#ifndef ISER_H_
#define ISER_H_
#include <stdint.h>
#define ISER1 *((volatile uint32_t *) (0xE000E104))

#define ISER0 *((volatile uint32_t *) (0xE000E100))

#define ISER2 *((volatile uint32_t *) 0xE000E108)


#endif /* ISER_H_ */
