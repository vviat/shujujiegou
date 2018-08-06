/*************************************************************************
	> File Name: kmp.c
	> Author: 
	> Mail: 
	> Created Time: 2018年08月02日 星期四 20时32分05秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int KMP(const char *text, const char *pattern) {
    #define RETURN(a){\
        free(next);\
        return a;\
    }
    int len1 = strlen(text);
    int len2 = strlen(pattern);
    int *next = (int *)malloc(sizeof(int) * len2);
    int j = -1;
    next[0] = -1;
    for(int i = 1; i < len2; i++){
        while(j != -1 && pattern[j + 1] != pattern[i]) j = next[j];
        if(pattern[ j+ 1 ] == pattern[i]){
            j+= 1;
        } else {
            next[i] = j;
        }
    }
    j = -1;
    for(int i =0; text[i]; i++){
        while(j != -1&& pattern[j + 1] != text[i]) j = next[i];
        if(pattern[j + 1] == text[i]) j += 1;
        if(pattern[j + 1] == 0) RETURN(1);
    }
    RETURN(0);
    #undef RETURN
}



int main(){
    char str1[] = " hello world";
    printf("KMP(%s, %s) = %d\n", str1, "wor", KMP(str1, "wor"));
    return 0;
}
