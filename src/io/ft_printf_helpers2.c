/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_helpers2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 02:52:15 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/19 20:55:28 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/ft_p_io.h"

__attribute__((__always_inline__))
inline void	pputs(int fd, const char *restrict const str)
{
	ssize_t		unused;

	if (!str)
		unused = ft_write(fd, (t_u8 *)"(nil)", 5);
	else
		unused = ft_write(fd, (t_u8 *)str, ft_strlen(str));
	(void)(unused == 0);
}

__attribute__((__always_inline__))
inline void	putc_(char c, int fd)
{
	ssize_t		unused;

	unused = ft_write(fd, (t_u8 *)&c, 1);
	(void)(unused == 0);
}
