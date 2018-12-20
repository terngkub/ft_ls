/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_mode.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <nkamolba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 21:32:18 by nkamolba          #+#    #+#             */
/*   Updated: 2018/12/20 18:48:13 by nkamolba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static char	get_entry_type(mode_t mode)
{
	if (S_ISREG(mode))
		return ('-');
	else if (S_ISDIR(mode))
		return ('d');
	else if (S_ISLNK(mode))
		return ('l');
	else if (S_ISBLK(mode))
		return ('b');
	else if (S_ISCHR(mode))
		return ('c');
	else if (S_ISFIFO(mode))
		return ('p');
	else if (S_ISSOCK(mode))
		return ('s');
	return ('-');
}

void		print_ls_file_mode(mode_t mode)
{
	char	mode_str[11];

	mode_str[0] = get_entry_type(mode);
	mode_str[1] = (mode & S_IRUSR) ? 'r' : '-';
	mode_str[2] = (mode & S_IWUSR) ? 'w' : '-';
	mode_str[3] = (mode & S_IXUSR) ? 'x' : '-';
	mode_str[4] = (mode & S_IRGRP) ? 'r' : '-';
	mode_str[5] = (mode & S_IWGRP) ? 'w' : '-';
	mode_str[6] = (mode & S_IXGRP) ? 'x' : '-';
	mode_str[7] = (mode & S_IROTH) ? 'r' : '-';
	mode_str[8] = (mode & S_IWOTH) ? 'w' : '-';
	mode_str[9] = '-';
	if (mode & S_ISVTX)
		mode_str[9] = 't';
	else if (mode & S_IXOTH)
		mode_str[9] = 'x';
	mode_str[10] = '\0';
	ft_putstr(mode_str);
}

void		print_acl_xattr(t_ls_file *file)
{
	acl_t	acl;
	ssize_t	xattr;

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
