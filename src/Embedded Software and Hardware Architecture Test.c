#include <stdio.h>

/*
 * -------------------------------------------------------------------------------
 * Example 1: Basic Function Pointer
 * -------------------------------------------------------------------------------
 * In this simplest example, we define a function that takes no parameters and returns void.
 * We then declare a function pointer that can point to such a function, assign it, and call it.
 *
 * Memory Consideration:
 * - The function code is stored in the Text Section (.text).
 * - The function pointer variable is a local variable, stored on the Stack.
 */
void sayHello() {
    printf("Hello, World!\n"); // This function prints "Hello, World!"
}

/*
 * -------------------------------------------------------------------------------
 * Example 2: Function Pointer with Parameters
 * -------------------------------------------------------------------------------
 * Here, we define a function that takes two integers as parameters and returns an integer (e.g., add).
 * We declare a function pointer matching that signature, assign it to the function, and then call it.
 *
 * Memory Consideration:
 * - The function and its code reside in the Text Section.
 * - The function pointer variable is stored on the Stack.
 */
int add(int a, int b) {
    return a + b;
}

/*
 * -------------------------------------------------------------------------------
 * Example 3: Function Pointer Array
 * -------------------------------------------------------------------------------
 * In this example, we use an array of function pointers to store multiple functions with the same signature.
 * This is similar to an Interrupt Vector Table or state machine table, where each element of the array
 * corresponds to a different function that can be called dynamically.
 *
 * Memory Consideration:
 * - The array of function pointers is a local variable stored on the Stack.
 * - Each function's code resides in the Text Section.
 *
 * We also use a typedef to simplify the declaration of the function pointer type.
 */
typedef int (*MathFunc)(int, int);  // Define a type for function pointers that take two ints and return int

int multiply(int a, int b) {
    return a * b;
}

int main() {
    // ------------------- Example 1: Basic Function Pointer -------------------
    // Declare a function pointer for a function that returns void and takes no parameters.
    void (*funcPtr)() = sayHello;  // Assign the function 'sayHello' to the pointer
    funcPtr();  // Call the function via the function pointer
    // Expected output: "Hello, World!"

    // ------------------- Example 2: Function Pointer with Parameters -------------------
    // Declare a function pointer for functions that take two ints and return an int.
    int (*mathPtr)(int, int) = add;  // Assign the function 'add' to the pointer
    int sum = mathPtr(3, 4);         // Call the function via the pointer
    printf("Sum (using add): %d\n", sum);
    // Expected output: "Sum (using add): 7"

    // Now, change the function pointer to point to 'multiply'
    mathPtr = multiply;            // Reassign the pointer to a different function with the same signature
    int product = mathPtr(3, 4);     // Call the new function via the pointer
    printf("Product (using multiply): %d\n", product);
    // Expected output: "Product (using multiply): 12"

    // ------------------- Example 3: Function Pointer Array -------------------
    // Declare an array of function pointers using the typedef MathFunc.
    MathFunc funcArray[2] = { add, multiply };

    // Call the first function in the array (add)
    int result1 = funcArray[0](5, 6);
    printf("Sum (using function pointer array): %d\n", result1);
    // Expected output: "Sum (using function pointer array): 11"

    // Call the second function in the array (multiply)
    int result2 = funcArray[1](5, 6);
    printf("Product (using function pointer array): %d\n", result2);
    // Expected output: "Product (using function pointer array): 30"

    return 0;
}
