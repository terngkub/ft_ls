/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nattapol <nattapol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 19:47:59 by nkamolba          #+#    #+#             */
/*   Updated: 2018/10/24 22:58:34 by nattapol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_dir_data *create_dir_data(const char *dir_name, t_options *options)
{
    t_dir_data      *dir_data;

    if (!(dir_data = (t_dir_data *)malloc(sizeof(t_dir_data))))
        return NULL;
    dir_data->dir_name = ft_strdup(dir_name);
    dir_data->file_tree = NULL;
    dir_data->options = options;
    return dir_data;
}

t_file_data    *create_file_data(char *file_name, const char *file_path, t_options *options)
{
    t_file_data *file_data;

    file_data = (t_file_data *)malloc(sizeof(t_file_data));
    file_data->file_name = ft_strdup(file_name);
    file_data->stat = (struct stat *)malloc(sizeof(struct stat));
    stat(file_path, file_data->stat);
    file_data->options = options;
    return (file_data);
}

void     handle_option_R(t_btree **dir_tree, t_options *options, const char *file_path, t_file_data *file_data)
{
    if (options->R == 1
            && ft_strcmp(file_data->file_name, ".") != 0
            && ft_strcmp(file_data->file_name, "..") != 0
            && S_ISDIR(file_data->stat->st_mode))
        process_path(dir_tree, options, file_path);
}

int    check_options(char *name, t_options *options)
{
    if (((ft_strcmp(name, ".") == 0 || ft_strcmp(name, "..") == 0) && !options->a)
            || (name[0] == '.' && !(options->a || options->A)))
        return 0;
    return 1;
}

void    process_path(t_btree **dir_tree, t_options *options, const char *path)
{
    DIR             *dir;
    struct dirent   *dirent;
    t_dir_data      *dir_data;
    t_file_data     *file_data;
    const char      *file_path;

    dir = opendir(path);
    dir_data = create_dir_data(path, options);
    btree_insert(dir_tree, dir_data, btree_dir_strcmp);
    while ((dirent = readdir(dir)))
    {
        if (check_options(dirent->d_name, options))
        {
            file_path = ft_strjoin(path, ft_strjoin("/", dirent->d_name));
            file_data = create_file_data(dirent->d_name, file_path, options);
            btree_insert(&(dir_data->file_tree), file_data, btree_file_strcmp);
            handle_option_R(dir_tree, options, file_path, file_data);
        }
    }
    closedir(dir);
}

void    process_queue(t_ls_data *ls_data)
{
    if (ls_data->dir_queue->size == 0)
    {
        process_path(&(ls_data->dir_tree), ls_data->options, ".");
        return ;
    }
    while (ls_data->dir_queue->size)
    {
        process_path(&(ls_data->dir_tree), ls_data->options, (const char *)ft_queue_dequeue(ls_data->dir_queue));
    }
}
