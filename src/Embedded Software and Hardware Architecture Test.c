#include <stdio.h>
#include <stdint.h>

// Temporarily disable optimizations to compare the behavior of inlined and non-inlined functions
#pragma GCC push_options
#pragma GCC optimize("O0")  // Disable compiler optimizations (Optimization Level 0)

// Define a packed structure using the 'packed' attribute
// This ensures the structure uses the minimum possible memory without padding
typedef struct {
    uint8_t byte1;     // 1-byte variable
    uint16_t halfWord; // 2-byte variable
    uint32_t word;     // 4-byte variable
} __attribute__((packed)) PackedAlignedStruct;

// Define a standard structure without any special alignment attributes
// This structure will follow the default memory alignment rules of the compiler
typedef struct {
    uint8_t byte1;     // 1-byte variable
    uint16_t halfWord; // 2-byte variable
    uint32_t word;     // 4-byte variable
} StandardStruct;

// Define an inlined function with the 'always_inline' attribute
// This forces the compiler to insert the function's code directly at the call site
__attribute__((always_inline)) inline void inlinedFunction() {
    printf("Inlined function called.\n");  // Print to indicate the inlined function is called
}

// Define a normal function without inlining
// This function will be called using the traditional function call mechanism
void normalFunction() {
    printf("Normal function called.\n");  // Print to indicate the normal function is called
}

// Restore the default optimization settings
#pragma GCC pop_options

int main() {
    // Initialize instances of both structures with sample values
    PackedAlignedStruct packedStruct = {0x12, 0x3456, 0x789ABCDE};
    StandardStruct standardStruct = {0x12, 0x3456, 0x789ABCDE};

    // Display the memory layout comparison between packed and standard structures
    printf("=== Memory Layout Comparison ===\n");

    // Using %lu to print the size of the structures in bytes
    printf("Size of PackedAlignedStruct: %lu bytes\n", (unsigned long)sizeof(PackedAlignedStruct));
    printf("Size of StandardStruct: %lu bytes\n", (unsigned long)sizeof(StandardStruct));

    // Display the contents of each structure's members
    printf("\n=== Accessing Struct Members ===\n");
    printf("PackedAlignedStruct - byte1: 0x%02X, halfWord: 0x%04X, word: 0x%08X\n",
           packedStruct.byte1, packedStruct.halfWord, packedStruct.word);
    printf("StandardStruct - byte1: 0x%02X, halfWord: 0x%04X, word: 0x%08X\n",
           standardStruct.byte1, standardStruct.halfWord, standardStruct.word);

    // Compare inlined function call and normal function call behavior
    printf("\n=== Function Call Comparison ===\n");

    // Calling the inlined function to see how the compiler handles it
    printf("Calling inlined function:\n");
    inlinedFunction();  // Function code is inlined, no call overhead

    // Calling the normal function to compare with the inlined version
    printf("Calling normal function:\n");
    normalFunction();  // Function is called normally, introducing call overhead

    return 0;
}

//
//	=== Memory Layout Comparison ===
//	Size of PackedAlignedStruct: 7 bytes
//	Size of StandardStruct: 12 bytes
//
//	=== Accessing Struct Members ===
//	PackedAlignedStruct - byte1: 0x12, halfWord: 0x3456, word: 0x789ABCDE
//	StandardStruct - byte1: 0x12, halfWord: 0x3456, word: 0x789ABCDE
//
//	=== Function Call Comparison ===
//	Calling inlined function:
//	Inlined function called.
//	Calling normal function:
//	Normal function called.
