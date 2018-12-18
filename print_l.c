/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_l.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <nkamolba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 21:28:09 by nkamolba          #+#    #+#             */
/*   Updated: 2018/12/17 21:05:22 by nkamolba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	print_name(t_ls_file *file)
{
	size_t			size;
	char			*buff;

	ft_putstr(file->name);
	if (S_ISLNK(file->lstat->st_mode))
	{
		size = file->lstat->st_size;
		if (!(buff = (char *)malloc(size + 1)))
			ft_error("Error: malloc failed");
		buff[size] = '\0';
		readlink(file->path, buff, size);
		ft_printf(" -> %s", buff);
		free(buff);
	}
}

static void	print_time(t_ls_file *file)
{
	char			*mtime;
	char			*date_str;
	char			*time_str;
	char			*year_str;

	mtime = ctime(&file->lstat->st_mtime);
	if (!(date_str = ft_strsub(mtime, 4, 7)))
		ft_error("Error: ft_strsub failed");
	if (!(time_str = ft_strsub(mtime, 11, 5)))
		ft_error("Error: ft_strsub failed");
	if (!(year_str = ft_strsub(mtime, 19, 5)))
		ft_error("Error: ft_strsub failed");
	ft_putstr(date_str);
	if (time(NULL) - file->lstat->st_mtime < 15552000)
		ft_putstr(time_str);
	else
		ft_putstr(year_str);
	ft_putchar(' ');
	free(date_str);
	free(time_str);
	free(year_str);
}

static void	print_user_group(t_ls_file *file)
{
	struct passwd	*pwd;
	struct group	*gr;

	gr = getgrgid(file->lstat->st_gid);
	if (!file->options->g)
	{
		if ((pwd = getpwuid(file->lstat->st_uid)))
		{
			ft_putstr(pwd->pw_name);
			print_space(file->parent_data->user_len - ft_strlen(pwd->pw_name) + 2);
		}
		else
		{
			perror("error:");
			ft_putnbr(file->lstat->st_uid);
			print_space(file->parent_data->user_len - ft_numlen(file->lstat->st_uid) + 2);
		}
	}
	ft_putstr(gr->gr_name);
	print_space(file->parent_data->group_len - ft_strlen(gr->gr_name) + 2);
}

static void	print_size(t_ls_file *file)
{
	if (S_ISBLK(file->lstat->st_mode) || S_ISCHR(file->lstat->st_mode))
	{
		print_space(file->parent_data->major_len
			- ft_numlen(major(file->lstat->st_rdev)) + 1);
		ft_printf("%d, ", major(file->lstat->st_rdev));
		print_space(file->parent_data->minor_len
			- ft_numlen(minor(file->lstat->st_rdev)));
		ft_putnbr(minor(file->lstat->st_rdev));
	}
	else
	{
		print_space(file->parent_data->size_len
			- ft_numlen(file->lstat->st_size));
		ft_putnbr(file->lstat->st_size);
	}
	ft_putchar(' ');
}

void		print_l(t_ls_file *file)
{
	print_serial_number(file);
	print_ls_file_mode(file->lstat->st_mode);
	print_acl_xattr(file);
	print_space(file->parent_data->files_len
		- ft_numlen(file->lstat->st_nlink) + 1);
	ft_putnbr(file->lstat->st_nlink);
	ft_putchar(' ');
	print_user_group(file);
	print_size(file);
	print_time(file);
	print_name(file);
	ft_putchar('\n');
}
