/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_p_io.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 12:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/17 12:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef XFT_P_IO_H
# define XFT_P_IO_H

# include <xft/io.h>

t_result		xft__fs_reader_stream(t_reader *r, t_writer *w, t_size limit,\
				t_size *size)\
				__attribute__((__nonnull__(1, 2, 4)));

t_result		xft__fs_reader_discard(t_reader *r, t_size limit,\
				t_size *size)\
				__attribute__((__nonnull__(1, 3)));

t_result		xft__fs_reader_read(t_reader *r, t_buffer dst, t_size *size)\
				__attribute__((__nonnull__(1, 3)));

t_result		xft__fs_reader_read_all(t_reader *r, t_buffer dst)\
				__attribute__((__nonnull__(1)));

t_result		xft__tcp_reader_discard(t_reader *r, t_size limit,\
				t_size *size)\
				__attribute__((__nonnull__(1, 3)));

t_result		xft__tcp_reader_read(t_reader *r, t_buffer dst, t_size *size)\
				__attribute__((__nonnull__(1, 3)));

t_result		xft__tcp_reader_read_all(t_reader *r, t_buffer dst)\
				__attribute__((__nonnull__(1)));

t_result		xft__udp_reader_discard(t_reader *r, t_size limit,\
				t_size *size)\
				__attribute__((__nonnull__(1, 3)));

t_result		xft__udp_reader_read(t_reader *r, t_buffer dst, t_size *size)\
				__attribute__((__nonnull__(1, 3)));

t_result		xft__reader_read_all(t_reader *r, t_buffer dst)\
				__attribute__((__nonnull__(1)));

t_result		xft__reader_stream_all(t_reader *r, t_writer *w,\
				t_size limit)\
				__attribute__((__nonnull__(1, 2)));

t_result		xft__reader_discard_all(t_reader *r, t_size limit)\
				__attribute__((__nonnull__(1)));

t_result		xft__fs_writer_flush(t_writer *w)\
				__attribute__((__nonnull__(1)));

t_result		xft__fs_writer_drain_fd(t_writer *w, t_fd fd, t_size limit,\
				t_size *size)\
				__attribute__((__nonnull__(1, 4)));

t_result		xft__fs_writer_writev(t_writer_fs *ctx, t_iovec *iov,\
				t_size count)\
				__attribute__((__nonnull__(1, 2)));

t_result		xft__tcp_writer_flush(t_writer *w)\
				__attribute__((__nonnull__(1)));

t_result		xft__tcp_writer_drain_fd(t_writer *w, t_fd fd, t_size limit,\
				t_size *size)\
				__attribute__((__nonnull__(1, 4)));

t_result		xft__tcp_writer_writev(t_writer_ctx_tcp *ctx, t_iovec *iov,\
				t_size count)\
				__attribute__((__nonnull__(1, 2)));

t_result		xft__udp_writer_send(t_writer_ctx_udp *ctx, t_buffer data)\
				__attribute__((__nonnull__(1)));

t_result		xft__udp_writer_flush(t_writer *w)\
				__attribute__((__nonnull__(1)));

t_result		xft__udp_writer_drain_fd(t_writer *w, t_fd fd, t_size limit,\
				t_size *size)\
				__attribute__((__nonnull__(1, 4)));

#endif
