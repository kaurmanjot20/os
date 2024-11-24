#include <stdio.h>

struct cpus {
    int pname;    // Process ID
    int burst;    // Burst time
    int arrival;  // Arrival time
    int priority; // Priority (not used in FCFS, but part of input)
}s[10];

int main() {
    int num_p, i, j, k;
    int arr[100];        // Timeline array
    int wt[10];          // Waiting time (not used here but useful in FCFS analysis)
    int rt[10];          // Response time
    int timeline_length; // Total number of slots in the timeline

    // Step 1: Input the number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &num_p);

    // Step 2: Input data for each process
    for (i = 0; i < num_p; i++) {
        printf("Enter data for process %d (pname burst arrival priority): ", i + 1);
        scanf("%d %d %d %d", &s[i].pname, &s[i].burst, &s[i].arrival, &s[i].priority);
    }

    // Step 3: Build the execution timeline
    k = 0;
    for (i = 0; i < num_p; i++) {
        for (j = 0; j < s[i].burst; j++) {
            arr[k] = s[i].pname; // Fill the timeline with process IDs
            k++;
        }
    }
    timeline_length = k;

    // Step 4: Calculate response time
    for (i = 0; i < num_p; i++) {
        for (j = 0; j < timeline_length; j++) {
            if (arr[j] == s[i].pname) {
                rt[i] = j - s[i].arrival; // Time from arrival to first execution
                break; // Stop after the first occurrence
            }
        }
    }

    // Step 5: Print the Gantt chart
    printf("\nGantt Chart:\n");
    
    // Print the top border
    for (i = 0; i < timeline_length; i++) {
        printf("----");
    }
    printf("-\n");

    // Print the process names in the timeline
    for (i = 0; i < timeline_length; i++) {
        printf("| P%d", arr[i]);
    }
    printf("|\n");

    // Print the bottom border
    for (i = 0; i < timeline_length; i++) {
        printf("----");
    }
    printf("-\n");

    // Print the time slots
    for (i = 0; i <= timeline_length; i++) {
        printf("%2d  ", i);
    }
    printf("\n");

    // Step 6: Print the response times
    printf("\nResponse Times:\n");
    for (i = 0; i < num_p; i++) {
        printf("Process %d: %d\n", s[i].pname, rt[i]);
    }

    return 0;
}
