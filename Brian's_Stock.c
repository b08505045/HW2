#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "price.h"

typedef struct node{
    unsigned long long s_i, day, price;
}node;

node node_new(unsigned long long s_i, unsigned long long day){
    node n;
    n.s_i = s_i;
    n.day = day;
    n.price = price(s_i, day);
    return n;
}

node remove_min(node *A, int *size){
    node result = A[1];
    A[1] = A[*size];
    (*size)--;
    // printf("size : %d, remove : %d, tail : %d\n", *size, result, tail);
    int left, right;
    // printf("root now : %d, size now : %d\n", A[1], *size);
    int i = 1, smallest;
    while(i <= *size){
        left = 2 * i;
        right = 2 * i + 1;
        if(left <= *size && A[left].price <= A[i].price)
            smallest = left;
        else smallest = i;
        if(right <= *size && A[right].price <= A[smallest].price)
            smallest = right;
        if(smallest == i){
            // printf("break\n");
            break;
        }
        else{
            node temp = A[i];
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

void insert(node *A, node new_node, int *size){
    (*size)++;
    A[*size] = new_node;
    int i = *size, parent;
    while(i != 1){
        parent = i / 2;
        if(A[i].price > A[parent].price)
            break;
        else{
            A[i] = A[parent];
            A[parent] = new_node;
            i = parent;
        }
    }
}

void heap_sort(node *heap, int size, node *sorted, unsigned long long cur, unsigned long long k, int N){
    // printf("\nLet's sort!\n");
    node n;
    for(int i = cur + 1; i < k + 1; i++){
        n = remove_min(heap, &size);
        // printf("data is : %d\n", data);
        sorted[i] = n;
        insert(heap, node_new(n.s_i, n.day + N), &size);
    }
}

void min_heapify(node *A, int i, int size){
    int left, right, smallest;
    while(i <= size){
        left = 2 * i;
        right = 2 * i + 1;
        if(left <= size && A[left].price <= A[i].price)
            smallest = left;
        else smallest = i;
        if(right <= size && A[right].price <= A[smallest].price)
            smallest = right;
        if(smallest != i){
            node temp = A[i];
            A[i] = A[smallest];
            A[smallest] = temp;
            i = smallest;
            // min_heapify(A, smallest, N);
        }
        else break;
    }
}
void build_min_heap(node *A, int size){
    for(int i = size / 2; i > 0; i--){
        min_heapify(A, i, size);
    }
}

void merge(unsigned long long *A, int l, int m, int r){
    int i, j, k;
    int n1 = m - l + 1, n2 = r - m;
    unsigned long long *L = malloc(n1 * sizeof(unsigned long long)), *R = malloc(n2 * sizeof(unsigned long long));
    for(i = 0; i < n1; i++)
        L[i] = A[l + i];
    for(j = 0; j < n2; j++)
        R[j] = A[m + 1 + j];
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2){
        if(L[i] <= R[j]){
            A[k] = L[i];
            i++;
        }
        else{
            A[k] = R[j];
            j++;
        }
        k++;
    }
    while(i < n1){
        A[k] = L[i];
        i++;
        k++;
    }
    while(j < n2){
        A[k] = R[j];
        j++;
        k++;
    }
    free(L);
    free(R);
}

void mergeSort(unsigned long long *A, int left, int right){
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(A, left, mid);
        mergeSort(A, mid + 1, right);
        merge(A, left, mid, right);
    }
}

int main(int argc, char *argv[]){
    int A, Q, N; // A : num of Brian's stock / Q : num of questions / N : N days
    scanf("%d %d %d", &A, &Q, &N);
    int *fav = malloc((A + 1) * sizeof(int));
    int size = N * A;
    node *heap = malloc((size + 1) * sizeof(node)); // using 1d to simulate 2d array
    node *sorted = malloc(1000001 * sizeof(node));

    // sorted[size] = node_new(5, 3);
    // printf("sorted[%d] : %llu\n", size, sorted[size].price);
    
    // read fav
    for(int i = 1; i < A + 1; i++){
        scanf("%d", &fav[i]);
    }
    // create all A * N
    for(int i = 1; i < A + 1; i++){
        for(int j = 1; j < N + 1; j++){
            heap[(i - 1) * N + j] = node_new(fav[i], j);
        }
    }
    free(fav);
    //--------------------------------------------------------------------------------------------
    // printf("Start create\n");
    // for(int i = 1; i < A + 1; i++){
    //     for(int j = 1; j < N + 1; j++){
    //         printf("%lld ", heap[(i - 1) * N + j].price);
    //     }
    //     printf("\n");
    // }
    //--------------------------------------------------------------------------------------------
    // build heap
    // printf("Start build heap\n");
    build_min_heap(heap, size);
    //--------------------------------------------------------------------------------------------
    // for(int i = 1; i < A + 1; i++){
    //     for(int j = 1; j < N + 1; j++){
    //         printf("%lld ", heap[(i - 1) * N + j].price);
    //     }
    //     printf("\n");
    // }
    // printf("Query :\n\n");
    //--------------------------------------------------------------------------------------------
    unsigned long long s, k, cur = 0; // (s, k) input, cur : current max k
    unsigned long long *ans = malloc(Q * sizeof(unsigned long long));
    for(int i = 0; i < Q; i++){
        scanf("%d %d", &s, &k);
        if(cur < k){
            heap_sort(heap, size, sorted, cur, k , N);
            cur = k;
            // ans[i] = sorted[k].price;
            // printf("\n k-th smallest : %llu\n", sorted[k].price);
        }
        // no addtional, good !
        if(!s)
            ans[i] = sorted[k].price;
        // addtional stock, oops
        else{
            if(N == 1){ // N = 1 means addtional stock is strictly increasing, e.g p1 < p2 < p3 <......
                // discord :
                //(1) s{k - n} <= sorted[n] && s{k - n + 1} >= sorted[n]: 答案為 sorted[n]
                //(2) s{k - n} >= sorted[n] && s{k - n} <= sorted[n + 1]: 答案為 s{k - n}
                //(3) s{k - n} <= sorted[n]: right = n - 1，繼續搜尋
                //(4) s_{k - n} >= sorted[n]: left = n + 1，繼續搜尋
                unsigned long long Start = 1, End = k, day = (Start + End) / 2;
                unsigned long long s_1 = price(s, 1), s_k = price(s, k), s_k_1 = price(s, k-1);
                //---------------------------------------------------------------------------edge case
                // 額外的最小 >= sorted最大 --> 前k小皆為sorted
                if(s_1 >= sorted[k].price)
                    ans[i] = sorted[k].price;
                // 額外的最大 <= sorted最小 --> 前k小皆為額外
                else if(s_k <= sorted[1].price)
                    ans[i] = s_k;
                // 先決定或排除 edge case
                else if(s_1 <= sorted[k-1].price && price(s, 2) >= sorted[k-1].price)
                    ans[i] = sorted[k-1].price;
                else if(s_1 >= sorted[k-1].price && s_1 <= sorted[k].price)
                    ans[i] = s_1;
                else if(s_k_1 <= sorted[1].price && s_k >= sorted[1].price)
                    ans[i] = sorted[1].price;
                else if(s_k_1 >= sorted[1].price && s_k_1 <= sorted[2].price)
                    ans[i] = s_k_1;
                //---------------------------------------------------------------------------
                else{
                    while(Start != day && End != day){
                        s_1 = price(s, day);
                        // s{n} <= sorted[k - n]
                        if(s_1 <= sorted[k - day].price){
                            // s{n + 1} >= sorted[k - n]
                            if(price(s, day + 1) >= sorted[k - day].price){
                                ans[i] = sorted[k - day].price;
                                break;
                            }
                            else 
                                Start = day;
                        }
                        // s{n} > sorted[k - n]
                        else{
                            // s{n} <= sorted[k - n + 1]
                            if(s_1 <= sorted[k - day + 1].price){
                                ans[i] = s_1;
                                break;
                            }
                            else
                                End = day;
                        }
                        day = (Start + End) / 2;
                    }
                }
            }
            // N != 1, shit man
            else{
                unsigned long long Start = 1, End = k, day = (Start + End) / 2, cur = 1;
                unsigned long long s_1, s_2;
                int kN = 0; // kN = 1 when add[k+N] == sorted[k-day]
                while((End - Start) >= 2 * N){
                    s_1 = price(s, day + N);
                    // add[i] < sorted[k -day] for all i <= k and add[k+N] < sorted[k - day], keep searching
                    if(s_1 < sorted[k - day].price){
                        Start = day;
                        cur = day;
                    }
                    // add[i] < sorted[k -day] for all i <= day, and add[k+N] == sorted[k-day], break;
                    else if(s_1 == sorted[k - day].price){
                        cur = day;
                        kN = 1;
                        break;
                    }
                    // keep searchingc
                    else
                        End = day;
                    day = (Start + End) / 2;
                }
                unsigned long long *add_stock = malloc(2 * N * sizeof(unsigned long long));
                // ans comes from add[k + 1] ~ add[k + N + N - 1] since add[day + N] == sorted[k - day]
                if(kN){
                    for(int j = 1; j < 2 * N; j++)
                        add_stock[j] = price(s, cur - N + j);
                    mergeSort(add_stock, 1, 2 * N - 1);
                    Start = 1;
                    End = 2 * N;
                    day = (Start + End) / 2;
                    while(Start != day && End != day){
                        // s{n} <= sorted[k - n]
                        if(add_stock[day] <= sorted[k - cur - day].price){
                            // s{n + 1} >= sorted[k - n]
                            if(add_stock[day + 1] >= sorted[k - cur - day].price){
                                ans[i] = sorted[k - cur - day].price;
                                break;
                            }
                            else 
                                Start = day;
                        }
                        // s{n} > sorted[k - n]
                        else{
                            // s{n} <= sorted[k - n + 1]
                            if(s_1 <= sorted[k - cur - day + 1].price){
                                ans[i] = add_stock[day];
                                break;
                            }
                            else
                                End = day;
                        }
                        day = (Start + End) / 2;
                    }
                }
                else{
                    // k-th will be (cur - N) ~ (cur + N)
                    // addtinoal stock's day-th will all <= sorted[1000000-day], including add[day + N]
                    for(int j = 1; j < 2 * N; j++)
                        add_stock[j] = price(s, cur - N + j);
                    mergeSort(add_stock, 1, 2 * N - 1);
                    Start = 1;
                    End = 2 * N;
                    day = (Start + End) / 2;
                    while(Start != day && End != day){
                        // s{n} <= sorted[k - n]
                        if(add_stock[day] <= sorted[k - cur - day].price){
                            // s{n + 1} >= sorted[k - n]
                            if(add_stock[day + 1] >= sorted[k - cur - day].price){
                                ans[i] = sorted[k - cur - day].price;
                                break;
                            }
                            else 
                                Start = day;
                        }
                        // s{n} > sorted[k - n]
                        else{
                            // s{n} <= sorted[k - n + 1]
                            if(s_1 <= sorted[k - cur - day + 1].price){
                                ans[i] = add_stock[day];
                                break;
                            }
                            else
                                End = day;
                        }
                        day = (Start + End) / 2;
                    }
                }
                free(add_stock);
            }
        }
        // printf("sorted : ");
        // for(int i = 1; i < k + 1; i++){
        //     printf("%llu ", sorted[i].price);
        // }
        // printf("\nheap :");
        // for(int i = 1; i < size + 1; i++){
        //     printf("%llu ", heap[i].price);
        // }
    }
    for(int i = 0; i < Q; i++){
        printf("%llu\n", ans[i]);
    }
    return 0;
}
