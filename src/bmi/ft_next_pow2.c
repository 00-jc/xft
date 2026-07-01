/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_next_pow2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:20 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bmi.h"

__attribute__((const, __always_inline__, __hot__))
inline t_size	ft_next_pow2(t_size qword)
{
	return (1ULL << (64ULL - ft_memclz_u64(qword - 1)));
}

__attribute__((const, __always_inline__, __hot__))
inline t_size	ft_last_pow2(t_size qword)
{
	return (1ULL << (63ULL - ft_memclz_u64(qword)));
}
