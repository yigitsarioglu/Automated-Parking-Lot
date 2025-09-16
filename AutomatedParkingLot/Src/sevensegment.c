#include <GPIO.h>

void display_number_on_segment(uint8_t segment_value) {
    GPIOE->ODR &= ~(0x7F << 2);       // Clear PE2 - PE8 for seven-segment
    GPIOE->ODR |= (segment_value << 2); // Display specified segment value
}
