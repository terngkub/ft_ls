/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <nkamolba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 19:55:19 by nkamolba          #+#    #+#             */
/*   Updated: 2018/10/15 20:41:24 by nkamolba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_ls_node  *ft_bt_new(t_ls_data *data)
{
    t_ls_node *node;

    node = (t_ls_node *)malloc(sizeof(t_ls_node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void    ft_bt_insert(t_ls_node *node, t_ls_data *data)
{
    if (data < node->data)
    {
        if (node->left == NULL)
            node->left = ft_bt_new(data);
        else
            ft_bt_insert(node->left, data);
    }
    else if (data > node->data)
    {
        if (node->right == NULL)
            node->right = ft_bt_new(data);
        else
            ft_bt_insert(node->right, data);
    }
}

void    ft_bt_delete(t_ls_node *node)
{
    if (node == NULL)
        return;
    ft_bt_delete(node->left);
    ft_bt_delete(node->right);
    free(node);
}

void    ft_bt_print(t_ls_node *node)
{
    if (node == NULL)
        return;
    ft_bt_print(node->left);
    //ft_printf("%d\n", node->data);
    ft_bt_print(node->right);
}

/*
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
*/