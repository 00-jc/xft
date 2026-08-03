/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_types.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:12 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/04 23:14:21 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IO_TYPES_H
# define IO_TYPES_H

# include "primitives.h"
# include "types/allocators_types.h"
# include "atomics.h"

/// \brief A single scatter/gather span, mirroring `struct iovec`, used to
/// pass buffered + overflow data to a writer's `drain` in one call.
typedef struct s_iovec
{
	t_u8		*mem;
	t_size		size;
}	t_iovec;

union	u_writer;

/// \brief Backend hooks for a `t_writer`. One instance per backend (fs,
/// raw/in-memory), selected once at construction and shared as a `static
/// const` table.
typedef struct s_writer_vtable
{
	/// \brief Push out any bytes still sitting in the writer's staging
	/// buffer. \return `OK`/`KO`.
	t_result	(*flush)(t_any __restrict__ const writer);
	/// \brief Push out \p nbufs iovecs directly (bypassing the staging
	/// buffer), used when a write is larger than the buffer can hold.
	/// \return `OK`/`KO`.
	t_result	(*drain)(t_any __restrict__ const writer,\
					t_iovec * __restrict__ const bufs, t_size nbufs);
}	t_writer_vtable;

/// \brief Backend state for a file-descriptor-backed writer.
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
	t_result	(*unbufered_fill)(t_any __restrict__ const reader,\
					t_u8 * __restrict__ const dst, const t_size len,\
					t_size * __restrict__ const total);
	t_result	(*fill)(t_any __restrict__ const reader);
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
