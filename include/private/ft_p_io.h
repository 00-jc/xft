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

# include "io.h"

void			putu(int fd, t_size n);
void			putx(int fd, t_size n, char or);
void			putd(int fd, t_ssize n);
void			puti(int fd, int n);
void			pputs(int fd, const char *__restrict__ const str);
void			pflt(int fd, t_f64 d);
void			putc_(char c, int fd);

#endif
