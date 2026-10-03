/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_fuzzer_get_rand.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:20 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fuzzer.h"
#include "math.h"

__attribute__((__nonnull__(1)))
t_buffer	*xft_fuzz_get_rand(t_fuzzer *fuzz)
{
	t_buffer	*b;

	b = fuzz->buffers + ((xft_xoshiro256ss(fuzz->xo) % fuzz->buf_n));
	fuzz->lastgen = (t_lastgen){.type = BUFFER, .as = (t_lastgenval){.b = b}};
	return (b);
}

__attribute__((__nonnull__(1)))
t_u64a	xft_fuzz_get_rand_u(t_fuzzer *fuzz)
{
	fuzz->lastgen = (t_lastgen){.type = UNSIGNED,
		.as = (t_lastgenval){.u = xft_xoshiro256ss(fuzz->xo)}};
	return (fuzz->lastgen.as.u);
}

__attribute__((__nonnull__(1)))
t_f64	xft_fuzz_get_rand_d(t_fuzzer *fuzz)
{
	fuzz->lastgen = (t_lastgen){.type = UNSIGNED,
		.as = (t_lastgenval){.d = (t_dp){.i = xft_xoshiro256ss(fuzz->xo)}.f}};
	return (fuzz->lastgen.as.d);
}
