/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gpa_bulk_test_same_size_fill.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:09 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:13 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/alloc/gpa/gpa_bulk_test.h"

__attribute__((__nonnull__(1, 2)))
void	test_bulk_same_size_fill(t_gpa *gpa, t_buffer *bufs)
{
	int	i;

	i = -1;
	while (++i < BULK_N)
	{
		bufs[i] = ft_gpa_alloc(gpa, 64, 8);
		ft_pin_invariant_msg(bufs[i].mem != nullptr,
			ft_fatptr((t_u8 *)"bulk alloc", sizeof("bulk alloc") - 1));
		ft_pin_invariant_msg(bufs[i].size >= 64,
			ft_fatptr((t_u8 *)"bulk size", sizeof("bulk size") - 1));
		ft_pin_invariant_msg(((t_uptr)bufs[i].mem & 7) == 0,
			ft_fatptr((t_u8 *)"bulk align", sizeof("bulk align") - 1));
		*(t_u64 *)bufs[i].mem = (t_u64)i;
	}
}
