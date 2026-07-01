/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xxh3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:20 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/ft_p_xxh3.h"

t_u64a	ft_xxh3_64bits(t_buffer input, t_u64a seed)
{
	t_buffer	secret;

	secret = ft_xxh3_get_secret();
	if (secret.size < XXH3_SECRET_SIZE_MIN)
		__builtin_unreachable();
	if (input.size <= 16)
		return (ft_xxh3_len_0to16(input, secret, seed));
	else if (input.size <= 128)
		return (ft_xxh3_len_17to128(input, secret, seed));
	else if (input.size <= XXH3_MIDSIZE_MAX)
		return (ft_xxh3_len_129to240(input, secret, seed));
	return (ft_xxh3_hashlong_64b(input, seed));
}
