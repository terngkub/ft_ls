/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <nkamolba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 17:04:50 by nattapol          #+#    #+#             */
/*   Updated: 2018/10/22 20:58:36 by nkamolba         ###   ########.fr       */
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

void print_l(t_ls_data *ls_data)
{
    t_file_data *data;
    struct passwd *pwd;
    struct group *gr;
    mode_t mode;
    char *mtime;
    char *mtime_cut;

    data = (t_file_data *)file_data;
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
    ft_printf("%s %s ", pwd->pw_name, gr->gr_name);
    ft_printf("%d %s %s\n", data->stat->st_size, mtime_cut, data->file_name);
}

void print_file_tree(void *data)
{
    t_ls_data *ls_data;
    ls_data = (t_ls_data *)data;
    if (ls_data->options->l || ls_data->options->g)
        print_l(ls_data);
}

void print_dir_tree(void *dir_data)
{
    ft_printf("%s\n", ((t_dir_data *)dir_data)->dir_name);
    btree_apply_infix(((t_dir_data *)dir_data)->file_tree, print_file_tree);
    ft_putchar('\n');
    ft_putchar('\n');
}
