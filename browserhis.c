#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
char url[50];// data
struct node* next; 
}node;

typedef struct{
    node* top;
}Stack;

typedef struct{
    char currentURL[50];
    Stack back_stack;
    Stack forward_stack;
}BrowserHistory;

void initialize(Stack* stack);
void initBrowser(BrowserHistory* History, char* homepage);
void push(Stack* stack, char* url);
char* pop(Stack* stack);
bool isEmpty(Stack stack);
void visit(BrowserHistory* History, char* tovisit);
void back(BrowserHistory* History);
void forward(BrowserHistory* History);

// T H E    M  A  I  N     F  C  T

int main(void){ 
BrowserHistory logs;
char homepage[50];
printf("Enter the link of your current website\n");
fgets(homepage,50, stdin);
initBrowser(&logs, homepage);
int choice;

char* tovisit = (char*)malloc(50*sizeof(char));
    if(tovisit == NULL){
        printf("Memory allocation has failed");
        exit(1);
    }

do
{
    printf("1) to visit a website\n");
    printf("2) to go back\n");
    printf("3) to go forward\n");
    printf("4) to quit the navigator\n");
    scanf("%d", &choice);
    getchar();

    switch (choice)
    {
    case 1:
        printf("enter the website you wanna visit\n");
        fgets(tovisit, 50, stdin);
        visit(&logs, tovisit);
        break;
    case 2:
        back(&logs);
        break;
    case 3:
        forward(&logs);
        break;
    case 4:
        printf("Leaving the browser\n");
        break;
    default:
        printf("Invalid Choice\n");
        break;
    }
} while(choice != 4);
    return 0;
}

 
// F U N C T I O N S    D E F I N I T I N I O N S

void initialize(Stack* stack){
    stack->top = NULL;
}

void initBrowser(BrowserHistory* History,  char* homepage){
    initialize(&History->back_stack);
    initialize(&History->forward_stack);
    strcpy(History->currentURL, homepage);
    
}

void push(Stack* stack, char* url){
    node* website = (node*)malloc(sizeof(node));
    if (website == NULL){
        printf("Memory allocation has failed");
        exit(1);
    }
    strcpy(website->url, url); // newNode->data = value;
    website->next = stack->top;
    stack->top = website;
}

char* pop(Stack* stack){
    if(isEmpty(*stack)){
        printf("Stack is empty\n");
        exit(2);
    }
    else{
        char* popped = (char*)malloc(50*sizeof(char));
        if (popped == NULL) {
            printf("Memory allocation failure\n");
            exit(1);
        }
        node* temp = stack->top; // temp = *head
        strcpy(popped, stack->top->url);
        stack->top = stack->top->next; //*head = (*head)->next
        free(temp);
        return popped;

    }
}

bool isEmpty(Stack stack){
    if(stack.top == NULL){
        return true;
    }
    else
        return false;
}

void visit(BrowserHistory* History, char* tovisit){
    push(&History->back_stack, History->currentURL);
    strcpy(History->currentURL, tovisit);
    while(History->forward_stack.top != NULL){
        free(pop(&History->forward_stack));
    }
    printf("Visiting  %s", History->currentURL);
}

void back(BrowserHistory* History){
    if(isEmpty(History->back_stack)){
        printf("You have no website in the back\n");
        return;
    }
    push(&History->forward_stack, History->currentURL);
    char* currentURL = (char*)malloc(50*sizeof(char)); //the one we wanna go back to
    if(currentURL == NULL){
        printf("Memory allocation has failed\n");
        exit(1);
    }
    currentURL = pop(&History->back_stack);
    strcpy(History->currentURL, currentURL);
    free(currentURL);
    printf("Backing to %s", History->currentURL);
}

void forward(BrowserHistory* History){
    if(isEmpty(History->forward_stack)){
        printf("You have no website in the forward\n");
        return;
    }
    push(&History->back_stack, History->currentURL);
    char* currentURL = (char*)malloc(50*sizeof(char)); //the one we wanna go forward to
     if(currentURL == NULL){
        printf("Memory allocation has failed\n");
        exit(1);
    }
    currentURL = pop(&History->forward_stack);
    strcpy(History->currentURL, currentURL);
    free(currentURL);
    printf("Forwarding to %s", History->currentURL);
}

