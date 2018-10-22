/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <nkamolba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 23:01:13 by nattapol          #+#    #+#             */
/*   Updated: 2018/10/22 19:51:34 by nkamolba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
- sort by
    name
    r = reverse (mutual)
    t = mod time (unique)
    S = size (unique)

there is a weird behavior
ls -tS
ls -St
what I think is which ever come later count
for time and size if the value is the same, sort by name?
I'm quite sure it work like this for size
*/

/*
int     compare_time()
{

}
*/

int     btree_file_strcmp(void * a, void *b)
{
    t_file_data *data_a;
    t_file_data *data_b;

    data_a = (t_file_data *)a;
    data_b = (t_file_data *)b;
    return ft_strcmp(data_a->file_name, data_b->file_name);
}

int     btree_dir_strcmp(void * a, void *b)
{
    t_dir_data  *dir_a;
    t_dir_data  *dir_b;

    dir_a = (t_dir_data *)a;
    dir_b = (t_dir_data *)b;
    return ft_strcmp(dir_a->dir_name, dir_b->dir_name);
}