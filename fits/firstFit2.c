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

    int allocationPointer = 0; // Pointer to track the current memory allocation

    // Process each memory request
    for (i = 0; i < 3; i++) {
        for (j = 0; j < totalChunks; j++) {
            // Check if the memory chunk is a free hole and can accommodate the request
            if (memory[j].status == 'h') {
                if (memory[j].size >= processRequests[i]) {
                    // Allocate memory to the process
                    remainingSize = memory[j].size - processRequests[i];
                    memory[j].size = processRequests[i];
                    memory[j].status = 'u';
                    allocationPointer = j;

                    // If there is remaining free memory, create a new hole
                    if (remainingSize > 0) {
                        insertMemoryChunk(remainingSize, j + 1, totalChunks);
                        totalChunks = totalChunks + 1;
                    }
                    break; // Move to the next process request
                }
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
