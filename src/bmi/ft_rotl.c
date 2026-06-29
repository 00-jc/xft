/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rotl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 03:05:22 by jaicastr          #+#    #+#             */
/*   Updated: 2026/04/12 06:38:15 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bmi.h"

#if __has_builtin(__builtin_rotateleft64)

__attribute__((const, __always_inline__))
inline t_u64a	ft_rotl64(t_u64a hash, t_size n)
{
	return (__builtin_rotateleft64(hash, n));
}

#elif __has_builtin(__builtin_stdc_rotate_left)

__attribute__((const, __always_inline__))
inline t_u64a	ft_rotl64(t_u64a hash, t_size n)
{
	return (__builtin_stdc_rotate_left(hash, n));
}

#else

__attribute__((const, __always_inline__))
inline t_u64a	ft_rotl64(t_u64a hash, t_size n)
{
	return ((hash << n) | (hash >> (64 - (n))));
}

#endif
