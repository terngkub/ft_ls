/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <nkamolba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 20:35:55 by nkamolba          #+#    #+#             */
/*   Updated: 2018/10/17 20:36:39 by nkamolba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <stdio.h>
# include "libft/libft.h"
# include <dirent.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <time.h>
# include <unistd.h>

/*
** Binary Tree
*/

typedef struct	 		s_ls_data
{
	char				*name;
	struct stat			*stat;
}						t_ls_data;

typedef struct			s_btree
{
	void				*item;
	struct s_btree		*left;
	struct s_btree		*right;
}						t_btree;

t_btree	*btree_create_node(void *item);
void    btree_insert(t_btree **root, void *item, int (*compare)(void *, void *));
void    btree_apply_prefix(t_btree *root, void (*applyf)(void *));
void    btree_apply_infix(t_btree *root, void (*applyf)(void *));
void    btree_apply_suffix(t_btree *root, void (*applyf)(void *));

/*
** Parsing
*/

void process_path(const char *path);

#endif
