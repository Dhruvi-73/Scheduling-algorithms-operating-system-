#include<stdio.h>
#include<stdlib.h>

struct node {
    int n;
    int a;
    int b;
    int f;
    int wt;
    int tt;
    struct node *next;
};

struct node* createnode(int n,int a,int b){
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    if(!newNode){
        return NULL;
    }
    newNode->n=n;
    newNode->a=a;
    newNode->b=b;
    newNode->f=0;
    newNode->wt=0;
    newNode->tt=0;
    newNode->next=NULL;
    return newNode;
}

void arrage(struct node **head, int a, int b, int n){
    struct node *newNode = createnode(n,a,b);
    if(!newNode){
        return;
    }

    if(*head == NULL){
        *head = newNode;
        return;
    }

    struct node *tem = *head;
    struct node *prev = NULL;

    while(tem != NULL && (tem->a < newNode->a || (tem->a == newNode->a && tem->n < newNode->n))){
        prev = tem;
        tem = tem->next;
    }

    if(prev == NULL){
        newNode->next = *head;
        *head = newNode;
    }
    else{
        prev->next = newNode;
        newNode->next = tem;
    }
}

void scheduling(struct node **head){
    if(*head==NULL){
        printf("CPU is idle\n");
        return;
    }

    int time = 0;
    float total_wt = 0, total_tt = 0;
    struct node *tem = *head;

    printf("\nGantt Chart:\n");

    while(tem != NULL){
        printf("P%d\t", tem->n);
        tem = tem->next;
    }
    printf("\n");

    tem = *head;

    while(tem != NULL){
        if(time < tem->a){
            time = tem->a;
        }

        time += tem->b;
        tem->f = time;
        tem->wt = tem->f - tem->a - tem->b;
        tem->tt = tem->f - tem->a;

        total_wt += tem->wt;
        total_tt += tem->tt;

        tem = tem->next;
    }

    printf("\nProcess\tArrival Time\tBurst Time\tFinish Time\tWaiting Time\tTurnaround Time\n");

    tem = *head;
    while(tem != NULL){
        printf("Process%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               tem->n, tem->a, tem->b, tem->f, tem->wt, tem->tt);
        tem = tem->next;
    }

    //  Averages
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