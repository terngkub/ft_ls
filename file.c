/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <nkamolba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 16:55:51 by nkamolba          #+#    #+#             */
/*   Updated: 2018/11/12 19:41:25 by nkamolba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static char				*create_path(char *old_path, char *name)
{
	size_t				path_len;
	size_t				name_len;
	char				*new_path;
	char				*ret;

	path_len = ft_strlen(old_path);
	name_len = ft_strlen(name);
	if (!(new_path = (char *)malloc(path_len + 1 + name_len + 1)))
		ft_error("Error: malloc failed.");
	ret = new_path;
	while (*old_path)
		*new_path++ = *old_path++;
	*new_path++ = '/';
	while (*name)
		*new_path++ = *name++;
	*new_path = '\0';
	return (ret);
}

static void				get_size_max(t_ls_file *file)
{
	size_t				size_len;
	size_t				major_len;
	size_t				minor_len;
	size_t				dev_len;

	if (S_ISBLK(file->lstat->st_mode) || S_ISCHR(file->lstat->st_mode))
	{
		major_len = ft_numlen(major(file->lstat->st_rdev));
		if (major_len > file->parent_data->major_len)
			file->parent_data->major_len = major_len;
		minor_len = ft_numlen(minor(file->lstat->st_rdev));
		if (minor_len > file->parent_data->minor_len)
			file->parent_data->minor_len = minor_len;
		dev_len = major_len + minor_len + 2;
		if (dev_len > file->parent_data->size_len)
			file->parent_data->size_len = dev_len;
	}
	else
	{
		size_len = ft_numlen(file->lstat->st_size);
		if (size_len > file->parent_data->size_len)
			file->parent_data->size_len = size_len;
	}
}

static void				get_max(t_ls_file *file)
{
	struct passwd		*pwd;
	struct group		*gr;
	size_t				len;

	len = ft_numlen(file->lstat->st_nlink);
	if (len > file->parent_data->files_len)
		file->parent_data->files_len = len;
	pwd = getpwuid(file->lstat->st_uid);
	len = ft_strlen(pwd->pw_name);
	if (len > file->parent_data->user_len)
		file->parent_data->user_len = len;
	gr = getgrgid(file->lstat->st_gid);
	len = ft_strlen(gr->gr_name);
	if (len > file->parent_data->group_len)
		file->parent_data->group_len = len;
	get_size_max(file);
	len = ft_strlen(file->name);
	if (len > file->parent_data->name_len)
		file->parent_data->name_len = len;
	file->parent_data->blocks += file->lstat->st_blocks;
}

static t_ls_filedata	*init_filedata(void)
{
	t_ls_filedata		*filedata;

	if (!(filedata = (t_ls_filedata *)malloc(sizeof(t_ls_filedata))))
		ft_error("Error: malloc failed");
	filedata->files_len = 0;
	filedata->user_len = 0;
	filedata->group_len = 0;
	filedata->size_len = 0;
	filedata->have_dev = 0;
	filedata->major_len = 0;
	filedata->minor_len = 0;
	filedata->name_len = 0;
	return (filedata);
}

t_ls_file				*init_file(char *name, char *path, t_options *options,
							t_ls_filedata *filedata)
{
	t_ls_file			*file;

	if (!(file = (t_ls_file *)malloc(sizeof(t_ls_file))))
		ft_error("Error: malloc failed");
	if (!(file->name = ft_strdup(name)))
		ft_error("Error: ft_strdup failed");
	if (!*path)
		file->path = ft_strdup(name);
	else
		file->path = create_path(path, name);
	if (!(file->stat = (struct stat *)malloc(sizeof(struct stat))))
		ft_error("Error: malloc failed");
	stat(file->path, file->stat);
	if (!(file->lstat = (struct stat *)malloc(sizeof(struct stat))))
		ft_error("Error: malloc failed");
	lstat(file->path, file->lstat);
	file->tree = NULL;
	file->options = options;
	file->parent_data = filedata;
	if (filedata != NULL)
		get_max(file);
	file->children_data = (S_ISDIR(file->stat->st_mode))
		? init_filedata() : NULL;
	return (file);
}
