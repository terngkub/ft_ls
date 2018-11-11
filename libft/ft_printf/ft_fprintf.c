/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <nkamolba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 19:43:32 by nkamolba          #+#    #+#             */
/*   Updated: 2018/11/11 19:54:08 by nkamolba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_fprintf(int fd, const char *format, ...)
{
	size_t		len;
	va_list		ap;
	char		*str;

	len = 0;
	va_start(ap, format);
	if (!(str = ft_readformat(format, ap, &len)))
		return (-1);
	va_end(ap);
	ft_putstr_fd_len(str, fd, len);
	free(str);
	return (len);
}
