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
inline void	ft_main(const t_any *__restrict__ const sp)
{
	t_tailor	t;

	((void)sp, ft_bind_process_to_cpu(0));
	if (!ft_tailor_new(&t, 2, 2000))
		ft_exit(1);
	ft_libc_bench_memcpy(&t);
	ft_libc_bench_strlen(&t);
	(ft_tailor_destroy(&t), ft_exit(0));
}
