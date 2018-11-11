/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <nkamolba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 17:04:50 by nattapol          #+#    #+#             */
/*   Updated: 2018/11/11 21:33:02 by nkamolba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void handle_Qp(t_ls_file *file)
{
    if (file->options->p && S_ISDIR(file->stat->st_mode))
        ft_strfreecat_back(&(file->name), "/");
    if (file->options->Q)
    {
        ft_strfreecat_front(&(file->name), "\"");
        ft_strfreecat_back(&(file->name), "\"");
    }
}

void print_item(void *file_data)
{
    t_ls_file   *file;

    file = (t_ls_file *)file_data;
    handle_Qp(file);
    if (file->options->l || file->options->g)
        print_l(file);
    else
        ft_putendl(file->name);
}

void print_tree(void *file_data)
{
    t_ls_file *file;

    file = (t_ls_file *)file_data;
    if (S_ISDIR(file->stat->st_mode)) {
        if (file->options->l)
            ft_printf("total %d\n", file->children_data->blocks);
        btree_apply_infix(file->tree, print_item);
    }
}