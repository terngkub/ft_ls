/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <nkamolba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 17:04:50 by nattapol          #+#    #+#             */
/*   Updated: 2018/11/12 15:25:52 by nkamolba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	handle_p(t_ls_file *file)
{
	if (file->options->p && S_ISDIR(file->stat->st_mode))
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
		ft_putendl(file->name);
}

void		print_tree(void *file_data)
{
	t_ls_file	*file;

	file = (t_ls_file *)file_data;
	if (S_ISDIR(file->stat->st_mode))
	{
		if (file->options->l)
			ft_printf("total %d\n", file->children_data->blocks);
		btree_apply_infix(file->tree, print_item);
	}
}
