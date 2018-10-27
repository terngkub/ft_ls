/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <nkamolba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 19:47:59 by nkamolba          #+#    #+#             */
/*   Updated: 2018/10/27 22:48:44 by nkamolba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char    *create_path(char *old_path, char *name)
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

void    get_max(t_file *file)
{
    struct passwd *pwd;
    struct group *gr;
	size_t				files_len;
	size_t				user_len;
	size_t				group_len;
	size_t				size_len;
	size_t				name_len;

    files_len = ft_numlen(file->lstat->st_nlink);
    if (files_len > file->parent_max->files)
        file->parent_max->files = files_len;
    pwd = getpwuid(file->lstat->st_uid);
    user_len = ft_strlen(pwd->pw_name);
    if (user_len > file->parent_max->user)
        file->parent_max->user = user_len;
    gr = getgrgid(file->lstat->st_gid);
    group_len = ft_strlen(gr->gr_name);
    if (group_len > file->parent_max->group)
        file->parent_max->group = group_len;
    size_len = ft_numlen(file->lstat->st_size);
    if (size_len > file->parent_max->size)
        file->parent_max->size = size_len;
    name_len = ft_strlen(file->name);
    if (name_len > file->parent_max->name)
        file->parent_max->name = name_len;
}

t_file    *init_file(char *name, char *path, t_options *options, t_ls_max *max)
{
    t_file *file;

    file = (t_file *)malloc(sizeof(t_file));
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
    file->parent_max = max;
    if (max != NULL)
        get_max(file);
    if (S_ISDIR(file->stat->st_mode))
    {
        file->children_max = (t_ls_max *)malloc(sizeof(t_ls_max));
        file->children_max->files = 0;
        file->children_max->user = 0;
        file->children_max->group = 0;
        file->children_max->size = 0;
        file->children_max->name = 0;
    }
    else
        file->children_max = NULL;
    return (file);
}

void     handle_option_R(t_file *file)
{
    if (file->options->R == 1
            && ft_strcmp(file->name, ".") != 0
            && ft_strcmp(file->name, "..") != 0
            && S_ISDIR(file->stat->st_mode))
        process_path(file);
}

int    check_options(char *name, t_options *options)
{
    if (((ft_strcmp(name, ".") == 0 || ft_strcmp(name, "..") == 0) && !options->a)
            || (name[0] == '.' && !(options->a || options->A)))
        return 0;
    return 1;
}


void    process_path(t_file *file)
{
    DIR             *dir;
    struct dirent   *dirent;
    t_file          *new_file;

    dir = opendir(file->path);
    while ((dirent = readdir(dir)))
    {
        if (check_options(dirent->d_name, file->options))
        {
            new_file = init_file(dirent->d_name, file->path, file->options, file->children_max);
            btree_insert(&(file->tree), new_file, compare_file);
            handle_option_R(new_file);
        }
    }
    closedir(dir);
}

void    process_queue(t_ls_data *ls_data)
{
    t_file  *file;
    char *name;

    if (ls_data->dir_queue->size == 0)
    {
        file = init_file(".", "", ls_data->options, NULL);
        process_path(file);
        print_tree(file);
        return ;
    }
    while (ls_data->dir_queue->size)
    {
        name = ft_queue_dequeue(ls_data->dir_queue);
        file = init_file(name, "", ls_data->options, NULL);
        process_path(file);
        print_tree(file);
    }
}
