#include <stdio.h>
#include <stdlib.h>

int main() {
	int numChars;

	// Prompt the user for the number of characters
	printf("Enter the number of characters (between 1 and 26): ");
	scanf("%d", &numChars);

	// Validate the input range
	if (numChars < 1 || numChars > 26) {
		printf("Invalid input! Please enter a number between 1 and 26.\n");
		return 1; // Exit the program if input is out of range
	}

	// Allocate memory for the specified number of characters
	char *ptr = (char*) malloc(numChars * sizeof(char));

	// Check if memory allocation was successful
	if (ptr == NULL) {
		printf("Memory allocation failed!\n");
		return 1; // Exit the program if memory allocation fails
	}

	// Initialize the allocated memory with letters
	for (int i = 0; i < numChars; i++) {
		ptr[i] = (char) ('A' + i); // Fill memory with letters 'A', 'B', ...
	}

	// Print the letters stored in memory
	printf("Stored letters:\n");
	for (int i = 0; i < numChars; i++) {
		printf("%c ", ptr[i]); // Output the letters
	}
	printf("\n");

	// Free the allocated memory
	free(ptr);
	printf("Memory has been freed.\n");

	return 0;
}
