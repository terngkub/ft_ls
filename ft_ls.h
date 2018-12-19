/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <nkamolba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 20:35:55 by nkamolba          #+#    #+#             */
/*   Updated: 2018/12/19 20:00:24 by nkamolba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "libft/libft.h"
# include <errno.h>
# include <stdio.h>
# include <dirent.h>
# include <stdlib.h>
# include <sys/acl.h>
# include <sys/xattr.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <string.h>
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

t_btree					*btree_create_node(void *item);
void					btree_insert(t_btree **root, void *item,
							int (*compare)(void *, void *));
void					btree_apply_prefix(t_btree *root,
							void (*applyf)(void *));
void					btree_apply_infix(t_btree *root,
							void (*applyf)(void *));
void					btree_apply_suffix(t_btree *root,
							void (*applyf)(void *));

/*
** Parse
*/

typedef struct			s_options
{
	char				l;
	char				ur;
	char				a;
	char				r;
	char				t;
	char				ua;
	char				us;
	char				p;
	char				g;
	char				i;
}						t_options;

typedef struct			s_ls_filedata
{
	size_t				blocks;
	size_t				files_len;
	size_t				user_len;
	size_t				group_len;
	size_t				size_len;
	int					have_dev;
	size_t				major_len;
	size_t				minor_len;
	size_t				name_len;
}						t_ls_filedata;

typedef struct			s_ls_file
{
	char				*name;
	char				*path;
	struct stat			*stat;
	t_btree				*tree;
	t_options			*options;
	t_ls_filedata		*parent_data;
	t_ls_filedata		*data;
	int					error;
}						t_ls_file;

typedef	struct			s_ls_data
{
	t_options			options;
	t_btree				*tree;
	int					flag_error;
}						t_ls_data;

void					parse_args(t_ls_data *ls_data, int argc, char **argv);

/*
** Process
*/

t_ls_filedata			*init_filedata(void);
t_ls_file				*init_file(char *name, char *path,
							t_options *options,
							t_ls_filedata *max);
void					get_max(t_ls_file *file);
void					process_path(void *file);
void					process_queue(t_ls_data *ls_data);
void					process_data(t_ls_data *ls_data);
void					process_recursive(void *file_data);

/*
** Compare
*/

int						compare_file(void *a, void *b);

/*
** Print
*/

void					print_serial_number(t_ls_file *file);
char					get_entry_type(mode_t mode);
void					print_ls_file_mode(mode_t mode);
void					print_acl_xattr(t_ls_file *file);
void					print_l(t_ls_file *file);
void					print_tree(void *dir_data);

/*
** Free
*/

void					btree_delete(t_btree *root);
void					free_file(void *file_var);

/*
** Utils
*/

void					print_space(int len);
void					ft_error(char *str);

#endif
