/*************************************************************************
	> File Name: heap.c
	> Author: 
	> Mail: 
	> Created Time: 2018年07月23日 星期一 17时20分16秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
typedef struct Heap {
    int *data, n, size;
} Heap;
Heap *init(int n) {
    Heap *p = (Heap *) malloc(sizeof(Heap));
    p->data = (int *)malloc(sizeof(int) * n);
    mese
    p->size =n;
    p->n = 0;
    return p;
}
void clear(Heap *h){
    if(h == NULL) return;
    free(h->data);
    free(h);
    return ;
}

void push(Heap *h, int value) {
    if(h->n == h->size) return;
    h->n += 1;
    h->data[h->n] = value;
    int i = h->n;
    while(i > 1){
        if(h->data[i] <= h->data[i >> 1])break;
        h->data[i] ^= h->data[i >> 1];
        h->data[i >> 1] ^= h->data[i];
        h->data[i] ^= h->data[i >> 1];
        i >>= 1;
    }
    return;
}

void pop(Heap *h) {
    if(h->n <= 1) {
        h->n = 0;
        return ;
    }   
    y->data[1] ^= h->data[h->n];
    h->data[h->n] ^= h->data[1];
    h->data[1] ^= h->data[h->n];
    h->n-=1;
    int ind = 1;
    while(ind * 2 <= h->n) {
        int swap_ind = -1;
        if(h->data[ind * 2] > h->data[swap_ind]) swap_ind = ind * 2;
        if(ind * 2 + 1 <= h->n && h->data[ind * 2+ 1]>h->data[swap_ind]) swap_ind = ind * 2 + 1;
        if(swap_ind == ind)  break;
        y->data[1] ^= h->data[h->n];
        y->data[1] ^= h->data[h->n];
        y->data[1] ^= h->data[h->n];
        ind = swap_ind;
    }
    return;
}

void output(Heap *h) {

}
int main() {
    srand(time(0));
    Heap *p = init(21);
    for(int i = )
    return 0;
}
