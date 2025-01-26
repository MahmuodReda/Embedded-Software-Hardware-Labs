#include <stdint.h>
#include <stdio.h>

// Define full bit masks for 16 bits with detailed binary explanation
#define BIT0     (uint16_t)(0x0001) // 0x0001 = 0000 0000 0000 0001 => Bit 0
#define BIT1     (uint16_t)(0x0002) // 0x0002 = 0000 0000 0000 0010 => Bit 1
#define BIT2     (uint16_t)(0x0004) // 0x0004 = 0000 0000 0000 0100 => Bit 2
#define BIT3     (uint16_t)(0x0008) // 0x0008 = 0000 0000 0000 1000 => Bit 3
#define BIT4     (uint16_t)(0x0010) // 0x0010 = 0000 0000 0001 0000 => Bit 4
#define BIT5     (uint16_t)(0x0020) // 0x0020 = 0000 0000 0010 0000 => Bit 5
#define BIT6     (uint16_t)(0x0040) // 0x0040 = 0000 0000 0100 0000 => Bit 6
#define BIT7     (uint16_t)(0x0080) // 0x0080 = 0000 0000 1000 0000 => Bit 7
#define BIT8     (uint16_t)(0x0100) // 0x0100 = 0000 0001 0000 0000 => Bit 8
#define BIT9     (uint16_t)(0x0200) // 0x0200 = 0000 0010 0000 0000 => Bit 9
#define BITA     (uint16_t)(0x0400) // 0x0400 = 0000 0100 0000 0000 => Bit 10
#define BITB     (uint16_t)(0x0800) // 0x0800 = 0000 1000 0000 0000 => Bit 11
#define BITC     (uint16_t)(0x1000) // 0x1000 = 0001 0000 0000 0000 => Bit 12
#define BITD     (uint16_t)(0x2000) // 0x2000 = 0010 0000 0000 0000 => Bit 13
#define BITE     (uint16_t)(0x4000) // 0x4000 = 0100 0000 0000 0000 => Bit 14
#define BITF     (uint16_t)(0x8000) // 0x8000 = 1000 0000 0000 0000 => Bit 15

int main() {
    // Define a 16-bit variable
    uint16_t foo = 0x0000; // Initial value: 0x0000 (0000 0000 0000 0000 in binary)
    printf("Initial value of foo: 0x%04X\n", foo);

    // 1. Set bits 0, 5, and 9
    // Operation: foo |= (BIT0 | BIT5 | BIT9);
    // Explanation:
    // foo:         0000 0000 0000 0000
    // OR 0x0221:   0000 0010 0010 0001 (BIT0 | BIT5 | BIT9)
    // Result:      0000 0010 0010 0001
    foo |= (BIT0 | BIT5 | BIT9);
    printf("After setting bits 0, 5, and 9: 0x%04X\n", foo);

    // 2. Clear bits 0 and 5
    // Operation: foo &= ~(BIT0 | BIT5);
    // Explanation:
    // foo:         0000 0010 0010 0001
    // AND ~0x0021: 1111 1101 1101 1110
    // Result:      0000 0010 0010 0000
    foo &= ~(BIT0 | BIT5);
    printf("After clearing bits 0 and 5: 0x%04X\n", foo);

    // 3. Toggle bits 3 and 12
    // Operation: foo ^= (BIT3 | BITC);
    // Explanation:
    // foo:         0000 0010 0010 0000
    // XOR 0x1008:  0001 0000 0000 1000 (BIT3 | BITC)
    // Result:      0001 0010 0010 1000
    foo ^= (BIT3 | BITC);
    printf("After toggling bits 3 and 12: 0x%04X\n", foo);

    // 4. Set all bits
    // Operation: foo |= 0xFFFF;
    // Explanation:
    // foo:         0001 0010 0010 1000
    // OR 0xFFFF:   1111 1111 1111 1111
    // Result:      1111 1111 1111 1111
    foo |= 0xFFFF;
    printf("After setting all bits: 0x%04X\n", foo);

    // 5. Clear all bits except bits 2, 7, and F
    // Operation: foo &= (BIT2 | BIT7 | BITF);
    // Explanation:
    // foo:         1111 1111 1111 1111
    // AND 0x8084:  1000 0000 1000 0100 (BIT2 | BIT7 | BITF)
    // Result:      1000 0000 1000 0100
    foo &= (BIT2 | BIT7 | BITF);
    printf("After clearing all bits except 2, 7, and F: 0x%04X\n", foo);

    // 6. Shift left by 3 bits
    // Operation: foo <<= 3;
    // Explanation:
    // foo:         1000 0000 1000 0100
    // Shift left:  0000 0000 0100 0011 (discard overflow)
    foo <<= 3;
    printf("After left shifting by 3: 0x%04X\n", foo);

    // 7. Shift right by 2 bits
    // Operation: foo >>= 2;
    // Explanation:
    // foo:         0000 0000 0100 0011
    // Shift right: 0000 0000 0001 0000
    foo >>= 2;
    printf("After right shifting by 2: 0x%04X\n", foo);

    // 8. Check if a specific bit (bit 7) is set
    // Operation: foo & BIT7;
    // Explanation:
    // foo:         0000 0000 0001 0000
    // AND 0x0080:  0000 0000 0000 0000 (BIT7 not set)
    if (foo & BIT7) {
        printf("Bit 7 is set.\n");
    } else {
        printf("Bit 7 is not set.\n");
    }

    // 9. Modify a specific field (bits 10-13) to 0x5 (0101)
    // Operation: foo &= ~(BITA | BITB | BITC | BITD); foo |= (0x5 << 10);
    // Explanation:
    // Clear bits 10-13:
    // foo:         0000 0000 0001 0000
    // AND 0x03FF:  0000 0000 0001 0000
    // Set field to 0x5:
    // OR 0x1400:   0001 0100 0001 0000
    foo &= ~(BITA | BITB | BITC | BITD);
    foo |= (0x5 << 10);
    printf("After modifying field (10-13) to 0x5: 0x%04X\n", foo);

    return 0;
}
