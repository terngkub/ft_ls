/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <nkamolba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 17:04:50 by nattapol          #+#    #+#             */
/*   Updated: 2018/10/26 21:01:11 by nkamolba         ###   ########.fr       */
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

char get_entry_type(mode_t mode)
{
    if (S_IFIFO & mode)
        return 'p';
    else if (S_IFCHR & mode)
        return 'c';
    else if (S_IFDIR & mode)
        return 'd';
    else if (S_IFBLK & mode)
        return 'b';
    else if (S_IFREG & mode)
        return '-';
    else if (S_IFLNK & mode)
        return 'l';
    else if (S_IFSOCK & mode)
        return 's';
    return '-';
}

void    print_file_mode(mode_t mode)
{
    char    mode_str[11];

    mode_str[0] = get_entry_type(mode);
    mode_str[1] = (mode & S_IRUSR) ? 'r' : '-';
    mode_str[2] = (mode & S_IWUSR) ? 'w' : '-';
    mode_str[3] = (mode & S_IXUSR) ? 'x' : '-';
    mode_str[4] = (mode & S_IRGRP) ? 'r' : '-';
    mode_str[5] = (mode & S_IWGRP) ? 'w' : '-';
    mode_str[6] = (mode & S_IXGRP) ? 'x' : '-';
    mode_str[7] = (mode & S_IROTH) ? 'r' : '-';
    mode_str[8] = (mode & S_IWOTH) ? 'w' : '-';
    mode_str[9] = (mode & S_IXOTH) ? 'x' : '-';
    mode_str[10] = '\0';
    ft_putstr(mode_str);
}

void    print_attr(t_file *file)
{
    ssize_t xattr;

    xattr = listxattr(file->name, NULL, 0, XATTR_NOFOLLOW);
    if (xattr < 0)
        xattr = 0;
    if (xattr > 0)
        ft_putchar('@');
    else
        ft_putchar(' ');
}

void print_l(t_file *file)
{
    struct passwd *pwd;
    struct group *gr;
    char *mtime;
    char *mtime_cut;

    print_file_mode(file->stat->st_mode);
    print_attr(file);
    pwd = getpwuid(file->stat->st_uid);
    gr = getgrgid(file->stat->st_gid);
    mtime = ctime(&file->stat->st_mtime);
    mtime_cut = ft_strsub(mtime, 4, 12);
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