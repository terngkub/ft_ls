/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nattapol <nattapol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 17:04:50 by nattapol          #+#    #+#             */
/*   Updated: 2018/10/21 23:00:56 by nattapol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
l = one file per line
1 = one file per line (addition)
Q = add double quote to filename (addition)
p = add / to directory (addition)
g = no owner (enforece l)
G = no group (only work with l or g)
*/

/*
use stuct
and print just once

type&permission
number of file inside
name
group
size
month
day
time
opened quote
name
slash
closed quote

init with empty string
if l assign to all
if g don't assign owner
if G don't assign group

*/


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
