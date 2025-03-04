#include <stdio.h>

/*
 * =============================================================================
 * VOID POINTER EXAMPLE (Without malloc)
 * =============================================================================
 *
 * This example demonstrates a void pointer that simply tracks the address
 * of a local variable. Here, we do not allocate memory dynamically.
 *
 * Memory Consideration:
 * - The local variable 'x' is stored on the Stack.
 * - The void pointer 'vp' is also stored on the Stack.
 *
 * Key Points:
 * - A void pointer holds a generic address and must be cast to a specific type
 *   before dereferencing.
 */
void demonstrate_void_pointer_no_malloc() {
    int x = 321;               // Local variable on the Stack
    void *vp = &x;             // Assign the address of x to a void pointer
    // Expected output: Value via void pointer (no malloc): 321
    printf("Value via void pointer (no malloc): %d\n", *((int *)vp));
}

/*
 * =============================================================================
 * DOUBLE POINTER EXAMPLE (Without malloc)
 * =============================================================================
 *
 * This example demonstrates a double pointer by updating the address of a pointer
 * using a statically allocated variable.
 *
 * Memory Consideration:
 * - The pointer 'p' is a local variable stored on the Stack.
 * - The function 'updatePointer' assigns 'p' to point to a static variable.
 *
 * Key Points:
 * - The double pointer allows a function to modify the pointer's address directly.
 */
void updatePointer(int **pp) {
    static int static_val = 789;  // Static variable stored in the Data Section (.data)
    *pp = &static_val;            // Update the pointer to point to the static variable
}

void demonstrate_double_pointer_no_malloc() {
    int *p = NULL;                // Local pointer on the Stack
    updatePointer(&p);            // Pass the address of p to updatePointer
    if (p != NULL) {
        // Expected output: Value from double pointer update: 789
        printf("Value from double pointer update: %d\n", *p);
    }
}

/*
 * =============================================================================
 * RESTRICT QUALIFIED POINTERS EXAMPLE (Without malloc)
 * =============================================================================
 *
 * This example demonstrates the use of restrict-qualified pointers by summing two arrays.
 * The 'restrict' qualifier informs the compiler that the memory areas referenced by the pointers
 * do not overlap, enabling optimized loop performance.
 *
 * Memory Consideration:
 * - The arrays 'a', 'b', and 'result' are all local variables stored on the Stack.
 *
 * Key Points:
 * - The restrict qualifier allows the compiler to assume that the arrays do not alias,
 *   which may lead to improved performance in tight loops.
 */
void sum_arrays(int *restrict a, int *restrict b, int *restrict result, int n) {
    for (int i = 0; i < n; i++) {
        result[i] = a[i] + b[i];
    }
}

void demonstrate_restrict_pointer_no_malloc() {
    int a[] = {2, 4, 6, 8};      // Local array on the Stack
    int b[] = {1, 3, 5, 7};      // Local array on the Stack
    int result[4];             // Local array for storing the sum
    int n = sizeof(a) / sizeof(a[0]);  // Compute array size at compile time

    // Sum the arrays using restrict-qualified pointers for optimization.
    sum_arrays(a, b, result, n);

    // Expected output: Summed array (no malloc): 3 7 11 15
    printf("Summed array (no malloc): ");
    for (int i = 0; i < n; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");
}

/*
 * =============================================================================
 * MAIN FUNCTION: Combining All Advanced Pointer Examples
 * =============================================================================
 *
 * This main function calls the three demonstration functions:
 * 1. Void pointer example without malloc.
 * 2. Double pointer example without using malloc (using a static variable).
 * 3. Restrict-qualified pointers example for array summation.
 *
 * All local variables are stored on the Stack, while static variables are stored in the Data Section.
 */
int main() {
    printf("\n--- Advanced Pointer Demonstration (Without malloc) in C ---\n\n");

    /* VOID POINTER DEMONSTRATION */
    printf("--- Void Pointer Example (No malloc) ---\n");
    demonstrate_void_pointer_no_malloc();
    // Expected output: Value via void pointer (no malloc): 321
    printf("\n");

    /* DOUBLE POINTER DEMONSTRATION */
    printf("--- Double Pointer Example (No malloc) ---\n");
    demonstrate_double_pointer_no_malloc();
    // Expected output: Value from double pointer update: 789
    printf("\n");

    /* RESTRICT POINTER DEMONSTRATION */
    printf("--- Restrict Pointer Example (No malloc) ---\n");
    demonstrate_restrict_pointer_no_malloc();
    // Expected output: Summed array (no malloc): 3 7 11 15
    printf("\n");

    return 0; // When main returns, all Stack memory is automatically reclaimed.
}
