/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <nkamolba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 14:04:47 by nattapol          #+#    #+#             */
/*   Updated: 2018/12/19 20:00:58 by nkamolba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	parse_flag(t_options *options, char *flag)
{
	++flag;
	while (*flag)
	{
		if (ft_strchr("lRartASgip", *flag) == NULL)
		{
			ft_fprintf(2, "ft_ls: illegal option -- %c\n", *flag);
			ft_fprintf(2, "usage: ft_ls [lRartASgip] [file ...]\n");
			exit(EXIT_FAILURE);
		}
		(*flag == 'l') ? options->l = 1 : 0;
		(*flag == 'R') ? options->ur = 1 : 0;
		(*flag == 'a') ? options->a = 1 : 0;
		(*flag == 'r') ? options->r = 1 : 0;
		(*flag == 't') ? options->t = 1 : 0;
		(*flag == 'A') ? options->ua = 1 : 0;
		(*flag == 'S') ? options->us = 1 : 0;
		(*flag == 'g') ? options->g = 1 : 0;
		(*flag == 'i') ? options->i = 1 : 0;
		(*flag == 'p') ? options->p = 1 : 0;
		++flag;
	}
}

void		parse_args(t_ls_data *ls_data, int argc, char **argv)
{
	int	i;
	t_ls_file *file;

	i = 1;
	while (i < argc && argv[i][0] == '-')
		parse_flag(&(ls_data->options), argv[i++]);
	ls_data->tree = NULL;
	while (i < argc)
	{
		file = init_file(argv[i++], "", &ls_data->options, NULL);
		btree_insert(&(ls_data->tree), file, compare_file);
	}
}
