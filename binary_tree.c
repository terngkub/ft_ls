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

void    ft_bt_insert(t_ls_node *node, t_ls_data *data, int (*compare)(t_ls_data *, t_ls_data*))
{
    int compare_result;

    if (node->data == NULL)
    {
        node->data = data;
        return;
    }
    compare_result = (*compare)(data, node->data);
    if (compare_result < 0)
    {
        if (node->left == NULL)
            node->left = ft_bt_new(data);
        else
            ft_bt_insert(node->left, data, compare);
    }
    else if (compare_result > 0)
    {
        if (node->right == NULL)
            node->right = ft_bt_new(data);
        else
            ft_bt_insert(node->right, data, compare);
    }
}

void    ft_bt_delete(t_ls_node *node)
{
    if (node == NULL)
        return;
    ft_bt_delete(node->left);
    ft_bt_delete(node->right);
    free(node->data->name);
    free(node->data->stat);
    free(node->data);
    free(node);
}

void    ft_bt_print(t_ls_node *node)
{
    if (node == NULL)
        return;
    ft_bt_print(node->left);
    //ft_printf("name: %s mode: %d\n", node->data->dirent->d_name, node->data->stat->st_mode);
    ft_printf("%s\n", node->data->name);
    ft_bt_print(node->right);
}

int     compare_name(t_ls_data *a, t_ls_data *b)
{
    return ft_strcmp(a->name, b->name);
}