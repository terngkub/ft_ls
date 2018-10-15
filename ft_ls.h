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
	struct dirent		*dirent
	struct stat			*stat
}						t_ls_data;

typedef struct			s_ls_node
{
	t_ls_data			*data;
	struct s_ls_node	*left;
	struct s_ls_node	*right;
}						t_ls_node;

t_node					*ft_bt_new(int data);
void					ft_bt_insert(t_node *root, int data);
void					ft_bt_delete(t_node *root);
void					ft_bt_print(t_node *root);

#endif
