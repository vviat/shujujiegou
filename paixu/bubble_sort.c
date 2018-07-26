/*************************************************************************
	> File Name: stable_sort.c
	> Author: 
	> Mail: 
	> Created Time: 2018年07月26日 星期四 17时11分27秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#define swap(a,b) { \
    __typeof(a) temp; \
    temp = a; \
    a = b;\
    b = temp; \ 
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

void bubble_sort(int *, int );

void output(int *, int, const char *);

int main(){
    srand(time(0));
   
    TEST(30,bubble_sort(num,30));

    return 0;
}

void output(int *num, int n, const char *str) {
    printf("%s = [", str);
    for (int i = 0; i < n; i++) {
        printf("%d ", num[i]);
    }
    printf("]\n"); 
}

void bubble_sort(int *num, int n){
    int flag = 0;
    for(int i =1; i< n;i++) {
        flag = 0;
        for(int j = 0; j < n - 1; j++) {
        if(num[j] <= num[j + 1]) continue;
            swap(num[j],num[j + 1]);
            flag += 1;
        }
        if(flag == 0) break;
    }
    return ;
}

