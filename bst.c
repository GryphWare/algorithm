#include <stdio.h>
#include <stdlib.h>

//tao node
typedef struct Node{
    int data;
    struct Node *left, *right;
}Node;

//tao node
Node *create(int data){
    Node *newNode = (Node*) malloc (sizeof(Node));
    if(newNode == NULL){
        perror("Loi tao node");
        exit(1);
    }
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

//insert node
Node *insert(Node *root, int data){
    if(root == NULL){
        return create(data);
    }
    if(data < root->data){
        root->left = insert(root->left, data);
    } else {
        root->right = insert(root->right, data);
    }
    return root;
}

//in theo tu trai->root->phai
void inorder(Node *root){
    if(root == NULL){
        return;
    }
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}

int main(){

    Node *root = NULL;

    root = insert(root, 6);
    insert(root, 9);
    insert(root, 4);
    insert(root, 2);
    insert(root, 0);

    inorder(root);

    puts("\n");
    
    return 0;
}
