/*************************************************************************
	> File Name: weighted_quick_union_with_path.c
	> Author: 
	> Mail: 
	> Created Time: 2018年08月11日 星期六 11时22分51秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

typedef struct UnionSet {
    int *data,*size;
    int n;
    int cnt;
}UnionSet;

UnionSet *init(int n){
    UnionSet *p = (UnionSet *) malloc(sizeof(UnionSet));
    p->data = (int *)malloc(sizeof(int ) * n);
    p->size = (int *)malloc(sizeof(int ) * n);
    p->n = p->cnt = n;
    for(int i = 0; i < n; i++) {
        p->data[i] = i;
        p->size[i] = 1;
    }
    return p;
}

void clear(UnionSet *u) {
    if(u == NULL) return;
    free(u->data);
    free(u);
    return ;
}

int find(UnionSet *u,int n) {
    if(u->data[n] == n) return n;
    int father = find(u, u->data[n]);
    u->data[n] = father;
    return father;
}

int merge(UnionSet *u, int a, int b) {
    int father_a = find(u, a), father_b = find(u,b);
    if(father_a == father_b) return 0;
    if(u->size[father_a] > u->size[father_b]) {
        u->data[father_b] = father_a;
        u->size[father_a] += u->size[father_b];
    } else {
        u->data[father_a] = father_b;
        u->size[father_b] += u->size[father_a];
    }
    u->cnt -= 1;
    return 1;
}
int main() {
    srand(time(0));
    UnionSet *u = init(10);
    #define OP_NUM 20
    for (int i = 0; i < OP_NUM; i++) {
        int a = rand() % 10, b = rand() % 10;
        printf("union %d with %d = %d\n", a, b, merge(u, a, b));
        printf("Union Set Cnt = %d\n", u->cnt);
    }
    #undef OP_NUM
    return 0;
}
