/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gpa_bulk_test_mixed_sizes_fill.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:09 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:13 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/alloc/gpa/gpa_bulk_test.h"

__attribute__((__nonnull__(1, 2)))
void	test_bulk_mixed_sizes_fill(t_gpa *gpa, t_buffer *bufs)
{
	static const t_size	sizes[BULK_SIZES] = {16, 64, 256, 1024};
	int					i;

	i = -1;
	while (++i < BULK_N)
	{
		bufs[i] = ft_gpa_alloc(gpa, sizes[i % BULK_SIZES], 8);
		ft_pin_invariant_msg(bufs[i].mem != nullptr,
			ft_fatptr((t_u8 *)"mixed alloc", sizeof("mixed alloc") - 1));
		ft_pin_invariant_msg(bufs[i].size >= sizes[i % BULK_SIZES],
			ft_fatptr((t_u8 *)"mixed size", sizeof("mixed size") - 1));
		*(t_u8 *)bufs[i].mem = (t_u8)(i & 0xff);
	}
}
