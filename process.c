/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <nkamolba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 19:47:59 by nkamolba          #+#    #+#             */
/*   Updated: 2018/12/18 15:38:51 by nkamolba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		check_options(char *name, t_options *options)
{
	if (((ft_strcmp(name, ".") == 0
			|| ft_strcmp(name, "..") == 0) && !options->a)
			|| (name[0] == '.' && !(options->a || options->ua)))
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
		free(err);
		return ;
	}
	while ((dirent = readdir(dir)))
	{
		if (check_options(dirent->d_name, file->options))
		{
			new_file = init_file(dirent->d_name, file->path,
					file->options, file->data);
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
	btree_apply_infix(file->tree, process_recursive);
}

void	process_queue(t_ls_data *ls_data)
{
	t_ls_file		*file;
	char			**name;
	size_t			queue_size;

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
		file = init_file(*name, "", &ls_data->options, NULL);
		process_path(file);
		free_file(file);
		free(name);
	}
}

void	process_data(t_ls_data *ls_data)
{
	t_ls_file		*file;

	if (ls_data->dir_queue->size == 0)
	{
		file = init_file(".", "", &ls_data->options, NULL);
		process_path(file);
		free_file(file);
	}
	else
		process_queue(ls_data);
}
