#include<stdio.h>
//0000000011111111
int binary_search3(int *num, int n, int x){
    int head = 0; 
    int tail = n;
    int mid;
    while(head < tail) {
        mid = (head + tail) >> 1;
        if(num[mid] == 1) {
            tail = mid ;
        } else {
            head = mid + 1;
        }
    } 
    return head == n ? -1: head;
}
int main(){
    int n;
    int num[n];


    return 0;
}
