/*************************************************************************
	> File Name: AVL.c
	> Author: 
	> Mail: 
	> Created Time: 2018年09月21日 星期五 20时17分26秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX(a,b) ({
    __typeof(a) _a = (a);\
    __typeof(b) _b = (b);\
    __a > __b ? __a : __b;\
})
typedef struct Node {
    int key, h;
    struct Node *lchild, *rchild;
}Node;

Node *NIL;

__attribute__((constructor))
void init_nil() {
    NIL = (Node *)malloc(sizeof(Node));
    NIL->key = 0;
    NIL->lchild = NIL->rchild = NIL;
    NIL->h = 0;
}

void *init(int key) {
    Node *p = (Node *)malloc(sizeof(Node));
    p->lchild = p->rchild = NIL;
    p->h = 1;
    p->key = key;
    return ;
}

Node *left_rotate(Node *root) {
    Node *temp = root->rchild;
    root->rchild = temp->lchild;
    temp->lchild = root;
    root->h = MAX(root->lchild->h,root->rchild->h) + 1;
    temp->h = MAX(temp->lchild->h,temp->rchild->h) + 1;
    return temp;
}

Node *right_rotate(Node *root){  
    Node *temp = root->lchild;
    root->lchild = temp->rchild;
    temp->rchild = root;
    root->h = MAX(root->lchild->h,root->rchild->h) + 1;
    temp->h = MAX(temp->lchild->h,temp->rchild->h) + 1;
    return temp;
}


Node *maintain(Node *root) {
    if(abs(root->lchild->h - root->rchild->h) < 2) return root;
    if(root->lchild->h > root->rchild->h) {
        if(root->lchild->lchild->h < root->lchild->rchild->h) {
            root->lchild = left_rotate(root->lchild);
        }
        root = right_rotate(root);
    } else {
        if(root->rchild->lchild->h < root->rchild->rchild->h) {
            root->rchild = right_rotate(root->rchild);
        }
        root = left_rotate(root);
    }
}

Node *insert(Node *root, int key) {
    if(root == NIL) {
        return init(key);
    }
    if(root->key == key) return root;
    if(root->key < key) {
        root->rchild = insert(root->rchild,key);
    } else {
        root->lchild = insert(root->lchild, key);
    }
    root->h = MAX(root->lchild->h,root->rchild->h) + 1;
    return maintain(root);
}
int main(){
    srand(time(0));
    Node *root = NIL;
    for(int i = 1; i <= 5; i++){
        root = insert(root, i);
        output(root);
        printf("------------\n");
    }
    clear
    root = NIL;
    return 0;
}
