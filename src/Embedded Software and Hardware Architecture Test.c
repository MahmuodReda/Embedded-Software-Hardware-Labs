#include <stdio.h>
#include <stdint.h>
#include <stdlib.h> // For malloc and free

int main() {
    // Define a normal variable
    int32_t value = 42; // A 32-bit integer variable with an initial value of 42
    printf("Initial value: %d\n", value);

    // Get the address of the variable
    int32_t *ptr = &value; // Pointer pointing to the address of 'value'
    printf("Address of value: %p\n", (void *)ptr);

    // Access the value using pointer dereferencing
    printf("Value using pointer dereferencing: %d\n", *ptr);

    // Modify the value via the pointer
    *ptr = 99; // Writing a new value through the pointer
    printf("Modified value through pointer: %d\n", value);

    // Manually assign an address (simulated, not valid in most cases)
    uint8_t *manual_address = (uint8_t *)0x20000000; // Assuming address 0x20000000 is valid
    // *manual_address = 255; // Uncommenting this might cause undefined behavior

    // Dynamic memory allocation
    int32_t *dynamic_ptr = (int32_t *)malloc(sizeof(int32_t)); // Allocate memory for a 32-bit integer
    if (dynamic_ptr == NULL) {
        printf("Memory allocation failed\n");
        return 1; // Exit if memory allocation fails
    }
    *dynamic_ptr = 77; // Assign a value to the allocated memory
    printf("Value in dynamically allocated memory: %d\n", *dynamic_ptr);
    free(dynamic_ptr); // Free the allocated memory

    // Pointer typecasting
    uint32_t large_value = 0x12345678; // A 32-bit value
    uint8_t *byte_ptr = (uint8_t *)&large_value; // Cast the 32-bit pointer to an 8-bit pointer

    // Access each byte of the 32-bit value
    printf("Byte 0: 0x%02X\n", byte_ptr[0]); // Least significant byte
    printf("Byte 1: 0x%02X\n", byte_ptr[1]);
    printf("Byte 2: 0x%02X\n", byte_ptr[2]);
    printf("Byte 3: 0x%02X\n", byte_ptr[3]); // Most significant byte

    // Null pointer initialization
    int32_t *null_ptr = NULL; // Null pointer
    if (null_ptr == NULL) {
        printf("Pointer is null\n");
    }

    return 0;
}
