/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nattapol <nattapol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 19:47:59 by nkamolba          #+#    #+#             */
/*   Updated: 2018/10/21 20:06:38 by nattapol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int     btree_file_strcmp(void * a, void *b)
{
    return ft_strcmp(((t_file_data *)a)->file_name, ((t_file_data *)b)->file_name);
}

int     btree_dir_strcmp(void * a, void *b)
{
    return ft_strcmp(((t_dir_data *)a)->dir_name, ((t_dir_data *)b)->dir_name);
}

t_dir_data *create_dir_data(const char *dir_name)
{
    t_dir_data      *dir_data;

    if (!(dir_data = (t_dir_data *)malloc(sizeof(t_dir_data))))
        return NULL;
    dir_data->dir_name = ft_strdup(dir_name);
    dir_data->file_tree = NULL;
    return dir_data;
}

t_file_data    *create_file_data(char *file_name, const char *file_path)
{
    t_file_data *file_data;

    file_data = (t_file_data *)malloc(sizeof(t_file_data));
    file_data->file_name = ft_strdup(file_name);
    file_data->stat = (struct stat *)malloc(sizeof(struct stat));
    stat(file_path, file_data->stat);
    return (file_data);
}

void    process_path(t_btree **dir_tree, t_options *options, const char *path)
{
    DIR             *dir;
    struct dirent   *dirent;
    t_dir_data      *dir_data;
    t_file_data     *file_data;
    const char      *file_path;

    dir = opendir(path);
    dir_data = create_dir_data(path);
    btree_insert(dir_tree, dir_data, btree_dir_strcmp);
    while ((dirent = readdir(dir)))
    {
        file_path = ft_strjoin(path, ft_strjoin("/", dirent->d_name));
        file_data = create_file_data(dirent->d_name, file_path);
        btree_insert(&(dir_data->file_tree), file_data, btree_file_strcmp);
        if (options->R == 1
                && ft_strcmp(file_data->file_name, ".") != 0
                && ft_strcmp(file_data->file_name, "..") != 0
                && S_ISDIR(file_data->stat->st_mode))
            process_path(dir_tree, options, file_path);
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


/*
trying stat
int main(int argc, char **argv)
{
    struct stat file_stat;

    if (argc != 2)
        return 1;
    if (stat(argv[1], &file_stat) < 0)
        return 1;
    printf("Size: %ld\n", file_stat.st_size);
    printf("Mode: %d\n", file_stat.st_mode);
    return (0);
}
*/

/*
trying time
int main(void)
{
    time_t seconds;
    const char *date;

    seconds = time(NULL);
    date = ctime(&seconds);
    printf("%ld\n", seconds);
    printf("%s", date);
    return (0);
}
*/