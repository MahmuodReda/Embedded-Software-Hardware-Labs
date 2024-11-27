#include <stdio.h>
#include <stdint.h>

// Structure with potential padding between members
struct Example1 {
	uint8_t a;   // 1 byte: occupies address 0
	uint16_t b;  // 2 bytes: must start at an even address (alignment)
				 // Padding of 1 byte will be added after 'a' to align 'b'
};

// Structure where padding may not be needed
struct Example2 {
	uint8_t a;   // 1 byte: occupies address 0
	uint8_t b;   // 1 byte: occupies address 1 (no padding needed)
	uint16_t c;  // 2 bytes: starts at address 2 (already aligned)
};

int main() {
	// Print the size of Example1, which includes padding
	printf("Size of Example1: %lu bytes\n",(unsigned long) sizeof(struct Example1));
	// Address: [0] [1] [2] [3]
	// Data:    [a] [Pad] [b0] [b1]
	// Size of Example1: 4 bytes
	// Print the size of Example2, with minimal or no padding
	printf("Size of Example1: %lu bytes\n",(unsigned long) sizeof(struct Example2));
	// Address: [0] [1] [2] [3]
	// Data:    [a] [b] [c0] [c1]
	// Size of Example2: 4 bytes
	return 0;
}

//	Explanation:
//	Structure Example1:
//
//	a is uint8_t (1 byte), stored at address 0.
//	b is uint16_t (2 bytes), must be aligned to a 2-byte boundary.
//	Padding of 1 byte is inserted after a to align b correctly.
//	Total size: 4 bytes (1 for a, 1 padding, 2 for b).
//	Structure Example2:
//
//	a and b are both uint8_t (1 byte each), stored consecutively.
//	c is uint16_t (2 bytes), starts at address 2, which is already aligned.
//	No extra padding is required.
//	Total size: 4 bytes (1 for a, 1 for b, 2 for c).

