/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_write_submission.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/19 18:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/19 18:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/linux/uring.h>

__attribute__((__nonnull__(1, 2)))
t_result	xft_write_submission(t_io_uring *ring, const t_io_uring_sqe *sqe)
{
	t_result	res;

	res = xft_queue_submission(ring, sqe);
	if (__builtin_expect(!res.ok, 0))
		return (res);
	return (xft_flush_submissions(ring));
}
