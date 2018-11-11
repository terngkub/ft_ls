/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <nkamolba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 19:47:59 by nkamolba          #+#    #+#             */
/*   Updated: 2018/11/11 22:40:08 by nkamolba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	handle_option_r(void *file_data)
{
	t_ls_file		*file;

	file = (t_ls_file *)file_data;
	if (file->options->R == 1
			&& ft_strcmp(file->name, ".") != 0
			&& ft_strcmp(file->name, "..") != 0
			&& S_ISDIR(file->stat->st_mode))
		process_path(file);
}

int		check_options(char *name, t_options *options)
{
	if (((ft_strcmp(name, ".") == 0
			|| ft_strcmp(name, "..") == 0) && !options->a)
			|| (name[0] == '.' && !(options->a || options->A)))
		return (0);
	return (1);
}

void	process_dir(t_ls_file *file)
{
	DIR				*dir;
	struct dirent	*dirent;
	t_ls_file		*new_file;
	char			*err;

	if ((dir = opendir(file->path)) == NULL)
	{
		if (!(err = ft_strjoin("ft_ls: ", file->path)))
			ft_error("Error: ft_strjoin failed\n");
		perror(err);
		return ;
	}
	while ((dirent = readdir(dir)))
	{
		if (check_options(dirent->d_name, file->options))
		{
			new_file = init_file(dirent->d_name, file->path,
					file->options, file->children_data);
			btree_insert(&(file->tree), new_file, compare_file);
		}
	}
	closedir(dir);
}

void	process_path(t_ls_file *file)
{
	if (file->parent_data)
		ft_printf("\n%s:\n", file->path);
	process_dir(file);
	print_tree(file);
	btree_apply_infix(file->tree, handle_option_r);
}

void	process_queue(t_ls_data *ls_data)
{
	t_ls_file		*file;
	char			**name;
	size_t			queue_size;

	if (ls_data->dir_queue->size == 0)
	{
		file = init_file(".", "", ls_data->options, NULL);
		process_path(file);
		return ;
	}
	queue_size = ls_data->dir_queue->size;
	while (ls_data->dir_queue->size)
	{
		name = (char **)ft_queue_dequeue(ls_data->dir_queue);
		if (queue_size > 1 || ls_data->flag_error)
		{
			if (queue_size - 1 != ls_data->dir_queue->size)
				ft_putchar('\n');
			ft_printf("%s:\n", *name);
		}
		file = init_file(*name, "", ls_data->options, NULL);
		process_path(file);
	}
}
