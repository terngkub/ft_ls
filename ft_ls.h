/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_ls.h											:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: nkamolba <nkamolba@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2018/10/15 19:33:38 by nkamolba		  #+#	#+#			 */
/*   Updated: 2018/10/15 20:11:10 by nkamolba		 ###   ########.fr	   */
/*																			*/
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

typedef struct			s_ls_node
{
	t_ls_data			*data;
	struct s_ls_node	*left;
	struct s_ls_node	*right;
}						t_ls_node;

void process_path(const char *path);
t_ls_node  *ft_bt_new(t_ls_data *data);
void    ft_bt_insert(t_ls_node *node, t_ls_data *data, int (*compare)(t_ls_data *, t_ls_data*));
void    ft_bt_delete(t_ls_node *node);
void    ft_bt_print(t_ls_node *node);
int     compare_name(t_ls_data *a, t_ls_data *b);

#endif
