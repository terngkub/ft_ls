/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nattapol <nattapol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 23:01:13 by nattapol          #+#    #+#             */
/*   Updated: 2018/10/25 23:48:07 by nattapol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
sort by
name
r = reverse (mutual)
t = mod time (unique)
S = size (unique)
*/

int     compare_time(t_file *file_a, t_file *file_b)
{
    long int sec_a;
    long int sec_b;
    long int nsec_a;
    long int nsec_b;

    sec_a = file_a->stat->st_mtime;
    sec_b = file_b->stat->st_mtime;
    nsec_a = file_a->stat->st_mtime;
    nsec_b = file_b->stat->st_mtime;
    if (sec_a == sec_b)
    {
        if (nsec_a == nsec_b)
            return ft_strcmp(file_a->name, file_b->name);
        return ((nsec_a > nsec_b) ? 1 : -1);
    }
    return ((sec_a > sec_b) ? 1 : -1);
}

int compare_size(t_file *file_a, t_file *file_b)
{
    int size_a;
    int size_b;

    size_a = file_a->stat->st_size;
    size_b = file_b->stat->st_size;
    if (size_a == size_b)
        return ft_strcmp(file_a->name, file_b->name);
    return ((size_a > size_b) ? 1 : -1);
}

int     compare_file(void *a, void *b)
{
    t_file *file_a;
    t_file *file_b;
    int     compare_result;

    file_a = (t_file *)a;
    file_b = (t_file *)b;
    if (file_a->options->t)
        compare_result = compare_time(file_a, file_b);
    else if (file_a->options->S)
        compare_result = compare_size(file_a, file_b);
    else
        compare_result = ft_strcmp(file_a->name, file_b->name);
    if (file_a->options->r)
        compare_result *= -1;
    return (compare_result);
}
