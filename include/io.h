/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 17:14:01 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/28 15:46:24 by username         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef IO_H
# define IO_H

# include <stdarg.h>
# include <stdbool.h>
# include "syscalls.h"
# include "cstr.h"
# include "mem.h"
# include "alloc.h"

typedef struct s_file
{
	t_u8 *__restrict__		content;
	t_u32a					fd;
	t_size					size;
}	t_file;

# ifndef BUFSIZE
#  define BUFSIZE 4096
# endif

void			ft_printf(const char *__restrict__ const fmt, ...)\
					__attribute__((__nonnull__(1)));
void			ft_fprintf(int fd, const char *__restrict__ const fmt, ...)\
					__attribute__((__nonnull__(2)));
void			ft_vfprintf(int fd, const char *fmt, va_list args)\
					__attribute__((__nonnull__(2), used));
t_file			ft_read_file(t_allocator alloc,\
					const char *__restrict__ const fname)\
					__attribute__((__nonnull__(2)));
void			ft_close_file(t_allocator alloc,\
					t_file *__restrict__ const f)\
					__attribute__((__nonnull__(2)));

#endif
