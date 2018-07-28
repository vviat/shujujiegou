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

void select_sort(int *num, int n){
    for(int i = 0;i< n-1; i++){
        int ind = i;
        for(int j= i+ 1; j < n; j++) {
            if(num[j] < num[ind]) ind = j;

        }
        swap(num[i], num[ind]);
    }
    return ;
}

void output(int *num, int n, const char *str) {
    printf("%s = [", str);
    for (int i = 0; i < n; i++) {
        printf("%d ", num[i]);
    }
    printf("]\n"); 
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
