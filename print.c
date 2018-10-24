/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nattapol <nattapol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 17:04:50 by nattapol          #+#    #+#             */
/*   Updated: 2018/10/24 23:09:28 by nattapol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
l = one file per line
1 = one file per line (addition)
Q = add double quote to filename (addition)
p = add / to directory (addition)
g = no owner (enforece l)
G = no group (only work with l or g)
*/

/*
use stuct
and print just once

type&permission
number of file inside
name
group
size
month
day
time
opened quote
name
slash
closed quote

init with empty string
if l assign to all
if g don't assign owner
if G don't assign group

*/

void print_l(t_file_data *data)
{
    struct passwd *pwd;
    struct group *gr;
    mode_t mode;
    char *mtime;
    char *mtime_cut;

    //make this another function
    mode = data->stat->st_mode;
    ft_printf( (S_ISDIR(mode)) ? "d" : "-");
    ft_printf( (mode & S_IRUSR) ? "r" : "-");
    ft_printf( (mode & S_IWUSR) ? "w" : "-");
    ft_printf( (mode & S_IXUSR) ? "x" : "-");
    ft_printf( (mode & S_IRGRP) ? "r" : "-");
    ft_printf( (mode & S_IWGRP) ? "w" : "-");
    ft_printf( (mode & S_IXGRP) ? "x" : "-");
    ft_printf( (mode & S_IROTH) ? "r" : "-");
    ft_printf( (mode & S_IWOTH) ? "w" : "-");
    ft_printf( (mode & S_IXOTH) ? "x" : "-");

    pwd = getpwuid(data->stat->st_uid);
    gr = getgrgid(data->stat->st_gid);
    mtime = ctime(&data->stat->st_mtime);
    mtime_cut = ft_strsub(mtime, 4, 15);
    ft_printf("% d ", data->stat->st_nlink);
    if (!data->options->g)
        ft_printf("%s ", pwd->pw_name);
    if (!data->options->G)
        ft_printf("%s ", gr->gr_name);
    ft_printf("%d %s %s\n", data->stat->st_size, mtime_cut, data->file_name);
}

void handle_Qp(t_file_data *data)
{
    if (data->options->p && S_ISDIR(data->stat->st_mode))
        ft_strfreecat_back(&(data->file_name), "/");
    if (data->options->Q)
    {
        ft_strfreecat_front(&(data->file_name), "\"");
        ft_strfreecat_back(&(data->file_name), "\"");
    }
}

void print_one(t_file_data *data)
{
    ft_printf("%s\n", data->file_name);
}

// still need to handle column
void print_normal(t_file_data *data)
{
    ft_printf("%s  ", data->file_name);
}

void print_file_tree(void *file_data)
{
    t_file_data   *data;

    data = (t_file_data *)file_data;
    handle_Qp(file_data);
    if (data->options->l || data->options->g)
        print_l(data);
    else if (data->options->one)
        print_one(data);
    else
        print_normal(data);
}

void print_dir_tree(void *dir_data)
{
    ft_printf("%s\n", ((t_dir_data *)dir_data)->dir_name);
    btree_apply_infix(((t_dir_data *)dir_data)->file_tree, print_file_tree);
    ft_putchar('\n');
    ft_putchar('\n');
}
