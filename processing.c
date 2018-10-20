/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nattapol <nattapol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 19:47:59 by nkamolba          #+#    #+#             */
/*   Updated: 2018/10/21 01:09:32 by nattapol         ###   ########.fr       */
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

void    process_path(t_btree **dir_tree, const char *path)
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
        file_data = (t_file_data *)malloc(sizeof(t_file_data));
        file_data->file_name = ft_strdup(dirent->d_name);
        file_data->stat = (struct stat *)malloc(sizeof(struct stat));
        file_path = ft_strjoin(path, ft_strjoin("/", file_data->file_name));
        stat(file_path, file_data->stat);
        btree_insert(&(dir_data->file_tree), file_data, btree_file_strcmp);

        if (ft_strcmp(file_data->file_name, ".") != 0
                && ft_strcmp(file_data->file_name, "..") != 0
                && S_ISDIR(file_data->stat->st_mode))
            process_path(dir_tree, file_path);
    }
    closedir(dir);
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