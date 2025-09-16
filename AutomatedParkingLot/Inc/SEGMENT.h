
#ifndef SEGMENT_H_
#define SEGMENT_H_


#define SEGMENT_1 0b0000110 // Display "1"
#define SEGMENT_2 0b1011011 // Display "2"
#define SEGMENT_3 0b1001111 // Display "3"
#define SEGMENT_F 0b1110001 // Display "F"
#define SEGMENT_U 0b0111110 // Display "U"
#define SEGMENT_L 0b0111000 // Display "L"

void display_number_on_segment(uint8_t segment_value);

#endif /* SEGMENT_H_ */
