#include <stdio.h>
#include <stdint.h>

// Enum to define the type of Endianness (Little Endian or Big Endian)
typedef enum {
    LITTLE_ENDIAN,  ///< Represents Little Endian byte order
    BIG_ENDIAN      ///< Represents Big Endian byte order
} Endianness;

/**
 * @brief: Swaps the byte order of a 32-bit unsigned integer in place.
 *         Converts the input value between Little Endian and Big Endian.
 * @param ptr: Pointer to the 32-bit unsigned integer to be swapped.
 */
void byte_swap32(uint32_t *ptr) {
    uint8_t i, temp_byte;  // Temporary storage for byte swapping

    // Loop to swap bytes in place
    for (i = 0; i < 2; i++) {
        // Swap the i-th byte with the (3-i)-th byte
        temp_byte = *((uint8_t*)ptr + (3 - i));  // Store the (3-i)-th byte
        *((uint8_t*)ptr + (3 - i)) = *((uint8_t*)ptr + i);  // Move i-th byte to (3-i)
        *((uint8_t*)ptr + i) = temp_byte;  // Place the stored byte in the i-th position
    }
}

/**
 * @brief: Prints the memory layout of a 32-bit integer in bytes.
 * @param value: The 32-bit unsigned integer to be displayed.
 */
void print_memory_layout(uint32_t value) {
    uint8_t* byte_ptr = (uint8_t*)&value;  // Treat the value as an array of bytes

    printf("Memory Layout (Address : Data):\n");
    for (int i = 0; i < 4; i++) {
        printf("Address 0x%02X: 0x%02X\n", i, byte_ptr[i]);
    }
    printf("\n");
}

int main() {
    uint32_t num = 0x12345678;  // Example value to demonstrate the function

    // Print the original value in hexadecimal format
    printf("Original value: 0x%08X\n", num);
    print_memory_layout(num);  // Print Little Endian memory layout

    // Swap the endianness using byte_swap32
    byte_swap32(&num);
    printf("After byte swapping:\n");
    print_memory_layout(num);  // Print the new memory layout after swapping

    return 0;
}

//	Original value: 0x12345678
//	Memory Layout (Address : Data):
//	Address 0x00: 0x78
//	Address 0x01: 0x56
//	Address 0x02: 0x34
//	Address 0x03: 0x12
//
//	After byte swapping:
//	Memory Layout (Address : Data):
//	Address 0x00: 0x12
//	Address 0x01: 0x34
//	Address 0x02: 0x56
//	Address 0x03: 0x78
