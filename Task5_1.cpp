#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <Windows.h>
#include <iomanip> 

using namespace std;

int nRet = 0;

struct tree
{
    int data;
    tree* left;
    tree* right;
};

struct Node
{
    int x;
    int lvl;
};

Node tree_out[15];

void create(int a, tree** node)
{
    if (((*node)) == NULL)
    {
        ((*node)) = (tree*)calloc(1, sizeof(tree));
        ((*node))->data = a;
        ((*node))->left = NULL;
        ((*node))->right = NULL;
    }
    else
    {
        if (a < ((*node))->data)
        {
            if (((*node))->left != NULL)
                create(a, &((*node))->left);
            else
            {
                ((*node))->left = (tree*)calloc(1, sizeof(tree));
                ((*node))->left->left = ((*node))->left->right = NULL;
                ((*node))->left->data = a;
            }
        }
    }
    if (a > ((*node))->data)
    {
        if (((*node))->right != NULL)
            create(a, &(*node)->right);
        else
        {
            ((*node))->right = (tree*)calloc(1, sizeof(tree));
            ((*node))->right->left = ((*node))->right->right = NULL;
            ((*node))->right->data = a;
        }
    }
}

int i = 0;

int _print_t(tree* root, int is_left, int offset, int depth, char s[20][255]) {
    char b[20];
    int width = 5;

    if (!root) return 0;

    sprintf_s(b, "(%03d)", root->data);

    int left = _print_t(root->left, 1, offset, depth + 1, s);
    int right = _print_t(root->right, 0, offset + left + width, depth + 1, s);

    for (int i = 0; i < width; i++)
        s[2 * depth][offset + left + i] = b[i];

    if (depth && is_left) {

        for (int i = 0; i < width + right; i++)
            s[2 * depth - 1][offset + left + width / 2 + i] = '-';

        s[2 * depth - 1][offset + left + width / 2] = '+';
        s[2 * depth - 1][offset + left + width + right + width / 2] = '+';

    }
    else if (depth && !is_left) {

        for (int i = 0; i < left + width; i++)
            s[2 * depth - 1][offset - width / 2 + i] = '-';

        s[2 * depth - 1][offset + left + width / 2] = '+';
        s[2 * depth - 1][offset - width / 2 - 1] = '+';
    }
    return left + width + right;
}

void print_t(tree* root) {
    if (root == NULL)
    {
        printf("Tree is empty. Nothing to display\n");
        return;
    }

    char s[20][255];
    for (int i = 0; i < 20; i++)
    {
        sprintf_s(s[i], "%80s", " ");
    }
    _print_t(root, 0, 0, 0, s);
    for (int i = 0; i < 20; i++)
    {
        printf("%s\n", s[i]);
    }
}

bool find_a(tree* p, int key)
{
    tree* curr = p;
    while (curr && curr->data != key)
    {
        if (curr->data > key)
        {
            if (curr->left != NULL)
                curr = curr->left;

        }
        else {
            if (curr->right != NULL)
                curr = curr->right;
        }
        if (curr->data == key)
            return 1;
    }
    return 0;
}

bool find_b(tree* p,int a, int b)
{
    tree* curr = p;
    while (curr && curr->data != b)
    {
        if (curr->data > b)
        {
            if(curr ->left!= NULL)
                curr = curr->left;
            
        }
        else {
            if(curr->right!=NULL)
            curr = curr->right;
        }
        if (curr->data == b)
            return find_a(curr, a);
    }
    return 0;
}

int main()
{
    tree* node = NULL;
    int x;
    int number;
    cin >> number;
    if (number == 0)
    {
        cout << "ERROR" << endl;
        return 0;
    }
    for (int i = 0; i < number; i++)
    {
        cin >> x;
        create(x, &node);
    }
    print_t(node);
    cout << "INPUT A AND B" << endl;
    int A; cin >> A;
    int B; cin >> B;

    switch (find_b(node, A, B))
    {
    case(1):
        cout << "Contains";
        break;
    default:
        cout << "There isn't such number" << endl;
    }
    return 0;
}