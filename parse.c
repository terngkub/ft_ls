/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nattapol <nattapol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 14:04:47 by nattapol          #+#    #+#             */
/*   Updated: 2018/10/21 21:31:59 by nattapol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void parse_flag(t_options *options, char *flag)
{
    ++flag;
    while (*flag)
    {
        if (ft_strchr("RaAdltSr1QpgG", *flag) == NULL)
            exit(1);
        (*flag == 'R') ? options->R = 1 : 0;
        (*flag == 'a') ? options->a = 1 : 0;
        (*flag == 'A') ? options->A = 1 : 0;
        (*flag == 'l') ? options->l = 1 : 0;
        (*flag == 't') ? options->t = 1 : 0;
        (*flag == 's') ? options->S = 1 : 0;
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
    while (i < argc)
    {
        if (argv[i][0] == '-')
            parse_flag(ls_data->options, argv[i]);
        else
            ft_queue_enqueue(ls_data->dir_queue, (void const *)argv[i]);
        ++i;
    }
}
