/*************************************************************************
	> File Name: double_array_trie.c
	> Author: 
	> Mail: 
	> Created Time: 2018年08月04日 星期六 16时05分04秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BASE 26
#define BEGIN_LETTER 'a'

typedef struct DANode {
    int base,check;
} DANode;

typedef struct Node {
    int flag;
    struct Node *next[BASE];
} Node, *Trie;

int node_cnt = 0;
Node *get_new_node() {
    Node *p = (Node *)calloc(sizeof(Node), 1);
    node_cnt++;
    return p;
}

void clear(Trie root) {
    if (root == NULL) return ;
    for (int i = 0; i < BASE; i++) {
        clear(root->next[i]);
    }
    free(root);
    return ;
}

Node *insert(Trie root, const char *str) {
    if (root == NULL) root = get_new_node();
    Node *p = root;
    for (int i = 0; str[i]; i++) {
        int ind = str[i] - BEGIN_LETTER;
        if (p->next[ind] == NULL) p->next[ind] = get_new_node();
        p = p->next[ind];
    }
    p->flag = 1;
    return root;
}

int search(Trie root, const char *str) {
    Node *p = root;
    int i = 0;
    while (p && str[i]) {
        int ind = str[i++] - BEGIN_LETTER;
        p = p->next[ind];
    }
    return (p && p->flag);
}

void get_random_string(char *str) {
    int len = rand() % 10 + 1;
    for (int i = 0; i < len; i++) str[i] = BEGIN_LETTER + rand() % BASE;
    str[len] = 0;
    return ;
}

void output(Trie root, char *str, int level) {
    if (root == NULL) return ;
    str[level] = 0;
    if (root->flag) {
        printf("find word : %s\n", str);
    }
    for (int i = 0; i < BASE; i++) {
        if (root->next[i] == NULL) continue;
        str[level] = i + BEGIN_LETTER;
        output(root->next[i], str, level + 1);
    }
    return ;
}

int get_base(Node *node, DANode *data) {
    int base = 2;
    int flag = 0;
    while(!flag){
        flag = 1;
        for(int i = 0; i < BASE; i++){
            if(data[base + i]. check==0) continue;
            flag = 0;
            break;
        }
        //if(flag) break;
        base += (!flag);
    }
    return base;
}

void build(Node *node, DANode *data, int ind) {
    if(node == NULL) return ;
    //int base = get_base(node,data);
    if(node->flag) data[ind].check = -data[ind].check;
    data[ind].base = get_base(node, data);
    for(int i = 0; i < BASE; i++){
        if(node->next[i] == NULL)continue;
        data[data[ind].base + i].check = ind;
    }
    for(int i = 0; i < BASE; i++) {
        if(node->next[i] == NULL) continue;
        build(node->next[i],data, data[ind].base +i);
    }
    return ;
}
void output_da(DANode *data, char *str, int level, int ind) {
    if (data == NULL) return ;
    str[level] = 0;
    if (data[ind].check < 0) {
        printf("find word : %s\n", str);
    }
    for (int i = 0; i < BASE; i++) {
        if (abs(data[data[ind].base + i].check) != ind) continue;
        str[level] = i + BEGIN_LETTER;
        output_da(data, str, level + 1,data[ind].base + 1);
    }
    return ;
}

int main() {
    srand(time(0));
    #define INSERT_CNT 20
    Trie root = NULL;
    char str[50];
    int word_cnt = 0;
    for (int i = 0; i < INSERT_CNT; i++) {
        get_random_string(str);
        root = insert(root, str);
        word_cnt += strlen(str);
        printf("insert %s to Trie\n", str);
    }
    output(root, str, 0);
    printf("storsge rate: %lf\n", 1.0 * word_cnt /(1.0 * node_cnt * sizeof(Node)));
    DANode *data = (DANode *) calloc(sizeof(DANode), (INSERT_CNT * 100));
    build(root, data,1);
    output_da(data, str ,0, 1);

    #undef INSERT_CNT 
    return 0;
}
