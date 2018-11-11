/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <nkamolba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 16:55:51 by nkamolba          #+#    #+#             */
/*   Updated: 2018/11/11 17:02:02 by nkamolba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static char    *create_path(char *old_path, char *name)
{
    size_t  path_len;
    size_t  name_len;
    char    *new_path;
    char    *ret;

    path_len = ft_strlen(old_path);
    name_len = ft_strlen(name);
    new_path = (char *)malloc(path_len + 1 + name_len + 1);
    ret = new_path;
    while (*old_path)
        *new_path++ = *old_path++;
    *new_path++ = '/';
    while (*name)
        *new_path++ = *name++;
    *new_path = '\0';
    return ret;
}

static void    get_max(t_ls_file *file)
{
    struct passwd *pwd;
    struct group *gr;
	size_t				files_len;
	size_t				user_len;
	size_t				group_len;
	size_t				size_len;
	size_t				name_len;

    files_len = ft_numlen(file->lstat->st_nlink);
    if (files_len > file->parent_data->files)
        file->parent_data->files = files_len;
    pwd = getpwuid(file->lstat->st_uid);
    user_len = ft_strlen(pwd->pw_name);
    if (user_len > file->parent_data->user)
        file->parent_data->user = user_len;
    gr = getgrgid(file->lstat->st_gid);
    group_len = ft_strlen(gr->gr_name);
    if (group_len > file->parent_data->group)
        file->parent_data->group = group_len;
    size_len = ft_numlen(file->lstat->st_size);
    if (size_len > file->parent_data->size)
        file->parent_data->size = size_len;
    name_len = ft_strlen(file->name);
    if (name_len > file->parent_data->name)
        file->parent_data->name = name_len;
    file->parent_data->blocks += file->lstat->st_blocks;
}

static t_ls_filedata	*init_filedata()
{
	t_ls_filedata *filedata;
	filedata = (t_ls_filedata *)malloc(sizeof(t_ls_filedata));
	filedata->files = 0;
	filedata->user = 0;
	filedata->group = 0;
	filedata->size = 0;
	filedata->name = 0;
	return filedata;
}

t_ls_file    *init_file(char *name, char *path, t_options *options, t_ls_filedata *max)
{
    t_ls_file *file;

    file = (t_ls_file *)malloc(sizeof(t_ls_file));
    file->name = ft_strdup(name);
    if (!*path)
        file->path = ft_strdup(name);
    else
        file->path = create_path(path, name);
    file->stat = (struct stat *)malloc(sizeof(struct stat));
    stat(file->path, file->stat);
    file->lstat = (struct stat *)malloc(sizeof(struct stat));
    lstat(file->path, file->lstat);
    file->tree = NULL;
    file->options = options;
    file->parent_data = max;
    if (max != NULL)
        get_max(file);
    if (S_ISDIR(file->stat->st_mode))
		file->children_data = init_filedata();
    else
        file->children_data = NULL;
    return (file);
}