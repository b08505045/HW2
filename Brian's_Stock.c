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

unsigned long long price(unsigned long long s, unsigned long long t){
    return s - t;
}

int main(int argc, char *argv[]){
    int A, Q, N; // A : num of Brian's stock / Q : num of questions / N : N days
    scanf("%d %d %d", &A, &Q, &N);
    int *fav = malloc((A + 1) * sizeof(int*));
    unsigned long long *heap = malloc((N * A + 1) * sizeof(unsigned long long)); // using 1d to simulate 2d array
    unsigned long long *sorted = malloc((N * A + 1) * sizeof(unsigned long long));
    fav[0] = -1; // empty
    heap[0] = -1; // empty
    sorted[0] = -1;
    // read fav
    for(int i = 1; i < A + 1; i++){
        scanf("%d", &fav[i]);
    }
    // create all A * N
    for(int i = 1; i < A + 1; i++){
        for(int j = 1; j < N + 1; j++){
            heap[(i - 1) * N + j] = price(fav[i], j);
        }
    }
    //--------------------------------------------------------------------------------------------
    for(int i = 1; i < A + 1; i++){
        for(int j = 1; j < N + 1; j++){
            printf("%d ", heap[(i - 1) * N + j]);
        }
        printf("\n");
    }
    //--------------------------------------------------------------------------------------------
    // build heap
    build_min_heap(heap, N * A);
    //--------------------------------------------------------------------------------------------
    for(int i = 1; i < A + 1; i++){
        for(int j = 1; j < N + 1; j++){
            printf("%d ", heap[(i - 1) * N + j]);
        }
        printf("\n");
    }
    //--------------------------------------------------------------------------------------------
    // int s, k, cur = 0; // (s, k) input, cur : current max k
    // for(int i = 0; i < Q; i++){
    //     scanf("%d %d", &s, &k);
    //     if(cur <= k){
    //         cur = k;
    //         for(int i = 0; i < k; i++){
    //             heap_sort(heap, N * A, sorted);
    //         }
    //     }
    // }
    // if(A == 1){
    //     // A == 1 && N == 1
    //     if(N == 1){
    //         int k;
    //         unsigned long long *ans = malloc(Q * sizeof(unsigned long long));
    //         for(int i = 0; i < Q; i++){
    //             scanf("%llu", &k);
    //             ans[i] = price(1, k);
    //         }
    //         for(int i = 0; i < Q; i++){
    //             printf("%d\n", ans[i]);
    //         }
    //     }
    //     // A == 1 && N != 1 : smallest 1 ~ N, second ~ N + 1, third ~ N + 2
    //     else{
    //         int *sorted = malloc(1000000 * sizeof(int));
    //         unsigned long long *fav = malloc(N * sizeof(unsigned long long));
    //         int s_i; // A = 1, only one Si
    //         scanf("%d", &s_i);
    //         for(int i = 0; i < N; i++){
    //             fav[i] = price(s_i, N);
    //         }
    //         build_min_heap(fav, N);
    //     }
    // }
    // else{
    //     // A != 1 && N == 1
    //     if(N == 1){

    //     }
    //     // A != 1 && N != 1
    //     else{

    //     }
    // }
    // for(int i  = 0; i < N; i++){
    //     fav[i] = malloc(A * sizeof(int));
    // }
    // for(int i = 0; i < N; i++){
    //     for(int j = 0; j < A; j++){
    //         fav[j][i] = price(j, i);
    //     }
    // }

    // printf("Start : ");
    // for(int i = 1; i <= 10; i++){
    //     printf("%d\n", price(1, i));
    // }
    return 0;
}
