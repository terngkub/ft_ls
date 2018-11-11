/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <nkamolba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 17:04:50 by nattapol          #+#    #+#             */
/*   Updated: 2018/11/11 16:52:35 by nkamolba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char get_entry_type(mode_t mode)
{
    if (S_ISREG(mode))
        return '-';
    else if (S_ISDIR(mode))
        return 'd';
    else if (S_ISLNK(mode))
        return 'l';
    else if (S_ISBLK(mode))
        return 'b';
    else if (S_ISCHR(mode))
        return 'c';
    else if (S_ISFIFO(mode))
        return 'p';
    else if (S_ISSOCK(mode))
        return 's';
    return '-';
}

void    print_ls_file_mode(mode_t mode)
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

void    print_acl_xattr(t_ls_file *file)
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

void print_name(t_ls_file *file)
{
    size_t size;
    char *buff;
    ft_putstr(file->name);
    
    if (S_ISLNK(file->lstat->st_mode))
    {
        size = file->lstat->st_size;
        buff = (char *)malloc(size + 1);
        buff[size] = '\0';
        readlink(file->path, buff, size);
        ft_printf(" -> %s", buff);
    }
}

void print_time(t_ls_file *file)
{
    char *mtime;
    char    *date_str;
    char    *time_str;
    char    *year_str;

    mtime = ctime(&file->lstat->st_mtime);
    date_str = ft_strsub(mtime, 4, 7);
    time_str = ft_strsub(mtime, 11, 5);
    year_str = ft_strsub(mtime, 19, 5);
    ft_putstr(date_str);
    if (time(NULL) - file->lstat->st_mtime < 15552000)
        ft_putstr(time_str);
    else
        ft_putstr(year_str);
}

void print_l(t_ls_file *file)
{
    struct passwd *pwd;
    struct group *gr;

    pwd = getpwuid(file->stat->st_uid);
    gr = getgrgid(file->stat->st_gid);

    print_ls_file_mode(file->lstat->st_mode);
    print_acl_xattr(file);
    print_space(file->parent_data->files - ft_numlen(file->lstat->st_nlink) + 1);
    ft_putnbr(file->lstat->st_nlink);
    print_space(file->parent_data->user - ft_strlen(pwd->pw_name) + 1);
    ft_putstr(pwd->pw_name);
    print_space(file->parent_data->group - ft_strlen(gr->gr_name) + 2);
    ft_putstr(gr->gr_name);
    print_space(file->parent_data->size - ft_numlen(file->lstat->st_size) + 2);
    ft_putnbr(file->lstat->st_size);
    ft_putchar(' ');
    print_time(file);
    ft_putchar(' ');
    print_name(file);
    ft_putchar('\n');
}

void handle_Qp(t_ls_file *file)
{
    if (file->options->p && S_ISDIR(file->stat->st_mode))
        ft_strfreecat_back(&(file->name), "/");
    if (file->options->Q)
    {
        ft_strfreecat_front(&(file->name), "\"");
        ft_strfreecat_back(&(file->name), "\"");
    }
}

void print_normal(t_ls_file *file)
{
    ft_printf("%s\n", file->name);
}

void print_item(void *file_data)
{
    t_ls_file   *file;

    file = (t_ls_file *)file_data;
    handle_Qp(file);
    if (file->options->l || file->options->g)
        print_l(file);
    else
        print_normal(file);
}

void print_tree(void *file_data)
{
    t_ls_file *file;

    file = (t_ls_file *)file_data;
    if (S_ISDIR(file->stat->st_mode)) {
        if (file->options->l)
            ft_printf("total %d\n", file->children_data->blocks);
        btree_apply_infix(file->tree, print_item);
    }
}