/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xxh3_mul128_fold64.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:20 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/ft_p_xxh3.h"

__attribute__((__always_inline__, const))
inline t_u64a	ft_xxh3_mul128_fold64(t_u64a a, t_u64a b)
{
	t_u128a	x;

	x = (t_u128a)a * (t_u128a)b;
	return ((t_u64a)(x) ^ (t_u64a)(x >> 64));
}
