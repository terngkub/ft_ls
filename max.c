/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   max.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <nkamolba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 15:47:29 by nkamolba          #+#    #+#             */
/*   Updated: 2018/12/18 15:47:48 by nkamolba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void				get_size_max(t_ls_file *file)
{
	size_t				size_len;
	size_t				major_len;
	size_t				minor_len;
	size_t				dev_len;

	if (S_ISBLK(file->lstat->st_mode) || S_ISCHR(file->lstat->st_mode))
	{
		major_len = ft_numlen(major(file->lstat->st_rdev));
		if (major_len > file->parent_data->major_len)
			file->parent_data->major_len = major_len;
		minor_len = ft_numlen(minor(file->lstat->st_rdev));
		if (minor_len > file->parent_data->minor_len)
			file->parent_data->minor_len = minor_len;
		dev_len = major_len + minor_len + 2;
		if (dev_len > file->parent_data->size_len)
			file->parent_data->size_len = dev_len;
	}
	else
	{
		size_len = ft_numlen(file->lstat->st_size);
		if (size_len > file->parent_data->size_len)
			file->parent_data->size_len = size_len;
	}
}

void				get_max(t_ls_file *file)
{
	struct passwd		*pwd;
	struct group		*gr;
	size_t				len;

	len = ft_numlen(file->lstat->st_nlink);
	if (len > file->parent_data->files_len)
		file->parent_data->files_len = len;
	if ((pwd = getpwuid(file->lstat->st_uid)))
		len = ft_strlen(pwd->pw_name);
	else
		len = ft_numlen(file->lstat->st_uid);
	if (len > file->parent_data->user_len)
		file->parent_data->user_len = len;
	gr = getgrgid(file->lstat->st_gid);
	len = ft_strlen(gr->gr_name);
	if (len > file->parent_data->group_len)
		file->parent_data->group_len = len;
	get_size_max(file);
	len = ft_strlen(file->name);
	if (len > file->parent_data->name_len)
		file->parent_data->name_len = len;
	file->parent_data->blocks += file->lstat->st_blocks;
}