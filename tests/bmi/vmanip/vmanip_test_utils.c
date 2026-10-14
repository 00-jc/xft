/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vmanip_test_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:09 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:13 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "tests/bmi/vmanip_test.h"

t_u64	vmanip_full(t_size n)
{
	if (n >= 64)
		return (~0ULL);
	return ((1ULL << n) - 1);
}

t_u64	vmanip_odd(t_size n)
{
	return (0xAAAAAAAAAAAAAAAAULL & vmanip_full(n));
}

t_u64	vmanip_even(t_size n)
{
	return (0x5555555555555555ULL & vmanip_full(n));
}

t_u64	vmanip_range(t_size n)
{
	return (6ULL & vmanip_full(n));
}

t_u64	vmanip_bit(t_size i, t_size n)
{
	if (i >= n)
		return (0);
	return (1ULL << i);
}
