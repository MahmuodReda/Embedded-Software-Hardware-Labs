#include <stdio.h>

/*
 * =============================================================================
 * EXAMPLE 1: BASIC ENUMERATION FOR MONTHS
 * =============================================================================
 * This example defines an enum called Month that lists all the months of the year.
 * Enums create a new integer-only data type and by default, the first value is 0,
 * with subsequent values auto-incremented by 1.
 *
 * Memory Consideration:
 * - The enum constants themselves do not consume memory until a variable of that enum type is declared.
 * - When a variable of type enum is declared, it is typically stored on the Stack (if local) or in the Data Section (if global).
 */
enum Month {
    JAN, // 0: January
    FEB, // 1: February
    MAR, // 2: March
    APR, // 3: April
    MAY, // 4: May
    JUN, // 5: June
    JUL, // 6: July
    AUG, // 7: August
    SEP, // 8: September
    OCT, // 9: October
    NOV, // 10: November
    DEC  // 11: December
};

// Function to print the value of a Month enum.
// This function takes an enum Month and prints its integer value.
void printMonth(enum Month m) {
    // Print the underlying integer value of the enum constant.
    printf("Month value: %d\n", m);
}

/*
 * =============================================================================
 * EXAMPLE 2: ENUMERATION WITH SPECIFIC VALUES FOR STATUS
 * =============================================================================
 * This example defines an enum for a circular buffer status (CB_Status) with explicit values.
 * Notice that we can assign specific integer values to each enum constant.
 * This is useful when the values have specific meaning or when interfacing with hardware.
 *
 * Memory Consideration:
 * - Like other enums, these constants only consume memory when a variable of type enum is declared.
 */
enum CB_Status {
    CB_EMPTY = 0,  // Circular Buffer is empty
    CB_FULL  = 1,  // Circular Buffer is full
    CB_ERROR = -1, // Error in Circular Buffer
    CB_NULL  = -2  // Circular Buffer is null or not initialized
};

// Function to print the status of the circular buffer.
void printCBStatus(enum CB_Status status) {
    printf("CB Status: %d\n", status);
}

/*
 * =============================================================================
 * EXAMPLE 3: TYPEDEF'ED ENUMERATION FOR SYSTEM STATE
 * =============================================================================
 * This example uses typedef with an enum to create a custom type for system states.
 * The typedef simplifies the syntax for declaring variables of that enum type.
 *
 * Memory Consideration:
 * - When a variable of this typedef'ed enum type is declared, it is stored on the Stack (if local)
 *   or in the Data Section (if global). The size of the enum is architecture dependent.
 */
typedef enum {
    RESET_e,    // Represents system reset (default 0)
    RUNNING_e,  // Represents system running (default 1)
    STOPPED_e,  // Represents system stopped (default 2)
    ERROR_e     // Represents system error (default 3)
} SystemState_e;

// Function to print the current system state.
void printSystemState(SystemState_e state) {
    printf("System State: %d\n", state);
}

/*
 * =============================================================================
 * EXAMPLE 4: FUNCTION THAT RETURNS AN ENUM VALUE
 * =============================================================================
 * This function simulates checking a system condition (using an error code)
 * and returns a corresponding system state as an enum.
 *
 * Function Behavior:
 * - If errorCode is 0, it returns RUNNING_e.
 * - Otherwise, it returns ERROR_e.
 * - This function demonstrates how enums can be used in function return types
 *   to clearly represent different states.
 */
SystemState_e getSystemState(int errorCode) {
    if (errorCode == 0) {
        return RUNNING_e;
    } else {
        return ERROR_e;
    }
}

/*
 * =============================================================================
 * MAIN FUNCTION: COMBINING ALL ENUMERATION EXAMPLES
 * =============================================================================
 * This main function demonstrates:
 * 1. A basic enum usage for months.
 * 2. An enum for circular buffer status with specific values.
 * 3. A typedef'ed enum for system state.
 * 4. A function returning a system state enum based on an error code.
 *
 * Memory Consideration:
 * - All local variables (including enum variables) are stored on the Stack.
 * - Enum constants themselves are compile-time constants and do not consume memory until used.
 */
int main() {
    printf("\n--- Enumeration Demonstration ---\n\n");

    /* Example 1: Basic Enumeration for Months */
    enum Month currentMonth = MAR;  // Set currentMonth to March (value 2)
    printf("--- Basic Enumeration (Month) ---\n");
    printMonth(currentMonth);  // Expected output: Month value: 2
    printf("\n");

    /* Example 2: Enumeration with Specific Values (Circular Buffer Status) */
    enum CB_Status bufferStatus = CB_FULL;  // Set bufferStatus to CB_FULL (value 1)
    printf("--- Enumeration with Specific Values (Circular Buffer Status) ---\n");
    printCBStatus(bufferStatus);  // Expected output: CB Status: 1
    printf("\n");

    /* Example 3: Typedef'ed Enumeration (System State) */
    SystemState_e sysState = RUNNING_e;  // Set sysState to RUNNING_e (value 1)
    printf("--- Typedef'ed Enumeration (System State) ---\n");
    printSystemState(sysState);  // Expected output: System State: 1
    printf("\n");

    /* Example 4: Function Returning an Enumeration (System State Based on Error Code) */
    printf("--- Function Returning Enumeration (System State) ---\n");
    int errorCode = 0;  // Simulate no error condition
    SystemState_e returnedState = getSystemState(errorCode);
    printSystemState(returnedState);  // Expected output when errorCode == 0: System State: 1 (RUNNING_e)

    errorCode = 100;  // Simulate an error condition
    returnedState = getSystemState(errorCode);
    printSystemState(returnedState);  // Expected output when errorCode != 0: System State: 3 (ERROR_e)
    printf("\n");

    return 0;
}
