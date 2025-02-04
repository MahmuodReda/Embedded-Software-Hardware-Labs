#include <stdio.h>

// Macro to swap two values using bitwise XOR operation
// Memory usage: Registers only (does not use Stack or Heap)
// Reason: XOR swap avoids the need for a temporary variable, reducing memory usage.
#define SWAP(a, b) ((a) ^= (b), (b) ^= (a), (a) ^= (b))

// Macro to determine the size of an array at compile-time
// Memory usage: No runtime memory usage, computed at compile-time
// Reason: This macro ensures efficiency by eliminating runtime calculations.
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

// Inline function to return the maximum of two numbers
// Memory usage: Stack (parameters are passed via registers or stack)
// Reason: Declaring it as "inline" reduces function call overhead, avoiding stack frame creation
static inline int max(int a, int b) {
    return (a > b) ? a : b;
}

// Inline function to return the minimum of two numbers
// Memory usage: Stack (parameters passed via registers or stack)
// Reason: Inline functions allow the compiler to optimize the code by replacing calls with direct computations
static inline int min(int a, int b) {
    return (a < b) ? a : b;
}

// Function to reverse an array in place
// Memory usage: Stack (local variables stored in stack frame)
// Reason: In-place modification avoids heap allocation, making it more memory-efficient
void reverse_array(int *arr, int size) {
    for (int i = 0; i < size / 2; i++) {
        SWAP(arr[i], arr[size - 1 - i]); // Swapping elements using XOR swap
    }
    // Memory impact: Only loop counter variables use stack space, no heap allocation.
}

// Function to print an array
// Memory usage: Stack (local variables) + standard output buffer (Heap, managed by stdout)
// Reason: Efficient memory usage by leveraging existing stdout buffering
void print_array(const int *arr, int size) {
    printf("Array: "); // Output buffer uses Heap memory for efficiency
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]); // Each call to printf writes to the output buffer (Heap-managed)
    }
    printf("\n");
    // Memory impact: Minimal stack usage, utilizes existing stdout buffering mechanism.
}

int main() {
    // Static allocation of an array (Memory: Stack since it's a local variable)
    // Reason: Using stack ensures automatic deallocation when function exits, avoiding manual memory management.
    int numbers[] = {1, 2, 3, 4, 5};
    int size = ARRAY_SIZE(numbers); // Computed at compile-time, no runtime memory usage

    // Print original array
    print_array(numbers, size);

    // Reverse the array (Modifies in place, no extra memory allocation)
    reverse_array(numbers, size);

    // Print reversed array
    print_array(numbers, size);

    // Demonstrate max and min functions
    // Memory usage: Stack (temporary storage for function parameters)
    int a = 10, b = 20; // Stack allocation, automatically managed
    printf("Max of %d and %d is %d\n", a, b, max(a, b));
    printf("Min of %d and %d is %d\n", a, b, min(a, b));

    return 0; // Program termination: Stack memory is automatically freed
}

//	Array: 1 2 3 4 5
//	Array: 5 4 3 2 1
//	Max of 10 and 20 is 20
//	Min of 10 and 20 is 10
