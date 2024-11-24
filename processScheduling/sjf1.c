#include <stdio.h>

// Structure to store process details
struct Process {
    int pname;    // Process name or ID
    int burst;    // Burst time
    int arrival;  // Arrival time
    int priority; // Priority (not used in SJF)
} processes[10];

// Function to sort the processes by their burst times
// After sorting, 'a[]' will contain the indices of processes in sorted order
void sort(int burst_times[], int n) {
    int temp_burst[10], original_burst[10];
    int min_value, i, j, temp, index;

    // Make copies of the burst times
    for (i = 0; i < n; i++) {
        temp_burst[i] = burst_times[i];
        original_burst[i] = burst_times[i];
    }

    // Sort the burst times in ascending order
    for (i = 0; i < n; i++) {
        min_value = 100; // Arbitrary large number to find the minimum
        for (j = i; j < n; j++) {
            if (temp_burst[j] < min_value) {
                min_value = temp_burst[j];
                index = j;
            }
        }
        // Swap the values to sort
        temp = temp_burst[i];
        temp_burst[i] = min_value;
        temp_burst[index] = temp;
    }

    // Map sorted burst times back to their original process indices
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (temp_burst[i] == original_burst[j]) {
                burst_times[i] = j; // Store the process index
                original_burst[j] = -1; // Mark as processed
                break;
            }
        }
    }

    // Print sorted process indices (for debugging/visual verification)
    printf("Sorted indices: ");
    for (i = 0; i < n; i++) {
        printf("%d ", burst_times[i]);
    }
    printf("\n");
}

int main() {
    int num_processes;          // Total number of processes
    int i, j, k;                // Loop counters
    int timeline[100];          // Timeline to store execution sequence
    int waiting_time[10];       // Array to store waiting times (not used here)
    int response_time[10];      // Array to store response times
    int sorted_indices[10];     // Array to store indices of sorted processes

    // Input the number of processes
    printf("Enter number of processes: ");
    scanf("%d", &num_processes);

    // Input details for each process
    for (i = 0; i < num_processes; i++) {
        printf("Enter data for process %d (pname, burst, arrival, priority): ", i + 1);
        scanf("%d %d %d %d", &processes[i].pname, &processes[i].burst, &processes[i].arrival, &processes[i].priority);
    }

    // Copy burst times to 'sorted_indices' for sorting
    for (i = 0; i < num_processes; i++) {
        sorted_indices[i] = processes[i].burst;
    }

    // Sort processes based on burst times (SJF scheduling)
    sort(sorted_indices, num_processes);

    // Build the execution timeline
    k = 0;
    for (i = 0; i < num_processes; i++) {
        int current_process_index = sorted_indices[i]; // Get the process index with the shortest burst time
        for (j = 0; j < processes[current_process_index].burst; j++) {
            timeline[k] = processes[current_process_index].pname; // Add process to the timeline
            k++;
        }
    }

    // Calculate response times for each process
    for (i = 0; i < num_processes; i++) {
        for (j = 0; j < k; j++) {
            if (timeline[j] == processes[i].pname) {
                response_time[i] = j - processes[i].arrival; // Response time = first execution time - arrival time
                break;
            }
        }
    }

    // Output response times for each process
    printf("Response Times:\n");
    for (i = 0; i < num_processes; i++) {
        printf("Process %d: %d\n", processes[i].pname, response_time[i]);
    }

    return 0;
}

