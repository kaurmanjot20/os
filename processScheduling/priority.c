#include <stdio.h>

// Structure to represent a process
struct Process {
    int processName;   // Process name/ID
    int burstTime;     // Burst time of the process
    int arrivalTime;   // Arrival time of the process
    int priority;      // Priority of the process
} processes[10];

// Function to sort processes based on their priority
void sortByPriority(int priorityIndex[], int numProcesses) {
    int sortedPriority[10], originalPriority[10];
    int minPriority, temp, index, i, j;

    // Copy the priorities to separate arrays for sorting and mapping
    for (i = 0; i < numProcesses; i++) {
        sortedPriority[i] = priorityIndex[i];
        originalPriority[i] = priorityIndex[i];
    }

    // Sort the priorities in ascending order (lower number = higher priority)
    for (i = 0; i < numProcesses; i++) {
        minPriority = 100; // Assume a very high initial priority value
        for (j = i; j < numProcesses; j++) {
            if (sortedPriority[j] < minPriority) {
                minPriority = sortedPriority[j];
                index = j;
            }
        }
        // Swap the current position with the minimum found
        temp = sortedPriority[i];
        sortedPriority[i] = minPriority;
        sortedPriority[index] = temp;
    }

    // Map sorted priorities back to process indices
    for (i = 0; i < numProcesses; i++) {
        for (j = 0; j < numProcesses; j++) {
            if (sortedPriority[i] == originalPriority[j]) {
                priorityIndex[i] = j;
                originalPriority[j] = -1; // Mark as visited
                break;
            }
        }
    }
}

int main() {
    int priorityIndex[10];
    int ganttChart[50];
    int numProcesses = 3, ganttIndex = 0;

    // Input process details
    for (int i = 0; i < numProcesses; i++) {
        printf("Enter the process name (ID), burst time, arrival time, and priority:\n");
        scanf("%d", &processes[i].processName);
        scanf("%d", &processes[i].burstTime);
        scanf("%d", &processes[i].arrivalTime);
        scanf("%d", &processes[i].priority);
    }

    // Copy priorities to an array for sorting
    for (int i = 0; i < numProcesses; i++) {
        priorityIndex[i] = processes[i].priority;
    }

    // Sort processes by priority
    sortByPriority(priorityIndex, numProcesses);

    // Create the Gantt chart based on sorted priorities
    for (int i = 0; i < numProcesses; i++) {
        int currentProcessIndex = priorityIndex[i];
        for (int j = 0; j < processes[currentProcessIndex].burstTime; j++) {
            ganttChart[ganttIndex] = processes[currentProcessIndex].processName;
            ganttIndex++;
        }
    }

    // Output the Gantt chart
    printf("\nGantt Chart:\n");
    for (int i = 0; i < ganttIndex; i++) {
        printf("%d\t", ganttChart[i]);
    }

    return 0;
}
