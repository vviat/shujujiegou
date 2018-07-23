/*************************************************************************
	> File Name: huffman.c
	> Author: 
	> Mail: 
	> Created Time: 2018年07月23日 星期一 15时16分17秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define CHAR_NUM 26
#define swap(a, b) {\
    __typeof(a) temp;\
    temp = a;\
    a = b;\
    b = temp;\
}
typedef struct HFNode{
    int frep;//频数
    char ch;
    struct HFNode *lchild, *rchild;
}HFNode;

HFNode *getNode(){
    HFNode *p = (HFNode *)malloc(sizeof(HFNode));
    p->lchild = NULL;
    p->rchild = NULL;
    p->frep = 0;
    return p;
}
void build(int n, HFNode *arr[n]){
    for(int  times = 0; times < n- 1; times++){
        HFNode *minnode = arr[0];
        int ind = 0;
        for (int i = 0; i < n - times;  i++){
            if(arr[i]->frep >= minnode->frep) continue;
            minnode = arr[i];
            ind = i;
        }
        swap(arr[ind],arr[n-times - 1]);
        minnode = arr[0];
        ind = 0;
        for (int i = 0; i < n - times;  i++){
            if(arr[i]->frep >= minnode->frep) continue;
            minnode = arr[i];
            ind = i;
        }
        swap(arr[ind], arr[n- times - 2]);
        HFNode *new_node = getNode();
        new_node->lchild = arr[n- times - 1];
        new_node->rchild = arr[n- times - 2];
        new_node->frep = arr[n-times -1]->frep + arr[n- times - 2]->frep;
        arr[n - times - 2]= new_node;
    }
    return;
}

void extract(HFNode *root, char *buff, char (*huffman_code)[100], int n){
    buff[n] = '\0';
    if(root->lchild == NULL && root->rchild == NULL) {
        strcpy(huffman_code[root->ch],buff);
        return ;
    }
    buff[n] = '0';
    extract(root->lchild,buff,huffman_code, n+1);
    buff[n] = '1';
    extract(root->rchild,buff,huffman_code, n+1);
    return;
}

int main(){
    HFNode *arr[CHAR_NUM] = {0};
    char buff[100];
    char huffman_code[256][100] = {0};
    int frep;
    for(int i = 0; i < CHAR_NUM; i++){
        scanf("%s %d",buff, &frep);
        printf("read %s = %d\n",buff , frep);
        HFNode *new_node = getNode();
        new_node->ch = buff[0];
        new_node->frep = frep;
        arr[i] = new_node;
    }
    build(CHAR_NUM, arr);
    extract(arr[0],buff,huffman_code, 0);
    for(int i = 0; i< 256; i++) {
        if(huffman_code[i][0] == 0)continue;
        printf("%c : %s\n",(char)i,huffman_code[i]);
    }
    return 0;
}
