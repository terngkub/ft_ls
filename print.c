/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <nkamolba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 17:04:50 by nattapol          #+#    #+#             */
/*   Updated: 2018/12/18 14:24:23 by nkamolba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		print_serial_number(t_ls_file *file)
{
	if (file->options->i)
	{
		ft_printf("%d ", file->lstat->st_ino);
	}
}

static void	handle_p(t_ls_file *file)
{
	if (file->options->p && S_ISDIR(file->lstat->st_mode))
		ft_strfreecat_back(&(file->name), "/");
}

static void	print_item(void *file_data)
{
	t_ls_file	*file;

	file = (t_ls_file *)file_data;
	handle_p(file);
	if (file->options->l || file->options->g)
		print_l(file);
	else
	{
		print_serial_number(file);
		ft_putendl(file->name);
	}
}

void		print_tree(void *file_data)
{
	t_ls_file	*file;

	file = (t_ls_file *)file_data;
	if (S_ISDIR(file->lstat->st_mode))
	{
		if (file->options->l)
			ft_printf("total %d\n", file->children_data->blocks);
		btree_apply_infix(file->tree, print_item);
	}
}
