#include<stdio.h>   
#include<stdlib.h>  

// Structure to represent each process 
struct node {
    int n;   // Process ID
    int a;   // Arrival Time
    int b;   // Burst Time (execution time)
    int f;   // Finish Time
    int wt;  // Waiting Time
    int tt;  // Turnaround Time
    struct node *next; // Pointer to next process (linked list)
};


struct node* createnode(int n,int a,int b){
    // Allocate memory for new process
    struct node *newNode = (struct node *)malloc(sizeof(struct node));

    // If memory allocation fails
    if(!newNode){
        return NULL;
    }

    // Assign values to the process
    newNode->n = n;
    newNode->a = a;
    newNode->b = b;

    // Initially all calculated values are 0
    newNode->f = 0;
    newNode->wt = 0;
    newNode->tt = 0;

    newNode->next = NULL; // No next process yet

    return newNode;
}

// Function to insert process in sorted order (based on arrival time)
void arrage(struct node **head, int a, int b, int n){
    struct node *newNode = createnode(n,a,b);

    // If node creation fails, exit
    if(!newNode){
        return;
    }

    // If list is empty, insert first process
    if(*head == NULL){
        *head = newNode;
        return;
    }

    struct node *tem = *head;
    struct node *prev = NULL;

    // Find correct position (sorted by arrival time, then process ID)
    while(tem != NULL && (tem->a < newNode->a || (tem->a == newNode->a && tem->n < newNode->n))){
        prev = tem;
        tem = tem->next;
    }

    // Insert at beginning
    if(prev == NULL){
        newNode->next = *head;
        *head = newNode;
    }
    // Insert in middle or end
    else{
        prev->next = newNode;
        newNode->next = tem;
    }
}

// Function to perform FCFS Scheduling
void scheduling(struct node **head){

    // If no process exists
    if(*head==NULL){
        printf("CPU is idle\n");
        return;
    }

    int time = 0;                // Current CPU time
    float total_wt = 0, total_tt = 0; 
    struct node *tem = *head;

    printf("\nGantt Chart:\n");

    
    while(tem != NULL){
        printf("P%d\t", tem->n);
        tem = tem->next;
    }
    printf("\n");

    tem = *head; // Reset pointer to beginning

    // Calculate times for each process
    while(tem != NULL){

        // If CPU is idle, jump to arrival time
        if(time < tem->a){
            time = tem->a;
        }

        // Execute process (add burst time)
        time += tem->b;

        // Store finish time
        tem->f = time;

        // Waiting Time = Finish - Arrival - Burst
        tem->wt = tem->f - tem->a - tem->b;

        // Turnaround Time = Finish - Arrival
        tem->tt = tem->f - tem->a;

        // Add to totals for average calculation
        total_wt += tem->wt;
        total_tt += tem->tt;

        // Move to next process
        tem = tem->next;
    }

    
    printf("\nProcess\tArrival Time\tBurst Time\tFinish Time\tWaiting Time\tTurnaround Time\n");

    tem = *head;
    while(tem != NULL){
        printf("Process%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               tem->n, tem->a, tem->b, tem->f, tem->wt, tem->tt);
        tem = tem->next;
    }

    // Count number of processes
    int count = 0;
    tem = *head;
    while(tem != NULL){
        count++;
        tem = tem->next;
    }

    
    printf("\nAverage Waiting Time: %.2f", total_wt / count);
    printf("\nAverage Turnaround Time: %.2f\n", total_tt / count);
}

int main(){
    int n;

    
    printf("Enter the numbers of process: ");
    scanf("%d",&n);

    int a,b;
    struct node *head=NULL; 

    
    for(int i=1;i<=n;i++){
        printf("Enter Arrival Time and Burst Time for Process %d: ",i);
        scanf("%d %d",&a,&b);

    
        arrage(&head,a,b,i);
    }

    
    scheduling(&head);
}