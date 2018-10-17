/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <nkamolba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 19:47:59 by nkamolba          #+#    #+#             */
/*   Updated: 2018/10/17 20:52:54 by nkamolba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int     btree_strcmp(void * a, void *b)
{
    return ft_strcmp(((t_ls_data *)a)->name, ((t_ls_data *)b)->name);
}

void     btree_print(void *data)
{
    ft_printf("%s\n", ((t_ls_data *)data)->name);
}

void    process_path(const char *path)
{
    DIR             *dir;
    struct dirent   *dirent;
    t_ls_data       *data;
    t_btree         *tree;

    dir = opendir(path);
    tree = NULL;
    while ((dirent = readdir(dir)))
    {
        data = (t_ls_data *)malloc(sizeof(t_ls_data));
        data->name = ft_strdup(dirent->d_name);
        if (!tree)
            tree = btree_create_node(data);
        else
            btree_insert(&tree, data, btree_strcmp);
    }
    btree_apply_infix(tree, btree_print);
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