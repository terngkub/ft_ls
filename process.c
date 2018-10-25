/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nattapol <nattapol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 19:47:59 by nkamolba          #+#    #+#             */
/*   Updated: 2018/10/25 23:58:06 by nattapol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_file    *init_file(char *name, const char *path, t_options *options)
{
    t_file *file;

    file = (t_file *)malloc(sizeof(t_file));
    file->name = ft_strdup(name);
    file->path = ft_strdup(path);
    file->stat = (struct stat *)malloc(sizeof(struct stat));
    stat(path, file->stat);
    file->tree = NULL;
    file->options = options;
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
    char            *path;

    dir = opendir(file->path);
    while ((dirent = readdir(dir)))
    {
        if (check_options(dirent->d_name, file->options))
        {
            path = ft_strjoin(file->path, ft_strjoin("/", dirent->d_name));
            new_file = init_file(dirent->d_name, path, file->options);
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
        file = init_file(".", ".", ls_data->options);
        process_path(file);
        print_tree(file);
        return ;
    }
    while (ls_data->dir_queue->size)
    {
        name = ft_queue_dequeue(ls_data->dir_queue);
        file = init_file(name, name, ls_data->options);
        process_path(file);
        print_tree(file);
    }
}
