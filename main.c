/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nattapol <nattapol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 19:33:02 by nkamolba          #+#    #+#             */
/*   Updated: 2018/10/21 22:47:48 by nattapol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void    init_ls_data(t_ls_data *ls_data)
{
    if (!(ls_data->options = (t_options *)malloc(sizeof(t_options))))
        exit(1);
    if (!(ls_data->dir_queue = ft_queue_create(sizeof(char *))))
        exit(1);
    ls_data->dir_tree = NULL;
}

int main(int argc, char **argv)
{
    t_ls_data   ls_data;

    init_ls_data(&ls_data);
    parse_args(&ls_data, argc, argv);
    //ft_printf("%s\n", (char *)ls_data.dir_queue->head->content);
    process_queue(&ls_data);
    btree_apply_infix(ls_data.dir_tree, print_dir_tree);
    return (0);
}
