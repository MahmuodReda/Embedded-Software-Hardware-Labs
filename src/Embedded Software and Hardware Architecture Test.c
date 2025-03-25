#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Define a node structure for a singly linked list.
// Each node contains a 32-bit data value and a pointer to the next node.
typedef struct Node {
    uint32_t data;       // Data stored in the node
    struct Node *next;   // Pointer to the next node in the list
} Node;

/*
 * Function: createNode
 * --------------------
 * Allocates memory on the Heap for a new node, initializes it with the provided data,
 * and returns a pointer to the newly created node.
 *
 * Parameters:
 *   data - The 32-bit unsigned integer data to store in the node.
 *
 * Returns:
 *   A pointer to the new node if successful, or NULL if memory allocation fails.
 *
 * Memory:
 *   The new node is allocated on the Heap.
 */
Node* createNode(uint32_t data) {
    Node* newNode = (Node*) malloc(sizeof(Node)); // Allocate memory for one node
    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }
    newNode->data = data;  // Initialize node data
    newNode->next = NULL;  // Set the next pointer to NULL (no next node yet)
    return newNode;
}

/*
 * Function: insertAtEnd
 * ---------------------
 * Inserts a new node with the specified data at the end of the linked list.
 *
 * Parameters:
 *   head - Double pointer to the head of the linked list.
 *          (Allows modification of the head if the list is initially empty)
 *   data - The data to insert into the new node.
 *
 * Returns:
 *   Nothing. The linked list is modified directly.
 *
 * Memory:
 *   A new node is allocated on the Heap.
 */
void insertAtEnd(Node **head, uint32_t data) {
    Node *newNode = createNode(data);
    if (newNode == NULL) {
        // If memory allocation fails, do not proceed.
        return;
    }
    // If the list is empty, set the new node as the head.
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    // Otherwise, traverse the list to find the last node.
    Node *current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    // Set the next pointer of the last node to the new node.
    current->next = newNode;
}

/*
 * Function: deleteNode
 * --------------------
 * Deletes the first node in the linked list that contains the specified data.
 *
 * Parameters:
 *   head - Double pointer to the head of the linked list.
 *   data - The data value to search for and delete.
 *
 * Returns:
 *   1 if deletion was successful, 0 if the node with the given data was not found.
 *
 * Memory:
 *   Frees the memory of the deleted node from the Heap.
 */
int deleteNode(Node **head, uint32_t data) {
    if (head == NULL || *head == NULL)
        return 0;

    Node *current = *head;
    Node *previous = NULL;

    // Check if the head node contains the target data.
    if (current->data == data) {
        *head = current->next; // Update head pointer
        free(current);         // Free memory of the removed node
        return 1;
    }

    // Traverse the list to find the node with the target data.
    while (current != NULL && current->data != data) {
        previous = current;
        current = current->next;
    }

    // If the node is not found, return 0.
    if (current == NULL)
        return 0;

    // Remove the node by linking the previous node to the next node.
    previous->next = current->next;
    free(current); // Free memory of the removed node
    return 1;
}

/*
 * Function: printList
 * -------------------
 * Traverses and prints all nodes in the linked list.
 *
 * Parameters:
 *   head - Pointer to the head of the linked list.
 *
 * Returns:
 *   Nothing.
 *
 * Memory:
 *   Uses local pointer variables on the Stack.
 */
void printList(Node *head) {
    Node *current = head;
    while (current != NULL) {
        printf("%u -> ", current->data);  // Print each node's data
        current = current->next;            // Move to the next node
    }
    printf("NULL\n");  // Indicate end of the list
}

/*
 * =============================================================================
 * MAIN FUNCTION: Linked List Demonstration
 * =============================================================================
 * This main function demonstrates:
 * 1. Creating a linked list.
 * 2. Inserting nodes at the end of the list.
 * 3. Deleting a node with a specific data value.
 * 4. Printing the linked list.
 *
 * Memory:
 *   - The linked list nodes are allocated on the Heap.
 *   - The head pointer and temporary variables are stored on the Stack.
 */
int main() {
    // Initialize the head pointer to NULL (empty list).
    Node *head = NULL;

    // Insert nodes with data values into the linked list.
    insertAtEnd(&head, 10);  // Insert node with data 10
    insertAtEnd(&head, 20);  // Insert node with data 20
    insertAtEnd(&head, 30);  // Insert node with data 30

    // Print the current linked list.
    printf("Linked List after insertion:\n");
    printList(head); // Expected output: 10 -> 20 -> 30 -> NULL

    // Delete the node with data 20.
    if (deleteNode(&head, 20)) {
        printf("Node with data 20 deleted successfully.\n");
    } else {
        printf("Node with data 20 not found.\n");
    }

    // Print the linked list after deletion.
    printf("Linked List after deletion:\n");
    printList(head); // Expected output: 10 -> 30 -> NULL

    // Free the remaining nodes to avoid memory leaks.
    while (head != NULL) {
        Node *temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}

//		Linked List after insertion:
//		10 -> 20 -> 30 -> NULL
//		Node with data 20 deleted successfully.
//		Linked List after deletion:
//		10 -> 30 -> NULL

