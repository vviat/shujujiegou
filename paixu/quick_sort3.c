/*************************************************************************
	> File Name: unstable_sort.c
	> Author: 
	> Mail: 
	> Created Time: 2018年07月28日 星期六 09时52分45秒
 ************************************************************************/

#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#define swap(a,b) { \
    __typeof(a) temp; \
    temp = a; \
    a = b;\
    b = temp;\  
}
#define TEST(n, func) { \
    int num[n] = {0};\
    printf("[");\
    for (int i = 0; i < n; i++) { \
        num[i] = rand() % 100; \
        printf("%d ", num[i]); \
    } \
    printf("]\n"); \
    func; \
    output(num, n, #func); \
}


void output(int *num, int n, const char *str) {
    printf("%s = [", str);
    for (int i = 0; i < n; i++) {
        printf("%d ", num[i]);
    }
    printf("]\n"); 
}

void quick_sort2(int *num, int l,int r){
    while(r - l >= 16) {
        int x = l, y = r, z = num[l];
        while(x < y) {
            while (x < y && num[y] >= z) --y;
            if(x < y) num[x++] = num[y];
            while (x < y && num[y] <= z) ++x;
            if(x < y) num[y--] = num[x];
        }
        num[x] = z;
        quick_sort(num, l, x-1);
        l = x + 1;
    }
    ungarded_insert_sort(num + l, r - l + 1);
    return ;
}


int main(){
    srand(time(0));
    TEST(30,select_sort(num,30));
    TEST(30,quick_sort(num, 0, 29));
    TEST(30,quick_sort1(num, 0, 29));
    TEST(30,quick_sort2(num, 0, 29));
    TEST(30,quick_sort3(num, 0, 29));
    TEST(30,quick_sort4(num, 0, 29));
    return 0;
}
