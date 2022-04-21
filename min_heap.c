#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned long long remove_min(unsigned long long *A, int *size){
    unsigned long long result = A[1];
    unsigned long long tail = A[*size];
    // printf("size : %d, remove : %d, tail : %d\n", *size, result, tail);
    int left, right;
    A[1] = tail;
    A[*size] = 0;
    (*size)--;
    // printf("root now : %d, size now : %d\n", A[1], *size);
    int i = 1, smallest;
    while(i <= *size){
        left = 2 * i;
        right = 2 * i + 1;
        if(left <= *size && A[left] <= A[i])
            smallest = left;
        else smallest = i;
        if(right <= *size && A[right] <= A[smallest])
            smallest = right;
        if(smallest == i){
            // printf("break\n");
            break;
        }
        else{
            int temp = A[i];
            A[i] = A[smallest];
            A[smallest] = temp;
            i = smallest;
        }
    }
    // printf("heap now : ");
    // for(int i = 1; i < *size + 1; i++){
    //     printf("%d ", A[i]);
    // }
    // printf("\n");
    return result;
}

void insert(unsigned long long *A, unsigned long long data, int *size){
    (*size)++;
    A[*size] = data;
    int i = *size, parent;
    while(i != 1){
        parent = i / 2;
        if(A[i] > A[parent])
            break;
        else{
            A[i] = A[parent];
            A[parent] = data;
            i = parent;
        }
    }
}

void heap_sort(unsigned long long *A, int N, unsigned long long *sorted){
    printf("\nLet's sort!\n");
    unsigned long long data;
    int size = N;
    for(int i = 1; i < N + 1; i++){
        data = remove_min(A, &size);
        // printf("data is : %d\n", data);
        sorted[i] = data;
    }
}
void min_heapify(unsigned long long *A, int i, int N){
    int left, right, smallest;
    while(i <= N){
        left = 2 * i;
        right = 2 * i + 1;
        if(left <= N && A[left] <= A[i])
            smallest = left;
        else smallest = i;
        if(right <= N && A[right] <= A[smallest])
            smallest = right;
        if(smallest != i){
            int temp = A[i];
            A[i] = A[smallest];
            A[smallest] = temp;
            i = smallest;
            // min_heapify(A, smallest, N);
        }
        else break;
    }
}
void build_min_heap(unsigned long long *A, int N){
    for(int i = N / 2; i > 0; i--){
        min_heapify(A, i, N);
    }
}

int main(){
    int capacity = 20;
    int N = 10;
    unsigned long long *A = malloc((capacity + 1) * sizeof(int));
    unsigned long long *sorted = malloc((capacity + 1) * sizeof(int));
    sorted[0] = -1;
    A[0] = -1;
    for(int i = 1; i < N + 1; i++){
        scanf("%d", &A[i]);
    }
    for(int i = 1; i < N + 1; i++){
        printf("%d ", A[i]);
    }
    printf("\n");
    // build heap
    build_min_heap(A, N);
    for(int i = 1; i < N + 1; i++){
        printf("%d ", A[i]);
    }
    printf("\ninsert\n");
    // insert
    insert(A, 5, &N);
    insert(A, 7, &N);
    printf("%d\n", N);
    for(int i = 1; i < N + 1; i++){
        printf("%d ", A[i]);
    }
    // heap-sort
    heap_sort(A, N, sorted);
    for(int i  = 1; i < N + 1; i++){
        printf("%d ", sorted[i]);
    }
    printf("\n");
    return 0;
}
