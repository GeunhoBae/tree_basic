#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

typedef struct {
    int data;
    struct tree* lchild;
    struct tree* rchild;
} tree;

//함수선언
tree* make_tree_by_code();
void inorder(tree*);
void preorder(tree*);
void postorder(tree*);
tree* copy(tree*);
int equal(tree*, tree*);
tree* swap(tree*);
tree* make_random_tree();
void print_traversal(tree*); //중위, 전위, 후위 순회출력의 모음
void free_tree(tree*); //트리의 삭제

//main함수
void main() {
    //8.1
    printf("트리 순회 A\n");
    tree* A = make_tree_by_code();
    print_traversal(A);
    printf("\n");

    //8.2
    printf("트리 복사 B\n");
    tree* B = copy(A);
    print_traversal(B);
    printf("\n");

    printf("트리 동질성검사\n");
    printf("equal(A,B): ");
    if (equal(A, B) == 1) printf("TRUE");
    else printf("FALSE");
    free_tree(B);
    printf("\n\n");

    printf("트리 swap A C\n");
    tree* C = swap(A);
    print_traversal(C);
    printf("\nequal(A,C): ");
    if (equal(A, C) == 1) printf("TRUE");
    else printf("FALSE");
    free_tree(A);
    free_tree(C);
    printf("\n\n");

    //8.3
    printf("랜덤 트리 자동 생성(D)\n");
    tree* D = make_random_tree();
    print_traversal(D);
    free_tree(D);
}

//함수구현
void free_tree(tree* A) {
    if (A == NULL)
        return;
    free_tree(A->lchild);
    free_tree(A->rchild);
    free(A);
}

void print_traversal(tree* A) {
    printf("inorder: ");
    inorder(A);
    printf("\n");

    printf("preorder: ");
    preorder(A);
    printf("\n");

    printf("postorder: ");
    postorder(A);
    printf("\n");
}

tree* make_random_tree() {
    tree* ptr, *root;
    int n;
    printf("Input n: ");
    scanf("%d", &n);

    root = (tree*)malloc(sizeof(tree));
    root->data = 1;
    root->lchild = NULL;
    root->rchild = NULL;
    
    for (int i = 2; i <= n; i++) {
        ptr = root;
        tree* temp = (tree*)malloc(sizeof(tree));
        temp->data = i;
        temp->lchild = NULL;
        temp->rchild = NULL;

        while (1) {
            if ((rand() % 2) == 0) { //좌로 이동
                if (ptr->lchild == NULL) {
                    ptr->lchild = temp;
                    break;
                }
                else ptr = ptr->lchild;
            }
            else { //우로 이동
                if (ptr->rchild == NULL) {
                    ptr->rchild = temp;
                    break;
                }
                else ptr = ptr->rchild;
            }
        }
    }   
    return root;
}

tree* swap(tree* original) {
    tree* temp;
    if (original) {
        temp = (tree*)malloc(sizeof(tree));
        temp->lchild = swap(original->rchild);
        temp->rchild = swap(original->lchild);
        temp->data = original->data;

        return temp;
    }
    return NULL;
}

int equal(tree* A, tree* B) {
    return ((!A && !B) || (A && B && (A->data == B->data) && equal(A->lchild, B->lchild) && equal(A->rchild, B->rchild)));
}

tree* copy(tree* original) {
    tree* temp;
    if (original) {
        temp = (tree*)malloc(sizeof(tree));
        temp->lchild = copy(original->lchild);
        temp->rchild = copy(original->rchild);
        temp->data = original->data;

        return temp;
    }
    return NULL;
}

void postorder(tree* A) {
    if (A) {
        postorder(A->lchild);
        postorder(A->rchild);
        printf("%d ", A->data);
    }
}

void preorder(tree* A) {
    if (A) {
        printf("%d ", A->data);
        preorder(A->lchild);
        preorder(A->rchild);
    }
}

void inorder(tree* A) {
    if (A) {
        inorder(A->lchild);
        printf("%d ", A->data);
        inorder(A->rchild);
    }
}

tree* make_tree_by_code() {
    tree* temp1 = (tree*)malloc(sizeof(tree));
    tree* temp2 = (tree*)malloc(sizeof(tree));
    tree* temp3 = (tree*)malloc(sizeof(tree));
    tree* temp4 = (tree*)malloc(sizeof(tree));
    tree* temp5 = (tree*)malloc(sizeof(tree));

    temp1->data = 5; temp1->lchild = temp2; temp1->rchild = temp3;
    temp2->data = 3; temp2->lchild = temp4; temp2->rchild = temp5;
    temp3->data = 8; temp3->lchild = NULL; temp3->rchild = NULL;
    temp4->data = 1; temp4->lchild = NULL; temp4->rchild = NULL;
    temp5->data = 4; temp5->lchild = NULL; temp5->rchild = NULL;
    return temp1;
}