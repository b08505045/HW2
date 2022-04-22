#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "price.h"

// unsigned long long price(unsigned long long s, unsigned long long t){
//     long long ans = s - t;
//     return ans < 0 ? 0 : ans;
// }

// unsigned long long price(unsigned long long s, unsigned long long t){
// 	unsigned long long p, x = (s ^ (s >> 30)) * 0xbf58476d1ce4e5b9ULL;
// 	p = (s - 1) / 1000000ULL + 1ULL;
// 	x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;
// 	x = x ^ (x >> 31);  
// 	unsigned long long la = 0, lb = 0, ra = 0xffffffffffefULL, rb = 0xffffffffffefULL, 
// 		ma, mb, na, nb, y = x, ta = (t > (p >> 1)) ? (t - (p >> 1)) : 0, tb = t + (p >> 1), tr = t / p;

// 	for(int i = 28; i >= 1; i -= 3){
// 		ma = la + (((ra - la) * (x >> 48)) >> 16); 
// 		mb = lb + (((rb - lb) * (y >> 48)) >> 16); 
// 		if((1ULL << (i + 2)) & ta) la = ma;
// 		else ra = ma;
// 		if((1ULL << (i + 2)) & tb) lb = mb;
// 		else rb = mb;
// 		ma = la + (((ra - la) * ((x & 0xffff00000000ULL) >> 32)) >> 16); 
// 		mb = lb + (((rb - lb) * ((y & 0xffff00000000ULL) >> 32)) >> 16); 
// 		if((1ULL << (i + 1)) & ta) la = ma;
// 		else ra = ma;
// 		if((1ULL << (i + 1)) & tb) lb = mb;
// 		else rb = mb;
// 		ma = la + (((ra - la) * ((x & 0xffff0000ULL) >> 16)) >> 16); 
// 		mb = lb + (((rb - lb) * ((y & 0xffff0000ULL) >> 16)) >> 16); 
// 		x = (x >> 21) ^ (ta & (1ULL << i)) ^ (x * 0xc0ffee123456789ULL);
// 		y = (y >> 21) ^ (tb & (1ULL << i)) ^ (y * 0xc0ffee123456789ULL);
// 		if((1ULL << i) & ta) la = ma;
// 		else ra = ma;
// 		if((1ULL << i) & tb) lb = mb;
// 		else rb = mb;
// 	}

// 	ma = la + (((ra - la) * (x >> 48)) >> 16); 
// 	mb = lb + (((rb - lb) * (y >> 48)) >> 16); 
// 	if(1ULL & ta) la = ma;
// 	else ra = ma;
// 	if(1ULL & tb) lb = mb;
// 	else rb = mb;
// 	y = (y ^ (y >> 30)) * 0xbf58476d1ce4e5b9ULL;
// 	x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;
// 	x = x ^ (y << 13);

// 	return 	la + tr + (((lb - la) * (x >> 48)) >> 16);
// }

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

void heap_sort(node *heap, int size, node *sorted, int cur, int k, int N){
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
    int s, k, cur = 0; // (s, k) input, cur : current max k
    unsigned long long *ans = malloc(Q * sizeof(unsigned long long));
    for(int i = 0; i < Q; i++){
        scanf("%d %d", &s, &k);
        if(cur < k){
            heap_sort(heap, size, sorted, cur, k , N);
            cur = k;
            ans[i] = sorted[k].price;
            // printf("\n k-th smallest : %llu\n", sorted[k].price);
        }
        else{
            ans[i] = sorted[k].price;
            // printf("already exist k-th smallest : %llu\n", sorted[k].price);
        }
        // printf("sorted : ");
        // for(int i = 1; i < k + 1; i++){
        //     printf("%llu ", sorted[i].price);
        // }
        // printf("\nheap :");
        // for(int i = 1; i < size + 1; i++){
        //     printf("%llu ", heap[i].price);
        // }
    
        // // addtional stock
        // if(s){

        // }
        // // no addtional
        // else{

        // }
    }
    for(int i = 0; i < Q; i++){
        printf("%llu\n", ans[i]);
    }

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
