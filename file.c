/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <nkamolba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 16:55:51 by nkamolba          #+#    #+#             */
/*   Updated: 2018/12/18 16:25:59 by nkamolba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void				get_path(t_ls_file *file, char *path)
{
	size_t				path_len;
	size_t				name_len;
	char				*path_tmp;
	char				*name_tmp;

	if (!*path)
	{
		if (!(file->path = ft_strdup(file->name)))
			ft_error("Error: ft_strdup failed");
		return ;
	}
	path_len = ft_strlen(path);
	name_len = ft_strlen(file->name);
	if (!(path_tmp = (char *)malloc(path_len + name_len + 2)))
		ft_error("Error: malloc failed.");
	file->path = path_tmp;
	while (*path)
		*path_tmp++ = *path++;
	*path_tmp++ = '/';
	name_tmp = file->name;
	while (*name_tmp)
		*path_tmp++ = *name_tmp++;
	*path_tmp = '\0';
}

static void				get_lstat(t_ls_file *file)
{
	if (!(file->lstat = (struct stat *)malloc(sizeof(struct stat))))
		ft_error("Error: malloc failed");
	lstat(file->path, file->lstat);
}

t_ls_file				*init_file(char *name, char *path, t_options *options,
							t_ls_filedata *filedata)
{
	t_ls_file			*file;

	if (!(file = (t_ls_file *)malloc(sizeof(t_ls_file))))
		ft_error("Error: malloc failed");
	if (!(file->name = ft_strdup(name)))
		ft_error("Error: ft_strdup failed");
	get_path(file, path);
	get_lstat(file);
	file->tree = NULL;
	file->options = options;
	file->parent_data = filedata;
	if (file->parent_data != NULL)
		get_max(file);
	file->data = (S_ISDIR(file->lstat->st_mode)) ? init_filedata() : NULL;
	return (file);
}
