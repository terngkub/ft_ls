/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <nkamolba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 23:01:13 by nattapol          #+#    #+#             */
/*   Updated: 2018/11/11 22:17:53 by nkamolba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	compare_time(t_ls_file *file_a, t_ls_file *file_b)
{
	if (file_a->stat->st_mtime == file_b->stat->st_mtime)
		return (ft_strcmp(file_a->name, file_b->name));
	return ((file_a->stat->st_mtime > file_b->stat->st_mtime) ? -1 : 1);
}

static int	compare_size(t_ls_file *file_a, t_ls_file *file_b)
{
	int			size_a;
	int			size_b;

	size_a = file_a->stat->st_size;
	size_b = file_b->stat->st_size;
	if (size_a == size_b)
		return (ft_strcmp(file_a->name, file_b->name));
	return ((size_a > size_b) ? 1 : -1);
}

int			compare_file(void *a, void *b)
{
	t_ls_file	*file_a;
	t_ls_file	*file_b;
	int			compare_result;

	file_a = (t_ls_file *)a;
	file_b = (t_ls_file *)b;
	if (file_a->options->t)
		compare_result = compare_time(file_a, file_b);
	else if (file_a->options->S)
		compare_result = compare_size(file_a, file_b);
	else
		compare_result = ft_strcmp(file_a->name, file_b->name);
	if (file_a->options->r)
		compare_result *= -1;
	return (compare_result);
}
