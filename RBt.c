/*************************************************************************
	> File Name: 23.red_black_tree.c
	> Author: 
	> Mail: 
	> Created Time: 五 10/12 20:33:14 2018
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

typedef struct RBNode {
    int key, color; // 0 red, 1 black, 2 double black
    struct RBNode *lchild, *rchild;
} RBNode;

RBNode *NIL;

RBNode *getNewNode(int key) {
    RBNode *p = (RBNode *)malloc(sizeof(RBNode));
    p->key = key;
    p->color = 0;
    p->lchild = p->rchild = NIL;
    return p;
}

__attribute__((constructor)) void init_NIL() {
    NIL = getNewNode(0);
    NIL->color = 1;
    NIL->lchild = NIL->rchild = NIL;
    return ;
}

int hasRedChild(RBNode *node) {
    return node->lchild->color == 0 || node->rchild->color == 0;
}

RBNode *left_rotate(RBNode *node) {//左旋
    RBNode *temp = node->rchild;
    node->rchild = temp->lchild;
    temp->lchild = node;
    return temp;
}

RBNode *right_rotate(RBNode *node) {//右旋
    RBNode *temp = node->lchild;
    node->lchild = temp->rchild;
    temp->rchild = node;
    return temp;
}

RBNode *insert_maintain(RBNode *root) {
    if (!hasRedChild(root)) return root;//如果没有红孩子　不调整
    if (root->lchild->color == 0 && root->rchild->color == 0) {
        if (hasRedChild(root->lchild) || hasRedChild(root->rchild)) {
            root->color = 0;
            root->rchild->color = root->lchild->color = 1;
        }
        return root;
    }
    if (root->lchild->color == 0) {//左孩子是红色
        if (!hasRedChild(root->lchild)) return root; //如果左孩子没有红孩子　不调整
        if (root->lchild->rchild->color == 0){ //如果有左孩子红孩子，且在右边
            root->lchild = left_rotate(root->lchild); //左旋左孩子
        }
        root = right_rotate(root);//右旋根节点
    } else {
        if (!hasRedChild(root->rchild)) return root;
        if (root->rchild->lchild->color == 0) {
            root->rchild = right_rotate(root->rchild);
        }
        root = left_rotate(root);
    }
    root->color = 0;
    root->lchild->color = root->rchild->color = 1;
    return root;
}

RBNode *__insert(RBNode *root, int key) {
    if (root == NIL || root == NULL) return getNewNode(key);
    if (root->key == key) return root;
    if (root->key < key) root->rchild = __insert(root->rchild, key);
    else root->lchild = __insert(root->lchild, key);
    return insert_maintain(root);
}

RBNode *insert(RBNode *root, int key) {
    root = __insert(root, key);
    root->color = 1;//根结点置黑
    return root;
}

RBNode *predecessor(RBNode *node) {//找前驱
    RBNode *temp = node->lchild;
    while (temp->rchild != NIL) temp = temp->rchild;
    return temp;
}

RBNode *erase_maintain(RBNode *root) {
    if (root->lchild->color != 2 && root->rchild->color != 2) return root;
    if (root->lchild->color == 0 || root->rchild->color == 0) {//父亲有一个红孩子
        root->color = 0;//父节点设为红色
        if (root->lchild->color == 0) {//case 1, x是双重黑，x的兄弟结点是红色 且在左
            root->lchild->color = 1;//先把x的兄弟结点设为黑色
            root = right_rotate(root);//右旋转化为case2,3,4
            root->rchild = erase_maintain(root->rchild);//转化为case2,3,4后再去掉x多余的黑色
        } else {
            root->rchild->color = 1;
            root = left_rotate(root);
            root->lchild = erase_maintain(root->lchild);
        }
        return root;
    }
    if (root->lchild->color == 2) {//已经调整到2，3，4，如果左孩子为x
        if (!hasRedChild(root->rchild)) {//case2,x是双重黑,x兄弟和x兄弟的孩子们都为黑色
            root->color += 1;//x的一重黑色上移给父节点
            root->lchild->color = 1;//x变为一重黑
            root->rchild->color = 0;//x的兄弟结点变为红色
            return root;
        } else if (root->rchild->rchild->color != 0) {//case3,x是双重黑,x的兄弟结点是黑色，x兄弟结点的左孩子是红色,右孩子是黑色
            root->rchild = right_rotate(root->rchild);//x兄弟结点右旋
            root->rchild->color = 1;//旋转后父节点的右结点变为黑色
            root->rchild->rchild->color = 0;//旋转后父节点的右孙子变为红色
        }
        root->lchild->color = 1;//case4,x兄弟结点为黑色,x兄弟结点的左孩子为任意颜色,x兄弟结点的右孩子是红色，将x去掉一重黑色
        root = left_rotate(root);//左旋父节点
        root->color = root->lchild->color;//将旋转前x父节点的颜色给x的兄弟结点,旋转后x的父节点变为父节点的左孩子,x的兄弟变为父节点
        root->lchild->color = root->rchild->color = 1;//旋转前x父节点和x兄弟结点的右孩子设为黑色，旋转后就是x的左右孩子
    } else {//case2,3,4右孩子是x
        if (!hasRedChild(root->lchild)) {
            root->color += 1;
            root->rchild->color = 1;
            root->lchild->color = 0;
            return root;
        } else if (root->lchild->lchild->color != 0) {
            root->lchild = left_rotate(root->lchild);
            root->lchild->color = 1;
            root->lchild->lchild->color = 0;
        }
        root->rchild->color = 1;
        root = right_rotate(root);
        root->color = root->rchild->color;
        root->lchild->color = root->rchild->color = 1;
    }
    return root;
}

RBNode *__erase(RBNode *root, int key) {
    if (root == NULL || root == NIL) return NIL;
    if (root->key < key) root->rchild = __erase(root->rchild, key);//递归右子树查找待删除结点
    else if (root->key > key) root->lchild = __erase(root->lchild, key);//递归左子树查找待删除结点
    else {
        if (root->lchild == NIL && root->rchild == NIL) {//待删除结点为叶子结点，叶子结点下存在两个NIL
            NIL->color += root->color;//将待删结点颜色加给NIL结点
            free(root);//将结点删除
            return NIL;
        } else if (root->lchild == NIL || root->rchild == NIL) {
            RBNode *temp = root->lchild == NIL ? root->rchild : root->lchild;//待删除结点下存在一个NIL
            temp->color += root->color;//将待删除结点颜色加给NIL结点
            free(root);//将结点删除
            return temp;
        } else {
            RBNode *temp = predecessor(root);//待删除结点存在两个子结点，找到待删除结点的前驱
            root->key = temp->key;//前驱的值赋给待删除结点（相当于删除待删除结点）
            root->lchild = __erase(root->lchild, temp->key);//递归删除前驱结点，上面两个if条件删除
        }
    }
    return erase_maintain(root);//调整删除该结点之后的树
}

RBNode *erase(RBNode *root, int key) {
    root = __erase(root, key);
    root->color = 1;//跟结点置黑
    return root;
}

void clear(RBNode *root) {
    if (root == NIL || root == NULL) return ;
    clear(root->lchild);
    clear(root->rchild);
    free(root);
    return ;
}

void output(RBNode *root) {
    if (root == NIL) return ;
    printf("(%d | %d, %d, %d)\n", root->color, root->key, root->lchild->key, root->rchild->key);
    output(root->lchild);
    output(root->rchild);
    return ;
}

int main() {
    int op, value;
    RBNode *root = NIL;
    while (scanf("%d%d", &op, &value) != EOF) {
        switch (op) {
            case 0: 
                printf("\ninsert %d\n", value);
                root = insert(root, value); break;
            case 1: 
                printf("\ndelete %d\n", value);
                root = erase(root, value); break;
            default: printf("error\n");
        }
        printf("----------\n");
        output(root);
    }
    return 0;
}
