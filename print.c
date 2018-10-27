/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <nkamolba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 17:04:50 by nattapol          #+#    #+#             */
/*   Updated: 2018/10/27 23:08:24 by nkamolba         ###   ########.fr       */
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

void    print_acl_xattr(t_file *file)
{
    acl_t   acl;
    ssize_t xattr;

    acl = acl_get_link_np(file->path, ACL_TYPE_EXTENDED);
    xattr = listxattr(file->path, NULL, 0, XATTR_NOFOLLOW);
    if (acl != NULL)
    {
        acl_free(acl);
        ft_putchar('+');
    }
    else if (xattr > 0)
        ft_putchar('@');
    else
        ft_putchar(' ');
}

void print_space(len)
{
    while (len--)
        ft_putchar(' ');
}

/*
void print_time(t_file *file)
{

}
*/

void print_name(t_file *file)
{
    size_t size;
    char *buff;
    ft_putstr(file->name);
    
    if (S_ISLNK(file->lstat->st_mode))
    {
        size = file->lstat->st_size;
        buff = (char *)malloc(size + 1);
        readlink(file->path, buff, size);
        ft_printf(" -> %s", buff);
    }
    
    // print name
    // if symbolic link print link
    // Qp
}

void print_time(t_file *file)
{
    char *mtime;
    char    *date_str;
    char    *time_str;
    char    *year_str;


    mtime = ctime(&file->lstat->st_mtime);
    date_str = ft_strsub(mtime, 4, 7);
    time_str = ft_strsub(mtime, 11, 5);
    year_str = ft_strsub(mtime, 20, 4);
    ft_putstr(date_str);
    if (time(NULL) - file->lstat->st_mtime < 15552000)
        ft_putstr(time_str);
    else
        ft_putstr(year_str);
}

void print_l(t_file *file)
{
    struct passwd *pwd;
    struct group *gr;

    pwd = getpwuid(file->stat->st_uid);
    gr = getgrgid(file->stat->st_gid);

    print_file_mode(file->lstat->st_mode);
    print_acl_xattr(file);
    print_space(file->parent_max->files - ft_numlen(file->lstat->st_nlink) + 1);
    ft_putnbr(file->lstat->st_nlink);
    print_space(file->parent_max->user - ft_strlen(pwd->pw_name) + 1);
    ft_putstr(pwd->pw_name);
    print_space(file->parent_max->group - ft_strlen(gr->gr_name) + 2);
    ft_putstr(gr->gr_name);
    print_space(file->parent_max->size - ft_numlen(file->lstat->st_size) + 2);
    ft_putnbr(file->lstat->st_size);
    ft_putchar(' ');
    print_time(file);
    ft_putchar(' ');
    print_name(file);
    ft_putchar('\n');

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

void print_normal(t_file *file)
{
    ft_printf("%s\n", file->name);
}

void print_item(void *file_data)
{
    t_file   *file;

    file = (t_file *)file_data;
    handle_Qp(file);
    if (file->options->l || file->options->g)
        print_l(file);
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
        if (file->options->R)
            btree_apply_infix(file->tree, print_tree);
    }
}