/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nattapol <nattapol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 20:35:55 by nkamolba          #+#    #+#             */
/*   Updated: 2018/10/24 22:56:23 by nattapol         ###   ########.fr       */
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
# include <pwd.h>
# include <grp.h>

/*
** Binary Tree
*/

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
** Parse
*/

typedef struct			s_options
{
	char	R;
	char	a;
	char	A;
	char	l;
	char	t;
	char	S;
	char	r;
	char	one;
	char	Q;
	char	p;
	char	g;
	char	G;
}						t_options;

typedef	struct			s_ls_data
{
	t_options			*options;
	t_queue				*dir_queue;
	t_btree				*dir_tree;
}						t_ls_data;

void        parse_args(t_ls_data *ls_data, int argc, char **argv);

/*
** Compare
*/

int     btree_file_strcmp(void * a, void *b);
int     btree_dir_strcmp(void * a, void *b);

/*
** Process
*/

typedef struct			s_dir_data
{
	char				*dir_name;
	t_btree				*file_tree;
	t_options			*options;
}						t_dir_data;

typedef struct	 		s_file_data
{
	char				*file_name;
	struct stat			*stat;
	t_options			*options;
}						t_file_data;

void	process_queue(t_ls_data *ls_data);
void	process_path(t_btree **dir_tree, t_options *options, const char *path);

/*
** Print
*/

void print_file_tree(void *file_data);
void print_dir_tree(void *dir_data);


#endif
