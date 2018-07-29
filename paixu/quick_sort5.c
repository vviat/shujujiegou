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

void ungarded_insert_sort(int *num,int n){ //非监督插入
    int ind = 0;
    for(int i = 1; i< n; i++){
        if(num[i] < num[ind]) ind = i;
    } //遍历n找一个最小的值；下面减小n方操作；
    swap(num[ind],num[0]);
    for(int i = 2; i < n;i++) {
        int j = i;
        while(num[j] < num[j - 1]) {
            swap(num[j], num[j - 1]);
            j--;
        }
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

void quick_sort4(int *num, int l,int r){
    while(r - l >= 16) {
        int x = l, y = r, z = num[rand()%(r- l + 1) +l];//随机找一个基准值
        do {
            while(num[x] < z) ++x;
            while(num[y] > z) --y;
            if(x <= y){
                swap(num[x], num[y]);
                ++x, --y;
            }
        } while(x <= y);
        quick_sort(num , l , y);
        l = x;
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
