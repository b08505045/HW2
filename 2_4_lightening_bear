#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct node{
    int vertex;
    struct node **neighbor; // arrary record neighbor
    struct node *main_down, *side_down;
}node;

typedef struct stack {
    node *top;
}stack;

stack * stack_new(){
    stack *stk = calloc(1, sizeof(stack));
    return stk;
}

int stack_is_empty(stack *stk){
    return !(stk -> top) ? 1 : 0;
}

node * stack_peek(stack *stk){
    return stk -> top;
}

void stack_push_main(stack *stk, node *n){
    n -> main_down = stk -> top;
    stk -> top = n;
}

void stack_pop_main(stack *stk){
    node *popped = stk -> top;
    stk -> top = popped -> main_down;
    popped -> main_down = NULL;
}

void stack_push_side(stack *stk, node *n){
    n -> side_down = stk -> top;
    stk -> top = n;
}

void stack_pop_side(stack *stk){
    node *popped = stk -> top;
    stk -> top = popped -> side_down;
    popped -> side_down = NULL;
}

node* node_new(int v, int num_of_neighbor) {
    node* new_node = calloc(1, sizeof(node));
    new_node -> vertex = v;
    new_node -> neighbor = calloc(num_of_neighbor, sizeof(node*));
    return new_node;
}

void mark(node *cur, node *prev, node *next, int *table, int *num_of_nei, int *count){
    int mark = cur -> vertex;
    table[mark - 1] = mark;
    stack *stk = calloc(1, sizeof(stack));
    for(int i = 0; i < num_of_nei[mark - 1]; i++){
        // DFS
        if(cur -> neighbor[i] != prev && cur -> neighbor[i] != next){
            node *temp = cur -> neighbor[i];
            table[temp -> vertex - 1] = mark;
            stack_push_side(stk, temp);
            int target;
            while(1){
                if(count[temp -> vertex - 1] < num_of_nei[temp -> vertex - 1] && (temp -> neighbor[count[temp -> vertex - 1]] == cur || temp -> neighbor[count[temp -> vertex - 1]] == temp -> side_down))
                    count[temp -> vertex - 1]++;
                if(count[temp -> vertex - 1] >= num_of_nei[temp -> vertex - 1]){
                    stack_pop_side(stk);
                    if(stack_is_empty(stk)) break;
                    else temp = stack_peek(stk);
                }
                else{
                    target = count[temp -> vertex - 1];
                    count[temp -> vertex - 1]++;
                    temp = temp -> neighbor[target];
                    table[temp -> vertex - 1] =  mark;
                    stack_push_side(stk, temp);
                }
            }
        }
    }
    free(stk);
}

int main(int argc, char *argv[]){
    int N, Q, S, R; // N = number of cities, Q = number of queires, S = capital, R = resort
    scanf("%d %d %d %d", &N, &Q, &S, &R);
    // if S == R, then the ans is always R(s)
    if(S == R){
        for(int i = 0; i < Q; i++)
            printf("%d\n", S);
        return 0;
    }

    node **adjLists = calloc(N, sizeof(node*));
    //   number of neighbor                  // help count
    int *num_of_nei = calloc(N, sizeof(int)), *count = calloc(N, sizeof(int));
    int **message = malloc((N - 1) * sizeof(int*)); // stores input
    int *table = malloc(N * sizeof(int)); // each node's ans
    // initialize message
    for(int i = 0; i < N - 1; i++)
        message[i] = malloc(2 * sizeof(int));
    // store input and record the number of each node's neighbor
    for(int i = 0; i < N - 1; i++){
        scanf("%d %d", &message[i][0], &message[i][1]);
        num_of_nei[message[i][0] - 1]++;
        num_of_nei[message[i][1] - 1]++;
    }
    // initialize each node's array contain its neighbor
    for(int i = 0; i < N; i++)
        adjLists[i] = node_new(i+1, num_of_nei[i]);

    // construct adj_list
    for(int i = 0; i < N - 1; i++){
        adjLists[message[i][0] - 1] -> neighbor[count[message[i][0] - 1]] = adjLists[message[i][1] - 1];
        adjLists[message[i][1] - 1] -> neighbor[count[message[i][1] - 1]] = adjLists[message[i][0] - 1];
        count[message[i][0] - 1]++;
        count[message[i][1] - 1]++;
    }

    free(count);
    count = calloc(N, sizeof(int));
    // counstruct main linked list from S to R
    node *temp = adjLists[S - 1];
    stack *stk = stack_new();
    stack_push_main(stk, temp);
    int target;
    while(stack_peek(stk) -> vertex != R){
        if(count[temp -> vertex - 1] < num_of_nei[temp -> vertex - 1] && temp -> main_down == temp -> neighbor[count[temp -> vertex - 1]]){
            count[temp -> vertex - 1]++;
        }
        if(count[temp -> vertex - 1] >= num_of_nei[temp -> vertex - 1]){
            stack_pop_main(stk);
            temp = stack_peek(stk);
        }
        else{
            target = count[temp -> vertex - 1];
            count[temp -> vertex - 1]++;
            temp = temp -> neighbor[target];
            stack_push_main(stk, temp); 
        }
    }
    free(count);
    count = calloc(N, sizeof(int));
    // counstruct table
    temp = stk -> top;
    node *prev = NULL, *next = NULL;
    while(temp != NULL){
        next = temp -> main_down;
        mark(temp, prev, next, table, num_of_nei, count);
        prev = temp;
        temp = next;
    }
    temp = stk -> top;
    int query;
    int *ans = malloc(Q * sizeof(int));
    for(int i = 0; i < Q; i++){
        scanf("%d", &query);
        ans[i] = table[query - 1];
    }
    for(int i = 0; i < Q; i++)
        printf("%d\n", ans[i]);
    
    // free
    free(num_of_nei);
    num_of_nei = NULL;
    free(table);
    table = NULL;
    free(count);
    count = NULL;
    for(int i = 0; i < N; i++)
        free(adjLists[i]);
    free(adjLists);
    adjLists = NULL;
    for(int i = 0; i < N - 1; i++)
        free(message[i]);
    free(message);
    message = NULL;
    return 0;
}
