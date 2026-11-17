/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 00:03:54 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/17 00:58:18 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IO_H
# define IO_H

# include <xft/primitives.h>
# include <xft/files.h>
# include <xft/types/io_types.h>

t_result	xft_fileinfo_from_name(const char *name, t_file_info *fileinfo)\
			__attribute__((__nonnull__(1, 2)));

t_result	xft_fileinfo_from_fd(t_fd fd, t_file_info *fileinfo)\
			__attribute__((__nonnull__(2)));

t_fd		xft_get_stdin(void)\
			__attribute__((__const__));

t_fd		xft_get_stdout(void)\
			__attribute__((__const__));

t_fd		xft_get_stderr(void)\
			__attribute__((__const__));

t_buffer	xft_map_file_into_memory(const char *name)\
			__attribute__((__nonnull__(1)));

void		xft_unmap_file_from_memory(t_buffer buffer);

t_reader	xft_fs_reader(t_reader_fs *ctx, t_fd fd, t_buffer buffer)\
			__attribute__((__warn_unused_result__, __nonnull__(1)));

t_reader	xft_tcp_reader(t_reader_ctx_tcp *ctx, t_fd fd, t_buffer buffer)\
			__attribute__((__warn_unused_result__, __nonnull__(1)));

t_reader	xft_udp_reader(t_reader_ctx_udp *ctx, t_fd fd, t_buffer buffer)\
			__attribute__((__warn_unused_result__, __nonnull__(1)));

t_reader	xft_mem_reader(t_reader_ctx_memory *ctx, t_buffer src)\
			__attribute__((__warn_unused_result__, __nonnull__(1)));

t_reader	xft_growable_reader(t_reader_ctx_growable *ctx, t_vec vec)\
			__attribute__((__warn_unused_result__, __nonnull__(1)));

t_writer	xft_fs_writer(t_writer_fs *ctx, t_fd fd, t_buffer buffer)\
			__attribute__((__warn_unused_result__, __nonnull__(1)));

t_writer	xft_tcp_writer(t_writer_ctx_tcp *ctx, t_fd fd, t_buffer buffer)\
			__attribute__((__warn_unused_result__, __nonnull__(1)));

t_writer	xft_udp_writer(t_writer_ctx_udp *ctx, t_fd fd, t_buffer buffer,\
			const t_ip_addr *dest)\
			__attribute__((__warn_unused_result__, __nonnull__(1, 4)));

t_writer	xft_mem_writer(t_writer_ctx_memory *ctx, t_buffer dst)\
			__attribute__((__warn_unused_result__, __nonnull__(1)));

t_writer	xft_growable_writer(t_writer_ctx_growable *ctx,\
			t_allocator allocator, t_vec vec)\
			__attribute__((__warn_unused_result__, __nonnull__(1)));

t_result	xft_reader_stream(t_reader *r, t_writer *w, t_size limit,\
			t_size *size)\
			__attribute__((__nonnull__(1, 2, 4)));

t_result	xft_reader_stream_all(t_reader *r, t_writer *w, t_size limit)\
			__attribute__((__nonnull__(1, 2)));

t_result	xft_reader_discard(t_reader *r, t_size limit, t_size *size)\
			__attribute__((__nonnull__(1, 3)));

t_result	xft_reader_discard_all(t_reader *r, t_size limit)\
			__attribute__((__nonnull__(1)));

t_result	xft_reader_read(t_reader *r, t_buffer dst, t_size *size)\
			__attribute__((__nonnull__(1, 3)));

t_result	xft_reader_read_all(t_reader *r, t_buffer dst)\
			__attribute__((__nonnull__(1)));

t_result	xft_writer_drain_all(t_writer *w, t_buffer data)\
			__attribute__((__nonnull__(1)));

t_result	xft_writer_flush(t_writer *w)\
			__attribute__((__nonnull__(1)));

#endif
