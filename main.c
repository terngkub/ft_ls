/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <nkamolba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 19:33:02 by nkamolba          #+#    #+#             */
/*   Updated: 2018/11/11 23:50:20 by nkamolba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	init_ls_data(t_ls_data *ls_data)
{
	if (!(ls_data->dir_queue = ft_queue_create(sizeof(t_ls_file *))))
		exit(EXIT_FAILURE);
	ls_data->flag_error = 0;
}

int		main(int argc, char **argv)
{
	t_ls_data	ls_data;

	init_ls_data(&ls_data);
	parse_args(&ls_data, argc, argv);
	process_queue(&ls_data);
	free(ls_data.dir_queue);
	return (0);
}
