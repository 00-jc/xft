/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 18:01:29 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/03 18:01:32 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IO_H
# define IO_H

# include <stdbool.h>
# include "syscalls.h"
# include "cstr.h"
# include "mem.h"
# include "alloc.h"
# include "types/io_types.h"

# ifndef BUFSIZE
#  define BUFSIZE 4096
# endif

t_result		xft_writer_write(t_writer *__restrict__ const writer,\
					t_buffer buf)\
					__attribute__((__nonnull__(1)));

t_writer		xft_get_fs_writer(t_buffer buffer, t_i32 fd)\
					__attribute__((const));

t_reader		xft_get_fs_reader(t_buffer buffer, t_i32 fd)\
					__attribute__((const, __always_inline__));

t_result		xft_read_from_reader(t_reader *reader,
					t_u8 *dst, const t_size len, t_size *total)\
					__attribute__((__nonnull__(1, 2, 4)));

t_result		xft_writer_flush(t_writer *__restrict__ const writer)\
					__attribute__((__nonnull__(1)));

t_writer		xft_get_raw_writer(t_buffer buffer,\
					t_u8 *__restrict__ const external, t_size external_valid)\
					__attribute__((const));

t_reader		xft_get_raw_reader(t_buffer buffer, t_buffer external)\
					__attribute__((const));

t_i32			xft_get_stderr(void)\
					__attribute__((const));
t_i32			xft_get_stdin(void)\
					__attribute__((const));
t_i32			xft_get_stdout(void)\
					__attribute__((const));

t_buffer		xft_map_file(const t_u8 *__restrict__ const name,\
					t_u32 flags)\
					__attribute__((__nonnull__(1)));

void			xft_unmap_file(t_buffer file);

#endif
