/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <nkamolba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 14:04:47 by nattapol          #+#    #+#             */
/*   Updated: 2018/12/20 17:18:39 by nkamolba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void init_options(t_options *options)
{
	options->l = 0;
	options->ur = 0;
	options->a = 0;
	options->r = 0;
	options->t = 0;
	options->ua = 0;
	options->us = 0;
	options->g = 0;
	options->i = 0;
	options->p = 0;
}

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
	int	size;
	t_ls_file *file;

	init_options(&ls_data->options);
	i = 1;
	while (i < argc && argv[i][0] == '-')
		parse_flag(&(ls_data->options), argv[i++]);
	ls_data->file = init_file("", "", &ls_data->options, NULL);
	size = 0;
	while (i < argc)
	{
		file = init_file(argv[i++], "", &ls_data->options, ls_data->file->data);
		btree_insert(&(ls_data->file->tree), file, compare_file);
		size++;
	}
	ls_data->options.printed = 0;
	ls_data->options.only_one = (size > 1) ? 0 : 1;
}
