#include<stdio.h>
#include<stdlib.h>

int n, nf; // Variables to store the length of page reference sequence and the number of frames
int ref[30]; // Array to store the page reference sequence
int p[50]; // Array to simulate the frames
int hit = 0; // Variable to track page hits
int i, j = 0, k; // Loop variables
int pgfaultcnt = 0; // Page fault count

// Function to get input from the user
void getData() {
    printf("\nEnter length of page reference sequence: ");
    scanf("%d", &n);
    printf("\nEnter the number of frames: ");
    scanf("%d", &nf);
    printf("\nEnter the page reference sequence:\n");
    for (i = 0; i < n; i++)
        scanf("%d", &ref[i]);
}

// Function to initialize variables and arrays
void initialize() {
    pgfaultcnt = 0;
    for (i = 0; i < nf; i++)
        p[i] = 9999;
}

// Function to check if a page hit occurs
int isHit(int data) {
    hit = 0;
    for (j = 0; j < nf; j++) {
        if (p[j] == data) {
            hit = 1;
            break;
        }
    }
    return hit;
}

// Function to display the current pages in frames
void displayPages() {
    for (k = 0; k < nf; k++)
        if (p[k] != 9999)
            printf("%d ", p[k]);
}

// Function to implement FIFO page replacement algorithm
void fifo() {
    int j = 0;
    initialize();
    printf("\tPAGE\tFRAMES\tFAULTS\n");
    for (i = 0; i < n; i++) {
        printf("\n\t%d\t", ref[i]);
        if (isHit(ref[i]) == 0) {
            p[j] = ref[i];
            j++;
            displayPages();
            printf("\tPage fault %d", pgfaultcnt);
            pgfaultcnt++;
        } else {
            displayPages();
            printf("\tNo page fault");
        }
        if (j == nf)
            j = 0;
    }
    printf("\nTotal number of page faults in FIFO: %d", pgfaultcnt);
}

// Function to implement LRU page replacement algorithm
void lru() {
    initialize();
    int least[50];
    printf("\t PAGE\tFRAMES\tFAULTS\n");
    for (i = 0; i < n; i++) {
        printf("\n\t%d\t", ref[i]);
        if (isHit(ref[i]) == 0) {
            for (j = 0; j < nf; j++) {
                int pg = p[j];
                int found = 0;
                for (k = i - 1; k >= 0; k--) {
                    if (pg == ref[k]) {
                        least[j] = k;
                        found = 1;
                        break;
                    } else
                        found = 0;
                }
                if (!found)
                    least[j] = -9999;
            }
            int min = 9999;
            int repindex;
            for (j = 0; j < nf; j++) {
                if (least[j] < min) {
                    min = least[j];
                    repindex = j;
                }
            }
            p[repindex] = ref[i];
            displayPages();
            printf("\tPage fault %d", pgfaultcnt);
            pgfaultcnt++;
        } else {
            displayPages();
            printf("\tNo page fault!");
        }
    }
    printf("\nTotal number of page faults in LRU: %d", pgfaultcnt);
}

int main() {
    int choice, yn;
    do {
        printf("Page Replacement Algorithms\n");
        printf("1. Enter data\n2. FIFO\n3. LRU\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                getData();
                break;
            case 2:
                fifo();
                break;
            case 3:
                lru();
                break;
            case 4:
                exit(0);
        }
        printf("\nDo you want to continue?\nIf yes, press 1\nIf no, press 0\n");
        scanf("%d", &yn);
    } while (yn == 1);
    return 0;
}

