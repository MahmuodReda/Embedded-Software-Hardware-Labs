#include <stdint.h>
#include <stdio.h>

// Define bit masks with explanations of their binary representation
#define SET_BITS_4_5   0x30    // 0x30 = 0011 0000 (Set bits 4 and 5)
#define CLEAR_BITS_6_7 ~0xC0   // 0xC0 = 1100 0000 => ~0xC0 = 0011 1111 (Clear bits 6 and 7)
#define TOGGLE_BITS_1_3 0x0E   // 0x0E = 0000 1110 (Toggle bits 1, 2, and 3)

// Main function
int main() {
    // Define an 8-bit variable
    uint8_t foo = 0x00; // Variable starts with value 0x00 (0000 0000 in binary)

    printf("Initial value of foo: 0x%02X\n", foo);

    // 1. **Set bits 4 and 5**
    // Operation: foo |= 0x30;
    // Explanation:
    // foo:         0000 0000
    // OR 0x30:     0011 0000
    // Result:      0011 0000 (Bits 4 and 5 are set to 1)
    foo |= SET_BITS_4_5;
    printf("After setting bits 4 and 5: 0x%02X\n", foo);

    // 2. **Clear bits 6 and 7**
    // Operation: foo &= ~0xC0;
    // Explanation:
    // foo:         0011 0000
    // AND 0x3F:    0011 1111
    // Result:      0011 0000 (Bits 6 and 7 are cleared to 0)
    foo &= CLEAR_BITS_6_7;
    printf("After clearing bits 6 and 7: 0x%02X\n", foo);

    // 3. **Toggle bits 1, 2, and 3**
    // Operation: foo ^= 0x0E;
    // Explanation:
    // foo:         0011 0000
    // XOR 0x0E:    0000 1110
    // Result:      0011 1110 (Bits 1, 2, and 3 are toggled)
    foo ^= TOGGLE_BITS_1_3;
    printf("After toggling bits 1, 2, and 3: 0x%02X\n", foo);

    // 4. **Set a specific bit field (4-5) to value 3 while clearing bits 6-7**
    // Operation:
    // foo &= ~0xF0;  // Clear bits 4-7
    // Explanation:
    // foo:           0011 1110
    // AND 0x0F:      0000 1111
    // Result:        0000 1110

    // Then set bits 4-5:
    // foo |= (3 << 4);
    // Explanation:
    // 3 << 4:        0011 0000
    // OR:            0000 1110
    // Result:        0011 1110
    foo &= ~0xF0;
    foo |= (3 << 4);
    printf("After setting bit field (4-5) to 3: 0x%02X\n", foo);

    return 0;
}
