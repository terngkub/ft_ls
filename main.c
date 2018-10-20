/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nattapol <nattapol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 19:33:02 by nkamolba          #+#    #+#             */
/*   Updated: 2018/10/21 01:09:11 by nattapol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void print_file_tree(void *file_data)
{
    ft_printf("%s   ", ((t_file_data *)file_data)->file_name);
}

void print_dir_tree(void *dir_data)
{
    ft_printf("%s\n", ((t_dir_data *)dir_data)->dir_name);
    btree_apply_infix(((t_dir_data *)dir_data)->file_tree, print_file_tree);
    ft_putchar('\n');
    ft_putchar('\n');
}

int main(int argc, char **argv)
{
    t_btree *dir_tree;

    dir_tree = NULL;
    if (argc == 1)
        process_path(&dir_tree, ".");
    else
        process_path(&dir_tree, argv[1]);
    btree_apply_infix(dir_tree, print_dir_tree);
    return (0);
}
