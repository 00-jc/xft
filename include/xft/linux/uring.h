/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uring.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 14:09:55 by jaicastr          #+#    #+#             */
/*   Updated: 2021/01/01 01:02:10 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef URING_H
# define URING_H

# ifndef __linux__
#  error __FILE__ " is a linux only header, to use xft/linux/* headers __linux__"\
" must be defined"
# endif

# include <xft/primitives.h>
# include <xft/files.h>
# include <xft/types/atomic_types.h>

# include <linux/io_uring.h>

typedef struct io_sqring_offsets	t_io_sqring_offsets;
typedef struct io_cqring_offsets	t_io_cqring_offsets;
typedef struct io_uring_params		t_io_uring_params;
typedef struct io_uring_sqe			t_io_uring_sqe;
typedef struct io_uring_cqe			t_io_uring_cqe;

typedef struct s_io_uring_enter
{
	t_u32	to_submit;
	t_u32	min_complete;
	t_u32	flags;
	t_any	arg;
	t_size	argsz;
}	t_io_uring_enter;

typedef struct s_io_uring_register
{
	t_u32	opcode;
	t_u32	nr_args;
	t_any	arg;
}	t_io_uring_register;

typedef struct s_io_uring
{
	t_atomic32		*sq_head;
	t_atomic32		*sq_tail;
	t_atomic32		*sq_flags;
	t_u32			*sq_array;
	t_io_uring_sqe	*sqes;
	t_u32			sq_mask;
	t_u32			sq_entries;
	t_u32			sq_local_tail;
	t_u32			sq_local_head;

	t_atomic32		*cq_head;
	t_atomic32		*cq_tail;
	t_io_uring_cqe	*cqes;
	t_u32			cq_mask;
	t_u32			cq_entries;

	t_any			sq_ring;
	t_any			cq_ring;
	t_size			sq_ring_size;
	t_size			cq_ring_size;
	t_size			sqes_size;
	t_u32			features;
	t_fd			fd;
}	t_io_uring;

t_result	xft_io_uring_setup(t_u32 entries,\
				t_io_uring_params *restrict params, int *restrict const fd)\
				__attribute__((__nonnull__(2, 3)));

t_result	xft_io_uring_enter(int fd, t_io_uring_enter enter,\
				int *restrict const submitted)\
				__attribute__((__nonnull__(3)));

t_result	xft_io_uring_register(int fd, t_io_uring_register reg,\
				int *restrict const ret)\
				__attribute__((__nonnull__(3)));

t_result	xft_new_io_uring(t_io_uring *ring)\
				__attribute__((__nonnull__(1)));

void		xft_io_uring_destroy(t_io_uring *ring)\
				__attribute__((__nonnull__(1)));

t_result	xft_read_completion(t_io_uring *ring, t_io_uring_cqe *cqe)\
				__attribute__((__nonnull__(1, 2)));

t_result	xft_queue_submission(t_io_uring *ring, const t_io_uring_sqe *sqe)\
				__attribute__((__nonnull__(1, 2)));

t_result	xft_flush_submissions(t_io_uring *ring)\
				__attribute__((__nonnull__(1)));

t_result	xft_write_submission(t_io_uring *ring, const t_io_uring_sqe *sqe)\
				__attribute__((__nonnull__(1, 2)));

#endif
