#include <stdio.h>
#include <stdint.h>

/*
 * =============================================================================
 * Example 1: Simple Union with Three uint8_t Members
 * =============================================================================
 * This union contains three uint8_t members (X, Y, Z).
 * All members share the same memory location, so the union's size is 1 byte.
 */
union SimpleUnion {
    uint8_t X;
    uint8_t Y;
    uint8_t Z;
};

void demonstrateSimpleUnion() {
    union SimpleUnion u;

    // Assign a value to member X.
    u.X = 13;
    // All members share the same memory, so they all display 13.
    printf("SimpleUnion - X: %u, Y: %u, Z: %u\n", u.X, u.Y, u.Z);

    // Now assign a new value to member Y, overwriting the previous value.
    u.Y = 65;
    // Expected output: All members reflect the new value (65).
    printf("After updating Y - X: %u, Y: %u, Z: %u\n", u.X, u.Y, u.Z);
}

/*
 * =============================================================================
 * Example 2: Mixed Union with Different Member Sizes
 * =============================================================================
 * This union contains:
 *   - a 16-byte array,
 *   - a uint8_t,
 *   - a uint16_t, and
 *   - a uint32_t.
 * The union's size is 16 bytes because the largest member is the array.
 */
union MixedUnion {
    uint8_t arr[16];
    uint8_t X;
    uint16_t Y;
    uint32_t Z;
};

void demonstrateMixedUnion() {
    union MixedUnion mu;

    // Initialize the array member with a pattern.
    for (int i = 0; i < 16; i++) {
        mu.arr[i] = i;
    }
    // Print the first 4 bytes of the array.
    printf("MixedUnion arr[0-3]: %u %u %u %u\n", mu.arr[0], mu.arr[1], mu.arr[2], mu.arr[3]);

    // Assign a value to member Z; this will overwrite the first 4 bytes of the union.
    mu.Z = 0xAABBCCDD;
    // Print the first 4 bytes to observe the effect on overlapping memory.
    printf("After updating Z, arr[0-3]: %u %u %u %u\n", mu.arr[0], mu.arr[1], mu.arr[2], mu.arr[3]);
}

/*
 * =============================================================================
 * Example 3: Union Containing Two Different Structures
 * =============================================================================
 * This union contains two structures:
 *   - StructOne: with three uint8_t members.
 *   - StructTwo: with three uint32_t members.
 * Updating one structure will overwrite the other because they share the same memory.
 */
struct StructOne {
    uint8_t a;
    uint8_t b;
    uint8_t c;
};

struct StructTwo {
    uint32_t x;
    uint32_t y;
    uint32_t z;
};

union StructUnion {
    struct StructOne s1;
    struct StructTwo s2;
};

void demonstrateStructUnion() {
    union StructUnion su;

    // Initialize StructOne members.
    su.s1.a = 10;
    su.s1.b = 20;
    su.s1.c = 30;
    printf("StructUnion - s1: a = %u, b = %u, c = %u\n", su.s1.a, su.s1.b, su.s1.c);

    // Update StructTwo members, overwriting s1.
    su.s2.x = 100;
    su.s2.y = 200;
    su.s2.z = 300;
    printf("StructUnion - s2: x = %u, y = %u, z = %u\n", su.s2.x, su.s2.y, su.s2.z);
}

/*
 * =============================================================================
 * Example 4: Union with 32-bit Integer and Float
 * =============================================================================
 * This union contains:
 *   - a 32-bit integer (int32_t)
 *   - a float
 * Both members share the same memory, which is typically 4 bytes.
 * This example demonstrates how writing to one member affects the reading of the other.
 */
union DataUnion {
    int32_t i;
    float f;
};

void demonstrateDataUnion() {
    union DataUnion du;

    // Assign a hexadecimal value to the integer member.
    // The value 0x40490FDB represents approximately 3.141593 as a float (IEEE 754).
    du.i = 0x40490FDB;
    printf("DataUnion as int: 0x%X\n", du.i);
    printf("DataUnion as float: %f\n", du.f);

    // Now assign a float value to the union; this overwrites the integer member.
    du.f = 2.71828;
    printf("\nAfter assigning float:\n");
    printf("DataUnion as int: 0x%X\n", du.i);
    printf("DataUnion as float: %f\n", du.f);
}

