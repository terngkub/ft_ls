/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_recursive.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <nkamolba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 22:46:11 by nkamolba          #+#    #+#             */
/*   Updated: 2018/11/12 22:50:32 by nkamolba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	process_recursive(void *file_data)
{
	t_ls_file		*file;

	file = (t_ls_file *)file_data;
	if (file->options->ur == 1
			&& ft_strcmp(file->name, ".") != 0
			&& ft_strcmp(file->name, "..") != 0
			&& S_ISDIR(file->stat->st_mode))
		process_path(file);
}
