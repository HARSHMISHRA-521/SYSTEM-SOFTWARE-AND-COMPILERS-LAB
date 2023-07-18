#include<stdio.h>
#include<stdlib.h>

// Function prototypes
void roundrobin(int, int, int[], int[]);
void srtf();

int main() {
    int n, tq, choice;
    int bt[10], st[10], i, j, k;
    
    while (1) {
        printf("\n1. Round Robin\n2. SRTF\n3. Exit\nEnter the choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("\nRound Robin scheduling algorithm\nEnter the number of processes: ");
                scanf("%d", &n);
                
                printf("\nEnter the burst time for sequences: ");
                for (i = 0; i < n; i++) {
                    scanf("%d", &bt[i]);
                    st[i] = bt[i];
                }
                
                printf("\nEnter the time quantum: ");
                scanf("%d", &tq);
                
                roundrobin(n, tq, st, bt);
                break;
                
            case 2:
                printf("\n\nShortest Remaining Time First (SRTF)\n");
                srtf();
                break;
                
            case 3:
                exit(0);
                break;
        }
    }
}

// Function to implement Round Robin scheduling algorithm
void roundrobin(int n, int tq, int st[], int bt[]) {
    int time = 0, tat[10], wt[10], count = 0, swt = 0, temp1, sq = 0, i, j, k, stat = 0;
    float awt = 0.0, atat = 0.0;
    
    while (1) {
        for (i = 0, count = 0; i < n; i++) {
            temp1 = tq;
            
            if (st[i] == 0) {
                count++;
                continue;
            }
            
            if (st[i] > tq)
                st[i] = st[i] - tq;
            else if (st[i] >= 0) {
                temp1 = st[i];
                st[i] = 0;
            }
            
            sq = sq + temp1;
            tat[i] = sq;
        }
        
        if (n == count)
            break;
    }
    
    for (i = 0; i < n; i++) {
        wt[i] = tat[i] - bt[i];
        swt = swt + wt[i];
        stat = stat + tat[i];
    }
    
    awt = (float) swt / n;
    atat = (float) stat / n;
    
    printf("Process no\t|Burst time\t|Waiting time\t|Turnaround time\n");
    
    for (i = 0; i < n; i++)
        printf("%d\t\t\t%d\t\t\t%d\t\t\t%d\t\t\n", i + 1, bt[i], wt[i], tat[i]);
    
    printf("\nAverage waiting time is %f\nAverage turnaround time is %f\n", awt, atat);
}


// Function to implement Shortest Remaining Time First (SRTF) algorithm
void srtf() {
    int n, j = 0, st[10], bt[10], rt[10], remain = 0, smallest, time = 0, i, endtime, swt = 0, stat = 0;
    
    printf("\nEnter the number of processes: ");
    scanf("%d", &n);
    
    for (i = 0; i < n; i++) {
        printf("Enter arrival time for p[%d]: ", i + 1);
        scanf("%d", &st[i]);
        
        printf("Enter the burst time for p[%d]: ", i + 1);
        scanf("%d", &bt[i]);
        
        rt[i] = bt[i];
    }
    
    rt[100] = 999;
    
    printf("\nProcess\t\tWaiting time\tTurnaround time\n");
    
    for (time = 0; remain != n; time++) {
        smallest = 100;
        
        for (i = 0; i < n; i++) {
            if (st[i] <= time && rt[i] < rt[smallest] && rt[i] > 0)
                smallest = i;
        }
        
        rt[smallest]--;
        
        if (rt[smallest] == 0) {
            remain++;
            endtime = time + 1;
            j = smallest;
            
            printf("p[%d]\t\t%d\t\t%d\n", smallest + 1, endtime - bt[j] - st[j], endtime - st[j]);
            
            swt += endtime - bt[j] - st[j];
            stat += endtime - st[j];
        }
    }
    
    float awt = 0.0, atat = 0.0;
    
    awt = (float) swt / n;
    atat = (float) stat / n;
    
    printf("Average waiting time: %f\n", awt);
    printf("Average turnaround time: %f\n", atat);
}

