#include <stdio.h>
#include <stdlib.h>

/*
 * =============================================================================
 * VOID POINTERS (Generic Pointers)
 * =============================================================================
 * A void pointer (void*) is used to store the address of any data type.
 * It does not have an inherent type, so it cannot be dereferenced without an explicit typecast.
 *
 * Memory Consideration:
 * - Memory allocated via malloc() is on the Heap.
 * - The void pointer variable, if declared locally, is stored on the Stack.
 *
 * Important Notes:
 * - Must cast to the appropriate type before dereferencing.
 * - Pointer arithmetic is not permitted on a void pointer because the size of the data it points to is unknown.
 */
void demonstrate_void_pointer() {
    // Allocate memory on the Heap for one integer.
    void *vp = malloc(sizeof(int));
    if (vp == NULL) {
        printf("Memory allocation failed\n");
        return;
    }

    // Cast the void pointer to an int pointer and assign a value.
    *((int *)vp) = 123;
    // Expected output: Value via void pointer: 123
    printf("Value via void pointer: %d\n", *((int *)vp));

    // Free the allocated Heap memory to prevent memory leaks.
    free(vp);
}

/*
 * =============================================================================
 * DOUBLE POINTERS (Pointer to Pointer)
 * =============================================================================
 * A double pointer (e.g., int**) stores the address of another pointer.
 *
 * Memory Consideration:
 * - The double pointer variable is stored on the Stack (if declared locally).
 * - It points to memory (often allocated on the Heap) that is managed dynamically.
 *
 * Usage:
 * - Useful when you want a function to modify the pointer variable (i.e., change the memory address it points to).
 * - Commonly used in dynamic memory allocation functions.
 */
void allocate_memory(int **pp) {
    // Allocate memory on the Heap for one integer and assign its address to *pp.
    *pp = (int *)malloc(sizeof(int));
    if (*pp != NULL) {
        // Set the allocated memory's value to 456.
        **pp = 456;
    }
}

void demonstrate_double_pointer() {
    int *p = NULL; // Local pointer stored on the Stack.
    // Pass the address of the pointer so that allocate_memory() can modify it.
    allocate_memory(&p);

    if (p != NULL) {
        // Expected output: Value from double pointer allocation: 456
        printf("Value from double pointer allocation: %d\n", *p);
        // Free the allocated Heap memory.
        free(p);
    }
}

/*
 * =============================================================================
 * RESTRICT QUALIFIED POINTERS
 * =============================================================================
 * The 'restrict' qualifier tells the compiler that for the lifetime of the pointer,
 * only that pointer (or a pointer derived directly from it) will be used to access the memory.
 * This allows the compiler to optimize code by eliminating redundant memory accesses.
 *
 * Memory Consideration:
 * - Restrict-qualified pointers, when passed as parameters, are stored on the Stack.
 * - They may point to memory allocated on the Stack (e.g., local arrays) or the Heap (dynamic allocation).
 */
void sum_arrays(int *restrict a, int *restrict b, int *restrict result, int n) {
    // Loop through each element; the compiler can optimize this loop assuming a, b, and result do not overlap.
    for (int i = 0; i < n; i++) {
        result[i] = a[i] + b[i];
    }
}

void demonstrate_restrict_pointer() {
    // Local arrays stored on the Stack.
    int arr1[] = {1, 2, 3, 4, 5};
    int arr2[] = {10, 20, 30, 40, 50};
    int result[5]; // Local array for storing results.
    int n = sizeof(arr1) / sizeof(arr1[0]); // Array size computed at compile time.

    // Call sum_arrays() with restrict-qualified pointers.
    // Expected that 'arr1', 'arr2', and 'result' do not overlap, allowing for compiler optimizations.
    sum_arrays(arr1, arr2, result, n);

    // Expected output: Summed array: 11 22 33 44 55
    printf("Summed array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");
}

/*
 * =============================================================================
 * MEMORY LAYOUT IN C - Detailed Explanation
 * =============================================================================
 * 1. Text Section (.text):
 *    - Contains the executable machine code (functions such as main, demonstrate_void_pointer, etc.).
 *    - This section is read-only, protecting the code from modification during execution.
 *
 * 2. Data Section (.data and .bss):
 *    - Stores global and static variables.
 *    - Initialized globals are in .data, while uninitialized ones are in .bss (zero-initialized at runtime).
 *
 * 3. Stack:
 *    - Used for local variables, function call parameters, and return addresses.
 *    - Managed automatically in a Last-In-First-Out (LIFO) manner; fast access but limited in size.
 *    - In our examples, all local variables and function parameters reside on the Stack.
 *
 * 4. Heap:
 *    - Used for dynamic memory allocation (e.g., via malloc or calloc).
 *    - Memory on the Heap must be managed manually (allocated and freed).
 *    - Typically larger than the Stack, but with additional overhead due to manual management.
 *
 * In our examples:
 * - The void pointer example allocates an integer on the Heap and uses a local void pointer on the Stack.
 * - The double pointer example uses a local pointer on the Stack that points to Heap memory allocated dynamically.
 * - The restrict pointer example uses local arrays on the Stack, and the restrict qualifier allows the compiler to optimize array operations.
 */

/*
 * =============================================================================
 * MAIN FUNCTION: Combining All Advanced Pointer Examples
 * =============================================================================
 * This function calls the demonstration functions for void pointers, double pointers,
 * and restrict-qualified pointers, and prints expected outputs for each example.
 */
int main() {
    printf("\n--- Advanced Pointer Demonstration in C ---\n\n");

    /* VOID POINTER DEMONSTRATION */
    printf("--- Void Pointer Example ---\n");
    demonstrate_void_pointer();
    // Expected output: Value via void pointer: 123
    printf("\n");

    /* DOUBLE POINTER DEMONSTRATION */
    printf("--- Double Pointer Example ---\n");
    demonstrate_double_pointer();
    // Expected output: Value from double pointer allocation: 456
    printf("\n");

    /* RESTRICT POINTER DEMONSTRATION */
    printf("--- Restrict Pointer Example ---\n");
    demonstrate_restrict_pointer();
    // Expected output: Summed array: 11 22 33 44 55
    printf("\n");

    return 0; // When main returns, Stack memory is automatically reclaimed; Heap memory was freed manually.
}
