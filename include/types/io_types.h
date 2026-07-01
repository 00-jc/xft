/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_types.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:12 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 13:41:44 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IO_TYPES_H
# define IO_TYPES_H

# include "primitives.h"
# include "types/allocators_types.h"

typedef struct s_file
{
	t_u8 *__restrict__		content;
	t_u32a					fd;
	t_size					size;
}	t_file;

typedef struct s_iovec
{
	t_u8		*mem;
	t_size		size;
}	t_iovec;

union	u_writer;

typedef struct s_writer_vtable
{
	t_result	(*flush)(void *__restrict__ const writer);
	t_result	(*drain)(void *__restrict__ const writer,\
					t_iovec * __restrict__ const bufs, t_size nbufs);
}	t_writer_vtable;

typedef struct s_fs_writer
{
	t_i32											fd;
}	t_fs_writer;

# ifdef __clang__

typedef struct s_mem_writer
{
	t_size													external_valid;
	t_size													external_size;
	t_u8 __attribute__	((counted_by(external_valid)))		*external;
}	t_mem_writer;

# else

typedef struct s_mem_writer
{
	t_size							external_valid;
	t_size							external_size;
	t_u8							*external;
}	t_mem_writer;

# endif

typedef union u_writer_union
{
	t_fs_writer		fs_writer;
	t_mem_writer	mem_writer;
}	t_writer_union;

typedef struct s_writer
{
	const t_writer_vtable *__restrict__				vtable;
	t_buffer										buffer;
	t_size											end;
	t_writer_union									as;
}	t_writer;

typedef struct s_reader_vtable
{
	t_result	(*unbufered_fill)(void *__restrict__ const reader,\
					t_u8 * __restrict__ const dst, const t_size len,\
					t_size * __restrict__ const total);
	t_result	(*fill)(void *__restrict__ const reader);
}	t_reader_vtable;

typedef struct s_fs_reader
{
	t_i32											fd;
}	t_fs_reader;

typedef struct s_mem_reader
{
	t_buffer				external;
	t_size					drained;
}	t_mem_reader;

typedef union u_reader_union
{
	t_fs_reader		fs_reader;
	t_mem_reader	mem_reader;
}	t_reader_union;

typedef struct s_reader
{
	const t_reader_vtable *__restrict__				vtable;
	t_buffer										buffer;
	t_size											end;
	t_size											valid;
	t_reader_union									as;
}	t_reader;

#endif
