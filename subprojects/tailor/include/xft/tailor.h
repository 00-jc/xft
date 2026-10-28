/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tailor.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 18:01:30 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/03 18:01:32 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TAILOR_H
# define TAILOR_H

# ifdef __linux__

#  include <xft/types/tailor_types.h>

t_result	xft_new_tailor(t_tailor *t, t_f64 warmup_sec, t_u64a min_samples)\
					__attribute__((__nonnull__(1)));

t_result	xft_tailor_bench(t_tailor *t, t_tailor_bench benches[],\
				t_size size)\
				__attribute__((__nonnull__(1, 2)));

t_size		xft_tailor_getcount(t_cany ptr)\
				__attribute__((pure, __nonnull__(1)));

t_result	xft_tailor_buffers(t_tailor *t, t_size *sizes,\
				t_u8 *alignment, t_size n)\
				__attribute__((__nonnull__(1, 2, 3)));

t_buffer	xft_get_random_buffer(t_cany ptr)\
				__attribute__((__nonnull__(1)));

void		xft_tailor_destroy(t_tailor *t)\
				__attribute__((__nonnull__(1)));

t_buffer	*xft_get_all_buffers(t_cany ptr, t_size *n)\
				__attribute__((__nonnull__(1)));

void		xft_tailor_add_processed_bytes(t_any ptr, const t_size bytes)\
				__attribute__((__nonnull__(1)));

t_u64a		xft_tailor_get_random_num(t_any ptr)\
				__attribute__((__nonnull__(1)));

# else

#  error "tailor.h is linux only: it is built on perf_event_open"

# endif
#endif
