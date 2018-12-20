/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <nkamolba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 17:04:50 by nattapol          #+#    #+#             */
/*   Updated: 2018/12/20 18:46:33 by nkamolba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_serial_number(t_ls_file *file)
{
	if (file->options->i)
	{
		ft_printf("%d ", file->stat->st_ino);
	}
}

void	print_item(void *file_data)
{
	t_ls_file	*file;

	file = (t_ls_file *)file_data;
	if (file->options->l || file->options->g)
		print_l(file);
	else
	{
		print_serial_number(file);
		ft_putstr(file->name);
		if (file->options->p && S_ISDIR(file->stat->st_mode))
			ft_putchar('/');
		ft_putchar('\n');
	}
}

void	print_tree(void *file_data)
{
	t_ls_file	*file;

	file = (t_ls_file *)file_data;
	if (S_ISDIR(file->stat->st_mode) && getgrgid(file->stat->st_gid))
	{
		if (file->options->l)
			ft_printf("total %d\n", file->data->blocks);
		btree_apply_infix(file->tree, print_item);
	}
}
