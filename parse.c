/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <nkamolba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 14:04:47 by nattapol          #+#    #+#             */
/*   Updated: 2018/11/11 18:04:03 by nkamolba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void parse_flag(t_options *options, char *flag)
{
    ++flag;
    while (*flag)
    {
        if (ft_strchr("RaAdltSr1QpgG", *flag) == NULL)
        {
            ft_putstr_fd("ft_ls: illegal option -- ", 2);
            ft_putchar_fd(*flag, 2);
            ft_putstr_fd("\nusage: ft_ls [RaAdltSr1QpgG] [file ...]\n", 2);
            exit(EXIT_FAILURE);
        }
        (*flag == 'R') ? options->R = 1 : 0;
        (*flag == 'a') ? options->a = 1 : 0;
        (*flag == 'A') ? options->A = 1 : 0;
        (*flag == 'l') ? options->l = 1 : 0;
        (*flag == 't') ? options->t = 1 : 0;
        (*flag == 'S') ? options->S = 1 : 0;
        (*flag == 'r') ? options->r = 1 : 0;
        (*flag == '1') ? options->one = 1 : 0;
        (*flag == 'Q') ? options->Q = 1 : 0;
        (*flag == 'p') ? options->p = 1 : 0;
        (*flag == 'g') ? options->g = 1 : 0;
        (*flag == 'G') ? options->G = 1 : 0;
        ++flag;
    }
}

void        parse_args(t_ls_data *ls_data, int argc, char **argv)
{
    int i;

    i = 1;
    while (i < argc && argv[i][0] == '-')
    {
        parse_flag(ls_data->options, argv[i++]);
    }
    while (i < argc)
    {
        if (argv[i][0] == '-')
        {
            ft_printf("ft_ls: %s: No such file or directory\n", argv[i++]);
            ls_data->printed = 1;
        }
        else
            ft_queue_enqueue(ls_data->dir_queue, &argv[i++]);
            //need error handling
    }
}
