/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libc_bench.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/08 01:34:28 by jaicastr          #+#    #+#             */
/*   Updated: 2026/09/08 01:34:28 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tailor.h"
#include "libc_bench.h"

__attribute__((__always_inline__))
inline void	xft_main(const t_any *__restrict__ const sp)
{
	t_tailor	t;

	((void)sp, xft_bind_process_to_cpu(0));
	if (!xft_new_tailor(&t, 2, 2000))
		xft_exit(1);
	xft_libc_bench_memcpy(&t);
	xft_libc_bench_strlen(&t);
	(xft_tailor_destroy(&t), xft_exit(0));
}
