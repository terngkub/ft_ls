/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <nkamolba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 23:48:49 by nkamolba          #+#    #+#             */
/*   Updated: 2018/12/20 16:59:38 by nkamolba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	btree_delete(t_btree *root)
{
	if (root)
	{
		btree_delete(root->left);
		btree_delete(root->right);
		free_file(root->item);
		free(root);
	}
}

void	free_file(void *file_var)
{
	t_ls_file	*file;

	file = (t_ls_file *)file_var;
	if (!file)
		return ;
	free(file->name);
	free(file->path);
	free(file->stat);
	if (file->data)
		free(file->data);
	if (file->tree)
		btree_delete(file->tree);
	free(file);
}
