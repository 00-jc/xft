/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tailor_top.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 00:29:02 by jaicastr          #+#    #+#             */
/*   Updated: 2026/04/20 00:32:58 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/ft_p_tailor.h"

__attribute__((__nonnull__(1, 2)))
t_result	ft_tailor_bench(t_tailor *t, t_tailor_bench benches[], t_size size)
{
	t_size	i;

	i = 0;
	while (i < size)
	{
		if (!ft_tailor_benchfn(t, benches[i].fn, benches[i].name))
			return (KO);
		++i;
	}
	return (OK);
}
