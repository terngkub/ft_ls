/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_recursive.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <nkamolba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 22:46:11 by nkamolba          #+#    #+#             */
/*   Updated: 2018/12/20 18:49:34 by nkamolba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	process_path(void *file_void)
{
	t_ls_file	*file;

	file = (t_ls_file *)file_void;
	if (S_ISDIR(file->stat->st_mode))
	{
		ft_printf("\n%s:\n", file->path);
		if (file->stat->st_mode & S_IXUSR)
		{
			process_dir(file);
			print_tree(file);
			btree_apply_infix(file->tree, process_recursive);
		}
	}
}

void		process_recursive(void *file_data)
{
	t_ls_file	*file;

	file = (t_ls_file *)file_data;
	if (file->options->ur == 1
			&& ft_strcmp(file->name, ".") != 0
			&& ft_strcmp(file->name, "..") != 0
			&& S_ISDIR(file->stat->st_mode))
		process_path(file);
}
