#include<stdio.h>
#include<stdlib.h>

struct node {
    int n; // Process ID
    int a; // Arrival Time
    int b; // Burst Time
    int rb; // Remaining Burst time
    int f;  // Finish time
    int wt; // Waiting Time
    int tt; // Turnaround Time
    struct node *next;
};

struct node *createnode(int n,int a,int b){
    struct node *new=(struct node *)malloc(sizeof(struct node));
    if(!new){
        return NULL;
    }
    new->n=n;
    new->a=a;
    new->b=b;
    new->rb=b;
    new->f=0;
    new->wt=0;
    new->tt=0;
    new->next=NULL;
    return new;
}

// Insert in sorted order (Arrival time, then Process ID)
void arrage(struct node **head, int a, int b, int n){
    struct node *new = createnode(n,a,b);
    if(!new){
        return;
    }

    if(*head == NULL){
        *head = new;
        return;
    }

    struct node *tem = *head;
    struct node *prev = NULL;

    while(tem != NULL && (tem->a < new->a || (tem->a == new->a && tem->n < new->n))){
        prev = tem;
        tem = tem->next;
    }

    if(prev == NULL){
        new->next = *head;
        *head = new;
    }
    else{
        prev->next = new;
        new->next = tem;
    }
}

void scheduling(struct node **head,int tq,int cs){
    if(*head==NULL){
        printf("CPU is idle\n");
        return;
    }

    int time=0, done;
    float avg_turnaround=0, avg_waiting=0;

    while(1){
        done=1;
        struct node* tem = *head;

        while(tem!=NULL){
            if(tem->rb > 0 && tem->a <= time){
                printf("P%d\t",tem->n);
                done=0;

                if(tem->rb > tq){
                    time += tq;
                    tem->rb -= tq;
                }
                else{
                    time += tem->rb;
                    tem->f = time;
                    tem->wt = tem->f - tem->a - tem->b;
                    avg_waiting += tem->wt;
                    tem->rb = 0;
                }

                // Check if any process still remaining
                struct node *check = *head;
                int remaining = 0;
                while(check != NULL){
                    if(check->rb > 0){
                        remaining = 1;
                        break;
                    }
                    check = check->next;
                }

                // Add context switch only if needed
                if(remaining){
                    time += cs;
                }
            }
            tem = tem->next;
        }

        if(done){
            printf("\n");
            break;
        }
    }

    struct node *tem = *head;
    int n=0;

    printf("\nProcess\tArrival\tBurst\tFinish\tWaiting\tTurnaround\n");

    while(tem!=NULL){
        tem->tt = tem->f - tem->a;
        avg_turnaround += tem->tt;
        tem = tem->next;
        n++;
    }

    tem = *head;
    while(tem!=NULL){
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               tem->n,tem->a,tem->b,tem->f,tem->wt,tem->tt);
        tem = tem->next;
    }

    printf("\nAverage Waiting Time: %.2f\n",avg_waiting/n);
    printf("Average Turnaround Time: %.2f\n",avg_turnaround/n);
}

int main(){
    int n;
    printf("Enter number of processes: ");
    scanf("%d",&n);

    int tq;
    printf("Enter Time Quantum: ");
    scanf("%d",&tq);

    int cs;
    printf("Enter Context Switch Time: ");
    scanf("%d",&cs);

    int a,b;
    struct node *head=NULL;

    for(int i=1;i<=n;i++){
        printf("Enter Arrival Time and Burst Time for Process %d: ",i);
        scanf("%d %d",&a,&b);
        arrage(&head,a,b,i);
    }

    scheduling(&head,tq,cs);

    return 0;
}