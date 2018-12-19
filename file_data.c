/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <nkamolba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 15:35:12 by nkamolba          #+#    #+#             */
/*   Updated: 2018/12/19 16:27:43 by nkamolba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_ls_filedata	*init_filedata(void)
{
	t_ls_filedata		*filedata;

	if (!(filedata = (t_ls_filedata *)malloc(sizeof(t_ls_filedata))))
		ft_error("Error: malloc failed");
	filedata->files_len = 0;
	filedata->user_len = 0;
	filedata->group_len = 0;
	filedata->size_len = 0;
	filedata->have_dev = 0;
	filedata->major_len = 0;
	filedata->minor_len = 0;
	filedata->name_len = 0;
	filedata->blocks = 0;
	return (filedata);
}