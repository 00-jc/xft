/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlen_bench_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/08 01:33:46 by jaicastr          #+#    #+#             */
/*   Updated: 2026/09/08 01:33:46 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tailor.h"
#include "cstr_bench.h"

void	ft_fill_strings(t_buffer *buffers, t_size n)
{
	t_size	i;
	t_size	j;

	i = 0;
	while (i < n)
	{
		j = 0;
		while (j + 1 < buffers[i].size)
			buffers[i].mem[j++] = 'a';
		buffers[i].mem[buffers[i].size - 1] = 0;
		++i;
	}
}

t_result	ft_strlen_bench_buffers(t_tailor *t)
{
	static t_size	bufsizes[] = {
		1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2049, (1 << 18), (1 << 20),
		1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2049, (1 << 18), (1 << 20),
	};
	static t_u8		bufalign[] = {
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
	};

	if (!ft_tailor_buffers(t, bufsizes, bufalign, 28))
		return (KO);
	ft_fill_strings((t_buffer *)t->rand_buffers.mem, t->rand_buffers.size);
	return (OK);
}