/*
 * =============================================================================
 * Example 5: Function Returning an Enum State
 * =============================================================================
 * This example demonstrates how to use an enum to represent a state and return it from a function.
 */
typedef enum {
    STATE_IDLE,       // 0: System is idle
    STATE_ACTIVE,     // 1: System is active
    STATE_ERROR,      // 2: System encountered an error
    STATE_UNKNOWN     // 3: State is unknown
} SystemState;

SystemState getSystemState(int condition) {
    if (condition == 0) {
        return STATE_ACTIVE;
    } else if (condition == -1) {
        return STATE_ERROR;
    } else {
        return STATE_UNKNOWN;
    }
}

void printSystemState(SystemState state) {
    printf("System State: %d\n", state);
}

/*
 * =============================================================================
 * MAIN FUNCTION: Combining All Examples
 * =============================================================================
 * This main function demonstrates:
 * 1. A simple union with identical members (SimpleUnion).
 * 2. A union with members of different sizes (MixedUnion).
 * 3. A union containing structures (StructUnion).
 * 4. A union with a 32-bit integer and a float (DataUnion).
 * 5. A function that returns an enum state and printing that state.
 */
int main() {
    printf("\n--- Union and Enum Demonstration ---\n\n");

    /* Example 1: Simple Union */
    printf("--- Simple Union Example ---\n");
    demonstrateSimpleUnion();
    // Expected outputs:
    // SimpleUnion - X: 13, Y: 13, Z: 13
    // After updating Y - X: 65, Y: 65, Z: 65
    printf("\n");

    /* Example 2: Mixed Union with Different Member Sizes */
    printf("--- Mixed Union Example ---\n");
    demonstrateMixedUnion();
    // Expected outputs:
    // MixedUnion arr[0-3]: 0 1 2 3
    // After updating Z, arr[0-3]: (Byte values corresponding to 0xAABBCCDD)
    printf("\n");

    /* Example 3: Struct Union Example */
    printf("--- Struct Union Example ---\n");
    demonstrateStructUnion();
    // Expected outputs:
    // StructUnion - s1: a = 10, b = 20, c = 30
    // StructUnion - s2: x = 100, y = 200, z = 300
    printf("\n");

    /* Example 4: Data Union Example (int32_t and float) */
    printf("--- Data Union Example (int32_t and float) ---\n");
    demonstrateDataUnion();
    // Expected outputs:
    // DataUnion as int: 0x40490FDB
    // DataUnion as float: 3.141593 (approximately)
    // After assigning float, outputs reflect the new float value and its raw binary representation.
    printf("\n");

    /* Example 5: Function Returning an Enum */
    printf("--- Function Returning Enum Example ---\n");
    int condition = 0;  // Test condition for active state
    SystemState state = getSystemState(condition);
    printSystemState(state);  // Expected output: System State: 1 (STATE_ACTIVE)

    condition = -1;  // Test condition for error state
    state = getSystemState(condition);
    printSystemState(state);  // Expected output: System State: 2 (STATE_ERROR)

    condition = 5;   // Test condition for unknown state
    state = getSystemState(condition);
    printSystemState(state);  // Expected output: System State: 3 (STATE_UNKNOWN)

    printf("\n");
    return 0;
}

//
//	--- Union and Enum Demonstration ---
//
//	--- Simple Union Example ---
//	SimpleUnion - X: 13, Y: 13, Z: 13
//	After updating Y - X: 65, Y: 65, Z: 65
//
//	--- Mixed Union Example ---
//	MixedUnion arr[0-3]: 0 1 2 3
//	After updating Z, arr[0-3]: 221 204 187 170
//
//	--- Struct Union Example ---
//	StructUnion - s1: a = 10, b = 20, c = 30
//	StructUnion - s2: x = 100, y = 200, z = 300
//
//	--- Data Union Example (int32_t and float) ---
//	DataUnion as int: 0x40490FDB
//	DataUnion as float: 3.141593
//
//	After assigning float:
//	DataUnion as int: 0x402DF84D
//	DataUnion as float: 2.718280
//
//	--- Function Returning Enum Example ---
//	System State: 1
//	System State: 2
//	System State: 3


