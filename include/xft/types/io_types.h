/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_types.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 18:01:29 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/17 16:36:24 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IO_TYPES_H
# define IO_TYPES_H

# include <xft/primitives.h>
# include <xft/files.h>
# include <xft/net.h>
# include <xft/alloc.h>
# include <xft/types/vec_types.h>

typedef struct s_iovec
{
	t_u8		*mem;
	t_size		size;
}	t_iovec;

typedef struct s_reader	t_reader;
typedef struct s_writer	t_writer;

typedef t_result		(*t_writer_drain_all)(t_writer *w, t_buffer data)\
						__attribute__((__nonnull__));

typedef t_result		(*t_writer_drain_fd)(t_writer *w, t_fd fd,\
						t_size limit, t_size *size)\
						__attribute__((__nonnull__));

typedef t_result		(*t_writer_flush)(t_writer *w)\
						__attribute__((__nonnull__));

typedef t_result		(*t_reader_stream)(t_reader *r, t_writer *w,\
						t_size limit, t_size *size)\
						__attribute__((__nonnull__));

typedef t_result		(*t_reader_discard)(t_reader *r, t_size limit,\
						t_size *size)\
						__attribute__((__nonnull__));

typedef t_result		(*t_reader_stream_all)(t_reader *r, t_writer *w,\
						t_size limit)\
						__attribute__((__nonnull__));

typedef t_result		(*t_reader_discard_all)(t_reader *r, t_size limit)\
						__attribute__((__nonnull__));

typedef t_result		(*t_reader_read)(t_reader *r, t_buffer dst, t_size *size)\
						__attribute__((__nonnull__));

typedef t_result		(*t_reader_read_all)(t_reader *r, t_buffer dst)\
						__attribute__((__nonnull__));

typedef struct s_writer_vtable
{
	t_writer_drain_all	drain_all;
	t_writer_drain_fd	drain_fd;
	t_writer_flush		flush;
}	t_writer_vtable;

typedef struct s_reader_vtable
{
	t_reader_stream			stream;
	t_reader_discard		discard;
	t_reader_stream_all		stream_all;
	t_reader_discard_all	discard_all;
	t_reader_read			read;
	t_reader_read_all		read_all;
}	t_reader_vtable;

typedef struct s_reader_ctx_fs
{
	t_buffer			buffer;
	t_fd				fd;
}	t_reader_fs;

typedef struct s_reader_ctx_memory
{
	t_buffer			buffer;
}	t_reader_ctx_memory;

typedef struct s_reader_ctx_growable
{
	t_vec				vec;
}	t_reader_ctx_growable;

typedef struct s_reader_ctx_tcp
{
	t_buffer			buf;
	t_fd				socket;
}	t_reader_ctx_tcp;

typedef struct s_reader_ctx_udp
{
	t_buffer			buf;
	t_fd				socket;
	t_ip_addr			ip;
}	t_reader_ctx_udp;

typedef struct s_reader
{
	t_any			reader_ctx;
	t_reader_vtable	vtable;
}	t_reader;

typedef struct s_writer_ctx_fs
{
	t_buffer_with_capacity	buffer;
	t_fd					fd;
}	t_writer_fs;

typedef struct s_writer_ctx_memory
{
	t_buffer			buffer;
}	t_writer_ctx_memory;

typedef struct s_writer_ctx_growable
{
	t_allocator				allocator;
	t_vec					vec;
}	t_writer_ctx_growable;

typedef struct s_writer_ctx_tcp
{
	t_buffer_with_capacity	buf;
	t_fd					socket;
}	t_writer_ctx_tcp;

typedef struct s_writer_ctx_udp
{
	t_buffer_with_capacity	buf;
	t_fd					socket;
	t_ip_addr				ip;
}	t_writer_ctx_udp;

typedef struct s_writer
{
	t_any					writer_ctx;
	t_writer_vtable			vtable;
}	t_writer;

#endif
