/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nattapol <nattapol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 23:01:13 by nattapol          #+#    #+#             */
/*   Updated: 2018/10/21 23:21:57 by nattapol         ###   ########.fr       */
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

static int compare_name(t_)
{
	while (*s1 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

static int compare_time()
{
}

static int compare_size()
{
}

int     btree_file_strcmp(void * a, void *b)
{
    t_file_data *data_a;
    t_file_data *data_b;

    data_a = (t_file_data *)a;
    data_b = (t_file_data *)b;
    if (option->t)
        return compare_time();
    else if (option->)

}

int     btree_dir_strcmp(void * a, void *b)
{
    return ft_strcmp(((t_dir_data *)a)->dir_name, ((t_dir_data *)b)->dir_name);
}