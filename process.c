/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <nkamolba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 19:47:59 by nkamolba          #+#    #+#             */
/*   Updated: 2018/12/20 18:40:21 by nkamolba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		process_first(void *file_void)
{
	t_ls_file	*file;

	file = (t_ls_file *)file_void;
	if (!file->error && S_ISDIR(file->stat->st_mode))
	{
		if (file->options->printed)
			ft_putchar('\n');
		if (!file->options->only_one)
			ft_printf("%s:\n", file->path);
		file->options->printed = 1;
		if (file->stat->st_mode & S_IXUSR)
		{
			process_dir(file);
			print_tree(file);
			btree_apply_infix(file->tree, process_recursive);
		}
	}
}

static void		process_not_dir(void *file_void)
{
	t_ls_file	*file;

	file = (t_ls_file *)file_void;
	if (!file->error && !S_ISDIR(file->stat->st_mode))
	{
		file->options->printed = 1;
		print_item(file);
	}
}

static void		process_error(void *file_void)
{
	t_ls_file	*file;
	DIR			*dir;
	char		*err;

	file = (t_ls_file *)file_void;
	if ((dir = opendir(file->path)) == NULL)
	{
		if (errno == 2)
		{
			file->error = 1;
			if (!(err = ft_strjoin("ft_ls: ", file->path)))
				ft_error("Error: ft_strjoin failed\n");
			perror(err);
			free(err);
		}
		return ;
	}
	closedir(dir);
}

void			process_data(t_ls_data *ls_data)
{
	t_ls_file	*file;

	if (ls_data->file->tree == NULL)
	{
		file = init_file(".", "", &ls_data->options, ls_data->file->data);
		btree_insert(&(ls_data->file->tree), file, compare_file);
	}
	btree_apply_infix(ls_data->file->tree, process_error);
	btree_apply_infix(ls_data->file->tree, process_not_dir);
	btree_apply_infix(ls_data->file->tree, process_first);
	free_file(ls_data->file);
}
