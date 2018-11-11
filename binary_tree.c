/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <nkamolba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 19:55:19 by nkamolba          #+#    #+#             */
/*   Updated: 2018/11/11 22:19:13 by nkamolba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_btree	*btree_create_node(void *item)
{
	t_btree *node;

	if ((node = (void *)malloc(sizeof(t_btree))))
	{
		node->item = item;
		node->left = NULL;
		node->right = NULL;
	}
	return (node);
}

void	btree_insert(t_btree **root, void *item, int (*compare)(void *, void *))
{
	if (*root)
	{
		if ((*compare)(item, (*root)->item) < 0)
			btree_insert(&((*root)->left), item, compare);
		else
			btree_insert(&((*root)->right), item, compare);
	}
	else
		*root = btree_create_node(item);
}

void	btree_apply_prefix(t_btree *root, void (*applyf)(void *))
{
	if (root)
	{
		(*applyf)(root->item);
		btree_apply_prefix(root->left, applyf);
		btree_apply_prefix(root->right, applyf);
	}
}

void	btree_apply_infix(t_btree *root, void (*applyf)(void *))
{
	if (root)
	{
		btree_apply_infix(root->left, applyf);
		(*applyf)(root->item);
		btree_apply_infix(root->right, applyf);
	}
}

void	btree_apply_suffix(t_btree *root, void (*applyf)(void *))
{
	if (root)
	{
		btree_apply_suffix(root->left, applyf);
		btree_apply_suffix(root->right, applyf);
		(*applyf)(root->item);
	}
}
