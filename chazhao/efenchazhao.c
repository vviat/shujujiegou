#include<stdio.h>
//正常问题
int binary_search1(int *num, int n, int x){
    int head = 0; 
    int tail = n - 1;
    int mid;
    while(head <= tail) {
        mid = (head + tail) >> 1;
        if(num[mid] == x) return mid;
        if(num[mid] < x) {
            head = mid + 1;
        } else {
            tail = mid - 1;
        }
    } 
    return -1;
}
int main(){
    int n;
    int num[n];


    return 0;
}
