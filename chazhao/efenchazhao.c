#include<stdio.h>
//111111000000
int binary_search2(int *num, int n, int x){
    int head = -1; 
    int tail = n - 1;
    int mid;
    while(head < tail) {
        mid = (head + tail + 1) >> 1;
        if(num[mid] == 1) {
            head = mid;
        } else {
            tail = mid - 1;
        }
    } 
    return head;
}
int main(){
    int n;
    int num[n];


    return 0;
}
