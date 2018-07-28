#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define lowbit(x) (x & 0xffff)
#define highbit(x) ((x >> 16) & 0xffff)

#define TEST(n ,func) {\
    int num[n] = {0};\
    printf("[");\
    for(int i = 0; i < n; i++) {\
        num[i] = rand() % 10000;\
        printf("%d ", num[i]);\
        }\
        printf("]\n");\
        func;\
        output(num, n, #func);\
}

void output(int *num, int n, const char *str) {
    printf("%s = [", str);
    for(int i = 0; i < n; i++) {
        printf("%d ",num[i]);
    }
    printf("]\n");

}

void raddix_sort(int *num, int n) {
    int *temp = (int *)malloc(sizeof(int) * n);
    int cnt[65536] = {0};
    for(int i = 0; i < n; i++) {
        cnt[lowbit(num[i])]++;
    }

    for(int i =1; i < 65536; i++) {
        cnt[i] += cnt[i - 1];
    }

    for(int i = n - 1; i >= 0; i--) {
        temp[--cnt[lowbit(num[i])]] = num[i];
    }
    


    for(int i = 0; i < n; i++) {
        cnt[highbit(temp[i])]++;
    }

    for(int i =1; i < 65536; i++) {
        cnt[i] += cnt[i - 1];
    }

    for(int i = n - 1; i >= 0; i--) {
        num[--cnt[highbit(temp[i])]] = temp[i];
    }

    free(temp);
}

int main() {
    TEST(20, raddix_sort(num, 20));
    return 0;
}
