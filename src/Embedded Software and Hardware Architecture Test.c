#include <stdio.h>
#include <stdint.h>

// Enum to define the type of Endianness (Little Endian or Big Endian)
typedef enum {
    LITTLE_ENDIAN,  ///< Represents Little Endian byte order
    BIG_ENDIAN      ///< Represents Big Endian byte order
} Endianness;

/**
 * @brief: Swaps the byte order of a 32-bit unsigned integer.
 *         Converts the input value between Little Endian and Big Endian.
 * @param value: The 32-bit unsigned integer to be swapped.
 * @param mode: Specifies the desired byte order (LITTLE_ENDIAN or BIG_ENDIAN).
 *              - LITTLE_ENDIAN: Convert to Little Endian
 *              - BIG_ENDIAN: Convert to Big Endian
 * @retval: Returns the value with its byte order swapped if the mode is valid.
 *          If the mode is invalid, it returns the original value.
 */
uint32_t swap_endianness(uint32_t value, Endianness mode) {
    uint32_t swapped;  // Variable to hold the swapped result

    // Check if the mode is either BIG_ENDIAN or LITTLE_ENDIAN
    if (mode == BIG_ENDIAN || mode == LITTLE_ENDIAN) {
        // Perform byte swapping
        swapped = ((value & 0x000000FF) << 24) |  // Move the least significant byte to the most significant position
                  ((value & 0x0000FF00) << 8)  |  // Move the second least significant byte two positions up
                  ((value & 0x00FF0000) >> 8)  |  // Move the second most significant byte two positions down
                  ((value & 0xFF000000) >> 24);   // Move the most significant byte to the least significant position
    } else {
        // If the mode is invalid, return the original value
        swapped = value;
    }

    return swapped;  // Return the swapped value or the original value
}

int main() {
    uint32_t num = 0x12345678;  // Example value to demonstrate the function

    // Print the original value in hexadecimal format
    printf("Original value: 0x%08X\n", num);

    // Convert the value to Big Endian and print the result
    uint32_t big_endian = swap_endianness(num, BIG_ENDIAN);
    printf("Big Endian: 0x%08X\n", big_endian);

    // Convert the value back to Little Endian and print the result
    uint32_t little_endian = swap_endianness(big_endian, LITTLE_ENDIAN);
    printf("Little Endian: 0x%08X\n", little_endian);

    return 0;
}

//	Original value: 0x12345678
//	Big Endian: 0x78563412
//	Little Endian: 0x12345678
