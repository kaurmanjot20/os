#include <stdio.h>

// Structure to represent a memory chunk
struct MemoryChunk {
    char status; // 'h' for free (hole), 'u' for used
    int size;    // Size of the memory chunk
} memory[25];    // Array of memory chunks

// Function to insert a new memory chunk into the memory array
void insertMemoryChunk(int remainingSize, int position, int totalChunks) {
    int i;

    // Shift memory chunks to make space for the new chunk
    for (i = totalChunks; i >= position; i--) {
        memory[i + 1].status = memory[i].status;
        memory[i + 1].size = memory[i].size;
    }

    // Insert the new chunk as free memory ('h')
    memory[position].size = remainingSize;
    memory[position].status = 'h';
}

int main() {
    int i, j, totalChunks, remainingSize, processRequests[25];
    totalChunks = 12; // Initial number of memory chunks

    // Input: Memory chunk statuses
    printf("Enter memory chunk statuses ('h' for hole, 'u' for used):\n");
    for (i = 0; i < totalChunks; i++) {
        scanf(" %c", &memory[i].status); // Space before %c to handle newline issues
    }

    // Input: Memory chunk sizes
    printf("Enter memory chunk sizes:\n");
    for (i = 0; i < totalChunks; i++) {
        scanf("%d", &memory[i].size);
    }

    // Input: Process memory requests
    printf("Enter memory requests for processes:\n");
    for (i = 0; i < 3; i++) {
        scanf("%d", &processRequests[i]);
    }

    // Best Fit Allocation
    for (i = 0; i < 3; i++) {
        int bestIndex = -1;           // Initialize best fit index as -1
        int smallestFit = __INT_MAX__; // Start with the largest possible integer

        // Search for the best fit hole
        for (j = 0; j < totalChunks; j++) {
            if (memory[j].status == 'h' && memory[j].size >= processRequests[i]) {
                if (memory[j].size < smallestFit) { // Find the smallest sufficient hole
                    smallestFit = memory[j].size;
                    bestIndex = j;
                }
            }
        }

        if (bestIndex != -1) { // If a suitable hole is found
            // Allocate memory to the process
            remainingSize = memory[bestIndex].size - processRequests[i];
            memory[bestIndex].size = processRequests[i];
            memory[bestIndex].status = 'u';

            // If there is remaining free memory, create a new hole
            if (remainingSize > 0) {
                insertMemoryChunk(remainingSize, bestIndex + 1, totalChunks);
                totalChunks = totalChunks + 1;
            }
        }
    }

    // Output: Display the final memory allocation
    printf("\nFinal Memory Allocation:\n");
    for (i = 0; i < totalChunks; i++) {
        printf("Chunk %d: Status = %c, Size = %d\n", i + 1, memory[i].status, memory[i].size);
    }

    return 0;
}
