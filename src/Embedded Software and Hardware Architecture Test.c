#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Enumeration for LIFO buffer status
typedef enum {
    LB_OK,     // Operation succeeded
    LB_FULL,   // Buffer is full, cannot add new item
    LB_EMPTY,  // Buffer is empty, nothing to remove
    LB_NULL    // Buffer pointer is null (error condition)
} LB_Status;

// LIFO buffer structure definition
typedef struct {
    uint8_t *base;     // Base pointer to the buffer memory region
    uint8_t *tip;      // Current pointer (head) where next item will be added
    uint32_t capacity; // Total capacity of the buffer (number of items)
} LIFO_Buffer;

/*
 * Function: LIFO_init
 * -------------------
 * Initializes a LIFO buffer.
 *
 * Parameters:
 *   buf: Pointer to the LIFO_Buffer structure.
 *   capacity: The total number of items that the buffer can hold.
 *
 * Returns:
 *   LB_OK if initialization is successful, LB_NULL if memory allocation fails.
 *
 * Memory:
 *   Allocates a buffer region on the heap for 'capacity' items of type uint8_t.
 *   The structure itself is typically stored on the stack.
 */
LB_Status LIFO_init(LIFO_Buffer *buf, uint32_t capacity) {
    if (buf == NULL) return LB_NULL;
    buf->capacity = capacity;
    // Allocate memory for the buffer region on the heap.
    buf->base = (uint8_t *)malloc(capacity * sizeof(uint8_t));
    if (buf->base == NULL) return LB_NULL;
    // Initially, the tip is equal to the base (buffer is empty).
    buf->tip = buf->base;
    return LB_OK;
}

/*
 * Function: LIFO_isFull
 * ---------------------
 * Checks if the LIFO buffer is full.
 *
 * Parameters:
 *   buf: Pointer to the LIFO_Buffer structure.
 *
 * Returns:
 *   LB_FULL if the buffer is full, otherwise LB_OK.
 */
LB_Status LIFO_isFull(LIFO_Buffer *buf) {
    if (buf == NULL || buf->base == NULL) return LB_NULL;
    // Calculate the number of items in the buffer
    if ((uint32_t)(buf->tip - buf->base) >= buf->capacity) {
        return LB_FULL;
    }
    return LB_OK;
}

/*
 * Function: LIFO_isEmpty
 * ----------------------
 * Checks if the LIFO buffer is empty.
 *
 * Parameters:
 *   buf: Pointer to the LIFO_Buffer structure.
 *
 * Returns:
 *   LB_EMPTY if the buffer is empty, otherwise LB_OK.
 */
LB_Status LIFO_isEmpty(LIFO_Buffer *buf) {
    if (buf == NULL || buf->base == NULL) return LB_NULL;
    if (buf->tip == buf->base) {
        return LB_EMPTY;
    }
    return LB_OK;
}

/*
 * Function: LIFO_push
 * -------------------
 * Adds an item to the LIFO buffer.
 *
 * Parameters:
 *   buf: Pointer to the LIFO_Buffer structure.
 *   data: The data item (of type uint8_t) to add to the buffer.
 *
 * Returns:
 *   LB_OK if the push operation is successful.
 *   LB_FULL if the buffer is full.
 */
LB_Status LIFO_push(LIFO_Buffer *buf, uint8_t data) {
    if (buf == NULL || buf->base == NULL) return LB_NULL;
    // Check if the buffer is full
    if (LIFO_isFull(buf) == LB_FULL) {
        return LB_FULL;
    }
    // Add the new item at the tip and move the tip pointer to the next free location
    *(buf->tip) = data;
    buf->tip++;
    return LB_OK;
}

/*
 * Function: LIFO_pop
 * ------------------
 * Removes the most recently added item from the LIFO buffer.
 *
 * Parameters:
 *   buf: Pointer to the LIFO_Buffer structure.
 *   data: Pointer to store the popped item.
 *
 * Returns:
 *   LB_OK if the pop operation is successful.
 *   LB_EMPTY if the buffer is empty.
 */
LB_Status LIFO_pop(LIFO_Buffer *buf, uint8_t *data) {
    if (buf == NULL || buf->base == NULL || data == NULL) return LB_NULL;
    // Check if the buffer is empty
    if (LIFO_isEmpty(buf) == LB_EMPTY) {
        return LB_EMPTY;
    }
    // Move the tip pointer back to the previous item and retrieve that item
    buf->tip--;
    *data = *(buf->tip);
    return LB_OK;
}

/*
 * Function: LIFO_free
 * -------------------
 * Frees the allocated memory for the buffer region.
 *
 * Parameters:
 *   buf: Pointer to the LIFO_Buffer structure.
 */
void LIFO_free(LIFO_Buffer *buf) {
    if (buf && buf->base) {
        free(buf->base);
        buf->base = NULL;
        buf->tip = NULL;
    }
}

/*
 * =============================================================================
 * MAIN FUNCTION: Demonstrating the LIFO Buffer
 * =============================================================================
 * This main function demonstrates how to:
 * 1. Initialize a LIFO buffer.
 * 2. Push items into the buffer.
 * 3. Pop items from the buffer.
 * 4. Check if the buffer is full or empty.
 * 5. Print the size of the LIFO_Buffer structure.
 *
 * Memory:
 * - The LIFO_Buffer structure is typically stored on the Stack.
 * - The buffer region is allocated on the Heap.
 */
int main() {
    // Create a LIFO buffer structure on the stack.
    LIFO_Buffer lifo;
    uint32_t capacity = 5;  // Define capacity of 5 items

    // Initialize the LIFO buffer with the given capacity.
    if (LIFO_init(&lifo, capacity) != LB_OK) {
        printf("Failed to initialize LIFO buffer.\n");
        return 1;
    }

    // Print the size of the LIFO_Buffer structure.
    printf("Size of LIFO_Buffer struct: %zu bytes\n", sizeof(LIFO_Buffer));

    // Push some temperature values (simulate sensor data) into the buffer.
    // For demonstration, we use arbitrary uint8_t values.
    for (uint8_t i = 10; i < 15; i++) {
        if (LIFO_push(&lifo, i) == LB_FULL) {
            printf("Buffer is full, cannot push value %d\n", i);
        } else {
            printf("Pushed value: %d\n", i);
        }
    }

    // Attempt to push one more value to test buffer full condition.
    if (LIFO_push(&lifo, 99) == LB_FULL) {
        printf("Buffer is full, cannot push value 99\n");
    }

    // Pop items from the buffer and print them.
    uint8_t data;
    printf("Popping items from LIFO buffer:\n");
    while (LIFO_pop(&lifo, &data) == LB_OK) {
        printf("Popped value: %d\n", data);
    }

    // Free the allocated buffer memory.
    LIFO_free(&lifo);

    return 0;
}

//		Size of LIFO_Buffer struct: 12 bytes
//		Pushed value: 10
//		Pushed value: 11
//		Pushed value: 12
//		Pushed value: 13
//		Pushed value: 14
//		Buffer is full, cannot push value 99
//		Popping items from LIFO buffer:
//		Popped value: 14
//		Popped value: 13
//		Popped value: 12
//		Popped value: 11
//		Popped value: 10
