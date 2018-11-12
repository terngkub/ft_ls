/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_l.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <nkamolba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 21:28:09 by nkamolba          #+#    #+#             */
/*   Updated: 2018/11/12 15:25:21 by nkamolba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	print_space(int len)
{
	while (len--)
		ft_putchar(' ');
}

static void	print_name(t_ls_file *file)
{
	size_t			size;
	char			*buff;

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

static void	print_time(t_ls_file *file)
{
	char			*mtime;
	char			*month_str;
	char			*date_str;
	char			*time_str;
	char			*year_str;

	mtime = ctime(&file->lstat->st_mtime);
	if (!(month_str = ft_strsub(mtime, 4, 4)))
		ft_error("Error: ft_strsub failed");
	if (!(date_str = ft_strsub(mtime, 8, 3)))
		ft_error("Error: ft_strsub failed");
	if (!(time_str = ft_strsub(mtime, 11, 5)))
		ft_error("Error: ft_strsub failed");
	if (!(year_str = ft_strsub(mtime, 19, 5)))
		ft_error("Error: ft_strsub failed");
	ft_putstr(date_str);
	ft_putstr(month_str);
	if (time(NULL) - file->lstat->st_mtime < 15552000)
		ft_putstr(time_str);
	else
		ft_putstr(year_str);
	free(month_str);
	free(date_str);
	free(time_str);
	free(year_str);
}

void		print_l(t_ls_file *file)
{
	struct passwd	*pwd;
	struct group	*gr;

	pwd = getpwuid(file->lstat->st_uid);
	gr = getgrgid(file->lstat->st_gid);
	print_ls_file_mode(file->lstat->st_mode);
	print_acl_xattr(file);
	print_space(file->parent_data->files_len
		- ft_numlen(file->lstat->st_nlink) + 1);
	ft_putnbr(file->lstat->st_nlink);
	ft_putchar(' ');
	if (!file->options->g)
	{
		ft_putstr(pwd->pw_name);
		print_space(file->parent_data->user_len - ft_strlen(pwd->pw_name) + 2);
	}
	ft_putstr(gr->gr_name);
	print_space(file->parent_data->group_len - ft_strlen(gr->gr_name) + 2);
	print_space(file->parent_data->size_len - ft_numlen(file->lstat->st_size));
	ft_putnbr(file->lstat->st_size);
	ft_putchar(' ');
	print_time(file);
	ft_putchar(' ');
	print_name(file);
	ft_putchar('\n');
}
