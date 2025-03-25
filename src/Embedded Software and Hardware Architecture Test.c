#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Define an enumeration to represent the buffer status.
typedef enum {
    CB_OK,      // Operation was successful.
    CB_FULL,    // The circular buffer is full.
    CB_EMPTY,   // The circular buffer is empty.
    CB_ERROR    // An error occurred (e.g., null pointer).
} CB_Status;

// Define a circular buffer structure (CB_t)
// This structure holds a pointer to the buffer memory, its capacity,
// and the current head and tail indices.
typedef struct {
    uint8_t *buffer;   // Pointer to the circular buffer array (stored on the Heap)
    uint32_t capacity; // Total capacity of the buffer (number of slots)
    uint32_t head;     // Index where the next element will be added (the "head")
    uint32_t tail;     // Index from where the next element will be removed (the "tail")
} CB_t;

/*
 * Function: CB_init
 * -----------------
 * Initializes the circular buffer by allocating memory for the buffer array,
 * setting the capacity, and initializing head and tail indices.
 *
 * Parameters:
 *   cb       - Pointer to the CB_t structure.
 *   capacity - Total number of elements the buffer can hold.
 *
 * Returns:
 *   CB_OK on success, or CB_ERROR if the allocation fails.
 *
 * Memory Consideration:
 *   - The buffer array is allocated on the Heap.
 *   - The CB_t structure itself is typically stored on the Stack.
 */
CB_Status CB_init(CB_t *cb, uint32_t capacity) {
    if (cb == NULL) return CB_ERROR;
    cb->capacity = capacity;
    // Allocate memory for the buffer region on the Heap.
    cb->buffer = (uint8_t*) malloc(capacity * sizeof(uint8_t));
    if (cb->buffer == NULL) return CB_ERROR;
    // Initialize head and tail to 0 (buffer is empty).
    cb->head = 0;
    cb->tail = 0;
    return CB_OK;
}

/*
 * Function: CB_isFull
 * -------------------
 * Checks whether the circular buffer is full.
 *
 * Returns:
 *   CB_FULL if the buffer is full; otherwise, CB_OK.
 *
 * Logic:
 *   - The buffer is full if the next head index equals the tail index,
 *     taking wrapping into account.
 */
CB_Status CB_isFull(CB_t *cb) {
    if (cb == NULL || cb->buffer == NULL) return CB_ERROR;
    if (((cb->head + 1) % cb->capacity) == cb->tail)
        return CB_FULL;
    return CB_OK;
}

/*
 * Function: CB_isEmpty
 * --------------------
 * Checks whether the circular buffer is empty.
 *
 * Returns:
 *   CB_EMPTY if the buffer is empty; otherwise, CB_OK.
 */
CB_Status CB_isEmpty(CB_t *cb) {
    if (cb == NULL || cb->buffer == NULL) return CB_ERROR;
    if (cb->head == cb->tail)
        return CB_EMPTY;
    return CB_OK;
}

/*
 * Function: CB_push
 * -----------------
 * Adds a new element to the circular buffer.
 *
 * Parameters:
 *   cb   - Pointer to the circular buffer structure.
 *   data - The data (uint8_t) to add.
 *
 * Returns:
 *   CB_OK if the push operation is successful;
 *   CB_FULL if the buffer is full.
 *
 * Logic:
 *   - Check if the buffer is full; if not, add the element at the head position.
 *   - Then, update the head index using modulo arithmetic to wrap around.
 */
CB_Status CB_push(CB_t *cb, uint8_t data) {
    if (cb == NULL || cb->buffer == NULL) return CB_ERROR;
    if (CB_isFull(cb) == CB_FULL) return CB_FULL;
    cb->buffer[cb->head] = data;
    cb->head = (cb->head + 1) % cb->capacity;
    return CB_OK;
}

/*
 * Function: CB_pop
 * ----------------
 * Removes and retrieves the oldest element from the circular buffer.
 *
 * Parameters:
 *   cb   - Pointer to the circular buffer structure.
 *   data - Pointer to store the popped data.
 *
 * Returns:
 *   CB_OK if the pop operation is successful;
 *   CB_EMPTY if the buffer is empty.
 *
 * Logic:
 *   - Check if the buffer is empty; if not, retrieve the element at the tail index.
 *   - Then, update the tail index using modulo arithmetic.
 */
CB_Status CB_pop(CB_t *cb, uint8_t *data) {
    if (cb == NULL || cb->buffer == NULL || data == NULL) return CB_ERROR;
    if (CB_isEmpty(cb) == CB_EMPTY) return CB_EMPTY;
    *data = cb->buffer[cb->tail];
    cb->tail = (cb->tail + 1) % cb->capacity;
    return CB_OK;
}

/*
 * Function: CB_free
 * -----------------
 * Frees the memory allocated for the circular buffer.
 *
 * Parameters:
 *   cb - Pointer to the circular buffer structure.
 *
 * Memory Consideration:
 *   - Frees the Heap memory allocated for the buffer array.
 */
void CB_free(CB_t *cb) {
    if (cb && cb->buffer) {
        free(cb->buffer);
        cb->buffer = NULL;
    }
}

/*
 * =============================================================================
 * MAIN FUNCTION: Demonstrating the Circular Buffer
 * =============================================================================
 * This main function demonstrates:
 *   1. Initialization of a circular buffer.
 *   2. Pushing data into the buffer.
 *   3. Popping data from the buffer.
 *   4. Checking the buffer status.
 *   5. Printing the size of the CB_t structure.
 *
 * Memory:
 *   - The CB_t structure is stored on the Stack.
 *   - The buffer array is allocated on the Heap.
 */
int main() {
    CB_t cb;
    uint32_t capacity = 5;  // Note: With this design, one slot is reserved to distinguish full from empty.

    // Initialize the circular buffer.
    if (CB_init(&cb, capacity) != CB_OK) {
        printf("Failed to initialize circular buffer.\n");
        return 1;
    }

    // Print the size of the circular buffer structure.
    printf("Size of CB_t structure: %zu bytes\n", sizeof(CB_t));

    // Push elements into the buffer.
    printf("Pushing elements into the circular buffer:\n");
    for (uint8_t i = 10; i < 14; i++) {
        if (CB_push(&cb, i) == CB_FULL) {
            printf("Buffer is full, cannot push value %d\n", i);
        } else {
            printf("Pushed value: %d\n", i);
        }
    }

    // Attempt to push one more element to test the full condition.
    if (CB_push(&cb, 99) == CB_FULL) {
        printf("Buffer is full, cannot push value 99\n");
    }

    // Pop elements from the buffer and print them.
    printf("Popping elements from the circular buffer:\n");
    uint8_t value;
    while (CB_pop(&cb, &value) == CB_OK) {
        printf("Popped value: %d\n", value);
    }

    // Free the allocated buffer memory.
    CB_free(&cb);

    return 0;
}

//		Size of CB_t structure: 16 bytes
//		Pushing elements into the circular buffer:
//		Pushed value: 10
//		Pushed value: 11
//		Pushed value: 12
//		Pushed value: 13
//		Buffer is full, cannot push value 99
//		Popping elements from the circular buffer:
//		Popped value: 10
//		Popped value: 11
//		Popped value: 12
//		Popped value: 13
