/*************************************************************************
	> File Name: lianbiao1.c
	> Author: 
	> Mail: 
	> Created Time: 2018年06月04日 星期一 22时40分19秒
 ************************************************************************/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#define malloc2(size) my_malloc(size, __FILE__, __func__, __LINE__)

void *my_malloc(int size, const char *file, const char *func, int line_no) {
    void *data = malloc(size);
    if (data == NULL) {
        fprintf(stderr, "[%s : %s-> %d] malloc error\n", file, func, line_no);
        fflush(stderr);
        exit(-1);
    }
    return data;
}

typedef struct Vector {
    int *data;
    int size, length;
} Vector;

Vector *init() {
    static int64_t n = 100LL;
    Vector *p = (Vector *)malloc2(sizeof(Vector));
    p->data = (int *)malloc2(sizeof(int) * n);
    p->size = n;
    p->length = 0;
    return p;
}

int expand(Vector *v) {
    int new_size = v->size;
    int *data;
    while (new_size) {
        data = (int *)realloc(v->data, sizeof(int) * (v->size + new_size));
        if (data == NULL) {
            new_size /= 2;
            continue;
        }
        break;
    }
    if (new_size == 0) return 0; 
    v->data = data;
    v->size += new_size;
    printf("vector expand\n");
    return 1;
}

int insert(Vector *v, int x, int ind) {
    if (v->length >= v->size) {
        if (!expand(v)) {
            return 0;
        }
    }
    if (ind < 0 || ind > v->length) {
        return 0;
    } 
    for (int i = v->length - 1; i >= ind; i--) {
        v->data[i + 1] = v->data[i];
    }
    v->data[ind] = x;
    v->length += 1;
    return 1;
}

int delete_element(Vector *v, int ind) {
    if (ind >= v->length || ind < 0) {
        return 0;
    }
    for (int i = ind + 1; i < v->length; i++) {
        v->data[i - 1] = v->data[i];
    }
    v->length -= 1;
    return 1;
}

void output(Vector *v) {
    printf("[");
    for (int i = 0; i < v->length; i++) {
        printf(" %d", v->data[i]);
    }
    printf(" ]\n");
    return ;
}

void clear(Vector *v) {
    if (v == NULL) return ;
    free(v->data);
    free(v);
    return ;
}

int main() {
    srand(time(0));
    Vector *v = NULL;
    v = init();
    for (int i = 0; i < 10; i++) {
        int x = rand() % 100, ind = rand() % (i + 3) - 1;
        printf("%d : insert(%d, %d) = ", i + 1, x, ind);
        int ret = insert(v, x, ind);
        printf("%d : ", ret);
        output(v);
    }
    for (int i = 0; i < 5; i++) {
        int ind = rand() % (v->length + 2) - 1;
        printf("%d : delete_element(%d) = ", i + 1, ind);
        int ret = delete_element(v, ind);
        printf("%d : ", ret);
        output(v);
    }
    return 0;
}
