#include <stdlib.h>
#include <stdio.h>

typedef struct      s_node {
    int             data;
    struct s_node   *left;
    struct s_node   *right;
}                   t_node;

t_node *ft_bt_new(int data)
{
    t_node *root;

    root = (t_node *)malloc(sizeof(t_node));
    root->data = data;
    root->left = NULL;
    root->right = NULL;
    return root;
}

void ft_bt_insert(t_node *root, int data)
{
    if (data < root->data)
    {
        if (root->left == NULL)
            root->left = ft_bt_new(data);
        else
            ft_bt_insert(root->left, data);
    }
    else if (data > root->data)
    {
        if (root->right == NULL)
            root->right = ft_bt_new(data);
        else
            ft_bt_insert(root->right, data);
    }
}

void ft_bt_delete(t_node *root)
{
    if (root == NULL)
        return;
    ft_bt_delete(root->left);
    ft_bt_delete(root->right);
    free(root);
}

void ft_bt_print(t_node *root)
{
    if (root == NULL)
        return;
    ft_bt_print(root->left);
    printf("%d\n", root->data);
    ft_bt_print(root->right);
}

int main(void)
{
    t_node *bt;

    bt = ft_bt_new(5);
    ft_bt_insert(bt, 2);
    ft_bt_insert(bt, 7);
    ft_bt_insert(bt, 1);
    ft_bt_insert(bt, 4);
    ft_bt_insert(bt, 9);
    ft_bt_insert(bt, 8);
    ft_bt_insert(bt, 6);
    ft_bt_print(bt);
    ft_bt_delete(bt);
    return (0);
}