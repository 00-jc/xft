/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p_io.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 17:58:03 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/13 23:49:02 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_P_IO_H
# define FT_P_IO_H

# ifdef __cplusplus

extern "C"
{

# endif

# include "io.h"

void			putu(int fd, size_t n);
void			putx(int fd, size_t n, char or);
void			putd(int fd, ssize_t n);
void			puti(int fd, int n);
void			pputs(int fd, const char *__restrict__ const str);
void			pflt(int fd, t_f64 d);
void			putc_(char c, int fd);

# ifdef __cplusplus
}
# endif

#endif
