/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nattapol <nattapol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 17:04:50 by nattapol          #+#    #+#             */
/*   Updated: 2018/10/26 00:01:36 by nattapol         ###   ########.fr       */
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

void print_l(t_file *file)
{
    struct passwd *pwd;
    struct group *gr;
    mode_t mode;
    char *mtime;
    char *mtime_cut;

    //make this another function
    mode = file->stat->st_mode;
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

    pwd = getpwuid(file->stat->st_uid);
    gr = getgrgid(file->stat->st_gid);
    mtime = ctime(&file->stat->st_mtime);
    mtime_cut = ft_strsub(mtime, 4, 15);
    ft_printf("% d ", file->stat->st_nlink);
    if (!file->options->g)
        ft_printf("%s ", pwd->pw_name);
    if (!file->options->G)
        ft_printf("%s ", gr->gr_name);
    ft_printf("%d %s %s\n", file->stat->st_size, mtime_cut, file->name);
}

void handle_Qp(t_file *file)
{
    if (file->options->p && S_ISDIR(file->stat->st_mode))
        ft_strfreecat_back(&(file->name), "/");
    if (file->options->Q)
    {
        ft_strfreecat_front(&(file->name), "\"");
        ft_strfreecat_back(&(file->name), "\"");
    }
}

void print_one(t_file *file)
{
    ft_printf("%s\n", file->name);
}

void print_normal(t_file *file)
{
    ft_printf("%s  ", file->name);
}

void print_item(void *file_data)
{
    t_file   *file;

    file = (t_file *)file_data;
    handle_Qp(file);
    if (file->options->l || file->options->g)
        print_l(file);
    else if (file->options->one)
        print_one(file);
    else
        print_normal(file);
}

void print_tree(void *file_data)
{
    t_file *file;

    file = (t_file *)file_data;
    if (S_ISDIR(file->stat->st_mode)) {
        ft_printf("%s:\n", file->path);
        btree_apply_infix(file->tree, print_item);
        if (file->tree)
            ft_printf("\n");
        ft_printf("\n");
        btree_apply_infix(file->tree, print_tree);
    }
}