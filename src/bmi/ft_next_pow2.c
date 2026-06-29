/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_next_pow2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 16:42:07 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/18 19:43:19 by jaicastr         ###   ########.fr       */
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
