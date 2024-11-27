#include <stdio.h>
#include <stdint.h>

// Directive to pack the structure with no padding between members
#pragma pack(1)

// Structure with forced packing (no padding added)
struct Example1 {
    uint8_t a;   // 1 byte: stored at address 0
    uint16_t b;  // 2 bytes: stored at address 1 (no padding due to #pragma pack(1))
};

// Structure with forced packing (no padding added)
struct Example2 {
    uint8_t a;   // 1 byte: stored at address 0
    uint8_t b;   // 1 byte: stored at address 1
    uint16_t c;  // 2 bytes: stored at address 2 (no padding due to #pragma pack(1))
};

int main() {
    // Print the size of Example1, where no padding is added due to #pragma pack(1)
    printf("Size of Example1: %lu bytes\n", (unsigned long)sizeof(struct Example1));
    // Address: [0] [1] [2]
    // Data:    [a] [b0] [b1]
    // Size of Example1: 3 bytes (no padding between 'a' and 'b')

    // Print the size of Example2, where all members are tightly packed
    printf("Size of Example2: %lu bytes\n", (unsigned long)sizeof(struct Example2));
    // Address: [0] [1] [2] [3]
    // Data:    [a] [b] [c0] [c1]
    // Size of Example2: 4 bytes (tightly packed)

    return 0;
}

/*
Explanation:
1. `#pragma pack(1)` forces the compiler to align all structure members on 1-byte boundaries,
   meaning no extra padding bytes are added to align data.

2. Structure Example1:
   - `a` is 1 byte (uint8_t) and stored at address 0.
   - `b` is 2 bytes (uint16_t) and stored immediately at address 1.
   - Normally, padding would be added to align `b` to an even address, but #pragma pack(1) prevents it.
   - Total size: 3 bytes (1 byte for `a` + 2 bytes for `b`).

3. Structure Example2:
   - `a` and `b` are both 1 byte each (uint8_t) and stored consecutively at address 0 and 1.
   - `c` is 2 bytes (uint16_t) and stored at address 2.
   - No padding is needed due to #pragma pack(1), allowing tight packing.
   - Total size: 4 bytes (1 byte for `a`, 1 byte for `b`, 2 bytes for `c`).

Without `#pragma pack(1)`, these structures would typically have padding to align multi-byte members
to their natural boundaries, which would increase the size.
*/
