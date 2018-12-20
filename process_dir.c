/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_dir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <nkamolba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/20 18:37:38 by nkamolba          #+#    #+#             */
/*   Updated: 2018/12/20 18:48:25 by nkamolba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	check_options(char *name, t_options *options)
{
	if (((ft_strcmp(name, ".") == 0
			|| ft_strcmp(name, "..") == 0) && !options->a)
			|| (name[0] == '.' && !(options->a || options->ua)))
		return (0);
	return (1);
}

void		process_dir(t_ls_file *file)
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
			if (getgrgid(new_file->stat->st_gid))
				btree_insert(&(file->tree), new_file, compare_file);
		}
	}
	closedir(dir);
}
