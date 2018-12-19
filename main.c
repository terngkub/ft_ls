/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <nkamolba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 19:33:02 by nkamolba          #+#    #+#             */
/*   Updated: 2018/12/19 19:26:14 by nkamolba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	init_ls_data(t_ls_data *ls_data)
{
	ls_data->flag_error = 0;
}

int		main(int argc, char **argv)
{
	t_ls_data	ls_data;

	init_ls_data(&ls_data);
	parse_args(&ls_data, argc, argv);
	process_data(&ls_data);
	return (0);
}
