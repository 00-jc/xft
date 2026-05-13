/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fuzzer_get_rand.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 18:11:51 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/13 23:49:02 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fuzzer.h"
#include "math.h"

__attribute__((__nonnull__(1)))
t_buffer	*ft_fuzz_get_rand(t_fuzzer *fuzz)
{
	t_buffer	*b;

	b = fuzz->buffers + ((ft_xoshiro256ss(fuzz->xo) % fuzz->buf_n));
	fuzz->lastgen = (t_lastgen){.type = BUFFER, .as = (t_lastgenval){.b = b}};
	return (b);
}

__attribute__((__nonnull__(1)))
t_u64a	ft_fuzz_get_rand_u(t_fuzzer *fuzz)
{
	fuzz->lastgen = (t_lastgen){.type = UNSIGNED,
		.as = (t_lastgenval){.u = ft_xoshiro256ss(fuzz->xo)}};
	return (fuzz->lastgen.as.u);
}

__attribute__((__nonnull__(1)))
t_f64	ft_fuzz_get_rand_d(t_fuzzer *fuzz)
{
	fuzz->lastgen = (t_lastgen){.type = UNSIGNED,
		.as = (t_lastgenval){.d = (t_dp){.i = ft_xoshiro256ss(fuzz->xo)}.f}};
	return (fuzz->lastgen.as.d);
}
