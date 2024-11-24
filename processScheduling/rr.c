#include <stdio.h>

struct Process {
    int pid;             // Process ID
    int burst_time;      // Burst Time
    int arrival_time;    // Arrival Time
    int remaining_time;  // Remaining Burst Time (for round-robin)
    int waiting_time;    // Waiting Time
    int turnaround_time; // Turnaround Time
};

void calculateRoundRobin(struct Process proc[], int n, int time_quantum) {
    int time = 0;       // Current time
    int completed = 0;  // Count of completed processes
    int i = 0;          // Index for looping through processes

    printf("\nGantt Chart:\n");
    printf(" ");

    while (completed < n) {
        int queue_empty = 1; // To check if any process has something to execute

        for (i = 0; i < n; i++) {
            // If the process has arrived and has remaining time to execute
            if (proc[i].remaining_time > 0 && proc[i].arrival_time <= time) {
                queue_empty = 0; // A process is in the queue

                printf("| P%d ", proc[i].pid); // Print process ID in Gantt chart
                int prev_time = time;        // Keep track of start time for time markers

                if (proc[i].remaining_time > time_quantum) {
                    time += time_quantum;
                    proc[i].remaining_time -= time_quantum;
                } else {
                    time += proc[i].remaining_time;
                    proc[i].turnaround_time = time - proc[i].arrival_time; // Calculate TAT
                    proc[i].waiting_time = proc[i].turnaround_time - proc[i].burst_time; // Calculate WT
                    proc[i].remaining_time = 0; // Process completed
                    completed++;
                }

                printf(" %d ", time); // Print time marker after each execution
            }
        }

        // Increment time when no process is ready
        if (queue_empty) {
            time++;
            printf("| Idle ");
            printf(" %d ", time); // Print idle time marker
        }
    }
    printf("|\n");
}

void displayMetrics(struct Process proc[], int n) {
    float avg_wt = 0, avg_tat = 0;
    printf("\nProcess\tBurst Time\tArrival Time\tWaiting Time\tTurnaround Time\n");

    for (int i = 0; i < n; i++) {
        avg_wt += proc[i].waiting_time;
        avg_tat += proc[i].turnaround_time;

        printf("P%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               proc[i].pid, proc[i].burst_time, proc[i].arrival_time,
               proc[i].waiting_time, proc[i].turnaround_time);
    }

    printf("\nAverage Waiting Time: %.2f\n", avg_wt / n);
    printf("Average Turnaround Time: %.2f\n", avg_tat / n);
}

int main() {
    int n, time_quantum;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process proc[n];

    for (int i = 0; i < n; i++) {
        printf("\nEnter details for Process P%d\n", i + 1);
        proc[i].pid = i + 1;
        printf("Burst Time: ");
        scanf("%d", &proc[i].burst_time);
        printf("Arrival Time: ");
        scanf("%d", &proc[i].arrival_time);
        proc[i].remaining_time = proc[i].burst_time; // Initialize remaining time
    }

    printf("\nEnter Time Quantum: ");
    scanf("%d", &time_quantum);

    calculateRoundRobin(proc, n, time_quantum);
    displayMetrics(proc, n);

    return 0;
}
