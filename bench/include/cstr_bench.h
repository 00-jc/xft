/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cstr_bench.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 16:00:44 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/03 16:00:47 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CSTR_BENCH_H
# define CSTR_BENCH_H

# include "cstr.h"
# include "primitives.h"
# include "rt.h"
# include "tailor.h"

void		xft_fill_strings(t_buffer *buffers, t_size n);
t_result	xft_strlen_bench_buffers(t_tailor *t);

void		xft_strlen_test_varied(t_any ptr);
void		xft_strlen_test_short_aligned(t_any ptr);
void		xft_strlen_test_short_unaligned(t_any ptr);
void		xft_strlen_test_medium_aligned(t_any ptr);
void		xft_strlen_test_medium_unaligned(t_any ptr);
void		xft_strlen_test_large_aligned(t_any ptr);
void		xft_strlen_test_large_unaligned(t_any ptr);

#endif
